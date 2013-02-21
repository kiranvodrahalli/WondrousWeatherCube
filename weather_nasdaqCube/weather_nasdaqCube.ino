/*
  COS 436: Lab 0: Wondrous Weather Cube
  Author: Kiran Vodrahalli, Dale Markowitz, Collin Stedman 
  Date: Feb 19, 2013
  weather_nasdaqCube.ino: Depending on what the serial reads, either
  interprets the incoming data as a NASDAQ percentage change (via python nasdaq_scraper)
  or as the temperature at Princeton University in degrees Farenheit (via python weather_scraper)
  
  NASDAQ:
  Depending on whether NASDAQ delta is positive or negative, makes the cube glow green or red 
  correspondingly, and the magnitude changes the intensity of the light color. 
  
  WEATHER:
  If the temperature <= 50 degrees Farenheit, the cube glows red -- the colder it is, the
  more intense the red color. If the temperature > 50 degrees Farenheit, the cube glows
  green. The hotter it is, the greener the cube glows. 
   
 */

int offset = 48; // offset for ascii digits 
int current_unit = -1; //current units digit
int current_tens = -1; //current tens digit
int current_hundreds = -1; //current hundreds digit (only used for color of the stock: red/green)
int current_temperature = -1; // current temperature from python weather scraper 
int current_stock_color = -1; //current stock color from python nasdaq scraper 

//pins controlling red, green leds (with PWM).
int greenPin = 3;
int redPin = 5;

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
  
  
  // initialize the photocell as an input. 
  pinMode(A0, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  //input 
  photo_voltage = analogRead(A0);
  Serial.println(photo_voltage);
  
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
      
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(redPin, red);
      analogWrite(greenPin, green);
     
      
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
          
          /* Code to write weather to LEDS */
          
          //Green for warm weather, red for cold!
          int displayTemp = map(current_temperature, 0, 100, 0, 255);
          analogWrite(redPin, 0);
          analogWrite(greenPin, 0);
          analogWrite(redPin, displayTemp);
          analogWrite(greenPin, (255-displayTemp));
          
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
