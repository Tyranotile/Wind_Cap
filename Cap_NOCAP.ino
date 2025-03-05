//2024 CWC Control Code

#define PWM_PIN 11 //Connected to LAC RC Input
#define VOLTAGE_PIN A0 //Read Voltage
#define PWM_MIN 1000 //Min PWM for retraction
#define PWM_MAX 2000 //Max PWM for extension

void setup() {
  Serial.begin(9600);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(VOLTAGE_PIN, INPUT);
}

void loop() {
  int sensorVal = analogRead(VOLTAGE_PIN);
  Serial.println(sensorVal);
  int pwmVal = map(sensorVal, 0, 1023, PWM_MIN, PWM_MAX);
  pulseServo(pwmVal);
  delay(20);
}

void pulseServo(int pulseWidth) {
  digitalWrite(PWM_PIN, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(PWM_PIN, LOW);
  delay(20);
}