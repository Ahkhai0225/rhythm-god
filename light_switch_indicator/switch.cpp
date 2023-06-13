#include "mbed.h"
#include "light.h"
#include "main.cpp"

DigitalIn but1(p23);
DigitalIn but2(p24);
DigitalIn but3(p25);

int a = 0;
Timer timer;

void switchIndicator(int noteDuration, float speed)
{
    timer.start();
        while (float(timer.read_ms())/10 < noteDuration*speed){
            if(ledrow3.read() == 0b100 && but1 == 1 && a == 0) {
                score++;
                a++;
                updateScore();
            }
            else if(ledrow3.read() == 0b010 && but2 == 1 && a == 0) {
                score++;
                a++;
                updateScore();
            }
            else if(ledrow3.read() == 0b001 && but3 == 1 && a == 0) {
                score++;
                a++;         
                updateScore();         
            }
        }
        timer.stop();
        timer.reset();
        a = 0;
}