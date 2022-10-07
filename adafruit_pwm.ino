#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

#define SERVOMIN  1000 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  1300 // This is the 'maximum' pulse length count (out of 4096)

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

unsigned long millisec;
int pulseCount = 0;
int lastMeasured = 0;

void setup() {
  Serial.begin(9600);

  //for i2c driver
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  //for rpm sensor
  attachInterrupt(digitalPinToInterrupt(2), event, RISING);
  
  delay(1000);
}

void event(){
  pulseCount++;
}

void loop() {
  
  //arm motor
  if(millis()<5000){
    pwm.setPWM(0,0,700);
    delay(500);
  }
  //spin motor
  else{
    millisec = millis();
    
    //speed 1
    if(millisec>=5000 && millisec<15000){
      pwm.setPWM(0, 0, SERVOMIN);
    }
    //speed 2
    else if(millisec>=15000 && millisec<25000){
      pwm.setPWM(0, 0, SERVOMAX);
    }
    //stop motor
    else {
      pwm.setPWM(0, 0, 0);
    }

    //output RPM every 500ms
    if(millisec - lastMeasured > 500){
      pulseCount = (pulseCount/6)*120; //RPM = RPS * 60
      Serial.println(pulseCount);
      lastMeasured = millisec;
      pulseCount = 0;
    }
  }


  
}
