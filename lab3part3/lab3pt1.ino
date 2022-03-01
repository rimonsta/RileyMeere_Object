//use the library manager to install the library first
//include the library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
//define the digital pin that the LED strip is connected to
#define PIN 6
//the first parameter is the number of LEDs you have - change for your strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);
// neopixel color variables (RGB)
int rVal;
int bVal;

// variables for ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;
// desired range of ultrasonic sensor detection
int minDistance = 5;
int maxDistance = 50;
// time it takes for sound to travel from the sensor to an object and back
long duration;
// distance of object from sensor 
int distance;

// https://docs.arduino.cc/learn/electronics/servo-motors
// include Servo library
#include <Servo.h>
// create Servo object
Servo myServo;

void setup() {
  // neopixel setup
  strip.begin(); 
  strip.show();
  // ultrasonic sensor setup
  pinMode(trigPin, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(echoPin, INPUT);
  // potentiometer setup
  pinMode(A0, INPUT);
  // servo setup
  myServo.attach(3);
  // initialize serial moniter
  Serial.begin(9600);
}

void loop() {
  // https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
  // https://www.youtube.com/watch?v=ZejQOX69K5M
  // ensure trigPin is clear
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // generate ultrasound wave from trigPin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // read duration of echo from echoPin
  duration = pulseIn(echoPin, HIGH);
  // distance is the duration multiplied by velocity of sound waves
    // divided by 2 because it is an echo (derived from s=v*t)
  distance = duration * 0.034/2;

  // check values in serial monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // map R val to ultrasonic sensor
  rVal = map(distance, maxDistance, minDistance, 0, 255);
  // map B val to ultrasonic sensor
  bVal = map(distance, minDistance, maxDistance, 0, 255);
  
  // check if object is within range
  if( (distance >= minDistance) && (distance <= maxDistance) ) {
    Serial.println("OBSTACLE WITHIN RANGE");
    //iterate through the LED strip to set the color then show
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, rVal, 0, bVal); 
        strip.show();
     }
  }

  // get potentiometer value
  int potentVal = analogRead(A0);
  Serial.print("Potentiometer: ");
  Serial.println(potentVal);
  
  // https://www.tinkercad.com/things/5i8kxJ67uJR-copy-of-arduino-uno-tutorial-3-servo-motor-project/editel?tenant=circuits
  // map servo motor speed to potentiometer
  int servoSpeed = map(potentVal, 0, 1023, 10, 0);
  
  for (int servoPos = 0; servoPos <= 179; servoPos += 1) {
    myServo.write(servoPos);
    delay(servoSpeed);
  }
  for (int servoPos = 179; servoPos >= 0; servoPos -= 1) {
    myServo.write(servoPos);
    delay(servoSpeed);
  }

  
}
