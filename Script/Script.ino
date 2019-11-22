//color sensor pin
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

// Radius color of orange
int RGBJeruk[3] = {176, 208, 81};
int radiusJeruk = 30;

// its orange?
bool isJeruk;

// Motor driver pin
#define BRAKE 0
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15

#define MOTOR_A1_PIN1 22 //INA
#define MOTOR_B1_PIN1 23 //INB
#define PWM_MOTOR_1 24    //PMW
#define CURRENT_SEN_1 A3  //CS
#define EN_PIN_1 A0       //EN
#define MOTOR_1 0

#define MOTOR_A1_PIN2 25 //INA
#define MOTOR_B1_PIN2 26 //INB
#define PWM_MOTOR_2 27    //PMW
#define CURRENT_SEN_2 A4  //CS
#define EN_PIN_2 A1       //EN
#define MOTOR_2 1

#define MOTOR_A1_PIN3 28 //INA
#define MOTOR_B1_PIN3 29 //INB
#define PWM_MOTOR_3 30    //PMW
#define CURRENT_SEN_3 A5  //CS
#define EN_PIN_3 A2       //EN
#define MOTOR_3 2

short usSpeed = 150;  //default motor speed
unsigned short usMotor_Status = BRAKE;

// Servo Lybrary
#include <Servo.h>
Servo guntingServo;

// Position of the servo for cutting the orange
int guntingPos = 0;

// Servo pin
int servoGunting = 11;

//// Pin sensor jarak depan
//#define echoPin1 14
//#define trigPin1 15
//
//// Pin sensor jarak kanan
//#define echoPin2 16
//#define trigPin2 17
//
//// Pin sensor jarak kiri
//#define echoPin3 18
//#define trigPin3 19
//
//// Pin sensor jarak belakang
//#define echoPin4 20
//#define trigPin4 21

//// Radius jarak maksimal yang dideteksi sebagai "Pohon/benda"
//int maxRange = 300;
//// Radius jarak minimal yang dideteksi sebagai "Pohon/benda" agar tidak terjadi benturan
//int minRange = 20;
//// Gelombang yang dikirim dan diterima oleh sensor
//long duration[4] = {0, 0, 0, 0};
//// Hasil perhitungan jarak berdasarkan hasil penerimaan gelombang oleh sensor
//long distance[4] = {0, 0, 0, 0};

/* menentukan arah pohon (
      1 maju
      2 kanan
      3 kiri
      4 mundur   */
//int arahPohon;

//bool stopMaju;                                                    // berhenti maju?
//bool outOfRange[4] = {false, false, false, false};                // diluar jangkauan?
//bool objekDiKanan = false;                                        // ada objek di kanan?

int state;
int flag = 0;

void guntingSetup() {
  guntingServo.attach(servoGunting);
}

void guntingBuka(bool tutup) {
  if (tutup) {
    guntingServo.write(180);
  } else {
    guntingServo.write(0);
  }
}

void setup() { //setting up all the pins, default output, etc
//  pinMode(echoPin1, INPUT);
//  pinMode(trigPin1, OUTPUT);
//
//  pinMode(echoPin2, INPUT);
//  pinMode(trigPin2, OUTPUT);
//
//  pinMode(echoPin3, INPUT);
//  pinMode(trigPin3, OUTPUT);
//
//  pinMode(echoPin4, INPUT);
//  pinMode(trigPin4, OUTPUT);

  motorSetup();
  colorSetup();
  guntingSetup();

  // Begins serial communication
  Serial.begin(9600);
  motorGo(MOTOR_3, CW, usSpeed);
}

void loop() {
  getColor();                               // get the data from the color sensor
  //getRange();                               // get the data from the range sensor
  digitalWrite(EN_PIN_1, HIGH);

  if(Serial.available() > 0){
    state = Serial.read();
    flag = 0;
  }

  if(state == '0'){
    berhenti();

    if(flag == 0){
      Serial.println("Motor: off");
      flag = 1;
    }
  }else if(state == '1'){
    kanan();

    if(flag = 0){
      Serial.println("Motor: right");
      flag = 1;
    }
  }else if(state == '2'){
    kiri();

    if(flag = 0){
      Serial.println("Motor: left");
      flag = 1;
    }
  }else if(state == '3'){
    maju();

    if(flag = 0){
      Serial.println("Motor: maju");
      flag = 1;
    }
  }else if(state == '4'){
    mundur();

    if(flag = 0){
      Serial.println("Motor: mundur");
      flag = 1;
    }
  }
  
  /*  1 maju
      2 kanan
      3 kiri
      4 mundur
  */

//  switch(arahPohon){
//    case 1: 
//      maju();
//      if (stopMaju) { kiri(); } break;
//    case 2:          
//      kanan(); delay(300); maju();
//      if (stopMaju) { kiri(); } break;
//    case 3:
//      kiri(); delay(300); maju(); 
//      if (stopMaju) { kiri(); } break;
//    case 4:
//      mundur(); 
//      if (stopMaju) { kanan(); } break;
//    default: berhenti();
//  }
//
//  if (objekDiKanan) {
//    maju();
//  } else if (!objekDiKanan) {
//    berhenti();
//  } 

  if (isJeruk) {                      // jika mendeteksi jeruk
    guntingBuka(false);               // membuka mulut gunting
    delay(1000);                      // delay 1 detik
    guntingBuka(true);                // menutup mulut gunting
  }
}

