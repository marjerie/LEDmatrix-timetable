#include <DS3231.h>
#include <Wire.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <LedControl.h>
#define  PRINT(s, v) { Serial.print(F(s)); Serial.print(v); }
#define MAX_DEVICES 4
#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS
// Text parameters
#define  CHAR_SPACING  1 // pixels between characters

MD_MAX72XX mx = MD_MAX72XX(CS_PIN, MAX_DEVICES);
DS3231 Clock;
bool Century=false;
bool h12;
bool PM;

byte year, month, date, DoW, hour, minute, second;
// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  10
char message[BUF_SIZE] = {"Hello!"};
bool newMessageAvailable = true;

void printText(uint8_t modStart, uint8_t modEnd, char *pMsg)

{
  uint8_t   state = 0;
  uint8_t   curLen;
  uint16_t  showLen;
  uint8_t   cBuf[8];
  int16_t   col = ((modEnd + 1) * COL_SIZE) - 1;

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  do     // finite state machine to print the characters in the space available
  {
    switch(state)
    {
      case 0: // Load the next character from the font table
        // if we reached end of message, reset the message pointer
        if (*pMsg == '\0')
        {
          showLen = col - (modEnd * COL_SIZE);  // padding characters
          state = 2;
          break;
        }

        // retrieve the next character form the font file
        showLen = mx.getChar(*pMsg++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
        curLen = 0;
        state++;
        // !! deliberately fall through to next state to start displaying

      case 1: // display the next part of the character
        mx.setColumn(col--, cBuf[curLen++]);

        // done with font character, now display the space between chars
        if (curLen == showLen)  
        {
          showLen = CHAR_SPACING;
          state = 2;
        }
        break;

      case 2: // initialize state for displaying empty columns
        curLen = 0;
        state++;
        // fall through

      case 3: // display inter-character spacing or end of message padding (blank columns)
        mx.setColumn(col--, 0);
        curLen++;
        if (curLen == showLen) 
          state = 0;
        break;

      default:
        col = -1;   // this definitely ends the do loop
    }
  } while (col >= (modStart * COL_SIZE));

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void setup()
{
  mx.begin();
  Wire.begin();
  Serial.begin(57600);
 
}

void loop() 
{
int year=Clock.getYear();
int month=Clock.getMonth(Century);
int date=Clock.getDate();
int DoW=Clock.getDoW();
int hour=Clock.getHour(h12,PM);
int minute=Clock.getMinute();
int second=Clock.getSecond();
int temperature=(Clock.getTemperature());
int lh = ((hour/10)%10);
int rh = (hour%10);
int lm = ((minute/10)%10);
int rm = (minute%10);
int lt = ((temperature/10)%10);
int rt = (temperature%10);
int ld = ((date/10)%10);
int rd = (date%10);

if (second==15){
message[0]=' ';
message[1]=' ';
message[2]=char(lt)+48;
message[3]=char(rt)+48;
message[4]=' ';
message[5]='C';
message[6]='\0';
printText(0, MAX_DEVICES-1, message);
delay(3000);
}
else if (second==45){
 
message[0]=char(ld)+48;
message[1]=char(rd)+48;
message[2]=' ';
switch (month)
{
  case 01:
  {
    message[3]='J';
    message[4]='A';
    message[5]='N';
    break;
   } 
   case 02:
  {
    message[3]='F';
    message[4]='E';
    message[5]='B';
    break;
   }
   case 03:
  {
    message[3]='M';
    message[4]='A';
    message[5]='R';
    break;
   }
   case 04:
  {
    message[3]='A';
    message[4]='P';
    message[5]='R';
    break;
   }
   case 05:
  {
    message[3]='M';
    message[4]='A';
    message[5]='Y';
    break;
   }
   case 06:
  {
    message[3]='J';
    message[4]='U';
    message[5]='N';
    break;
   }
   case 07:
  {
    message[3]='J';
    message[4]='U';
    message[5]='L';
    break;
   }
   case 8:
  {
    message[3]='A';
    message[4]='U';
    message[5]='G';
    break;
   }
   case 9:
  {
    message[3]='S';
    message[4]='E';
    message[5]='P';
    break;
   }
   case 10:
  {
    message[3]='O';
    message[4]='C';
    message[5]='T';
    break;
   }
   case 11:
  {
    message[3]='N';
    message[4]='O';
    message[5]='V';
    break;
   }
   case 12:
  {
    message[3]='D';
    message[4]='E';
    message[5]='C';
    break;
   }
   }
message[6]='\0';
printText(0, MAX_DEVICES-1, message);
delay(3000);
}

else if (second==30){
 
message[0]=' ';
message[1]=' ';
message[2]=' ';
switch (DoW)
{
  case 01:
  {
    message[3]='M';
    message[4]='0';
    message[5]='N';
    break;
   } 
   case 02:
  {
    message[3]='T';
    message[4]='U';
    message[5]='E';
    break;
   }
   case 03:
  {
    message[3]='W';
    message[4]='E';
    message[5]='D';
    break;
   }
   case 04:
  {
    message[3]='T';
    message[4]='H';
    message[5]='U';
    break;
   }
   case 05:
  {
    message[3]='F';
    message[4]='R';
    message[5]='I';
    break;
   }
   case 06:
  {
    message[3]='S';
    message[4]='A';
    message[5]='T';
    break;
   }
   case 07:
  {
    message[3]='S';
    message[4]='U';
    message[5]='N';
    break;
   }
}
   message[6]='\0';
printText(0, MAX_DEVICES-1, message);
delay(5000);
}

else{
//message[0]=' ';
message[0]=' ';
message[1]=char(lh)+48;
message[2]=char(rh)+48;
message[3]=':';
message[4]=char(lm)+48;
message[5]=char(rm)+48;
message[6]='\0';
printText(0, MAX_DEVICES-1, message);
}


}

