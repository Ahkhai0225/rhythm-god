#include "C12832.h"
#include "mbed.h"
#include "musicplayer.h"

// PwmOut speaker(p26);
AnalogIn pot1(p19);
DigitalIn joystickCenter(p14);
C12832 lcd(p5, p7, p6, p8, p11);
BusIn joy(p13, p16);
BusOut leds(LED1, LED2, LED3, LED4);
Serial pc(USBTX, USBRX);

int main() {
    int i = 0;
    int dimX = 120;
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf("welcome to rhythm-god game");
    ThisThread::sleep_for(2 * 100);
    int flag = 0;
    int score = 0;
    int difficulty = 0; // 0 - Easy, 1 - Medium, 2 - Hard
    lcd.cls();
    musicplayer speaker(p26);
    while (1) {
    // CONDITION FOR CHECKING FOR THE center joystick
        if (joystickCenter) {
            flag = 100;
            // Perform an action based on the selected difficulty
            if (difficulty == 0) {
                // Easy selected
                speaker.selectSong(1);
            } 
            else if (difficulty == 1) {
                speaker.selectSong(2);
                pc.printf("Score: %d", scoree);
                // Medium selected
            } 
            else if (difficulty == 2) {
                speaker.selectSong(3);
                // Hard selected
            }
            flag = 0;
        } 
        else {
            if (flag == 0) {
                leds = joy;
                // moving arrow right
                if (joy == 0x2) {
                    pc.printf("Hello");
                    // Update difficulty based on the arrow's position
                    if (i == 96) {
                        i = 0;
                        difficulty = 0; // Easy
                    } 
                    else if (i == 0) {
                        i = 42;
                        difficulty = 1; // Medium
                    } 
                    else if (i == 42) {
                        i = 96;
                        difficulty = 2; // Hard
                    }
                    lcd.cls();
                }
                // moving arrow left
                else if (joy == 0x1) {
                    // Update difficulty based on the arrow's position
                    pc.printf("Hi");
                    if (i == 0) {
                        i = 96;
                        difficulty = 2; // Hard
                    } 
                    else if (i == 96) {
                        i = 42;
                        difficulty = 1; // Medium
                    } 
                    else if (i == 42) {
                        i = 0;
                        difficulty = 0; // Easy
                    }
                    lcd.cls();
                }
            }
        }
        if (flag == 0) {
            lcd.locate(i, 0);
            lcd.printf("->");
            lcd.locate(10, 0);
            lcd.printf("Easy");

            lcd.locate(52, 0);
            lcd.printf("Medium");

            lcd.locate(106, 0);
            lcd.printf("Hard");

            lcd.locate(0, 22);
            lcd.printf("%d", score);
            ThisThread::sleep_for(2 * 10);
        }
    }
}