/*
 * Unlike our other sketch, we aren't using the joysticks to control
 * the arm in this sketch.  Instead, the arm will run on a loop that
 * we program.  Each individual motor movement is written sequentially
 * in the loop() function.
 * 
 * You can see how little code it takes to control servos when we're not
 * mapping inputs from analog joysticks.  You need to configure three
 * things to control servos: 
 * 1. Include the Servo.h library
 * 2. Create the Servo object using 'Servo <name>;' 
 * 3. Attach the servo object to a pin using '<name>.attach(pin)'
 * 
 * That's it!  Youre ready to write positions to your servo motors.  
 * The below loop will have your arm close the gripper, swing 120
 * degrees, lower istelf, and open the gripper.  Try your own program,
 * and see what you can make your robot arm pick up and move from
 * one point to another!
 * 
 */



#include <Servo.h>                     // include the Servo.h library

  Servo base;                          // create our five servo objects
  Servo armone;  
  Servo armtwo;  
  Servo armthree;  
  Servo gripper;  

void setup() {
  base.attach(6);                      // attach the five servos to their respective pins
  armone.attach(9);
  armtwo.attach(8);
  armthree.attach(7);
  gripper.attach(5);


  base.write(90);                      // Set all motor positions to 90 degrees at startup  
  delay(250); 
  armone.write(70); 
  delay(250);
  armtwo.write(90); 
  delay(250);
  armthree.write(90); 
  delay(250);
  gripper.write(90);           
  delay(1000); 


}

void loop() {     

     /* Write your servo motor sequence in this loop.
      * Try different values for the delays between Servo movement.
      * Lower values will speed up the arm, higher values will slow it down.
      */
      
  base.write(25);     
  delay(1000); 
  armone.write(70);
  delay(250);
  armtwo.write(110);
  delay(250);
  armthree.write(110);
  delay(250); 
  gripper.write(5);          
  delay(250); 
  armone.write(70);
  delay(250);
  armtwo.write(90);
  delay(250);
  armthree.write(90);
  delay(250);
  base.write(155);
  delay(250);
  armtwo.write(110);
  delay(250);
  armthree.write(110);
  delay(250); 
  gripper.write(90);              
  delay(1000);
}
