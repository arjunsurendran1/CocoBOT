// Full code with motor controlling, check ripeness of the coconut and cutting
#include <Servo.h>

const int RipeSensorPin = A0;   // Analog pin for color sensor
const int servoPin1 = 9;          // Digital pin 9 for servo motor
const int servoPin2 = 10;          // Digital pin 10 for servo motor
const int trigPin = 8;      // trig pin of Ultrasonic sensor
const int echoPin = 12;     // Echo pin of Ultrasonic sensor
const int ripeThreshold = 500;  // Adjust this value based sensor readings

Servo cuttingServo;  // coconut harvesting servo
Servo RipenessServo;  //coconut ripeness checking servo
long duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(RipeSensorPin, INPUT);
  cuttingServo.attach(servoPin1);  
    RipenessServo.attach(servoPin2);
  pinMode(trigPin, OUTPUT);         

  pinMode(echoPin, INPUT);          
}

void loop() {
  
  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);    

  delayMicroseconds(10);

  duration = pulseIn(echoPin, HIGH); 
  
  distance = duration / 58.2;   // convert to distance
  
  Serial.println("distance: ");

  Serial.println(distance);

  delay(10);
  

  if (distance <= 10) { //if the cocobot reaches top of the coconut tree then check the coco nut ripeness
 checkRipenessAndCut();

  }

}

void checkRipenessAndCut() {
    Serial.println("checkRipenessAndCut");

    RipenessServo.write(0);  // Set servo angle to 90 degrees
    delay(2000);
   int RipeSensorReading = analogRead(RipeSensorPin); //reading the water content in the coconut husk
  Serial.print("RipeSensorReading: ");
  Serial.println(RipeSensorReading);

  if (RipeSensorReading < ripeThreshold) {
      Serial.println("Coconut is ready to ripen!");

    performCuttingAction();
   }
  Serial.println("Coconut is not ready to ripen!");
  RipenessServo.write(180);   // Set servo angle to 0 degrees (reset position)
  

  delay(5000);  // Wait for 5 seconds before checking the next coconut
}


void performCuttingAction() {
  Serial.println("Performing cutting action.");

  // Adjust the servo angle to simulate the cutting action
  cuttingServo.write(90);  // Set servo angle to 90 degrees
  delay(2000);             // Keep the servo active for 2 seconds
  cuttingServo.write(0);   // Set servo angle to 0 degrees (reset position)
  
}
