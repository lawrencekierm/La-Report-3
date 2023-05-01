/*This code uses an ultrasonic sensor to measure the distance between the sensor and an object 
in front of it, and display the measured distance on both the serial monitor and an LCD screen.*/

//define the pins used for the ultrasonic sensor 
#define trigPin 9   // This sends the trigger signal
#define echoPin 10 // This receives the echo signal

#include <LiquidCrystal.h> 
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Declare two float variables to store the duration and distance values
float duration, distance;

void setup() {
/* Initialize the LCD screen using the lcd.begin(16, 2) command, start the serial communication 
using Serial.begin(9600), and set the trigger and echo pins as output and input respectively.*/
Serial.begin(9600);
pinMode(trigPin, OUTPUT);    // Assign trigPin as OUTPUT
pinMode(echoPin, INPUT);     // Assign echoPin as Input
  lcd.begin(16, 2);


}

void loop() {

digitalWrite(trigPin, LOW); // Sets the trigger pin (connected to the ultrasonic sensor) to LOW
delayMicroseconds(2);       // To ensure trigger pin has settle down, put delay
digitalWrite(trigPin, HIGH); // Set the trigger pin to HIGH, which sends a 10-microsecond pulse to the ultrasonic sensor.
delayMicroseconds(20);     // Recommended minimum time between the trigger signal and the start of the echo pulse
digitalWrite(trigPin, LOW); // Set the trigger pin back to LOW to complete the trigger signal.

//measure the duration of the echo pulse and calculate the distance 
//based on the duration and the speed of sound
duration = pulseIn(echoPin, HIGH);
distance = (duration /2 ) * 0.0343;

// Print the distance on the serial monitor
Serial.print("Distance: ");
/*If the distance is out of range (less than 2cm or more than 400cm), 
it prints "Out of Range" instead of the distance*/
if (distance >= 400 || distance <= 2) {
  Serial.println("Out od Range");
} else {
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}
//delay(500);

// Print the details also on the LCD
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Distance: ");
if (distance >= 400 || distance <= 2) {
  lcd.setCursor(0,1);
  lcd.print("Out of Range");
} else {
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.print(" cm");
}
}
