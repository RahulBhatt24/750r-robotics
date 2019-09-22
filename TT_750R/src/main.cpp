/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Nitin                                            */
/*    Created:      Sun Jul 14 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "config.h"
#include "robot.h"
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here
vex::controller  primary    (vex::controllerType::primary);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
vex::mutex driveMutex;
Robot robot(Brain);

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {
  vex::motor fL = vex::motor (D_MOTOR_FL,false);
    vex::motor bL = vex::motor (D_MOTOR_BL,false);
    vex::motor fR = vex::motor (D_MOTOR_FR,false);
    vex::motor bR = vex::motor (D_MOTOR_BR,false);
    vex:: motor magazine = ves::motor (MAG, false);4

    robot.driveFor(fL,720);
    robot.driveFor(fR,720);
    robot.driveFor(bL,720);
    robot.driveFor(bR,720);

    robot.turnLeft();
    robot.turnRight();

    robot.reverseFor(fL,-720);
    robot.reverseFor(fR,-720);
    robot.reverseFor(bL,-720);
    robot.reverseFor(bR,-720);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol( void ) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................
    robot.drive(primary.Axis2.position());
    
    if(primary.Axis1.position()>50)
      robot.strafe(-1);
    else if (primary.Axis1.position()<-50)
      robot.strafe(1);
    else
      robot.strafe(0);

    if(primary.ButtonR1.pressing())
      robot.turnRight();
    else if(primary.ButtonR2.pressing())
      robot.turnLeft();
    
    if(primary.ButtonY.pressing())
    {
      //Button subject to change
      robot.magazineForward();
    }
    else if(primary.ButtonX.pressing())
    {
      //Button subject to change
      robot.magazineBackward();
    }

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}
