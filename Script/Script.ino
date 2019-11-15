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

int RGBJeruk[3] = {176, 208, 81};
int radiusJeruk = 20;

bool isJeruk;

int pwml = 9;
int pwmr = 10;
int ml[] = {0, 1};
int mr[] = {2, 3};

#include <Servo.h>
Servo guntingServo1;
Servo guntingServo2;
Servo servoPenekan;

int guntingPos1 = 0;
int guntingPos2 = 180;

int servoGunting[2] = {11,12};
int servoPenekanPin = 13;

#define echoPin1 14
#define trigPin1 15

#define echoPin2 16
#define trigPin2 17

#define echoPin3 18
#define trigPin3 19

#define echoPin4 20
#define trigPin4 21

int maxRange = 500;
int minRange = 50;
long duration[4] = {0,0,0,0};
long distance[4] = {0,0,0,0};

int arahPohon;
bool stopMaju;
bool outOfRange[4] = {false,false,false,false};

void setup() {
  pinMode(echoPin1, INPUT);
  pinMode(trigPin1, OUTPUT);
  
  pinMode(echoPin2, INPUT);
  pinMode(trigPin2, OUTPUT);
  
  pinMode(echoPin3, INPUT);
  pinMode(trigPin3, OUTPUT);
  
  pinMode(echoPin4, INPUT);
  pinMode(trigPin4, OUTPUT);
  
  servoPenekan.attach(servoPenekanPin);
  
  motorSetup();
  colorSetup();
  
  // Begins serial communication
  Serial.begin(9600);

  servoPenekan.write(0);
}

void loop() {
  getColor();
  getRange();

  if(isJeruk){
    berhenti();
    delay(300);
    guntingBuka(false);
    delay(1500);
    guntingBuka(true);
  }else{
    guntingBuka(true);
    maju();
  }

  /*  1 maju
   *  2 kanan
   *  3 kiri
   *  4 mundur
   */

  if(arahPohon == 1){
    maju();

    if(stopMaju){
      kiri();
      delay(300);
      maju();
    }

    if(outOfRange[0] == true){
      arahPohon = 0;
    }
  }else if(arahPohon == 2){
    kanan();
    delay(300);
    maju();

    if(stopMaju){
      kiri();
      delay(300);
      maju();
    }

    if(outOfRange[1] == true){
      arahPohon = 0;
    }
  }else if(arahPohon == 3){
    kiri();
    delay(300);
    maju();

    if(stopMaju){
      kiri();
      delay(300);
      maju();
    }

    if(outOfRange[2] == true){
      arahPohon = 0;
    }
  }else if(arahPohon == 4){
    mundur();

    if(stopMaju){
      kanan();
      delay(300);
      maju();
    }

    if(outOfRange[3] == true){
      arahPohon = 0;
    }
  }else if(arahPohon == 0){
    berhenti();
  }
}

void getRange(){  // S = 340.t/2
  digitalWrite(trigPin1, LOW); delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration[0] = pulseIn(echoPin1, HIGH);
  distance[0] = duration[0]/58.2;

  digitalWrite(trigPin2, LOW); delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration[1] = pulseIn(echoPin2, HIGH);
  distance[1] = duration[1]/58.2;

  digitalWrite(trigPin3, LOW); delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration[2] = pulseIn(echoPin3, HIGH);
  distance[2] = duration[2]/58.2;

  digitalWrite(trigPin4, LOW); delayMicroseconds(2);
  digitalWrite(trigPin4, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  duration[3] = pulseIn(echoPin4, HIGH);
  distance[3] = duration[3]/58.2;

  for(int i = 0; i <= 3; i++){
    if(distance[i] <= maxRange && distance[i] > minRange){
      arahPohon = i + 1;
      stopMaju = false;
    }else if(distance[i] > maxRange){
      outOfRange[i] = true;
    }else{
      stopMaju = true;
    }
  }
}

void getColor() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  redColor = map(redFrequency, 65, 762, 255,0);
  
  // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(redColor);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  greenColor = map(greenFrequency, 108, 2054, 255, 0);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenColor);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  //R = 65 G = 108 B = 96
  //R = 762 G = 2054 B = 879
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  blueColor = map(blueFrequency, 96, 879, 255, 0);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.println(blueColor);
  delay(100);

  if(redColor > RGBJeruk[0] - radiusJeruk && redColor < RGBJeruk[0] + radiusJeruk){
    if(greenColor > RGBJeruk[1] - radiusJeruk && greenColor < RGBJeruk[1] + radiusJeruk){
      if(blueColor > RGBJeruk[2] - radiusJeruk && greenColor < RGBJeruk[2] + radiusJeruk){
        isJeruk = true;
      }else{
        isJeruk = false;
      }
    }else{
      isJeruk = false;
    }
  }else{
    isJeruk = false;
  }
}

void colorSetup(){
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

void motorSetup(){
  pinMode(pwml, OUTPUT);
  pinMode(pwmr, OUTPUT);

  pinMode(ml[0], OUTPUT);
  pinMode(ml[1], OUTPUT);
  pinMode(mr[0], OUTPUT);
  pinMode(mr[1], OUTPUT);
}

void kanan() {
  digitalWrite(pwml, 250);
  digitalWrite(ml[0], HIGH);
  digitalWrite(ml[1], LOW);
  digitalWrite(pwmr, 250);
  digitalWrite(mr[0], LOW);
  digitalWrite(mr[1], HIGH);
}

void kiri() {
  digitalWrite(pwml, 250);
  digitalWrite(ml[0], LOW);
  digitalWrite(ml[1], HIGH);
  digitalWrite(pwmr, 250);
  digitalWrite(mr[0], HIGH);
  digitalWrite(mr[1], LOW);
}

void mundur() {
  digitalWrite(pwml, 250);
  digitalWrite(ml[0], HIGH);
  digitalWrite(ml[1], LOW);
  digitalWrite(pwmr, 250);
  digitalWrite(mr[0], HIGH);
  digitalWrite(mr[1], LOW);
}

void maju() {
  digitalWrite(pwml, 250);
  digitalWrite(ml[0], LOW);
  digitalWrite(ml[1], HIGH);
  digitalWrite(pwmr, 250);
  digitalWrite(mr[0], LOW);
  digitalWrite(mr[1], HIGH);
}

void berhenti() {
  digitalWrite(pwml, 0);
  digitalWrite(pwmr, 0);
}

void guntingSetup(){
  guntingServo1.attach(servoGunting[0]);
  guntingServo2.attach(servoGunting[1]);
}

void guntingBuka(bool tutup){
  if(tutup){
    for(guntingPos1 = 0; guntingPos1 <= 180; guntingPos1++){
      guntingServo1.write(guntingPos1);
      delay(10);
    }

    for(guntingPos2 = 180; guntingPos2 >= 0; guntingPos2--){
      guntingServo2.write(guntingPos2);
      delay(10);
    }
  }else{
    for(guntingPos1 = 180; guntingPos1 >= 0; guntingPos1--){
      guntingServo1.write(guntingPos1);
      delay(10);
    }

    for(guntingPos2 = 0; guntingPos2 <= 180; guntingPos2++){
      guntingServo2.write(guntingPos2);
      delay(10);
    }
  }
}
