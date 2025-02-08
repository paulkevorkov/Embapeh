#include <ezButton.h>

#define VRX_PIN  A1 // Arduino pin connected to VRX pin
#define VRY_PIN  A0 // Arduino pin connected to VRY pin
#define SW_PIN   2  // Arduino pin connected to SW  pin

#define AL1 5  // Motor A pins
#define AL2 6
#define AR1 10 // Motor B pins
#define AR2 11

int incomingByte = 0; // for incoming serial data

ezButton button(SW_PIN);

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis
int bValue = 0; // To store value of the button

void setup() {
  pinMode(AL1, OUTPUT);
  pinMode(AL2, OUTPUT);
  pinMode(AR1, OUTPUT);
  pinMode(AR2, OUTPUT);

  digitalWrite(AL1, LOW);
  digitalWrite(AL2, LOW);
  digitalWrite(AR1, LOW);
  digitalWrite(AR2, LOW);
  
  Serial.begin(9600) ;
  button.setDebounceTime(50); // set debounce time to 50 milliseconds

  Serial.println("select direction of movement");
  Serial.println("1.forward");
  Serial.println("2.backward");
  Serial.println("3.stop");
}

int  input = 0;
void loop() {
  
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    input = incomingByte - 48; //convert ASCII code of numbers to 1,2,3

    switch (input) { 
    case 1:         // if input=1 ....... motors turn forward
      forward();
      break;
    case 2:         // if input=2 ....... motors turn backward
      backward();
      break;
    case 3:         // if input=1 ....... motors turn stop
      Stop();
      break;
    }
  delay(200);
  input=0;
  }
  
  button.loop(); // MUST call the loop() function first

  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  // Read the button value
  bValue = button.getState();

  if (button.isPressed()) {
    Serial.println("The button is pressed");
    // TODO do something here
  }

  if (button.isReleased()) {
    Serial.println("The button is released");
    // TODO do something here
  }

  // print data to Serial Monitor on Arduino IDE
  Serial.print("x = ");
  Serial.print(xValue);
  Serial.print(", y = ");
  Serial.print(yValue);
  Serial.print(" : button = ");
  Serial.println(bValue);

  delay(50);
}

void forward() {          //function of forward 
  analogWrite(AL1, 120);
  analogWrite(AL2, 0);
  analogWrite(AR1, 120);
  analogWrite(AR2, 0);
}

void backward() {         //function of backward
  analogWrite(AL1, 0);
  analogWrite(AL2, 120);
  analogWrite(AR1, 0);
  analogWrite(AR2, 120);
}

void Stop() {              //function of stop
  digitalWrite(AL1, LOW);
  digitalWrite(AL2, LOW);
  digitalWrite(AR1, LOW);
  digitalWrite(AR2, LOW);
}
