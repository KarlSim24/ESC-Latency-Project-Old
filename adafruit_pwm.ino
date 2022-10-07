#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

#define SERVOARM  700  // pulse length to arm motor
#define SERVOMIN  1000 // minimum pulse length
#define SERVOMAX  1500 // maximum pulse length

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

int pulseCount = 0;
int lastMeasured = 0;

void setup() {
  Serial.begin(9600);

  //for i2c driver
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  //for rpm sensor
  attachInterrupt(digitalPinToInterrupt(2), event, RISING);
  delay(100);
}

void loop() {
  //arm motor
  if (millis()<5000){
    Serial.println("arming");
    pwm.setPWM(0,0,SERVOARM);
  }
  
  //spin motor 
  
  if(millis()>=5000 && millis()<10000){
    Serial.println("low");
    pwm.setPWM(0, 0, SERVOMIN);
  }
  else if(millis()>=10000 && millis()<15000){
    Serial.println("mid");
    pwm.setPWM(0, 0, SERVOMAX);
  }
  else if(millis()>15000) {
    Serial.println("off");
    pwm.setPWM(0, 0, 0);
  }
}

void event(){
  if (millis() - lastMeasured > 1000){
    pulseCount = (pulseCount/6)*60; //RPM = RPS * 60
    Serial.println(pulseCount);
    lastMeasured = millis();
    pulseCount = 0;
  }
  else {
    pulseCount++;
  }
}
