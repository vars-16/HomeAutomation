#include<LiquidCrystal.h>
#include<SoftwareSerial.h>
#include<dht.h>
dht DHT;

SoftwareSerial XBeeSerial = SoftwareSerial(2,3);

#define DHT11_PIN 8 // pin number for humidity and temp sensor

LiquidCrystal lcd(12, 11, 7,6,5,4); 

int pir=9; //The output of PIR sensor connected to pin 7
int pir_value; //variable to hold read sensor value
const int ProxSensor=13;
int contact  = 10; //contact switch
boolean state_pir = false;
boolean state_prox = false;
boolean limit_switch = false;
boolean entry = false;
int user_value;
String value;
int sensor=8; //The output of PIR sensor connected to pin 8
int gas_value=0; // for non-threat 
int sensor_value; //variable to hold read sensor value

void setup()
{
pinMode(contact, INPUT);
pinMode(ProxSensor,INPUT);
pinMode(pir,INPUT); // configuring pin 7 as Input

Serial.begin(9600); // To show output value of sensor in serial monitor
  
pinMode(sensor,INPUT); 
pinMode(A0,INPUT);
pinMode(DHT11_PIN,INPUT);
XBeeSerial.begin(9600);
Serial.begin(9600);
lcd.begin(16,2);  
  delay(500);
  
}
void loop() 
{
  //if(XBeeSerial.available())
  //{
   //Serial.println((char)XBeeSerial.read());
  //}

  
 // user enterance and exit...........

 if(!digitalRead(contact)){
 limit_switch = !limit_switch;

}

if(limit_switch){

if(digitalRead(pir))
{
  state_pir=!state_pir;
}
if(state_pir)
{
  if(digitalRead(ProxSensor)== HIGH)
  {
  Serial.println("user has entered");
  entry = true;
  user_value = 1;
  delay(500);
  state_pir=!state_pir;
  }
}
limit_switch = !limit_switch;
}

// User Exit...................
if(digitalRead(contact)){
  
if(digitalRead(ProxSensor))
{
  state_prox=!state_prox;
}
 if(state_prox) 
  {
  if(digitalRead(pir)== HIGH)
  {
  state_pir=!state_pir;
  }
  if(!digitalRead(contact))
  {
  Serial.println("user has moved out");
  user_value = 0;
  delay(500);
  state_prox=!state_prox;
  state_pir=!state_pir;
  }
  }
}

 //sensor values..............
  
int chk = DHT.read11(DHT11_PIN);
//sensor_value=digitalRead(sensor); // Reading sensor value from pin 7
//Serial.println(sensor_value); // Printing output to serial monitor

gas_value=analogRead(A0); //read gas sensor value
//Serial.println(gas_value); // print gas value to serial monitor

//Serial.println(" Humidity " );
//Serial.println(DHT.humidity, 1);
//XBeeSerial.println(DHT.humidity);
//delay(2000);

//Serial.println(" Temparature "); 
//Serial.println(DHT.temperature, 1);

value="User="+ String(entry)+" Humidity="+String(DHT.humidity)+" Temperature="+String(DHT.temperature)+" Gas="+ String(gas_value); //store value of humidity,temperature and gas presence
entry = false;

XBeeSerial.println(value); // send this value to raspberry through xbee

delay(1000);

lcd.setCursor(0,0);
//lcd.print("hello");
lcd.print("Humidity ");
lcd.print(DHT.humidity);
lcd.setCursor(0,1);
lcd.print("Temparature");
lcd.print(DHT.temperature);
delay(1000); //Delay of 1 second for ease of viewing in serial monitor
}
