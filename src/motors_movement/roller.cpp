#include "motors_movement/roller.h"
#include "vars.h"

/* Our PCB is 3.3V, the ESC uses 5V and has an onboard 5V/3A regulated output
To command the ESC we use a Sparkfun's 3.3V-5V board, which also does 5V-3.3V.
To PWM command the ESC we pass a PWM pin to the adapter board.
We use the same adapter board to adapt the ESC's internally regulated 5V to 3.3V.
Since the ESC is turned on (and outputs) only when the motors are turned on, we can detect when the ESC is turned on and needs the startup sequence*/

unsigned long t = 0;
unsigned long t1 = 0;

Roller::Roller(int pinPwm_, int pinSense_, int MIN_, int MAX_, int ARM_){
    pinPwm = pinPwm_;
    pinSense = pinSense_;
    MIN = MIN_;
    MAX = MAX_;
    ARM = ARM_;

    roller_armed = false;
    roller_arm_setup = false;
    roller_setup_phase = 99;

    roller_counter = 0;
    roller_speed = 0;
    
    pinMode(pinSense, INPUT_PULLUP);
    roller = new ESC(pinPwm, MIN, MAX, ARM);
}

void Roller::setup(){
    if(roller_setup_phase == 0){
        roller->arm();
        roller_setup_phase=1;
        roller_counter = 0;
        roller_armed = false;
    }else if(roller_setup_phase == 1){
        if(millis() - t1 > 1){
            t1 = millis();
            roller->speed(roller_counter);
            roller_counter++;
            if(roller_counter > 255) roller_setup_phase = 2;
        }
    }else if(roller_setup_phase == 2){
        if(millis() - t1 > 1){
            t1 = millis();
            roller->speed(roller_counter);
            roller_counter--;
            if(roller_counter <= 0) roller_setup_phase = 3;
        }
    }else if(roller_setup_phase == 3){
        roller_setup_phase = 4;
        roller_armed = true;
    }

    // DEBUG.print(roller_setup_phase);
    // DEBUG.print(" --- ");
    // DEBUG.println(roller_counter);

//   roller->arm();
//   delay(1000);
//   for(int i = MIN; i < MAX; i++){
//       roller->speed(i);
//       delay(1);
//   }
//   for(int i = MAX; i > MIN; i--){
//       roller->speed(i);
//       delay(1);
//   }
}

void Roller::update(){
    bool arm = digitalReadFast(pinSense);

    if(arm){
        if(!roller_arm_setup){
            roller_setup_phase = 0;
            roller_arm_setup = true;
            roller_armed = false;
        }
    }else{
        roller_armed = false;
        roller_arm_setup = false;
    }

    this->setup();

  if(millis() - t > 10 && roller_armed){
    roller->speed(roller_speed);
    t = millis();
  }
}

void Roller::speed(int speed_){
    if(roller_armed)
        roller_speed = speed_;
}