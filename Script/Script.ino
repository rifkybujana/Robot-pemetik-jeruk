/* pin
 * S0 KE DIGITAL PIN 4
 * S1 KE DIGITAL PIN 5
 * VCC KE 5V
 * S3 KE DIGITAL PIN 6
 * S4 KE DIGITAL PIN 7
 * OUT KE DIGITAL PIN 8
 */

int Sensor[4] = { 4, 5, 6, 7};
#define sensorOut 8

int redFrequency, greenFrequency, blueFrequency;
int redColor, greenColor, blueColor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("START");

  //setting output
  pinMode(Sensor[0], OUTPUT);
  pinMode(Sensor[1], OUTPUT);
  pinMode(Sensor[2], OUTPUT);
  pinMode(Sensor[3], OUTPUT);

  //setting sensorOut sebagai input
  pinMode(sensorOut, INPUT);

  //setting frequency
  digitalWrite(Sensor[0], HIGH);
  digitalWrite(Sensor[1], LOW);

  Serial.begin(9600);
}

void loop() {
  getColor();
}

void getColor(){
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
