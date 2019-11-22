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

int state;
int flag = 0;

void setup() {
  motorSetup();

  // Begins serial communication
  Serial.begin(9600);
  motorGo(MOTOR_3, CW, usSpeed);
}

void loop() {
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
