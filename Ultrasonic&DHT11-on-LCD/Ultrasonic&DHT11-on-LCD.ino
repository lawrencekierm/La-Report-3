/*This code uses a DHT11 sensor to measure temperature and humidity, and an HC-SR04 sensor 
to measure distance and calculate the speed of sound based on temperature and humidity. 
The code  sends the measurements to the serial monitor for debugging and further analysis. 
Then, the measurements are displayed on the LCD screen. This code runs in a continuous loop 
with a delay of 2 seconds between measurements.*/

// Include required libraries
#include "DHT.h"; // For DHT sensor
#include "NewPing.h"; // For Ultrasonic sensor
#include <LiquidCrystal.h> // For LCD display

// Define pin connections for DHT sensor, Ultrasonic sensor, and LCD display
#define DHTPIN 6 // DHT-11 Output Pin connection
#define DHTTYPE DHT11 // DHT Type is DHT 11 (AM2302)
#define TRIGGER_PIN 9 // Trigger pin for Ultrasonic sensor
#define ECHO_PIN 10 // Echo pin for Ultrasonic sensor
#define MAX_DISTANCE 400 // Maximum distance (in cm) for Ultrasonic sensor
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // Pins for LCD display

// Initialize objects for sensors and LCD display
DHT dht(DHTPIN, DHTTYPE);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Declare variables
float hum; // Stores Humidity value
float temp; // Stores Temperature value
float duration; // Stores duration of sound wave
float distance; // Stores calculated distance from Ultrasonic sensor
float soundsp; // Stores calculated speed of sound in m/s
float soundcm; // Stores calculated speed of sound in cm/ms
int iterations = 5; // Number of iterations for Ultrasonic sensor readings

void setup() {
// Initialize serial communication and LCD display
Serial.begin (9600);
lcd.begin(16, 2);

// Initialize DHT sensor
dht.begin();
}

void loop() {
// Wait for 2 seconds
delay(2000);

// Read values from DHT sensor
hum = dht.readHumidity();
temp = dht.readTemperature();

// Calculate the speed of sound in m/s using temperature and humidity values
soundsp = 331.4 + (0.606 * temp) + (0.0124 * hum);

// Convert speed of sound from m/s to cm/ms
soundcm = soundsp / 10000;

// Calculate the distance using Ultrasonic sensor
duration = sonar.ping_median(iterations);
distance = (duration / 2) * soundcm;

// Send results to Serial Monitor
Serial.print("Sound: ");
Serial.print(soundsp);
Serial.print(" m/s, ");
Serial.print("Humid: ");
Serial.print(hum);
Serial.print(" %, Temp: ");
Serial.print(temp);
Serial.print(" C, ");
Serial.print("Distance: ");

// Check if the calculated distance is within the valid range
if (distance >= 400 || distance <= 2) {
Serial.print("Out of range");
}
else {
Serial.print(distance);
Serial.println(" cm");
delay(200);
}

// Move the cursor to the beginning of the first line of the LCD display and print the sound speed
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Sound:");
lcd.print(soundsp);
lcd.print("m/s");

// Move the cursor to the beginning of the second line of the LCD display and print the distance
lcd.setCursor(0,1);
lcd.print("Distance:");
lcd.print(distance);
lcd.print("cm");
}
