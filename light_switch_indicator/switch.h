#include "mbed.h"
#include "light.h"
#include "C12832.h"

extern DigitalIn but1;
extern DigitalIn but2;
extern DigitalIn but3;
extern int score;
extern Timer timer;
extern C12832 lcd;

void switchIndicator(int noteDuration, float speed);
float showScore(int score);