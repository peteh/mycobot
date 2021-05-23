#include <Arduino.h>
#include <EEPROM.h>
#include <MycobotBasic.h>
#include <ParameterList.h>
#include <WiFi.h>
#include <EStopReceiver.h>
#include <Log.h>
#include <SerialLogger.h>
uint8_t  WIFI_CHANNEL = 0;

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
estop::EStopReceiver* g_estopReceiver;
void setup() {
  Serial.begin(115200);
  Log::init(new SerialLogger());
  myCobot.setup();
  myCobot.powerOn();

  // delete old wifi settings
  WiFi.disconnect();

  WiFi.mode(WIFI_STA); // Place in station mode for ESP-NOW sender node
  //disable sleep mode
  //WiFi.setSleepMode(WIFI_NONE_SLEEP);

  g_estopReceiver = new estop::EStopReceiver(BUTTON_STATION_MAC, WIFI_CHANNEL, CELL_ID, MSG_TIME_MS * SKIP_BEFORE_TIMEOUT);
  g_estopReceiver->init();
}

void loop() {
    estop::EStopReceiver::EStopState eStopState = g_estopReceiver->getEStopState();
    if(eStopState == estop::EStopReceiver::ESTOP_FREE){
      myCobot.setLEDRGB(0, 0, 0XFF);       // set RGB show green
    }
    else{
      myCobot.setLEDRGB(0XFF, 0, 0);       // set RGB show red
    }

    delay(2000);
}
