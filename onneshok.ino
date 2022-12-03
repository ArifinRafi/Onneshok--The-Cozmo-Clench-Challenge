int R_IS = 8;
int L_IS = 9;
int R_EN = 7;
int L_EN = 6;

//motor1, motor3 and motor5
int RPWM_1 = 3;
int LPWM_1 = 5;

//motor2, motor4 and motor 6
int RPWM_2 = 10;
int LPWM_2 = 11;


int speed1 = 200;
int speed2 = 200;

//############Arm Code#############

#include <Servo.h>

Servo base;
Servo dan_pas;
Servo bam_pas;

int nutral = 90;
int temp = 'x';
int i;




void setup() {
  //define pinmode


  pinMode(R_IS, OUTPUT);
  pinMode(L_IS, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);

  //motor1, motor3
  pinMode(RPWM_1 , OUTPUT);
  pinMode(LPWM_1, OUTPUT);

  //motor2, motor4 and motor6
  pinMode(RPWM_2 , OUTPUT);
  pinMode(LPWM_2, OUTPUT);


  digitalWrite(R_IS, LOW);
  digitalWrite(L_IS, LOW);

  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);
  Serial.begin(9600);


  //////Servo/////////

  base.attach(13);
  dan_pas.attach(12);
  bam_pas.attach(4);

  /////////////// Nutral///////////////////////
  base.write(nutral);
  dan_pas.write(175);
  bam_pas.write(5);
  //////////////////////////////////////////////


}

void loop() {
  if (Serial.available() > 0) {
    char state = Serial.read();

    if (state == 'w') {
      forward();
      Serial.print("f");
    }
    else if (state == 'x') {
      reset();
    }
    else if (state == 's') {
      backward();
    }
    else if (state == 'd') {
      right();
    }
    else if (state == 'a') {
      left();
    }
    if (state == 'o') {   //// open
      dan_pas.write(130);
      bam_pas.write(50);
    }
    if (state == 'c') {   //// close
      dan_pas.write(175);
      bam_pas.write(5);
    }
    if (state == 'n') {   /// niche namtese
      for (i = 50; i <= 110; i += 5) {
        base.write(i);
        delay(100);
      }
    }
    if (state == 'u') { ///// upore ut tese
      base.write(50);
    }
    if (state == 'g') {
      base.write(nutral);
      dan_pas.write(175);
      bam_pas.write(5);
    }


  }

}



void forward() {
//ok
 analogWrite(LPWM_1, speed1);
  analogWrite(RPWM_1, 0);
  analogWrite(LPWM_2, speed1);
  analogWrite(RPWM_2, 0);
 

}

void backward() { 
  analogWrite(LPWM_2, speed1);
  analogWrite(LPWM_1, 0);
  analogWrite(RPWM_1, speed1);
  analogWrite(RPWM_2, 0);
  

}


void right() { //done
  analogWrite(RPWM_1, speed1);
  analogWrite(RPWM_2, 0);
  analogWrite(LPWM_2, speed1);
  analogWrite(LPWM_1, 0);

}

void left() { //okay
  analogWrite(LPWM_2, speed1);
  analogWrite(LPWM_1, 0);
  analogWrite(RPWM_1, speed1);
  analogWrite(RPWM_2, 0);

}

void reset() {
  analogWrite(RPWM_1, 0);
  analogWrite(RPWM_2, 0);
  analogWrite(LPWM_1, 0);
  analogWrite(LPWM_2, 0);

}
