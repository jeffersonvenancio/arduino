#include <PS3BT.h>
#include <usbhub.h>

#include <Servo.h>

#include <AFMotor.h>

AF_DCMotor motor_direita(1);
AF_DCMotor motor_esquerda(3);

USB Usb;
BTD Btd(&Usb);
//PS3BT PS3(&Btd);
//00:19:86:00:0F:F9
PS3BT PS3(&Btd, 0x00, 0x19, 0x86, 0x00, 0x0F, 0xF9);

bool direita, esquerda, frente, tras, servo_direita, servo_esquerda, servo_cima, servo_baixo, aciona_gatilho;

Servo servo_y_direita;
Servo servo_y_esquerda;
Servo servo_direita_esquerda;
Servo servo_gatilho;

int pos_direita_esquerda = 90;
int pos_y_servo_esquerda = 15;
int pos_y_servo_direita = 15;

void setup() {
  Serial.begin(115200);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  motor_direita.setSpeed(255);
  motor_esquerda.setSpeed(255);

  servo_y_direita.attach(39);
  servo_y_esquerda.attach(41);
  servo_direita_esquerda.attach(45);
  servo_gatilho.attach(37);

  servo_y_direita.write(15);
  servo_y_esquerda.write(15);
  servo_direita_esquerda.write(90);
  servo_gatilho.write(90);
}

void loop() {
  Usb.Task();
  if (PS3.PS3Connected) {

    //Motores
    if (PS3.getAnalogHat(LeftHatX) > 200) {
      Serial.println("Direita");
      direita = true;
    } else {
      direita = false;
    }

    if (PS3.getAnalogHat(LeftHatX) < 55) {
      Serial.println("Esquerda");
      esquerda = true;
    } else {
      esquerda = false;
    }

    if (PS3.getAnalogHat(LeftHatY) > 200) {
      Serial.println("Tras");
      tras = true;
    } else {
      tras = false;
    }

    if (PS3.getAnalogHat(LeftHatY) < 55) {
      Serial.println("Frente");
      frente = true;
    } else {
      frente = false;
    }

    //Servos
    if (PS3.getAnalogHat(RightHatX) > 200) {
      Serial.println("Servo Direita");
      servo_direita = true;
    } else {
      servo_direita = false;
    }

    if (PS3.getAnalogHat(RightHatX) < 55) {
      Serial.println("Servo Esquerda");
      servo_esquerda = true;
    } else {
      servo_esquerda = false;
    }

    if (PS3.getAnalogHat(RightHatY) > 200) {
      Serial.println("Servo Baixo");
      servo_baixo = true;
    } else {
      servo_baixo = false;
    }

    if (PS3.getAnalogHat(RightHatY) < 55) {
      Serial.println("Servo Cima");
      servo_cima = true;
    } else {
      servo_cima = false;
    }

    if (PS3.getButtonClick(R1) || PS3.getButtonClick(L1)) {
      aciona_gatilho = true;
    } else {
      aciona_gatilho = false;
    }

    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    } else {
      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
      }
    }

    if (frente) {
      if (direita) {
        motor_direita.setSpeed(120);
        motor_direita.run(FORWARD);
        motor_esquerda.run(FORWARD);
        Serial.println("frente direita");
      } else if (esquerda) {
        motor_esquerda.setSpeed(120);
        motor_direita.run(FORWARD);
        motor_esquerda.run(FORWARD);
        Serial.println("frente esquerda");
      } else {
        motor_direita.setSpeed(255);
        motor_esquerda.setSpeed(255);
        motor_direita.run(FORWARD);
        motor_esquerda.run(FORWARD);
        Serial.println("frente");
      }
    } else if (tras) {
      if (direita) {
        motor_direita.setSpeed(120);
        motor_direita.run(BACKWARD);
        motor_esquerda.run(BACKWARD);
        Serial.println("tras direita");
      } else if (esquerda) {
        motor_esquerda.setSpeed(120);
        motor_direita.run(BACKWARD);
        motor_esquerda.run(BACKWARD);
        Serial.println("tras esquerda");
      } else {
        motor_direita.setSpeed(255);
        motor_esquerda.setSpeed(255);
        motor_direita.run(BACKWARD);
        motor_esquerda.run(BACKWARD);
        Serial.println("tras");
      }
    } else if (direita) {
      motor_direita.setSpeed(255);
      motor_esquerda.setSpeed(255);
      motor_direita.run(BACKWARD);
      motor_esquerda.run(FORWARD);
      Serial.println("direita");
    } else if (esquerda) {
      motor_direita.setSpeed(255);
      motor_esquerda.setSpeed(255);
      motor_direita.run(FORWARD);
      motor_esquerda.run(BACKWARD);
      Serial.println("esquerda");
    } else {
      motor_direita.run(RELEASE);
      motor_esquerda.run(RELEASE);
    }

    if (servo_cima  && pos_y_servo_esquerda < 30) {
      pos_y_servo_esquerda += 1;
      pos_y_servo_direita -= 1;
    }
    if (servo_baixo  && pos_y_servo_esquerda > -30) {
      pos_y_servo_esquerda -= 1;
      pos_y_servo_direita += 1;
    }

    if (servo_direita && pos_direita_esquerda < 180) {
      pos_direita_esquerda += 1;
    }

    if (servo_esquerda && pos_direita_esquerda > 0) {
      pos_direita_esquerda -= 1;
    }

    if (pos_direita_esquerda != 0) {
      servo_direita_esquerda.write(pos_direita_esquerda);
    }

    if (pos_y_servo_direita != 15 && pos_y_servo_esquerda != 15) {
      Serial.println("Sobe");
      servo_y_direita.write(pos_y_servo_direita);
      servo_y_esquerda.write(pos_y_servo_esquerda);
    }

    if (aciona_gatilho) {
      Serial.println("Tiro");
      servo_gatilho.write(120);
      delay(100);
    } else {
      servo_gatilho.write(90);
    }

  }
}





