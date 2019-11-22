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

// Radius color of orange
int RGBJeruk[3] = {176, 208, 81};
int radiusJeruk = 30;

// its orange?
bool isJeruk;

// Servo Lybrary
#include <Servo.h>
Servo guntingServo;

// Position of the servo for cutting the orange
int guntingPos = 0;

// Servo pin
int servoGunting = 11;

void guntingSetup() {
  guntingServo.attach(servoGunting);
  guntingServo.write(180);
}

void guntingBuka(bool tutup) {
  if (tutup) {
    guntingServo.write(0);
  } else {
    guntingServo.write(180);
  }
}

void setup() {
  // put your setup code here, to run once:
  colorSetup();
  guntingSetup();

  // Begins serial communication
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  getColor();
  
  if (isJeruk) {                      // jika mendeteksi jeruk
    guntingBuka(true);               // membuka mulut gunting
    delay(1000);                      // delay 1 detik
    guntingBuka(false);                // menutup mulut gunting
  }
}

void getColor() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  //R = 65 G = 108 B = 96
  //R = 762 G = 2054 B = 879

  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);

  Serial.print("R: ");
  Serial.print(redFrequency);
  Serial.print("G: ");
  Serial.print(greenFrequency);
  Serial.print("B: ");
  Serial.println(blueFrequency);

  if (redFrequency > RGBJeruk[0] - radiusJeruk && redFrequency < RGBJeruk[0] + radiusJeruk) {
    if (greenFrequency > RGBJeruk[1] - radiusJeruk && greenFrequency < RGBJeruk[1] + radiusJeruk) {
      if (blueFrequency > RGBJeruk[2] - radiusJeruk && blueFrequency < RGBJeruk[2] + radiusJeruk) {
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
