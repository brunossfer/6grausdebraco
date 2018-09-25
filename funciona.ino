/*
 Try this test sketch with the Servo library to see how your
 servo responds to different settings, type a position
 (0 to 180) or if you type a number greater than 200 it will be
 interpreted as microseconds(544 to 2400), in the top of serial
 monitor and hit [ENTER], start at 90 (or 1472) and work your
 way toward zero (544) 5 degrees (or 50 micros) at a time, then
 toward 180 (2400).
*/
#include <Servo.h>
Servo cintura; 
Servo ombro;
Servo cotovelo;
Servo pulsoSD;
Servo pulsoG;
Servo garra;

void setup() {
  // initialize serial:
  Serial.begin(9600); //set serial monitor baud rate to match
  cintura.write(10);
  ombro.write(100);
  cotovelo.write(110);
  pulsoSD.write(90);
  pulsoG.write(150);
  garra.write(100);
  
  cintura.attach(3);
  ombro.attach(5);
  cotovelo.attach(7);
  pulsoSD.attach(9);
  pulsoG.attach(11);
  garra.attach(13);
  prntIt();
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int pos = Serial.parseInt();
    pos = constrain(pos, 0, 2400);
    pulsoSD.write(pos);
    prntIt();
  }
}
void prntIt()
{
  Serial.print("  degrees = ");
  Serial.print(pulsoSD.read());
  Serial.print("\t");
  Serial.print("microseconds =  ");
  Serial.println(pulsoSD.readMicroseconds());
} 

