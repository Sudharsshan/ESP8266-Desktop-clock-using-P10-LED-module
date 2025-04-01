//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test P10
/*
 * Original source code : https://github.com/busel7/DMDESP/blob/master/examples/TeksDiamdanJalan/TeksDiamdanJalan.ino by  busel7
 * Links to download libraries : https://github.com/busel7/DMDESP
 * Modified By: S Y Sudharsshan
 * Modified source code: https://github.com/Sudharsshan/ESP8266-Desktop-clock-using-P10-LED-module.git
 * This code fetches the realtime current time and date from cloud and displays it
*/

//----------------------------------------Include Library
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <DMDESP.h>
#include <fonts/Mono5x7.h>
#include <fonts/EMSans5x6.h>
#include <ESP8266WiFi.h>   // Library to manage WiFi connection on ESP8266
#include <WiFiUdp.h>
#include <NTPClient.h> // for synchronizing the time with could API
#include <TimeLib.h> // for time synchronization
//----------------------------------------

//----------------------------------------DMD Configuration (P10 Panel)
#define DISPLAYS_WIDE 1 //--> Panel Columns
#define DISPLAYS_HIGH 1 //--> Panel Rows
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);  //--> Number of Panels P10 used (Column, Row)
//----------------------------------------

//----------------------------------------WiFi & NTP Configuration
const char* ssid = "Sangeetha";
const char* password = "Sangu1978";
const long utcOffsetInSeconds = 19800;  // Time zone offset
//----------------------------------------

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds, 60000);

char Time[] = "00:00";
char Seconds[] = "00";
char Date[] = "00-00-2000";
byte last_second, second_, minute_, hour_, day_, month_;
int year_;

const char* DaysWeek[] = { "SUN", "MON", "TUES", "WED", "THUR", "FRI", "SAT" };

//========================================================================VOID SETUP()
void setup() {
  //----------------------------------------DMDESP Setup
  Disp.start(); //--> Run the DMDESP library
  Disp.setBrightness(25); //--> Brightness level
  Disp.setFont(EMSans5x6); //--> Determine the font used
  //----------------------------------------

  Serial.begin(9600);

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  timeClient.begin();
}
//========================================================================

//========================================================================VOID LOOP()
void loop() {
  timeClient.update();
  unsigned long unix_epoch = timeClient.getEpochTime();  // Get Unix epoch time from the NTP server
  int Day = timeClient.getDay();
  second_ = second(unix_epoch);
  if (last_second != second_) {
    minute_ = minute(unix_epoch);
    hour_ = hour(unix_epoch);
    day_ = day(unix_epoch);
    month_ = month(unix_epoch);
    year_ = year(unix_epoch);

    Seconds[1] = second_ % 10 + 48;
    Seconds[0] = second_ / 10 + 48;
    Time[4] = minute_ % 10 + 48;
    Time[3] = minute_ / 10 + 48;
    Time[1] = hour_ % 10 + 48;
    Time[0] = hour_ / 10 + 48;

    Date[0] = day_ / 10 + 48;
    Date[1] = day_ % 10 + 48;
    Date[3] = month_ / 10 + 48;
    Date[4] = month_ % 10 + 48;
    Date[8] = (year_ / 10) % 10 + 48;
    Date[9] = year_ % 10 % 10 + 48;
    last_second = second_;
  }

  // Set custom display brightness parameter according to time
  if(hour_ > 18 && hour_ < 21)
  {
    Disp.setBrightness(65);
  }else if(hour_ > 21 || hour_ < 4)
  {
    Disp.setBrightness(20);
  }else{
    Disp.setBrightness(45);
  }

  Disp.loop(); //--> Run "Disp.loop" to refresh the LED
  Disp.drawText(1, 0, Time); //--> Display text "Disp.drawText(x position, y position, text)"
  Scrolling_Text(9, 60, Date); //--> Show running text "Scrolling_Text(y position, speed);"
}
//========================================================================

//========================================================================Subroutines for scrolling Text
void Scrolling_Text(int y, uint8_t scrolling_speed, const char* message) {
  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  Disp.setFont(Mono5x7);
  int fullScroll = Disp.textWidth(message) + width;
  if((millis() - pM) > scrolling_speed) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      return;
    }
    Disp.drawText(width - x, y, message);
  }  
}
//========================================================================
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
