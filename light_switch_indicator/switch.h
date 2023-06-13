#include "mbed.h"
#include "light.h"

extern DigitalIn but1;
extern DigitalIn but2;
extern DigitalIn but3;
extern int score;
extern Timer timer;

void switchIndicator(int noteDuration, float speed);
