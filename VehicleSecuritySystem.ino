//Global Variables
const int doorSwitch = 2; // our door signal
const int ignitionSwitch = 3; // our ignition signal
const int button1 = 4; // our button 1
const int button2 = 5; // our button 2
const int LED = 13; // to ON LED
const int hazard = 12; // to hazard lights
const int horn = 11; // to car horn
const int relay = 10; // to latchning relay (cuts off fuel pump)
int hornState = LOW;
 
unsigned long alarmOnMillis; // when alarm was activated
unsigned long hazardTurnOnDelay = 3000; // wait to turn on hazard
unsigned long hornTurnOnDelay = 4000; // wait to turn on horn
unsigned long relayTurnOnDelay = 5000; // wait to activat relay
unsigned long previousMillis = 0;
long interval = 500;           // horn ON and OFF interval
bool hazardOn = false; // 
bool hornOn = false; //
bool relayOn = false; //
bool alarmOn = false; // for when alarm is ON
bool ignitionOn = false;
bool doorOn = false;


void setup() {
  // put your setup code here, to run once:
pinMode(doorSwitch, INPUT_PULLUP);
pinMode(hazard, OUTPUT);
pinMode(LED, OUTPUT);
pinMode(horn, OUTPUT);
pinMode(relay, OUTPUT);
pinMode(button1, INPUT);
pinMode(ignitionSwitch, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

 // get the time at the start of this loop()
if (digitalRead(ignitionSwitch) == HIGH)
{
  ignitionOn = true;
}
if (digitalRead(doorSwitch) == HIGH){
  doorOn = true;
}

 unsigned long currentMillis = millis(); 
if ((alarmOn) == false)
{
if ((doorOn) && (ignitionOn)){
  alarmOn = true;
  alarmOnMillis = currentMillis;
}
}

 // check the button
 if (alarmOn)
 {
  // update the time when button was pushed
        digitalWrite(LED,HIGH);
        hazardOn = true;
        hornOn = true;
        relayOn = true;
       }
       else{
        (digitalWrite(LED,LOW));
        hazardOn = false;
        (digitalWrite(hazard,LOW));
        hornOn = false;
        (digitalWrite(horn,LOW));
        relayOn = false;
        (digitalWrite(relay,LOW));
       }
  
 // make sure this code isn't checked until after button has been let go
 
 if (hazardOn)
 {
   if ((unsigned long)(currentMillis - alarmOnMillis) >= hazardTurnOnDelay) {
     digitalWrite(hazard, HIGH);
      }
 }

if (hornOn)
{
   if ((unsigned long)(currentMillis - alarmOnMillis) >= hornTurnOnDelay)
{
    
    if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the Klaxon is off turn it on and vice-versa:
    if (hornState == LOW) {
      hornState = HIGH;
    } else {
      hornState = LOW;
    }

    // set the horn with the hornState of the variable:
    digitalWrite(horn, hornState);
   }
}
}

if (relayOn)
{
   if ((unsigned long)(currentMillis - alarmOnMillis) >= relayTurnOnDelay) {
     digitalWrite(relay, HIGH);
   }
}
 
 if (digitalRead(button1) && (digitalRead(button2)== HIGH)) {
  alarmOn = false;
  ignitionOn = false;
  doorOn = false;
 }
}

 

