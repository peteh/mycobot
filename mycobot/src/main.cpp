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

// Address of the central station
uint8_t BASE_STATION_MAC[] = {0xDE, 0xAD, 0x13, 0x37, 0x00, 0x01};

// Address of the client station (wireless estop button)
uint8_t BUTTON_STATION_MAC[] = {0xDE, 0xAD, 0x13, 0x37, 0x00, 0x02};

MycobotBasic myCobot;
estop::EStopReceiver *g_eStopReceiver;
estop::EStopReceiver::EStopState g_eStopState;

cobot::IMode* g_mode;
cobot::RobotState g_robotState;
void visualizeEStopState(estop::EStopReceiver::EStopState state)
{
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextSize(5);
  M5.Lcd.setCursor(100, 100);
  if (state == estop::EStopReceiver::ESTOP_FREE)
  {
    myCobot.setLEDRGB(0, 0xFF, 0x00); // set RGB show green
    M5.Lcd.print("FREE");
  }
  else
  {
    myCobot.setLEDRGB(0xFF, 0, 0); // set RGB show red
    M5.Lcd.print("E-STOP");
  }
}

void setup()
{
  Serial.begin(115200);
  Log::init(new SerialLogger());
  myCobot.setup();
  myCobot.powerOn();

  // delete old wifi settings
  WiFi.disconnect();

  WiFi.mode(WIFI_STA); // Place in station mode for ESP-NOW sender node
  //disable sleep mode
  //WiFi.setSleepMode(WIFI_NONE_SLEEP);

  g_eStopReceiver = new estop::EStopReceiver(BUTTON_STATION_MAC, WIFI_CHANNEL, CELL_ID, MSG_TIME_MS * SKIP_BEFORE_TIMEOUT);
  g_eStopReceiver->init();
  g_eStopState = g_eStopReceiver->getEStopState();

  g_mode = new cobot::EStopMode(myCobot);
  g_mode->init();
}


void loop()
{
  M5.update(); 
  estop::EStopReceiver::EStopState eStopState = g_eStopReceiver->getEStopState();
  g_mode->visualize();
  g_mode->process(g_robotState);

//  if (eStopState != g_eStopState)
//  {
//    g_eStopState = eStopState;
//    visualizeEStopState(g_eStopState);
//  }

  delay(10);
}
