
#include <Servo.h>
int R_IS = 8;
int L_IS = 9;
int R_EN = 7;
int L_EN = 6;

//motor1, motor3 
int RPWM_1 = 3;
int LPWM_1 = 5;

//motor2, motor4 
int RPWM_2 = 10;
int LPWM_2 = 11;


int speed1 = 200;
int speed2 = 200;

////arm/////////


Servo base;
Servo dan_pas;
Servo bam_pas;

int nutral = 90;
int i;




void setup() {
  //define pinmode

  Serial.begin(9600);
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
  


   base.attach(13);
  dan_pas.attach(12);
  bam_pas.attach(4);


  //////////////// Nutral///////////////////////
  base.write(nutral);
  dan_pas.write(175);
  bam_pas.write(5);
  //////////////////////////////////////////////
 delay(200);
}

void loop(){
  if (Serial.available()>0) {
  char state = Serial.read();

  if (state == 'w') {
   analogWrite(LPWM_2, speed1);
   analogWrite(LPWM_1, speed1);
   analogWrite(RPWM_2, 0);        //forward
   analogWrite(RPWM_1, 0);
   
  
  
    
    Serial.print("f");
  }
 else if (state == 'x') {
   reset();
  }
  else if (state == 'o') {   //// open
    dan_pas.write(130);
    bam_pas.write(50);
  }
    if (state == 'c') {   //// close
    dan_pas.write(175);
    bam_pas.write(5);
  }
 else if (state == 'n') {   /// niche namtese
    for(i = 50; i<= 110; i+= 5) {
      base.write(i);
      delay(100);
      }
  }
 else if (state == 'u') { ///// upore ut tese
    base.write(50);
  }
 else if (state == 'g') {
    base.write(nutral);
    dan_pas.write(175);
    bam_pas.write(5);
  }
   else if (state == 's') { //thik ache
    analogWrite(RPWM_2, 0);
    analogWrite(LPWM_1, 0);
   analogWrite(RPWM_1, speed2);
  analogWrite(LPWM_2, speed2);
  
  }
  else if (state == 'd') { //thik ache
    analogWrite(LPWM_2, speed1);
   analogWrite(LPWM_1, speed1);
   analogWrite(RPWM_2, 0);        //left
   analogWrite(RPWM_1, 0);
   
  }
   else if (state == 'a') {
    analogWrite(LPWM_2, speed1);
   analogWrite(LPWM_1, speed1);
   analogWrite(RPWM_2, speed1);        //left
   analogWrite(RPWM_1, speed1);
  
  }
  

  
 }
  
}
  


void forward() { //done
  analogWrite(RPWM_2, speed1);
  analogWrite(LPWM_1, speed1);
  analogWrite(LPWM_2, 0);
  analogWrite(RPWM_1, 0);
  
}

void backward() { ///done
  analogWrite(RPWM_1, speed2);
  analogWrite(RPWM_2, 0);
  analogWrite(LPWM_2, speed2);
  analogWrite(LPWM_1, 0);
}


void right() { //done
  analogWrite(RPWM_1, 0);
  analogWrite(RPWM_2, 0);
  analogWrite(LPWM_2, speed1);
  analogWrite(LPWM_1, speed1);
  
}

void left() { //done
  
  analogWrite(RPWM_1, speed1);
  analogWrite(RPWM_2, speed1);
  analogWrite(LPWM_2, 0);
  analogWrite(LPWM_2, 0);
}

void reset() {
  analogWrite(RPWM_1, 0);
  analogWrite(RPWM_2, 0);
  analogWrite(LPWM_1, 0);
  analogWrite(LPWM_2, 0);
  
}
