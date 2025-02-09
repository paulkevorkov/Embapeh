#include <ezButton.h>
#include <Servo.h>

#define VLX_PIN  A0 // Arduino pin connected to VRX pin
#define VLY_PIN  A1 // Arduino pin connected to VRY pin
#define SWL_PIN   2  // Arduino pin connected to SW  pin

#define VRX_PIN  A3
#define VRY_PIN  A2
#define SWR_PIN   4

#define AL1 5  // Motor A pins
#define AL2 6
#define AR1 11 // Motor B pins
#define AR2 10

#define SERVO_PIN 9   // servo
Servo servo;


int incomingByte = 0; // for incoming serial data

ezButton leftButton(SWL_PIN);
ezButton rightButton(SWR_PIN);

int lyValue = 0; // To store value of the X axis
int ryValue = 0; // To store value of the Y axis
int bValue = 0; // To store value of the button

int leftSpeed = 0;
int rightSpeed = 0;

int switchSpeed = 0;  // 0 means fast mode, 1 means slow mode
int maxMapValue = 0; //255 is fast mode, 120 is slow mode

void setup() {
  pinMode(AL1, OUTPUT);
  pinMode(AL2, OUTPUT);
  pinMode(AR1, OUTPUT);
  pinMode(AR2, OUTPUT);

  digitalWrite(AL1, LOW);
  digitalWrite(AL2, LOW);
  digitalWrite(AR1, LOW);
  digitalWrite(AR2, LOW);
  
  servo.attach(SERVO_PIN);   // assigns PWM pin to the servo object

  Serial.begin(9600) ;
  leftButton.setDebounceTime(30); // set debounce time to 50 milliseconds
  rightButton.setDebounceTime(30);
  Serial.println("Starting");

}

int defaultAngle = 100;  
int kickAngle = 180;
long timer = millis();
long startTime = millis();
void loop() {
  leftButton.loop(); // MUST call the loop() function first
  rightButton.loop();

  timer = millis();

  if (rightButton.isPressed()){
    startTime = millis();
    servo.write(kickAngle);
    //Serial.println("Right button is pressed");
    //Serial.print("Timer: "); Serial.println(timer);
    //Serial.print("startTime: "); Serial.println(startTime);
  }
  if (timer - startTime >= 500){
    servo.write(defaultAngle);
  }

  // Left button status for speed
  if (leftButton.isPressed()) {
    Serial.println("Left button is pressed");
    switchSpeed = !switchSpeed;
  }

  if (switchSpeed) {
    maxMapValue = 180;
  } else {
    maxMapValue = 255;
  }

  // read analog X and Y analog values
  lyValue = 1023 - analogRead(VLY_PIN);
  ryValue = 1023 - analogRead(VRY_PIN);

  /*Serial.print("Left joystick: ");
  Serial.println(lyValue);

  Serial.print("Right joystick: ");
  Serial.println(ryValue);
  Serial.println();*/

  //rxValue = 1023 - analogRead(VRX_PIN);
  //ryValue = 1023 - analogRead(VRY_PIN);

  
  // left joystick
  if (lyValue > 550) {
    leftSpeed = map(lyValue, 550, 1023, 0, maxMapValue);
    analogWrite(AL1, leftSpeed);
    analogWrite(AL2, 0);
  }
  else if (lyValue < 470) {
    leftSpeed = map(lyValue, 470, 0, 0, maxMapValue);
    analogWrite(AL1, 0);
    analogWrite(AL2, leftSpeed);
  }
  else {
    leftSpeed = 0;
    analogWrite(AL1, 0);
    analogWrite(AL2, 0);
  }

  // right joystick
  if (ryValue > 550) {
    rightSpeed = map(ryValue, 550, 1023, 0, maxMapValue);
    analogWrite(AR1, rightSpeed);
    analogWrite(AR2, 0);
  }
  else if (ryValue < 470) {
    rightSpeed = map(ryValue, 470, 0, 0, maxMapValue);
    analogWrite(AR1, 0);
    analogWrite(AR2, rightSpeed);
  }
  else {
    rightSpeed = 0;
    analogWrite(AR1, 0);
    analogWrite(AR2, 0);
  }
  
  delay(50);
}


