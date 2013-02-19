/*
  COS 436: Lab 0: Wondrous Weather Cube
  Author: Kiran Vodrahalli 
  Date: Feb 14, 2013
  weather_nasdaqCube.ino: Depending on what the serial reads, either
  interprets the incoming data as a NASDAQ percentage change (via python nasdaq_scraper)
  or as the temperature at Princeton University in degrees Farenheit (via python weather_scraper)
  
  NASDAQ:
  Depending on whether NASDAQ delta is positive or negative, makes the cube glow green or red 
  correspondingly, and the magnitude changes the intensity of the light color. 
  
  WEATHER:
  If the temperature <= 50 degrees Farenheit, the cube glows blue -- the colder it is, the
  more intense the blue color. If the temperature > 50 degrees Farenheit, the cube glows
  orange. The hotter it is, the more orange the cube glows. 
   
 */
 
// Pin 13 has an LED connected on most Arduino boards.
int led_test = 13; 

int offset = 48; // offset for ascii digits 
int current_unit = -1; //current units digit
int current_tens = -1; //current tens digit
int current_hundreds = -1; //current hundreds digit (only used for color of the stock: red/green)
int current_temperature = -1; // current temperature from python weather scraper 
int current_stock_color = -1; //current stock color from python nasdaq scraper 

//RGB
int red = 0;
int green = 0;
int blue = 0; // will stay 0 for stock color 

int stockSign = 0; // initialize to 0 (has no sign)
int stockMag = 0; //magnitude of the stock change -- given by the value of R or G

int minTemp = 0; // assume min temperature is 0 degrees F
int maxTemp = 100; // assume max temperature is 100 degrees F
double scale = 255/100; // temperature scale translation 

int photo_voltage = 0; // analog value of the photo voltage 

// the setup routine runs once when you press reset:
void setup() {          
  // initialize Serial 
  Serial.begin(9600);  
  
  // initialize the pin as an output.  
  pinMode(led_test, OUTPUT);  
  // initialize the photocell as an input. 
  pinMode(A0, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  
  //input 
  photo_voltage = analogRead(A0);
  Serial.println(photo_voltage);
  //delay(1000); 
  
  
  
  if(Serial.available() > 0){
    
    current_tens = Serial.read() - offset;
    //nasdaq case 
    if(current_tens+offset == '+' || current_tens+offset == '-'){
      if(current_tens+offset == '+'){
        stockSign = 1; 
      }else{
        stockSign = -1;
      }
      Serial.println("Stock color and sign: ");
      Serial.println(stockSign);
      delay(2);
      current_hundreds = Serial.read()-offset;
      Serial.println(current_hundreds);
      delay(2);
      current_tens = Serial.read()-offset;
      Serial.println(current_tens);
      delay(2);
      current_unit = Serial.read()-offset;
      Serial.println(current_unit);
      
      if(stockSign > 0){
        green = 100*current_hundreds + 10*current_tens + current_unit;
        stockMag = green;
      }else if(stockSign < 0){
        red = 100*current_hundreds + 10*current_tens + current_unit; 
        stockMag = red;
      }
      
      Serial.println("RGB values: ");
      Serial.println(red);
      Serial.println(green);
      Serial.println(blue);
      
      /* USE THE RGB VALUES TO MAKE THE TRICOLOR LED GLOW PROPERLY */
      
      /*WRITE CODE HERE */
      
      /* Use the magnitude of the stock change to dictate the blinking. 
       * The higher the stock change, the faster the blinking. */
      digitalWrite(led_test, HIGH); 
      delay(stockMag/255); 
      digitalWrite(led_test, LOW);
      delay(stockMag/255); 
    }
      
    //weather case  
    else{  
      
      if(current_tens > 0){
        //use the temperature 
        Serial.println("Current temperature in degrees F: "); 
        delay(2);
        current_unit = Serial.read() - offset;
        if(current_unit > 0){
          current_temperature = 10*current_tens + current_unit; 
          Serial.println(current_temperature); 
        
          //scale the temperature 
          current_temperature = scale*current_temperature; 
          
          //Serial.println(current_tens);
          //Serial.println(current_unit); 
          Serial.println("Temperature Magnitude: "); 
          Serial.println(current_temperature);  
          //analogWrite(led_test, current_temperature); 
          //digitalWrite(led_test, HIGH); 
          //digitalWrite(led_test, LOW);
          
          /* WRITE CODE HERE TO MAKE THE LEDS WORK PROPERLY FOR WEATHER */
          delay(2); 
        }
        else{
          Serial.println("Failed to read unit digit");
        }
      }
      else{
        Serial.println("Failed to read tens digit");
      }
    }
    
  } 
 
}
