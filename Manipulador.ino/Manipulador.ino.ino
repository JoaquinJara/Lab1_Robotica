#include <Servo.h>

typedef enum {
  PINZA,
  BASE,
  BRAZO,
  ANTEBRAZO
};

Servo servos[4];
bool reading = false, writing = false;
int movements = 0;

void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);

  servos[0].attach(6); // Pinza
  servos[1].attach(9); // Base
  servos[2].attach(10); // Brazo
  servos[3].attach(11); // Antebrazo

  servos[0].write(90);
  servos[1].write(90);
  servos[2].write(30);
  servos[3].write(70);
}

void loop() {  
  if(Serial.available() == 3 && !reading) {
    movements++;
    
    reading = true;
    int part = Serial.read();
    Servo servo = servos[part];
    
    int op = Serial.read();
    int angle = Serial.read();
    reading = false;
    
    if(op == '+') {
      int newAng = servo.read() + angle;
      if((part == ANTEBRAZO && newAng <= 105) || (part != ANTEBRAZO && newAng <= 160))
        servo.write(newAng);
    } else if(op == '-' && (servo.read() - angle >= 10))
      servo.write(servo.read() - angle);
    else if(angle >= 10 && angle <= 160)
      servo.write(angle);

    String angles = "";
    for(int i = 0; i < 4; i++) {
      angles += servos[i].read();
      angles += ",";
    }
    
    Serial.println(angles);
  }
}
