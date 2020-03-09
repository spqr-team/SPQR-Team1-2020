#include "test_menu.h"
#include "sensors/data_source_ball.h"
#include "sensors/data_source_bno055.h"
#include "sensors/data_source_bt.h"
#include "sensors/data_source_camera_conicmirror.h"
#include "sensors/linesys_camera.h"
#include "sensors/linesys_2019.h"
#include "sensors/sensors.h"
#include "motors_movement/motor.h"
#include "motors_movement/drivecontroller.h"
#include "position/positionsys_camera.h"
#include "strategy_roles/game.h"
#include "strategy_roles/games.h"
#include "behaviour_control/data_source.h"

void TestMenu :: testMenu(){
    DEBUG.println();
    DEBUG.println("Welcome to the test menu c:");
    DEBUG.println("Set the baudrate to 9600 & NO LINE ENDING");
    DEBUG.println("Hit correspondent key (1-->8) to execute and press ENTER");
    DEBUG.println("Hit '0' to exit test menu");
    DEBUG.println();

    DEBUG.println("Test Menu: ");
    DEBUG.println("0)Exit test menu and start playing");
    DEBUG.println("1)Ball test");
    DEBUG.println("2)IMU test");
    DEBUG.println("3)Motors test");
    DEBUG.println("4)Recenter");
    DEBUG.println("5)BT test");
    DEBUG.println("6)Camera test");
    DEBUG.println("7)Line Sensors camera test");
    DEBUG.println("8)Line Sensors test");
    do{
        testNum = DEBUG.read();
        DEBUG.println();
        DEBUG.println("Test:");
        DEBUG.println(testNum);
        DEBUG.println(" ");
        if (testNum == '0') DEBUG.println("EXIT TEST MENU");
        else if (testNum == '1') DEBUG.println("Ball test, turn the ball on and turn it around the robot");
        else if (testNum == '2') DEBUG.println("IMU test, keep the robot still and on a flat surface");
        else if (testNum == '3') DEBUG.println("Motor test, turn on SW_MOTORI and keep the robot at eye level");
        else if (testNum == '4') DEBUG.println("Recenter, turn both SWS on and tilt the robot");
        else if (testNum == '5') DEBUG.println("BT test, pair to BT");
        else if (testNum == '6') DEBUG.println("Camera Test");
        else if (testNum == '7') DEBUG.println("Line Sensors camera test, turn on SW_ELETT");
        else if (testNum == '8') DEBUG.println("Line Sensors test, turn on SW_ELETT");
    else {
      DEBUG.println("UNKNOWN COMMAND");
      flagtest = false;
    }
  }  while (DEBUG.available() > 0);
    do{
        switch(testNum){
            case '0':
                DEBUG.println("Exiting test menu, may the odds be in your favor c:");
                flagtest = false;
                return;
            break;
            case '1':
                ball->test();
                delay(TEST_DELAY);
            break;
            case '2':
                compass->test();
                delay(TEST_DELAY);
            break;
            case '3':
                drive->m1->test();
                drive->m2->test();
                drive->m3->test();
                drive->m4->test();
            break;
            case '4':
                drive->drive(0,0,0);
            break;
            case '5':
                bt->test();
            break;
            case '6':
                camera->test();
            break;
            case '7':
            case '8':
                DEBUG.println("To do Line Sensors test, decide the role first");
                DEBUG.println("1)Keeper");
                DEBUG.println("2)Goalie");
                currentRole = DEBUG.read();
                switch(currentRole){
                    case '1':
                        (goalie->ls)->test();
                    break;
                    case '2':
                        (keeper->ls)->test();
                    break;
                    default:
                        DEBUG.println("INVALID ROLE");
                    break;
                }
            break;
            default:
            break;
        }
    } while (DEBUG.available() == 0);
}