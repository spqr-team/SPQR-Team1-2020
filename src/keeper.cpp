#include "keeper.h"

Keeper::Keeper(){

}

void Keeper::keeper(){
    digitalWrite(LED_Y, HIGH);
    drive->prepareDrive(0, 0, 0);
    drive->drive(0, 0, 0);
}

/* void Keeper::keeperGoalie(){
    to be implemented
} */