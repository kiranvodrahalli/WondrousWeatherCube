/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 2;
int led_test = 13; 
int offset = 48; // offset for ascii digits 
int current_unit = -1; //current units digit
int current_tens = -1; //current tens digit
int current_temperature = -1; // current temperature from python weather scraper 

// the setup routine runs once when you press reset:
void setup() {          
  // initialize Serial 
  Serial.begin(9600);  
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);   
  pinMode(led_test, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  //Serial.println("test\n");
  
  if(Serial.available() > 0){
    current_tens = Serial.read() - offset;
    //do something with what's being read in 
    Serial.println("Current temperature in degrees C: "); 
    /*
    digitalWrite(led_test, HIGH);  
    delay(1); 
    digitalWrite(led_test, LOW); 
    delay(1);*/
    current_unit = Serial.read() - offset;
    current_temperature = 10*current_tens + current_unit; 
    Serial.println(current_tens);
    Serial.println(current_unit);
    Serial.println(current_temperature);  
    analogWrite(led, current_temperature*5); 
    delay(2); 
    
  }
 
 
 /*
 if(current_temperature > 32 || current_temperature <= 36){
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    } 
  else if(current_temperature<= 32 || current_temperature > 30){
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
      delay(10);               // delay
  }
  
  */
    
 
 
}
