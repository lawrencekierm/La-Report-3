/*
This code reads temperature and humidity data from a DHT11 sensor and displays it 
on an LCD screen. It also uses a push button to cycle through different display 
options, including displaying the temperature in Celsius, displaying the humidity, 
and displaying the temperature in Fahrenheit*/

/*Include the LiquidCrystal and DHT libraries using the #include directive. The 
DHT library is used to interface with the DHT11 sensor, while the LiquidCrystal 
library is used to control the LCD screen.*/

#include <LiquidCrystal.h> // include the LiquidCrystal library to provide a set of functions for controlling LCD

//DHT11
#include <Adafruit_Sensor.h> // Include this library to provide common interface for reading sensor data
#include <DHT.h> // Include DHT library to provide functions for reading temperature and humidity data from DHT sensor
#include <DHT_U.h>

//Define the pins used to connect the LCD screen and the DHT11 sensor
#define DHTPIN 6 // Define a constant macro and assigns it the value (pin) of 6
#define DHTTYPE    DHT11 
DHT_Unified dht(DHTPIN, DHTTYPE); // Initialize an instance of the "DTH_Unified" class called "dht"
uint32_t delayMS;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Set up a constant integer variable to represent the button pin number
const int buttonPin = 7;

// Initialize integer variables to hold the current and last state of the button
int buttonState = LOW;
int lastButtonState = LOW;

// Set up variables to manage debouncing the button signal
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Set up a variable to keep track of how many times the button has been pressed
int count= 0;


void setup() {
  /* Initialize the LCD screen using the lcd.begin(16, 2) command and starts the serial communication 
using Serial.begin(9600).*/
  pinMode(buttonPin, INPUT_PULLUP);  // Use built-in pullup 
  lcd.begin(16, 2);
  Serial.begin(9600);       //serial communication at 9600 bits per second

/*Set up the DHT11 sensor by calling the dht.begin() function and print
the details of the temperature and humidity sensors to the Serial Monitor.*/
  //DHT11
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {

// DON LCD, display Temperature in Celsius, Humidity and Temperature in Fahrenheit

int reading = digitalRead(buttonPin); //Read the state of the button

//debounce the button to avoid bouncing signals
if (reading != lastButtonState) {
  lastDebounceTime = millis();
}
if ((millis() - lastDebounceTime) > debounceDelay) {
  //if the button state has changed, and is stable, update buttonState variable
  if (reading != buttonState) {
    buttonState = reading;
    //if the button is pressed, cycle through display options
    if (buttonState == HIGH) {
      count++;
      //reset count to 1 after reaching max count
      if(count == 4){
        count = 1;
      }
      //switch case statement to handle different display options
      switch(count){
        case 1:
          //Display temperature in Celsius
          sensors_event_t event;
          dht.temperature().getEvent(&event);// Read the temperature data from DHT11 sensor using temperature() function and store results in "event" variable.
          if (isnan(event.temperature)) { // If temperature event is not a number
            Serial.println(F("Error reading temperature!")); // Print error
          }
          else { // Print temperature event number with Celsius symbol
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Temp: ");
            lcd.print(event.temperature);
            lcd.print(char(223));
            lcd.print("C");
          }
          break;
        case 2:
          //Display humidity
          dht.humidity().getEvent(&event);// reads the humidity data from the DHT11 sensor using humidity() function and store the result in the "event" variable.
          if (isnan(event.relative_humidity)) { // If humidity event is not a number
            Serial.println(F("Error reading humidity!")); //print error
          }
          else {
            lcd.clear(); // Print humidity number with a percentage symbol
            lcd.setCursor(0,0);
            lcd.print("Humidity: ");
            lcd.print(event.relative_humidity);
            lcd.print("%");
          }
          break;
        case 3:
          //Display temperature in Fahrenheit
          dht.temperature().getEvent(&event);
          if (isnan(event.temperature)) {
            Serial.println(F("Error reading temperature!"));
          }
          else {  // Conversion from Celsius to Fahrenheit
            float f = (event.temperature * 1.8) + 32;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Temp: ");
            lcd.print(f);
            lcd.print(char(223));
            lcd.print("F");
          }
          break;
      }
    }
  }
}
//update lastButtonState to current reading for next cycle
lastButtonState = reading;


}

