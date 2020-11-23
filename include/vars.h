#pragma once
#define DEBUG Serial

#ifdef VARS
#define extr
#else
#define extr extern
#endif

#define GLOBAL_SPD_MULT 1.0

/*SWS and LEDS are to be tested and implemented in the code. 
the new setup is the one commented, leds have to be written 
in the 32U4 code*/

#define LED_R 20
#define LED_Y 17
#define LED_G 13

#define BUZZER 30
#define SWITCH_SX 28
#define SWITCH_DX 29

/*#define BUZZER 6
#define SWITCH_1 39
#define SWITCH_2 38
#define SWITCH_3 33*/

extr float sins[360], cosins[360];
