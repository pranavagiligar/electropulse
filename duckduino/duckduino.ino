/*
 * Author: Seytonic, Pranava
 *         https://twitter.com/seytonic
 *         https://www.youtube.com/seytonic
 * GIT:
 *         https://github.com/Seytonic/Duckduino-microSD
 */

#include <SPI.h>
#include <SD.h>
#include <Keypad.h>
#include <string.h>
#include "Keyboard.h"

const int led = 10;
File myFile;

String dip = "";
unsigned long prevTime = 0;
boolean keyPressed = false;

const byte numRows= 2; //number of rows on the keypad
const byte numCols= 2; //number of columns on the keypad

/*keymap defines the key pressed according to the row and columns just as appears on the keypad*/
char keymap[numRows][numCols]=
{
{'1', '2'},
{'3', '4'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {6,7}; //Rows 0 to 1
byte colPins[numCols]= {8,9}; //Columns 0 to 1

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup() {
  Serial.begin(9600);
  /*pinMode(LED_BUILTIN_TX,INPUT);
  pinMode(LED_BUILTIN_RX,INPUT);
  digitalWrite(LED_BUILTIN_RX, LOW);
  digitalWrite(LED_BUILTIN_TX, LOW);
  bitClear(DDRD,5);
  bitClear(DDRB,0);*/
  pinMode(LED_BUILTIN_TX,INPUT);
  digitalWrite(LED_BUILTIN_TX, LOW);
  pinMode(LED_BUILTIN_RX,INPUT);
  digitalWrite(LED_BUILTIN_RX, LOW);
  pinMode(17, OUTPUT);
 digitalWrite(17, LOW);
  pinMode(10, OUTPUT);
 
  if (!SD.begin(4)) {
    blinkn(10);
    return;
  }
}

void runScript() {
  myFile = SD.open(dip+".txt");
  if (myFile) {
    Keyboard.begin();
    
    String line = "";
    while (myFile.available()) {
      char m = myFile.read();
      if (m == '\n'){
        Line(line);
        line = "";
        }
        else if((int) m != 13)
        {
          line += m;
        }
    }
    Line(line);
    myFile.close();
    Keyboard.end();
    blinkn(1);
  } else {
    blinkn(4);
  }
}

void blinkn(int n)
{
  for(int i=0;i<=n*2-1;i++) {
     if(i%2==0) {
      digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
      }
      else {
        digitalWrite(10,  LOW);    // turn the LED off by making the voltage LOW
      }
      delay(100);   
  }
}

void Line(String l)
{
  int space_1 = l.indexOf(" ");
  if (space_1 == -1)
  {
    Press(l);
  }
  else if (l.substring(0,space_1) == "STRING")
  {
    Keyboard.print(l.substring(space_1 + 1));
  }
  else if (l.substring(0,space_1) == "DELAY")
  {
    int delaytime = l.substring(space_1 + 1).toInt();
    delay(delaytime);
  }
  else if(l.substring(0,space_1) == "REM"){}
  else
  {
      String remain = l;

      while(remain.length() > 0)
      {
        int latest_space = remain.indexOf(" ");
        if (latest_space == -1)
        {
          Press(remain);
          remain = "";
        }
        else
        {
          Press(remain.substring(0, latest_space));
          remain = remain.substring(latest_space + 1);
        }
        delay(5);
      }
  }

  Keyboard.releaseAll();
}


void Press(String b)
{
  if(b.length() == 1)
  {
    char c = b[0];
    Keyboard.press(c);
  }
  else if (b.equals("ENTER"))
  {
    Keyboard.press(KEY_RETURN);
  }
  else if (b.equals("CTRL"))
  {
    Keyboard.press(KEY_LEFT_CTRL);
  }
    else if (b.equals("SHIFT"))
  {
    Keyboard.press(KEY_LEFT_SHIFT);
  }
    else if (b.equals("ALT"))
  {
    Keyboard.press(KEY_LEFT_ALT);
  }
    else if (b.equals("GUI"))
  {
    Keyboard.press(KEY_LEFT_GUI);
  }
    else if (b.equals("UP") || b.equals("UPARROW"))
  {
    Keyboard.press(KEY_UP_ARROW);
  }
    else if (b.equals("DOWN") || b.equals("DOWNARROW"))
  {
    Keyboard.press(KEY_DOWN_ARROW);
  }
    else if (b.equals("LEFT") || b.equals("LEFTARROW"))
  {
    Keyboard.press(KEY_LEFT_ARROW);
  }
    else if (b.equals("RIGHT") || b.equals("RIGHTARROW"))
  {
    Keyboard.press(KEY_RIGHT_ARROW);
  }
    else if (b.equals("DELETE"))
  {
    Keyboard.press(KEY_DELETE);
  }
    else if (b.equals("PAGEUP"))
  {
    Keyboard.press(KEY_PAGE_UP);
  }
    else if (b.equals("PAGEDOWN"))
  {
    Keyboard.press(KEY_PAGE_DOWN);
  }
    else if (b.equals("HOME"))
  {
    Keyboard.press(KEY_HOME);
  }
    else if (b.equals("ESC"))
  {
    Keyboard.press(KEY_ESC);
  }
    else if (b.equals("INSERT"))
  {
    Keyboard.press(KEY_INSERT);
  }
    else if (b.equals("TAB"))
  {
    Keyboard.press(KEY_TAB);
  }
    else if (b.equals("END"))
  {
    Keyboard.press(KEY_END);
  }
    else if (b.equals("CAPSLOCK"))
  {
    Keyboard.press(KEY_CAPS_LOCK);
  }
    else if (b.equals("F1"))
  {
    Keyboard.press(KEY_F1);
  }
    else if (b.equals("F2"))
  {
    Keyboard.press(KEY_F2);
  }
    else if (b.equals("F3"))
  {
    Keyboard.press(KEY_F3);
  }
    else if (b.equals("F4"))
  {
    Keyboard.press(KEY_F4);
  }
    else if (b.equals("F5"))
  {
    Keyboard.press(KEY_F5);
  }
    else if (b.equals("F6"))
  {
    Keyboard.press(KEY_F6);
  }
    else if (b.equals("F7"))
  {
    Keyboard.press(KEY_F7);
  }
    else if (b.equals("F8"))
  {
    Keyboard.press(KEY_F8);
  }
    else if (b.equals("F9"))
  {
    Keyboard.press(KEY_F9);
  }
    else if (b.equals("F10"))
  {
    Keyboard.press(KEY_F10);
  }
    else if (b.equals("F11"))
  {
    Keyboard.press(KEY_F11);
  }
    else if (b.equals("F12"))
  {
    Keyboard.press(KEY_F12);
  }
    else if (b.equals("SPACE"))
  {
    Keyboard.press(' ');
  } 
}

void loop() {
  char keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY)
   {
      dip += keypressed;
     
     
      if(prevTime == 0) {
        Serial.println("Dial initiated");
        prevTime= millis();
      }
      Serial.print("\r"+ dip); 
      keyPressed = true;
    }
    
    if(keyPressed && prevTime != 0)
     {
          unsigned long currentTime = millis();
          if(currentTime-prevTime > 2000) {
              prevTime = 0;
              keyPressed = false;
              runScript(dip);
              dip = "";
          }
          else {
            if(keypressed !=NO_KEY) prevTime = currentTime;
          }
     }
}

void runScript(String dip) {
  Serial.println("\n\rFile name :" + dip + ".txt");
  runScript();
}
