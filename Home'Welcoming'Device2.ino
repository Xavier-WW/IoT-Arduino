//Arduino 2 - Home'Welcoming'Device - desk assistassistance
#include <SimpleDHT.h>
SimpleDHT11 oneDht11(6);
//int mq2 = A0;      //Gas sensor
//int val=0;
int fPin = 11;     //Fire sensor
int sPin = 10;     //Sound sensor
int ulinPin = 13;  //Ultrasonic ECHO
int uloPin = 12;   //Ultrasonic TRIG
int tsPin = 5;     //Touch sensor - This module takes a second to active, and recalibration time is roughly 5s. That why I keep press it
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  pinMode(ulinPin, INPUT);     //Ultrasonic ECHO
  pinMode(uloPin, OUTPUT);     //Ultrasonic TRIG
  pinMode(tsPin, INPUT);       //Touch sensor
  pinMode(fPin,INPUT);         //Fire sensor
  pinMode(sPin, INPUT);        //Sound sensor   
  lcd.init();                  // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Waitting Master");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Come to desk");
  delay(3000);
  //Protocol Configuration
  Serial.begin(9600); 

}
void loop () {
  byte oneTemp = 0;
  byte oneHumidity = 0;
  oneDht11.read(&oneTemp, &oneHumidity, NULL);

///////////Ultrasonic begin///////////////
  digitalWrite(uloPin, LOW);
  delayMicroseconds(2);
  digitalWrite(uloPin, HIGH); // Pulse for 10μs to trigger ultrasonic detection
  delayMicroseconds(10);
  digitalWrite(uloPin, LOW);  
  int distance = pulseIn(ulinPin, HIGH);  // Read receiver pulse time
  distance= distance/58;      // Transform pulse time to distance
  Serial.println(distance);   // Ourput distance                
  delay(500); 
///////////Ultrasonic end/////////////// 

//2nd UNO//    
///////////Stage4///////////////
//Ultrosonic sensor detect Master X - instructions to proceed
  if (distance <= 30){
    Serial.println(digitalRead(tsPin));
    delay(100);
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sit down,Please");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("Master X");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Touch to review");
    lcd.setCursor(0,1);
    lcd.print("Real-time stats");
    delay(5000);            //Add delay to 5S
    }
///////////Stage5///////////////
//After touching the module, it will display flame-sound-temperature-humidity sensor signals in sequence.     
  if (digitalRead(tsPin)){
//    val=analogRead(mq2);
    Serial.println(digitalRead(tsPin));
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Fire:");    
    lcd.setCursor(0,1);
    lcd.print("Sound:");
    lcd.setCursor(11,0);
    lcd.print("1:yes");
    lcd.setCursor(11,1);
    lcd.print("0:no");
    lcd.setCursor(6,0);
    lcd.print(digitalRead(fPin));
    lcd.setCursor(6,1);
    lcd.print(digitalRead(sPin));
    delay(5000);            //Add delay to 5S
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperature:");
    lcd.setCursor(12,0);
    lcd.print(oneTemp);
    lcd.setCursor(14,0);
    lcd.print("C");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("Humidity:");
    lcd.setCursor(10,1);
    lcd.print(oneHumidity);
    lcd.setCursor(12,1);
    lcd.print("%");
    delay(5000);            //Add delay to 5S
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("Gas sensor read");
//    lcd.setCursor(0,1);
//    lcd.print(val);
//    lcd.setCursor(7,1);
//    lcd.print("safe<100");
//    delay(5000);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enjoy your day");    
    lcd.setCursor(0,1);
    lcd.print("See you soon");
    
    delay(10000);
    }
}
// The way things go project - Home welcome(instuction) - Xavier NOV. 2020
