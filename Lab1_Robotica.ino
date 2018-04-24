#include <Servo.h>

Servo servoMotor;

void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);
 
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(9);
}

void loop() {
  // Desplazamos a la posición 0º
  write(servoMotor, 0, 1000);
  //servoMotor.write(0);
  // Esperamos 1 segundo
  //delay(3000);
  
  // Desplazamos a la posición 90º
  //servoMotor.write(720);
  // Esperamos 1 segundo
  //delay(5000);
  
  // Desplazamos a la posición 180º
  write(servoMotor, 90, 5000);
  // Esperamos 1 segundo
}

void write(Servo servo, int angle, int mili) {
  if(servo.read() - angle == 0) return;
  
  int way, wait;
  if(angle < servo.read()) {
    way = -1;
    wait = servo.read() - angle;
  } else {
    way = 1;
    wait = angle - servo.read();
  }

  wait = mili / wait;
  while(servo.read() != angle) {
    servo.write(servo.read() + way);
    delay(wait);
  }
}

