/* pin
   S0 KE DIGITAL PIN 4
   S1 KE DIGITAL PIN 5
   VCC KE 5V
   S3 KE DIGITAL PIN 6
   S4 KE DIGITAL PIN 7
   OUT KE DIGITAL PIN 8
*/

#define sensorOut 8
int Sensor[4] = { 4, 5, 6, 7};

int redFrequency, greenFrequency, blueFrequency;
int warnaJeruk = 0;

void colorSetup(){
  //setting output sensor warna
  pinMode(Sensor[0], OUTPUT);
  pinMode(Sensor[1], OUTPUT);
  pinMode(Sensor[2], OUTPUT);
  pinMode(Sensor[3], OUTPUT);

  //setting sensorOut dari sensor warna sebagai input
  pinMode(sensorOut, INPUT);

  //setting frequency sensor warna
  digitalWrite(Sensor[0], HIGH);
  digitalWrite(Sensor[1], LOW);
}

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
  Serial.begin(9600);
  Serial.println("START...");

  motorSetup();
  colorSetup();
}

void loop() {
  getColor();
}

void getColor() {
  // setting red (R)
  digitalWrite(Sensor[2], LOW);
  digitalWrite(Sensor[3], LOW);

  //read red output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  //redColor = map(redFrequency, minValue, maxValue, 255, 0);
  delay(100);

  //setting green (G)
  digitalWrite(Sensor[2], HIGH);
  digitalWrite(Sensor[3], HIGH);

  //read green output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  //greenColor = map(greenFrequency, minValue, maxValue, 255, 0);
  delay(100);

  //setting blue (B)
  digitalWrite(Sensor[2], LOW);
  digitalWrite(Sensor[3], HIGH);

  //read blue output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  //blueColor = map(blueFrequency, minValue, maxValue, 255, 0);
  delay(100);
}
