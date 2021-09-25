//Arduino 1 - The way things go - Entry assistance (instruction)
#include <Stepper.h>
const int stepsPerRevolution = 1024;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int lsPin = 6;     //Limited Switch Pin
int val;           //LSPin val
int ulinPin = 13;  //Ultrasonic ECHO
int uloPin = 12;   //Ultrasonic TRIG
int ledPin = 5;    //10MM big LED
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int pirPin = 7;   //Small PIR sensor
int pirStat = 0;  //Small PIR Stats  

void setup() {
  pinMode(pirPin, INPUT);      //PIR sensor
  pinMode(lsPin, INPUT);       //Limited Switch Pin
  pinMode(ulinPin, INPUT);     //Ultrasonic ECHO
  pinMode(uloPin, OUTPUT);     //Ultrasonic TRIG
  pinMode(ledPin, OUTPUT);     //LED
  myStepper.setSpeed(5);      //Stepper speed
  lcd.init();                  // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  //lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Waitting Master");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Come back home");
  delay(1000);

  //Protocol Configuration
  Serial.begin(9600); 

}
void loop () {
pirStat = digitalRead(pirPin);
int val=digitalRead(lsPin);
///////////Ultrasonic begin///////////////
  digitalWrite(uloPin, LOW);
  delayMicroseconds(2);
  digitalWrite(uloPin, HIGH); // Pulse for 10μs to trigger ultrasonic detection
  delayMicroseconds(10);
  digitalWrite(uloPin, LOW);  
  int distance = pulseIn(ulinPin, HIGH);  // Read receiver pulse time
  distance= distance/58;   // Transform pulse time to distance
  Serial.println(distance);   //Ourput distance                
  delay(50); 
///////////Ultrasonic end/////////////// 

///////////Stage1///////////////
//Enter room trige PIR = welcome light
  if ((pirStat == HIGH) && (val == HIGH)){
    Serial.println(val); 
    digitalWrite(ledPin,HIGH);    //Welcome red light
    delay(1000); 
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Welcome home!");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("Master X");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Shoes off");
    lcd.setCursor(0,1);
    lcd.print("Please");
    delay(5000);            //Add delay to 5S
    }
///////////Stage2///////////////
//trige PIR and limited switch, open tissue box cover 
  if ((pirStat == HIGH) && (val == LOW)){
    Serial.println(val); 
    digitalWrite(ledPin,LOW);
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Shoes Secure!");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("Scrub hand,Master");
    delay(3000);            //Add delay to 3S
    Serial.println("clockwise");
    myStepper.step(stepsPerRevolution);  
    } 
///////////Stage3///////////////
//Ultrosonic sensor detect hand grab the tissue,then proceed - to desk - Arduino 2 phase
  if (distance <= 20){
    Serial.println(val); 
    digitalWrite(ledPin,LOW);
    delay(3000);
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("hygiene completed");
    delay(2000);
    lcd.setCursor(0,1);
    lcd.print("Sit down,Please");
    delay(2000);
    }       
   else{
    digitalWrite(ledPin,LOW); 
   }
}
//Go to desk - begin Arduino 2 phase

// The way things go project - Home welcome(instuction) - Xavier NOV. 2020
