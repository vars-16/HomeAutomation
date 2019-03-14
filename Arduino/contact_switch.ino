#define led 3
int ingresso = 10;
void setup() {
  pinMode(led, OUTPUT);
  pinMode(ingresso, INPUT);
  
}

void loop() {  
 if(!digitalRead(ingresso)) digitalWrite(led, HIGH);
 if(digitalRead(ingresso)) digitalWrite(led, LOW);
  }
