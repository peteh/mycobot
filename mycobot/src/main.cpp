#include <Arduino.h>
#include <EEPROM.h>
#include <MycobotBasic.h>
#include <ParameterList.h>
#include <WiFi.h>
#include <EStopReceiver.h>
#include <Log.h>
#include <SerialLogger.h>
#include "mode/Mode.h"
#include "mode/EStopMode.h"
#include "mode/AutomaticMode.h"
#include "mode/DebugMode.h"
#include "mode/MainMode.h"
#include "mode/BootMode.h"
#include "mode/ModeLogger.h"

uint8_t WIFI_CHANNEL = 0;

// id of the cell to which the station and the wireless estop belong
// this allows to have multiple setups belonging to different scopes
// e.g. Wireless estop with cell id 1 will stop all master stations
// that are set to id 1, however master stations set to other ids
// will drop and ignore the message.
uint8_t CELL_ID = 10;

// how long we wait between sending messages
unsigned long MSG_TIME_MS = 20;

// how many messages we can lose before activating E-Stop because of
// message timeout
unsigned long SKIP_BEFORE_TIMEOUT = 5;

// Address of the client station (wireless estop button)
uint8_t BUTTON_STATION_MAC[] = {0xDE, 0xAD, 0x13, 0x37, 0x00, 0x02};

MycobotBasic myCobot;
estop::EStopReceiver *g_eStopReceiver;
estop::EStopState g_previousEStopState;

cobot::IMode *g_mode;
cobot::IMode *g_modeEStop;
cobot::IMode *g_modeAutomatic;
cobot::IMode *g_modeDebug;
cobot::IMode *g_modeMain;
cobot::IMode *g_modeBoot;

cobot::RobotState g_previousRobotState;

void setup()
{
  Serial.begin(115200);
  Log::init(new ModeLogger());
  //Log::init(new SerialLogger());
  myCobot.setup();
  myCobot.powerOn();

  // delete old wifi settings
  WiFi.disconnect();

  WiFi.mode(WIFI_STA); // Place in station mode for ESP-NOW sender node
  //disable sleep mode
  //WiFi.setSleepMode(WIFI_NONE_SLEEP);

  g_eStopReceiver = new estop::EStopReceiver(BUTTON_STATION_MAC, WIFI_CHANNEL, CELL_ID, MSG_TIME_MS * SKIP_BEFORE_TIMEOUT);
  g_eStopReceiver->init();
  g_previousEStopState = g_eStopReceiver->getEStopState();

  g_modeBoot = new cobot::BootMode(myCobot);
  g_modeAutomatic = new cobot::AutomaticMode(myCobot);
  g_modeMain = new cobot::MainMode(myCobot);
  g_modeDebug = new cobot::DebugMode(myCobot);
  g_modeEStop = new cobot::EStopMode(myCobot);

  g_mode = g_modeBoot;
  g_mode->init();

  delay(200);
}

void updateRobotState(cobot::RobotState &robotState)
{
  robotState.eStopState = g_eStopReceiver->getEStopState();
}

void loop()
{
  M5.update();
  cobot::RobotState robotState = g_previousRobotState;

  updateRobotState(robotState);

  // if estop state changes to stopped, then immidiately go to estop for any more we are in
  if (robotState.eStopState != g_previousRobotState.eStopState && robotState.eStopState != estop::ESTOP_FREE)
  {
    g_mode = g_modeEStop;
    g_mode->init();
  }
  
  g_mode->visualize();
  cobot::Mode newMode = g_mode->process(g_previousRobotState, robotState);

  if(newMode != cobot::MODE_THIS)
  {
    switch(newMode)
    {
      case cobot::MODE_MAIN:
        g_mode = g_modeMain;
        break;
      case cobot::MODE_AUTOMATIC:
        g_mode = g_modeAutomatic;
        break;
    }
    g_mode->init();
    g_mode->forceNextVisualizationUpdate();
  }
  //delay(5);
  //visualizeState(g_previousRobotState, robotState, false);
  
  g_previousRobotState = robotState;
}
