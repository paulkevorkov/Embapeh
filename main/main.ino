#include <ezButton.h>

#define VRY_PIN  A1 // Arduino pin connected to VRX pin
#define VRX_PIN  A0 // Arduino pin connected to VRY pin
#define SW_PIN   2  // Arduino pin connected to SW  pin
#define AL1 5  // Motor A pins
#define AL2 6
#define AR1 11 // Motor B pins
#define AR2 10

#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    550
#define DOWN_THRESHOLD  450

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

ezButton button(SW_PIN);

// controller
int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis
int bValue = 0; // To store value of the button

// motors
int incomingByte = 0; // for incoming serial data

void setup() {
  Serial.begin(9600) ;
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  
  pinMode(AL1, OUTPUT);
  pinMode(AL2, OUTPUT);
  pinMode(AR1, OUTPUT);
  pinMode(AR2, OUTPUT);

  digitalWrite(AL1, LOW);
  digitalWrite(AL2, LOW);
  digitalWrite(AR1, LOW);
  digitalWrite(AR2, LOW);
  
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  Serial.println("select direction of movement");
  Serial.println("1.forward");
  Serial.println("2.backward");
  Serial.println("3.stop");
}


int  input = 0;
void forward(int x, int y) {          //function of forward 
  analogWrite(AL1, y);
  analogWrite(AL2, 0);
  analogWrite(AR1, y);
  analogWrite(AR2, 0);
}

void backward(int x, int y) {         //function of backward
  analogWrite(AL1, 0);
  analogWrite(AL2, abs(y));
  analogWrite(AR1, 0);
  analogWrite(AR2, abs(y));
}

void stop() {              //function of stop
  digitalWrite(AL1, LOW);
  digitalWrite(AL2, LOW);
  digitalWrite(AR1, LOW);
  digitalWrite(AR2, LOW);
}

int command = COMMAND_NO;

void loop() {
  button.loop(); // MUST call the loop() function first

  // read analog X and Y analog values
  xValue = 1023 - analogRead(VRX_PIN);
  yValue = 1023 - analogRead(VRY_PIN);

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

  command = COMMAND_NO;
  // check left/right commands
  if (xValue < LEFT_THRESHOLD)
    command = command | COMMAND_LEFT;
  else if (xValue > RIGHT_THRESHOLD)
    command = command | COMMAND_RIGHT;

  // check up/down commands
  if (yValue > UP_THRESHOLD)
    command = command | COMMAND_UP;
  else if (yValue < DOWN_THRESHOLD)
    command = command | COMMAND_DOWN;

  // NOTE: AT A TIME, THERE MAY BE NO COMMAND, ONE COMMAND OR TWO COMMANDS

  // print command to serial and process command
  if (command & COMMAND_LEFT) {
    Serial.println("COMMAND LEFT");
    // TODO: add your task here
  }

  if (command & COMMAND_RIGHT) {
    Serial.println("COMMAND RIGHT");
    // TODO: add your task here
  }

  if (command & COMMAND_UP) {
    Serial.println("COMMAND UP");
    // TODO: add your task here
  }

  if (command & COMMAND_DOWN) {
    Serial.println("COMMAND DOWN");
    // TODO: add your task here
  }

  delay(50);

  // send data only when you receive data:
  // if (Serial.available() > 0) {
  //   // read the incoming byte:
  //   incomingByte = Serial.read();
  //   input = incomingByte - 48; //convert ASCII code of numbers to 1,2,3

  // switch (input) { 
  //   case 1:         // if input=1 ....... motors turn forward
  //     forward();
  //     break;
  //   case 2:         // if input=2 ....... motors turn backward
  //     backward();
  //     break;
  //   case 3:         // if input=1 ....... motors turn stop
  //     stop();
  //     break;
  // }


  if(command & COMMAND_UP) {
    forward(xValue, yValue - 500);
  } else if(command & COMMAND_DOWN) {
    backward(xValue, 500 - yValue);
  } else {
    stop();
    Serial.println("stopping");
  }



  delay(200);
  input=0;
  
}




