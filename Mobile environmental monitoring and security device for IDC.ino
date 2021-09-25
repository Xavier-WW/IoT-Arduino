//Mobile environmental monitoring and security device for IDC 
//NSCAD丨 MDes-6530丨 Fall 2020
//Instructor: Professor Michael LeBlanc
//Xavier W. Wang @ Halifax Dec.2020 

//L298N drive board -need even more current than other driver board- aviod this in the future!!!
int IN1 = 5;     //Left motor forward
int IN2 = 6;     //Left motor dback
int IN3 = 9;     //Right motor forward
int IN4 = 10;    //Right motor back
//int key= 0;    //Button

//Line track
int L = 11;   //Left IR line track sensor
int M = 12;   //Middle IR line track sensor
int R = 13;   //Right IR line track sensor

//IR obstacle
int OL = 8;   //IR obstacle sensor left
int OR = 7;   //IR obstacle sensor right

//Rest Environmental sensors
int wPin = A0;     //Water sensor
int pirPin = A1;   //PIR sensor
int fPin = A2;     //Fire sensor
int mq2 = A3;      //Gas sensor(MQ2)


//DHT22
#include <DHT.h>;
#define DHTPIN 4     
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);
//Airpresure BOSCH BMP180
#include <SFE_BMP180.h>;    
SFE_BMP180 AirPresure;      
char presureDelayTime;       
double presureP, presureT; 

//Variables丨value
int SL;             //Left IR line track sensor
int SR;             //Middle IR line track sensor
int SM;             //Right IR line track sensor
int IROL;           //IR obstacle sensor left variable
int IROR;           //IR obstacle sensor right variable
float hum;          //DHT22 humidity value
float temp;         //DHT22 temperature value

void setup()
{
//  pinMode(key, INPUT);  // Button
  Serial.println("BMP180 Measurements");  
  dht.begin();
  AirPresure.begin();
  //Driver moudle pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // other sensor
  pinMode(pirPin, INPUT);      //PIR sensor
  pinMode(fPin, INPUT); //Fire sensor
  pinMode(L, INPUT);   //left IR line track sensor
  pinMode(M, INPUT);   //middle IR line track sensor
  pinMode(R, INPUT);   //right IR line track sensor
  Serial.begin(9600);  
  pinMode(OL, INPUT);   //IR obstacle sensor left
  pinMode(OR, INPUT);   //IR obstacle sensor right
}
// --------Define movement------------
// -----------Forward-----------------
void run()     
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

// -----------Brake-----------------
void brake()         
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

// -----------Left turn (light)Not in use ATM)-----------------
void left()         
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);

}

// -----------Left turn (hard)-----------------
void spin_left()         
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

}

// -----------Right turn (light)(Not in use ATM)-----------------
void right()        
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);  
}

// -----------Right turn (hard)-----------------
void spin_right()        
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

// -----------Backwards-----------------
void back()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}


void loop()
{
  while(1) // infinity loop
  {
  SL = digitalRead(L);
  SR = digitalRead(R);
  SM = digitalRead(M);  
  IROL = digitalRead(OL);
  IROR = digitalRead(OR);
  hum = dht.readHumidity();
  temp = dht.readTemperature();
    //-----------line track & obstacle aviod---------------
      if(SM==HIGH&&SR==LOW&&SL==LOW)     //Middle is black line, forward
      {
          run();
//All comment out because the Serial.print will slow the Arduino uno down, and obstacle avoid will not be processed in time
//And it also needs more strong power source.
//          Serial.print("Humidity: ");
//          Serial.print(hum);
//          Serial.print(" %, Temp: ");
//          Serial.print(temp);
//          Serial.println(" Celsius");
//          Serial.print("Gas sensor: ");
//          Serial.println(analogRead(mq2));
//          Serial.print("Fire sensor: ");
//          Serial.println(digitalRead(fPin));
//          Serial.print("PIR sensor: ");
//          Serial.println(digitalRead(pirPin));
//          Serial.print("Water sensor: ");
//          Serial.println(digitalRead(wPin));
//          Serial.print("Current Preasure: ");
//          Serial.print(presureP);
//          Serial.println(" bar");
//          Serial.print(presureP);
//          Serial.print(" bar is");
//          Serial.print(presureP / 1000.0);
//          Serial.println(" atm");
//          delay(10000);
      }
      else if(SM==LOW&&SR==LOW&&SL==HIGH)//Middle & right are white，left is black line(far from the right direction)， then big left TURN
      {
          spin_left();
      }
//      else if(SM==HIGH&&SR==LOW&&SL==HIGH)//Middle & leftt are black，right is white，then left TURN
//      {                                   //Working badly in some scenario, jeopardize the whole line tracking process
//          left();
//      }
      else if(SM==LOW&&SR==HIGH&&SL==LOW)//Middle & left are white，right is black(far from the right direction), then big right  TURN
      {
          spin_right();
      }
//      else if(SM==HIGH&&SR==HIGH&&SL==LOW)//Middle & right are white，left is black，then right TURN
//      {                                   //Working badly in some scenario, jeopardize the whole line tracking process
//          right();
//      }
      else if(SM==HIGH&&SR==HIGH&&SL==HIGH)  //All black - STOP
      {
        brake();
      }
      else if(SM==LOW&&SR==LOW&&SL==LOW)  //All white（Out of line) - BACK
      {
        back();
      }
      else if(IROL==LOW||IROR==LOW)  //Left IR or Right IR detect obstacles, STOP(LOW when it detect something)
      {
        back();
      }
      else                //Defualt state is forward
      {
        run();
      }
   }
}
