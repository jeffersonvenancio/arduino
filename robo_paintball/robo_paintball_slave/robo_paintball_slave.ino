#include <Servo.h>

const int entrada_servo_direita =  12;
const int entrada_servo_esquerda =  11;
const int entrada_servo_baixo =  10;
const int entrada_servo_cima =  9;
const int entrada_servo_gatilho =  8;

Servo servo_cima_baixo;
Servo servo_direita_esquerda;
Servo servo_gatilho;

int pos_direita_esquerda = 0;
int pos_cima_baixo = 0;

void setup() {
  Serial.begin(9600);
  pinMode(entrada_servo_direita,   INPUT_PULLUP);
  pinMode(entrada_servo_esquerda,   INPUT_PULLUP);
  pinMode(entrada_servo_baixo,   INPUT_PULLUP);
  pinMode(entrada_servo_cima,  INPUT_PULLUP);
  pinMode(entrada_servo_gatilho,   INPUT_PULLUP);

  servo_cima_baixo.attach(7);
  servo_direita_esquerda.attach(6);
  servo_gatilho.attach(5);

}

void loop() {


  Serial.println(bitRead(PORTD, entrada_servo_direita));
  Serial.println(digitalRead(entrada_servo_direita));
  //  int int_servo_direita = digitalRead(entrada_servo_direita);
  //  if (int_servo_direita == HIGH && pos_direita_esquerda < 90) {
  //    Serial.println("direita");
  //    pos_direita_esquerda += 1;
  //  }
  //  delay(1);
  //
  //  int int_servo_esquerda = digitalRead(entrada_servo_esquerda);
  //  if (int_servo_esquerda == HIGH && pos_direita_esquerda > -90) {
  //    Serial.println("esquerda");
  //    pos_direita_esquerda -= 1;
  //  }
  //  delay(1);
  //
  //  int int_servo_cima = digitalRead(entrada_servo_cima);
  //  if (int_servo_cima == HIGH && pos_cima_baixo < 15) {
  //    Serial.println("cima");
  //    pos_cima_baixo += 1;
  //  }
  //  delay(1);
  //
  //
  //  int int_servo_baixo = digitalRead(entrada_servo_baixo);
  //  if (int_servo_baixo == HIGH && pos_cima_baixo > -15) {
  //    Serial.println("baixo");
  //    pos_cima_baixo -= 1;
  //  }
  //  delay(1);
  //
  //  if (pos_direita_esquerda != 0) {
  //    servo_direita_esquerda.write(pos_direita_esquerda);
  //  }
  //
  //  if (pos_cima_baixo != 0) {
  //    servo_cima_baixo.write(pos_cima_baixo);
  //  }
  //
  //  int int_servo_gatilho = digitalRead(entrada_servo_gatilho);
  //  if (int_servo_gatilho == HIGH) {
  //    Serial.println("Gatilho");
  //    servo_gatilho.write(30);
  //  } else {
  //    servo_gatilho.write(0);
  //  }
  delay(1000);
}
