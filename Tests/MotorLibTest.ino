#include <AFMotor.h>
AF_DCMotor m1(1);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly
m1.setSpeed(255);
m1.run(FORWARD);
delay(1000);
m1.setSpeed(128);
m1.run(FORWARD);
delay(1000);
m1.setSpeed(50);
m1.run(FORWARD);
delay(1000);
m1.setSpeed(128);
m1.run(BACKWARD);
delay(1000);
m1.setSpeed(255);
m1.run(BACKWARD);
delay(1000);


}
