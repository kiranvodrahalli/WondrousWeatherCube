/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 2;

// the setup routine runs once when you press reset:
void setup() {          
  // initialize Serial 
  Serial.begin(9600);  
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  if(Serial.available() > 0){
    int inByte = Serial.read();
    //do something with what's being read in 
    Serial.println(Serial.read());
    digitalWrite(led, HIGH);  
    delay(1000); 
  }
    /*
    if(Serial.read() > 20){
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);      // wait for 3 seconds
  } else{
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
  }
  
  if(Serial.available() > 0){
    Serial.println(Serial.read());
  }*/
}
