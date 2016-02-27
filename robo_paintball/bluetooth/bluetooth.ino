/*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#include <AFMotor.h>

AF_DCMotor motor1(1); 
AF_DCMotor motor2(4);

USB Usb;
BTD Btd(&Usb); 
//PS3BT PS3(&Btd);
//00:19:86:00:0F:F9
PS3BT PS3(&Btd, 0x00, 0x19, 0x86, 0x00, 0x0F, 0xF9);

bool printTemperature, printAngle;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial);
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

  motor1.setSpeed(255); 
  motor2.setSpeed(255); 
}
void loop() {
  Usb.Task();

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117){
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS3.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));

      motor1.run(FORWARD); 
      motor2.run(BACKWARD); 
    } 
    else {
      motor1.run(RELEASE); 
      motor2.run(RELEASE);
    }

    if(PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\tRightHatX: "));
      Serial.print(PS3.getAnalogHat(RightHatX));
      Serial.print(F("\tRightHatY: "));
      Serial.print(PS3.getAnalogHat(RightHatY));
    } 

    // Analog button values can be read from almost all buttons
    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      if (PS3.PS3Connected) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
      }
    }

    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      //      if (PS3.getButtonClick(TRIANGLE)) {
      //        Serial.print(F("\r\nTraingle"));
      //        PS3.setRumbleOn(RumbleLow);
      //      }
      //      if (PS3.getButtonClick(CIRCLE)) {
      //        Serial.print(F("\r\nCircle"));
      //        PS3.setRumbleOn(RumbleHigh);
      //      }
      //      if (PS3.getButtonClick(CROSS)){
      //        Serial.print(F("\r\nCross"));
      //      }
      //      if (PS3.getButtonClick(SQUARE)){
      //        Serial.print(F("\r\nSquare"));
      //      }
      //      if (PS3.getButtonClick(UP)) {
      //        Serial.print(F("\r\nUp"));
      //        if (PS3.PS3Connected) {
      //          PS3.setLedOff();
      //          PS3.setLedOn(LED4);
      //        }
      //      }
      //      if (PS3.getButtonClick(RIGHT)) {
      //        Serial.print(F("\r\nRight"));
      //        if (PS3.PS3Connected) {
      //          PS3.setLedOff();
      //          PS3.setLedOn(LED1);
      //        }
      //      }
      //      if (PS3.getButtonClick(DOWN)) {
      //        Serial.print(F("\r\nDown"));
      //        if (PS3.PS3Connected) {
      //          PS3.setLedOff();
      //          PS3.setLedOn(LED2);
      //        }
      //      }
      //      if (PS3.getButtonClick(LEFT)) {
      //        Serial.print(F("\r\nLeft"));
      //        if (PS3.PS3Connected) {
      //          PS3.setLedOff();
      //          PS3.setLedOn(LED3);
      //        }
      //      }

      //      if (PS3.getButtonClick(L1))
      //        Serial.print(F("\r\nL1"));
      //      if (PS3.getButtonClick(L3))
      //        Serial.print(F("\r\nL3"));
      //      if (PS3.getButtonClick(R1))
      //        Serial.print(F("\r\nR1"));
      //      if (PS3.getButtonClick(R3))
      //        Serial.print(F("\r\nR3"));

      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
    }
    //#if 0 // Set this to 1 in order to see the angle of the controller
    //    if (printAngle) {
    //      Serial.print(F("\r\nPitch: "));
    //      Serial.print(PS3.getAngle(Pitch));
    //      Serial.print(F("\tRoll: "));
    //      Serial.print(PS3.getAngle(Roll));
    //    }
    //#endif
  }
}





