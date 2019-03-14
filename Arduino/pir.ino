int pir=2; //The output of PIR sensor connected to pin 7
int pir_value; //variable to hold read sensor value
int led=7;
const int ProxSensor=5;
boolean state_pir = false;
boolean state_prox = false;


void setup()
{

pinMode(ProxSensor,INPUT);
pinMode(pir,INPUT); // configuring pin 7 as Input

pinMode(led,OUTPUT); // configuring pin 7 as Input
Serial.begin(9600); // To show output value of sensor in serial monitor
}

void loop()
{
pir_value=digitalRead(pir); // Reading sensor value from pin 7

if(digitalRead(pir)==HIGH)
{
  state_pir=!state_pir;
}
if(state_pir)
{
  if(digitalRead(ProxSensor)== HIGH)
  {
  digitalWrite(led,HIGH);
  Serial.println("user has entered");
  delay(200);
  digitalWrite(led,LOW);
    state_pir=!state_pir;
  }
}
if(digitalRead(ProxSensor)==HIGH)
{
  state_prox=!state_prox;
}
  if(state_prox) 
  {
  if(digitalRead(pir)== HIGH)
  {
  digitalWrite(led,HIGH);
  Serial.println("user has moved out");
  delay(200);
  digitalWrite(led,LOW);
  state_prox=!state_prox;
  }
}
//Serial.println(sensor_value); // Printing output to serial monitor
delay(1000);
}
