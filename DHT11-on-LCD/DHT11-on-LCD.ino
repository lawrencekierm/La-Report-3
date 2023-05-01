/*This code reads data from a DHT11 temperature and humidity sensor and displays 
the values on an LCD screen and the Serial Monitor.*/

/*Include the LiquidCrystal and DHT libraries using the #include directive. The 
DHT library is used to interface with the DHT11 sensor, while the LiquidCrystal 
library is used to control the LCD screen.*/

//LCD
#include <LiquidCrystal.h>  // include the LiquidCrystal library to provide a set of functions for controlling LCD

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


void setup() {
/* Initialize the LCD screen using the lcd.begin(16, 2) command and starts the serial communication 
using Serial.begin(9600).*/
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
 
 // *********Serial Monitor*******************
//Read the temperature and humidity data from the DHT11 sensor 
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event); // Read the temperature data from DHT11 sensor using temperature() function and store results in "event" variable.
  if (isnan(event.temperature)) {                    // If temperature event is not a number
    Serial.println(F("Error reading temperature!")); // Print error
  }
  else {                                      // Print temperature event number with Celsius symbol
    Serial.print(F("Temperature: ")); 
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event); // reads the humidity data from the DHT11 sensor using humidity() function and store the result in the "event" variable.
  if (isnan(event.relative_humidity)) {             // If humidity event is not a number
    Serial.println(F("Error reading humidity!"));   //print error
  }
  else {                                      // Print humidity number with a percentage symbol
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }


// Display both Temperature and Humidity event numbers on LCD
 // *********LCD*******************
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    lcd.setCursor(0, 0); 
    lcd.print(F("Error reading temperature!"));
  }
  else {
    lcd.setCursor(0, 0); 
    lcd.print(F("Temp: "));
    lcd.print(event.temperature);
    lcd.print(char(223));
    lcd.print(F("C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    lcd.setCursor(0, 1); 
    lcd.print(F("Error reading humidity!"));
  }
  else {
    lcd.setCursor(0, 1); 
    lcd.print(F("Humidity: "));
    lcd.print(event.relative_humidity);
    lcd.print(F("%"));
  }

}