//void getRange() { // S = 340.t/2
//  digitalWrite(trigPin1, LOW); delayMicroseconds(2);
//  digitalWrite(trigPin1, HIGH); delayMicroseconds(10);
//  digitalWrite(trigPin1, LOW);
//  duration[0] = pulseIn(echoPin1, HIGH);
//  distance[0] = duration[0] / 58.2;
//
//  digitalWrite(trigPin2, LOW); delayMicroseconds(2);
//  digitalWrite(trigPin2, HIGH); delayMicroseconds(10);
//  digitalWrite(trigPin2, LOW);
//  duration[1] = pulseIn(echoPin2, HIGH);
//  distance[1] = duration[1] / 58.2;
//
//  digitalWrite(trigPin3, LOW); delayMicroseconds(2);
//  digitalWrite(trigPin3, HIGH); delayMicroseconds(10);
//  digitalWrite(trigPin3, LOW);
//  duration[2] = pulseIn(echoPin3, HIGH);
//  distance[2] = duration[2] / 58.2;
//
//  digitalWrite(trigPin4, LOW); delayMicroseconds(2);
//  digitalWrite(trigPin4, HIGH); delayMicroseconds(10);
//  digitalWrite(trigPin4, LOW);
//  duration[3] = pulseIn(echoPin4, HIGH);
//  distance[3] = duration[3] / 58.2;
//
//  for (int i = 0; i <= 3; i++) {
//    if (distance[i] <= maxRange && distance[i] > minRange) {
//      arahPohon = i + 1;
//      stopMaju = false;
//    } else if (distance[i] > maxRange) {
//      outOfRange[i] = true;
//      stopMaju = true;
//    }
//  }
//
//  if (distance[1] <= minRange) {
//    objekDiKanan = true;
//  } else {
//    objekDiKanan = false;
//  }
//}

void getColor() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  redColor = map(redFrequency, 65, 762, 255, 0);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  greenColor = map(greenFrequency, 108, 2054, 255, 0);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  //R = 65 G = 108 B = 96
  //R = 762 G = 2054 B = 879

  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  blueColor = map(blueFrequency, 96, 879, 255, 0);

  if (redColor > RGBJeruk[0] - radiusJeruk && redColor < RGBJeruk[0] + radiusJeruk) {
    if (greenColor > RGBJeruk[1] - radiusJeruk && greenColor < RGBJeruk[1] + radiusJeruk) {
      if (blueColor > RGBJeruk[2] - radiusJeruk && greenColor < RGBJeruk[2] + radiusJeruk) {
        isJeruk = true;
      } else {
        isJeruk = false;
      }
    } else {
      isJeruk = false;
    }
  } else {
    isJeruk = false;
  }
}

void colorSetup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);

  // Setting frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

void motorSetup() {
  pinMode(MOTOR_A1_PIN1, OUTPUT);
  pinMode(MOTOR_B1_PIN1, OUTPUT);
  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(CURRENT_SEN_1, OUTPUT);
  pinMode(EN_PIN_1, OUTPUT);
  
  pinMode(MOTOR_A1_PIN2, OUTPUT);
  pinMode(MOTOR_B1_PIN2, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);
  pinMode(CURRENT_SEN_2, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);
  
  pinMode(MOTOR_A1_PIN3, OUTPUT);
  pinMode(MOTOR_B1_PIN3, OUTPUT);
  pinMode(PWM_MOTOR_3, OUTPUT);
  pinMode(CURRENT_SEN_3, OUTPUT);
  pinMode(EN_PIN_3, OUTPUT);
}

void kanan() {
  motorGo(MOTOR_1, BRAKE, usSpeed);
  motorGo(MOTOR_2, CW, usSpeed);
}

void kiri() {
  motorGo(MOTOR_1, CW, usSpeed);
  motorGo(MOTOR_2, BRAKE, usSpeed);
}

void mundur() {
  motorGo(MOTOR_1, CCW, usSpeed);
  motorGo(MOTOR_2, CCW, usSpeed);
}

void maju() {
  motorGo(MOTOR_1, CW, usSpeed);
  motorGo(MOTOR_2, CW, usSpeed);
}

void berhenti() {
  motorGo(MOTOR_1, BRAKE, 0);
  motorGo(MOTOR_2, BRAKE, 0);
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  switch(motor){
    case MOTOR_1:
      if(direct == CW) {
        digitalWrite(MOTOR_A1_PIN1, LOW); 
        digitalWrite(MOTOR_B1_PIN1, HIGH);
      } else if(direct == CCW) {
        digitalWrite(MOTOR_A1_PIN1, HIGH);
        digitalWrite(MOTOR_B1_PIN1, LOW);      
      } else {
        digitalWrite(MOTOR_A1_PIN1, LOW);
        digitalWrite(MOTOR_B1_PIN1, LOW);            
      }
      analogWrite(PWM_MOTOR_1, pwm); 
      break;
    case MOTOR_2:
      if(direct == CW) {
        digitalWrite(MOTOR_A1_PIN2, LOW); 
        digitalWrite(MOTOR_B1_PIN2, HIGH);
      } else if(direct == CCW) {
        digitalWrite(MOTOR_A1_PIN2, HIGH);
        digitalWrite(MOTOR_B1_PIN2, LOW);      
      } else {
        digitalWrite(MOTOR_A1_PIN2, LOW);
        digitalWrite(MOTOR_B1_PIN2, LOW);            
      }
      analogWrite(PWM_MOTOR_2, pwm); 
      break;
    case MOTOR_3:
      if(direct == CW) {
        digitalWrite(MOTOR_A1_PIN3, LOW); 
        digitalWrite(MOTOR_B1_PIN3, HIGH);
      } else if(direct == CCW) {
        digitalWrite(MOTOR_A1_PIN3, HIGH);
        digitalWrite(MOTOR_B1_PIN3, LOW);      
      } else {
        digitalWrite(MOTOR_A1_PIN3, LOW);
        digitalWrite(MOTOR_B1_PIN3, LOW);            
      }
      analogWrite(PWM_MOTOR_3, pwm); 
      break;
  }
}
