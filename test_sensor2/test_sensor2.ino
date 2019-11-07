int s0 = 4;

int s1 = 5;

int s2 = 6;

int s3 = 7;

int out = 8;

int LED = 13;

void TCS3200setup() {

  pinMode(LED, OUTPUT);

  pinMode(s2, OUTPUT);

  pinMode(s3, OUTPUT);

  pinMode(s0, OUTPUT);

  pinMode(s1, OUTPUT);

  return;

}

void setup() {

  TCS3200setup();

  Serial.begin(115200);

  delay(100);

}

void loop() {

  Serial.print(detectColor(out));

  delay(1000);

}

unsigned int detectColor(int taosOutPin) {

  double isPresentTolerance = 10;

  double isPresent = colorRead(taosOutPin, 0, 0) / colorRead(taosOutPin, 0, 1);

  Serial.print("isPresent: ");

  Serial.println(isPresent, 2);

  Serial.print("isPresentTolerance curently set to: ");

  Serial.println(isPresentTolerance, 2);

  if (isPresent < isPresentTolerance) {

    Serial.println("nothing is in front of sensor");

    return 0;

  }

  double red, blue, green;

  //long x = readColor – blackColor;

  //x = x * 255;

  //x = x / maxColor;

  double white = colorRead(taosOutPin, 0, 1);

  unsigned int maxColor = white;

  unsigned  int red2, blue2, green2;

  red = white / colorRead(taosOutPin, 1, 1);

  red2 = red * 255 / maxColor;

  blue = white / colorRead(taosOutPin, 2, 1);

  blue2 = blue * 255 / maxColor;

  green = white / colorRead(taosOutPin, 3, 1);

  green2 = green * 255 / maxColor;

  Serial.print("red  : ");

  Serial.println(red2);

  Serial.print("blue  : ");

  Serial.println(blue2);

  Serial.print("green  : ");

  Serial.println(green2);

}

unsigned int colorRead(unsigned int taosOutPin, unsigned int color, boolean LEDstate) {

  pinMode(taosOutPin, INPUT);

  taosMode(1);

  int sensorDelay = 1;

  if (color == 0) {

    digitalWrite(s3, LOW);

    digitalWrite(s2, HIGH);

  } else if (color == 1) {

    digitalWrite(s3, LOW);

    digitalWrite(s2, LOW);

  } else if (color == 2) {

    digitalWrite(s3, HIGH);

    digitalWrite(s2, LOW);

  } if (color == 3) {

    digitalWrite(s3, HIGH);

    digitalWrite(s2, HIGH);

  }

  unsigned int  readPulse;

  if (LEDstate == 0) {

    digitalWrite(LED, LOW);

  }

  if (LEDstate == 1) {

    digitalWrite(LED, HIGH);

  }

  delay(sensorDelay);

  readPulse = pulseIn(taosOutPin, LOW, 25000) / 2;

  if ( readPulse < .1) {

    readPulse = 25000;

  }

  taosMode(0);

  return  readPulse;

}

void taosMode(int mode) {

  if (mode == 0) {

    digitalWrite(LED, LOW);

    digitalWrite(s0, LOW);

    digitalWrite(s1, LOW);

  } else if (mode == 1) {

    digitalWrite(s0, HIGH);

    digitalWrite(s1, HIGH);

  } else if (mode == 2) {

    digitalWrite(s0, HIGH);

    digitalWrite(s1, LOW);

  } else if (mode == 3) {

    digitalWrite(s0, LOW);

    digitalWrite(s1, HIGH);

  }

  return;

}
