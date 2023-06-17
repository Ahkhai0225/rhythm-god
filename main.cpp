#include "C12832.h"
#include "mbed.h"
#include "musicplayer.h"
#include "switch.h"

DigitalIn joystickCenter(p14);
C12832 lcd(p5, p7, p6, p8, p11);
BusIn joy(p13, p16);
Serial pc(USBTX, USBRX);
PwmOut servo(p22);

int main() {
    int i = 0;
    int dimX = 120;
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf("welcome to rhythm-god game");
    ThisThread::sleep_for(2 * 100);
    int flag = 0;
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
                lcd.cls();
                lcd.locate(0, 3);
                lcd.printf("Now Playing Pink Panther...");
                servo.period_ms(20);
                servo.pulsewidth_ms(1);
                speaker.timerStart();
                servo.write(0);
                speaker.selectSong(1);
                servo.period_ms(20);
                servo.pulsewidth_ms(2);
            } 
            else if (difficulty == 1) {
                // Medium selected
                lcd.cls();
                lcd.locate(0, 3);
                lcd.printf("Now Playing Harry Potter...");
                servo.period_ms(20);
                servo.pulsewidth_ms(1);
                speaker.timerStart();
                servo.write(0);
                speaker.selectSong(2);
                servo.period_ms(20);
                servo.pulsewidth_ms(2);
            } 
            else if (difficulty == 2) {
                // Hard selected
                lcd.cls();
                lcd.locate(0, 3);
                lcd.printf("Now Playing Fur Elise...");
                servo.period_ms(20);
                servo.pulsewidth_ms(1);
                speaker.timerStart();
                servo.write(0);
                speaker.selectSong(3);
                servo.period_ms(20);
                servo.pulsewidth_ms(2);
            }
            flag = 0;
            lcd.cls();
            lcd.locate(0, 3);
            lcd.printf("Final Score: %d", score);
            ThisThread::sleep_for(5 * 100);
            lcd.cls();
        } 
        else {
            if (flag == 0) {
                // moving arrow right
                if (joy == 0x2) {
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
            ThisThread::sleep_for(2 * 10);
        }
    }
}