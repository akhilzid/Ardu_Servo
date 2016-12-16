/****   akhilzid   ***/

/** Servo Controller Based On Arduino
 *  Geared DC Motor + Potentiometer
 *  L298 H-Bridge
 *  That Can be Controlled Using Common RC Transmitter (PWM 1000 to 2000)
 */
 
int potPin = 19;

int motor_p1 = 7;
int motor_p2 = 8;
int pwmPin = 6;
int ErrorGap = 3;
int turnSpeed = 230;
int CurrentPos = 500;
volatile int pwm_value = 1500;
volatile int Old_pwm_value = 1500;
volatile int prev_time = 0;

void rising() {
  attachInterrupt(0, falling, FALLING);
  prev_time = micros();
}

void falling() {
  attachInterrupt(0, rising, RISING);
  pwm_value = micros() - prev_time - 1000;
}

void setup() {
  Serial.begin(115200);
  attachInterrupt(0, rising, RISING);
}

void loop() {
  CurrentPos = analogRead(potPin);
  if (CurrentPos < pwm_value) {
    digitalWrite(motor_p1, HIGH);
    digitalWrite(motor_p2, LOW);
  }
  else if (CurrentPos > pwm_value)
  {
    digitalWrite(motor_p1, LOW);
    digitalWrite(motor_p2, HIGH);
  }
  int Gap = abs(CurrentPos - pwm_value);
  if (Gap > ErrorGap)
  {
    analogWrite(pwmPin,(Gap > turnSpeed)? turnSpeed : Gap);
  }
  else analogWrite(pwmPin, 0);
  Serial.println(pwm_value);
}
