#include <Servo.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

Servo myServo;
int pos = 0;
int data;

const int trigpin = 9;
const int echopin = 8;
int bluetooth = 4;
long duration;
int distance;

LiquidCrystal_I2C lcd(0x27,20,4); // set the LCD address to 0x27 for a 20 chars and 4 line display

void setup() {
  Serial.begin(9600);
  myServo.attach(7);
  pinMode(6, OUTPUT);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(bluetooth, OUTPUT);
  
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

void loop() {
  if (Serial.available()) {
    data = Serial.read();
    if (data == 'A') {
      Serial.print("\nA");
      for (pos = 0; pos <= 180; pos += 1) {
        myServo.write(pos);
      }
    }  
    if (data == 'B') {
      Serial.print("\nB");
      for (pos = 180; pos >= 0; pos -= 1) { 
        myServo.write(pos);
      }
    }    
    if (data == 'S') {
      Serial.print("\nS");
      for (pos = 0; pos >= 0; pos += 1) { 
        myServo.write(pos);
      }
    }
  }

  digitalWrite(trigpin, HIGH);
  delayMicroseconds(5000);
  digitalWrite(trigpin, LOW);

  duration = pulseIn(echopin, HIGH);

   distance = duration * 0.034 / 2;
   if(distance >=30){
       Serial.print("distance = ");
       Serial.print(distance);
       delay(1000);
       Serial.println("cm");
   }

   if (distance <= 30) {
    Serial.println("KNOCK KNOCK");
    delay(1000);
    
    lcd.setCursor(0,0); // set the cursor to column 0, line 0
    lcd.print("Hii..Wait!");
    delay(5000);
    lcd.clear();
   }
}