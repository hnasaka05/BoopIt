#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const int bop = 2;
const int motorpin = A0;
const int scream  = A1; 
const int startbutton = 2; 
int score = 0; 
int startVal = 0;
bool lose = false; 
int wait = 2000; 
int picker = 0;
int bopState = 0;
bool hit = false;
int prevValue = 0;

const int sampleRate = 100;    // Sample every 100ms (10 readings per second)
const int duration = 500;     // 4 seconds tracking window
const int numSamples = 5;  // Total samples stored
const int threshold = 10;     // Change this as needed

int readings[numSamples];      // Array to store past readings
int index = 0;                 // Tracks current position in array
long sum = 0;                  // Stores sum of values for averaging


void setup()
{
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  pinMode(bop, INPUT);
  pinMode(motorpin, INPUT);
  pinMode(scream, INPUT);
  pinMode(startbutton, INPUT);
  Serial.begin(9600);
  lcd.print("Touch it to start");
  delay(1000);

}
void loop() 
{
  while(startVal == 0) {
    startVal = digitalRead(startbutton);
  }
  startVal = digitalRead(startbutton);
  Serial.println(startVal);
  if(startVal) {
    lcd.clear();
    lcd.print("3");
    Serial.println("3");
    delay(1000);
    lcd.print("2");
    Serial.println("2");
    delay(1000);
    lcd.print("1");
    Serial.println("1");
    delay(1000);
    lcd.clear();
    Serial.println(lose);
    while(!lose) {
      picker = random(1,4);
      //picker = 3; 
      Serial.print("picker ");
      Serial.println(picker);
      Serial.print("lose state: ");
      Serial.println(lose); 
      switch(picker) {
        case 1: 
          bopIt();
          delay(2000);
          break;
        case 2:
          twistIt();
          delay(2000);
          break;
        case 3:
          screamIt();
          delay(2000);
          break;
      }
    }
  }
  Serial.println("You lose");
  lcd.clear();
  lcd.print("You lose");
}
int bopIt(){
  lcd.print("Touch It");
  Serial.println("Touch It");
  //bopState = digitalRead(bop);
  int time = millis(); 
  while(millis() - time < wait) {
    if(digitalRead(bop)) {
      lcd.clear();
      lcd.print("*bop noise*");
      Serial.println("BEEEP");
      hit = true;
      if(wait > 90) {
        wait = wait - 10; 
      }
      break; 
    }
  }
  if(hit == false) {
      lose = true; 
    }
  hit = false; 
  lcd.clear();
  return 0;
}


int twistIt(){
  lcd.print("Twist It"); 
  Serial.println("Twist It");
 
  int time = millis();
  while(millis() - time < wait) {
    int sensorValue = analogRead(motorpin); 
    //Serial.println(sensorValue);
    if (sensorValue > 80) {
      lcd.clear();
      lcd.print("*twist noise*");
      Serial.println("BEEEP");
      hit = true; 
      if(wait > 90) {
        wait = wait - 10; 
      }
      break; 
    }
  }
  if(hit == false) {
      lose = true; 
    }
  hit = false; 
  lcd.clear(); 
  return 0; 
}


int screamIt() {
  lcd.print("Scream It");
  Serial.println("Scream It");
  //bopState = analogRead(scream);
  int time = millis();
  while(millis() - time < wait) {
    int screamVal = analogRead(scream);
    Serial.println(screamVal);
    if(screamVal > 720) {
      lcd.clear();
      lcd.print("*screaming noise");
      Serial.println("AAAAAAAA");
      hit = true; 
      if (wait > 90) {
        wait = wait - 10; 
      }
      break; 
    }
  }
  if(hit == false) {
    lose = true; 
  }
  hit = false;
  lcd.clear(); 
  return 0; 
}