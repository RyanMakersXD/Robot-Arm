#include <Servo.h>                     //  This includes the servo library in our sketch.  Libraries like this save programmers
                                       //  A LOT of time and headaches.

Servo base;                            //  These five lines establish the servo motor objects in our sketch
Servo armone;  
Servo armtwo;  
Servo armthree;  
Servo gripper;  

int joy1x = A1;                        //  Assign the value 'A1' to the variable 'joy1x'
int joy1y = A0;                        //  Assign the value 'A0' to the variable 'joy1y'
int joy2x = A3;                        //  Assign the value 'A3' to the variable 'joy2x'
int joy2y = A2;                        //  Assign the value 'A2' to the variable 'joy2y'
int joy1sw = 2;                        //  Assign the value '2' to the variable 'joy1sw'

int swivel = 0;                        //  This variable stores the value for our base servo position
int arms = 0;                          //  This variable stores the value for our arm servo position
int motor = 0;                         //  This variable stores the value for which motor is selected

int j1x;                               //  Variable to store analog value for joystick 1 x-axis
int j1y;                               //  Variable to store analog value for joystick 1 y-axis
int j2x;                               //  Variable to store analog value for joystick 2 x-axis
int j2y;                               //  Variable to store analog value for joystick 2 y-axis

int buttonState;                        // the current reading from the input pin
int lastButtonState = HIGH;             // the previous reading from the input pin
unsigned long lastDebounceTime = 0;     // the last time the output pin was toggled
unsigned long debounceDelay = 100;      // the debounce time; increase if the output flickers

void setup() {                          // the setup() function runs once when the Arduino boots up
  base.attach(6);                       // Attach the base servo to pin 6
  armone.attach(9);                     // Attach the armone servo to pin 9
  armtwo.attach(8);                     // Attach the armtwo servo to pin 8
  armthree.attach(7);                   // Attach the armthree servo to pin 7
  gripper.attach(5);                    // Attach the gripper servo to pin 5

  pinMode(joy1x, INPUT);                // Configure joystick 1 x-axis pin as an INPUT
  pinMode(joy1y, INPUT);                // Configure joystick 1 y-axis pin as an INPUT
  pinMode(joy2x, INPUT);                // Configure joystick 2 x-axis pin as an INPUT
  pinMode(joy2y, INPUT);                // Configure joystick 2 y-axis pin as an INPUT
  pinMode(joy1sw, INPUT);               // Configure joystick switch pins as an INPUT

  base.write(70);                       // At the end of the setup function, set all five motors to 90 degrees
  delay(250);                           // with quarter-second delays between each motor write
  armone.write(90); 
  delay(250);
  armtwo.write(90); 
  delay(250);
  armthree.write(90); 
  delay(250);
  gripper.write(90);           
  delay(1000); 

//  Serial.begin(9600);                 // Begin serial communication with the computer, comment out if not debugging
}

void loop() {                           // the loop() runs over and over continuously, until the Arduino is powered down
  joypoll();                            // This function gets the current analog values from the joysticks
//joyreport();                          // This function writes the current joystick values to the serial monitor, comment out if not debugging
  joymap();                             // This function maps the analog values to the 0-180 degree values for the servos
  changeMotor();                        // This function changes which motor is selected to move with the joystick button
  motorWrite();                         // With the correct motor selected, this function writes the position to the servo
delay(70);
}

void joypoll(){                         // This function stores the joystick readings in variables
  j1x = analogRead(joy1x);              // Read the value at pin 'joy1x' and store it in the variable 'j1x'
  j1y = analogRead(joy1y);              // Read the value at pin 'joy1y' and store it in the variable 'j1y'
  j2x = analogRead(joy2x);              // Read the value at pin 'joy2x' and store it in the variable 'j2x'
  j2y = analogRead(joy2y);              // Read the value at pin 'joy2y' and store it in the variable 'j2y'
}

/*
void joyreport(){                       // This function is for debugging purposes, comment out if not debugging.
  Serial.print("J1X: ");                // This function continuously writes the current joystick positions to Serial Monitor
  Serial.print(j1x);
  Serial.print(" | J1Y: ");
  Serial.print(j1y);
  Serial.print(" | J2X: ");
  Serial.print(j2x);
  Serial.print(" | J2Y: ");
  Serial.println(j2y);
}
*/

void joymap() {                         // This function takes the 0-1023 values from the joystick, and maps them
  swivel = map(j1x, 0, 1023, 0, 180);   // to the 0-180 degree values for the position of the servos.  The 'swivel' value
  arms = map(j2y, 0, 1023, 0, 180);     // is for the base motor, and the 'arms' value is for the arms and gripper motors.
}

void motorWrite() {                     // This function writes the current mapped joystick value to the selected motor
base.write(swivel);                     // Write the 'swivel' value to the base motor, no matter which motor is selected
 if (motor == 1){                       // If motor 1 is selected...
  motor = 2;                            // ...then set the motor value to 2, bypassing this first value.  Motor 1 is the base
 }                                      // which already has been written to at the beginning of this funcion
 if (motor == 2){                       // if motor 2 is selected...
  armone.write(arms);                   // ...then write the current 'arms' value to the first arm motor
 }
 if (motor == 3){                       // If motor 3 is selected...
  armtwo.write(arms);                   // ...then write the current 'arms' value to the second arm motor
 }
 if (motor == 4){                       // If motor 4 is selected...
  armthree.write(arms);                 // ...then write the current 'arms' value to the third arm motor
 }
 if (motor == 5){                       // If motor 5 is selected...
    if (arms > 90){                     // ...then limit the range of position values to 0-90.  This is the gripper motor.
    arms = 90;                          // If we tried to position this motor at >90 degrees, then the gripper arms
  }                                     // will fall off of the gripper motor.
  gripper.write(arms);                  // after limiting the value to <90, write this value to the gripper motor
 }
}

/* 
Below this comment is the 'changeMotor' function.  This function exists to increment
our 'motor' variable when the joystick button is pressed, and to act as a debounce
for our pushbutton on the joysticks.  Without the code in this function, the
Arduino would have a difficult time telling when the button is pressed and released. 
*/

void changeMotor() {    
  int reading = digitalRead(joy1sw);    // read the state of the switch into a local variable:
                                        // check to see if you just pressed the button
                                        // (i.e. the input went from LOW to HIGH), and you've waited long enough
                                        // since the last press to ignore any noise:
                                        
  if (reading != lastButtonState) {     // If the switch changed, due to noise or pressing:
    lastDebounceTime = millis();        // reset the debouncing timer
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
                                        // whatever the reading is at, it's been there for longer than the debounce
                                        // delay, so take it as the actual current state:  
    if (reading != buttonState) {       // if the button state has changed:
      buttonState = reading;
      if (buttonState == LOW) {         // If the button is pressed
        motor = motor + 1;              // increase the 'motor' variable by 1
        if (motor > 5) {                // If the 'motor' variable is greater than 5
          motor = 1;                    // then set the 'motor' variable back to 1
        }
      }
    }
  }
  lastButtonState = reading;             // save the reading. Next time through the loop, it'll be the lastButtonState:
}
