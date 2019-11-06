#include <TCS3200.h>
#define SERIALREMOTE Serial
#define BPS 9600

TCS3200 color( 4, 5, 6, 2, 3, 7 );

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("START");
  color.begin();
  color.nSamples(40);
  color.setRefreshTime(200);
  color.setFrequency(TCS3200_FREQ_HI);

  color.loadCal(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(color.onChangeColor()){
    Serial.println(color.readColorID());
    Serial.println(color.readColor());
  }
}
