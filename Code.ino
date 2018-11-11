#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 9, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

long randNumber;
long randNumbers[100];
int counter = 0;
bool prompted = false;
bool check = true;
bool playing = true;
int single = 0;
int pick = 0;
bool start;
int correct = 0;
long mass = 0;

int r = LOW;
int l = LOW;
int g = LOW;
int b = LOW;

const int speaker_pin = 10;

const int red_pin = 5;
const int blue_pin = 6;
const int green_pin = 7;
const int yellow_pin = 4;
  
const int joy_x_pin = 0;
const int joy_y_pin = 1;
int x = 0;
int y = 0;

int red_button_state = 0;
int blue_button_state = 0;
int green_button_state = 0;
int yellow_button_state = 0;

void setup(){
  Serial.begin(9600);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(5));
  
  pinMode(red_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  
  pinMode(speaker_pin, OUTPUT);
  
  lcd.begin(16, 2);
}

void loop() {
  if(pick == 0){
    Serial.println(mass);
    digitalWrite(red_pin,HIGH);
    digitalWrite(blue_pin,HIGH);
    digitalWrite(green_pin,HIGH);
    digitalWrite(yellow_pin,HIGH);
    if(mass < 25){
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Yellow: Puzzle");
      mass++;
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Red: Bop It");
      lcd.setCursor(0, 1);
      lcd.print("Blue: Simon Says");
      mass++;
      if (mass > 50){
        mass = 0;
      }
    digitalWrite(red_pin,LOW);
    digitalWrite(blue_pin,LOW);
    digitalWrite(green_pin,LOW);
    digitalWrite(yellow_pin,LOW);
    }
    
    x = analogRead(joy_x_pin);
    delay(100);
    y = analogRead(joy_y_pin);
    //Red=Original
    if(y <= 2){
      pick = 1;
      lcd.clear();
    }
    //Blue = Simon Says
    else if(y >= 1022){
      pick = 2;
      lcd.clear();
    }
    //Yellow = Turn off lights
    else if(x <= 2){
      pick = 3;
      lcd.clear();
    }
  }
  if (pick == 1){
    if (playing){
      if (!prompted){
        digitalWrite(red_pin, LOW);
        digitalWrite(blue_pin, LOW);
        digitalWrite(green_pin, LOW);
        digitalWrite(yellow_pin, LOW);
        x = analogRead(joy_x_pin);
        delay(100);
        y = analogRead(joy_y_pin);
        if (y < 560 && y  > 470 && x > 470 && x < 560){
          check = true;
        }
        if (check){
          prompted = true;
          check  = false;
          randNumber = random(4);  
          Serial.println(counter);
          switch(randNumber){
            case 0 :
              digitalWrite(red_pin, HIGH);
              break;
            case 1 : 
              digitalWrite(blue_pin, HIGH);
              break;
            case 2 : 
              digitalWrite(green_pin, HIGH);
              break;
            case 3 :       
              digitalWrite(yellow_pin, HIGH);
              break;  
          }
        }
      }
      x = analogRead(joy_x_pin);
      delay(100);
      y = analogRead(joy_y_pin);
      switch (randNumber){
        //Red Light
        case 0 :
          if(y <= 2){
            prompted = false;
            tone(speaker_pin, 50, 25);
            counter++;
            randNumber = 4;
          }
          else if(y >= 1022 || x <= 2 || x>= 1022){
            playing = false;
          }
          break;
        //Blue Light
        case 1 : 
          if(y >= 1022){
            prompted = false;
            tone(speaker_pin, 50, 25);   
            counter++;
            randNumber = 4;
          }
          else if(y <= 2 || x <= 2 || x >= 1022){
            playing = false;
          }
          break;
        //Green Light
        case 2 :
          if(x <= 2){
            prompted = false;
            tone(speaker_pin, 50, 25); 
            counter++; 
            randNumber = 4;
          }
          else if(y >= 1022 || y <= 2 || x>= 1022){
            playing = false;
          }
          break;
        //Yellow light
        case 3 : 
          if(x >= 1022){
            prompted = false;
            tone(speaker_pin, 50, 25);
            counter++;
            randNumber = 4;
          }
          else if (y >= 1022 || y <= 2 || x <= 2){
            playing = false;
          }
          break;
      } 
    }
    else if(single == 0){
      digitalWrite(red_pin, HIGH);
      digitalWrite(blue_pin, HIGH);
      digitalWrite(green_pin, HIGH);
      digitalWrite(yellow_pin, HIGH);
      tone(speaker_pin, 25, 100);
      delay (200);
      tone(speaker_pin, 25, 100);
      delay (200);
      tone(speaker_pin, 25, 100);
      delay (200);
      single = 1;
    }
  }
  if (pick == 2){
    if (playing && start){
      counter++;
      Serial.println(counter);
      randNumbers[counter-1] = random(4);
      for (int i = 0; i < counter; i++){
        switch(randNumbers[i]){
          //Red Light
          case 0 :
            digitalWrite(red_pin, HIGH);
            tone(speaker_pin, 125, 25);
            delay (500);
            digitalWrite(red_pin, LOW);
            break;
          //Blue Light
          case 1 : 
            digitalWrite(blue_pin, HIGH);
            tone(speaker_pin, 25, 25);
            delay (500);
            digitalWrite(blue_pin, LOW);
            break;
          //Green Light
          case 2 :
            digitalWrite(green_pin, HIGH);
            tone(speaker_pin, 75, 25);
            delay (500);
            digitalWrite(green_pin, LOW);
            break;
          //Yellow light
          case 3 : 
            digitalWrite(yellow_pin, HIGH);
            tone(speaker_pin, 175, 25);
            delay (500);
            digitalWrite(yellow_pin, LOW);
            break;
        }
      }
      start = false;
    }
    while(playing && correct < counter){
      x = analogRead(joy_x_pin);
      delay(100);
      y = analogRead(joy_y_pin);
      switch(randNumbers[correct]){
         //Red Light
        case 0 :
          if(y <= 2){
            tone(speaker_pin, 100, 25);
            digitalWrite(red_pin, HIGH);
            delay (100);
            digitalWrite(red_pin, LOW);
            correct++;
            while(y > 560 || y  < 470 || x < 470 || x > 560){
              x = analogRead(joy_x_pin);
              delay(100);
              y = analogRead(joy_y_pin);
            }
          }
          else if(y >= 1022 || x <= 2 || x>= 1022){
            playing = false;
          }
          break;
        //Blue Light
        case 1 : 
          if(y >= 1022){
            tone(speaker_pin, 50, 25);
            digitalWrite(blue_pin, HIGH);
            delay (100);
            digitalWrite(blue_pin, LOW);
            correct++;
            while(y > 560 || y  < 470 || x < 470 || x > 560){
              x = analogRead(joy_x_pin);
              delay(100);
              y = analogRead(joy_y_pin);
            }
          }
          else if(y <= 2 || x <= 2 || x >= 1022){
            playing = false;
          }
          break;
        //Green Light
        case 2 :
          if(x <= 2){
            tone(speaker_pin, 75, 25); 
            digitalWrite(green_pin, HIGH);
            delay (100);
            digitalWrite(green_pin, LOW);
            correct++; 
            while(y > 560 || y  < 470 || x < 470 || x > 560){
              x = analogRead(joy_x_pin);
              delay(100);
              y = analogRead(joy_y_pin);
            }
          }
          else if(y >= 1022 || y <= 2 || x>= 1022){
            playing = false;
          }
          break;
        //Yellow light
        case 3 : 
          if(x >= 1022){
            tone(speaker_pin, 125, 25);
            digitalWrite(yellow_pin, HIGH);
            delay (100);
            digitalWrite(yellow_pin, LOW);
            correct++;
            while(y > 560 || y  < 470 || x < 470 || x > 560){
              x = analogRead(joy_x_pin);
              delay(100);
              y = analogRead(joy_y_pin);
            }
          }
          else if (y >= 1022 || y <= 2 || x <= 2){
            playing = false;
          }
          break;
        }
    }
    if (playing && correct == counter){
      start = true;
      correct = 0;
      Serial.println("Did get here");
    }
    if (!playing && single == 0){
      digitalWrite(red_pin, HIGH);
      digitalWrite(blue_pin, HIGH);
      digitalWrite(green_pin, HIGH);
      digitalWrite(yellow_pin, HIGH);
      tone(speaker_pin, 25, 100);
      delay (200);
      tone(speaker_pin, 25, 100);
      delay (200);
      tone(speaker_pin, 25, 100);
      delay (200);
      single = 1;
    }
  }
  if (pick == 3){
    x = analogRead(joy_x_pin);
    delay(100);
