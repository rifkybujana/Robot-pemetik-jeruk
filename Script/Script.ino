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

bool isJeruk;

//////////////////////////////////////////////////////////////////////////

int pwml = 9;
int pwmr = 6;
int ml[] = {0, 1};
int mr[] = {2, 3};

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
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  digitalWrite(pwmr, 250);
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
}

void kiri() {
  digitalWrite(pwml, 250);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  digitalWrite(pwmr, 250);
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
}

void mundur() {
  digitalWrite(pwml, 250);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  digitalWrite(pwmr, 250);
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
}

void maju() {
  digitalWrite(pwml, 250);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  digitalWrite(pwmr, 250);
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
}

void berhenti() {
  digitalWrite(pwml, 0);
  digitalWrite(pwmr, 0);
}

/////////////////////////////////////////////////////////////////////////

void setup() {
  motorSetup();
  colorSetup();
  
  // Begins serial communication
  Serial.begin(9600);
}

void loop() {
  getColor();
}

void getColor() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  redColor = map(redFrequency, 25, 72, 255,0);
  
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
   greenColor = map(greenFrequency, 30, 90, 255, 0);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenColor);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  blueColor = map(blueFrequency, 25, 70, 255, 0);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.print(blueColor);
  delay(100);
}
