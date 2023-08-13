#include <Servo.h>

Servo servo_x;
Servo servo_y;

int servo_x_pin = 9;
int servo_y_pin = 11;
int angle_x = 0;
int angle_y = 0;
int margin = 150;
void setup()
{
  Serial.begin(9600);
  servo_x.attach(servo_x_pin);
  pinMode(A0, INPUT);
  servo_y.attach(servo_y_pin);
  pinMode(A2, INPUT);
  pinMode(A4, INPUT);
    
}

void loop() {
  int light_sensor_2 = analogRead(A2);
  int light_sensor_4 = analogRead(A4);
  int light_sensor_0 = analogRead(A0);
  while ( light_sensor_2 > light_sensor_4 + margin)
  {
    angle_x += 2;
    servo_x.write(angle_x);
    light_sensor_2 = analogRead(A2);
    light_sensor_4 = analogRead(A4);
    light_sensor_0 = analogRead(A0);
     Serial.print("x+ light_sensor_2  ");
      Serial.print(light_sensor_2);
      Serial.print("\n");
      Serial.print("x+  light_sensor_4  ");
      Serial.print(light_sensor_4);
      Serial.print("\n");
      Serial.print("x+  light_sensor_0  ");
      Serial.print(light_sensor_0);
      Serial.print("\n");
    delay(100);
  }
  while ( light_sensor_4 > light_sensor_2 + margin)
  {
    angle_x -=2;
    servo_x.write(angle_x);
    light_sensor_2 = analogRead(A2);
    light_sensor_4 = analogRead(A4);
    light_sensor_0 = analogRead(A0);
     Serial.print("x- light_sensor_2  ");
      Serial.print(light_sensor_2);
      Serial.print("\n");
      Serial.print("x-  light_sensor_4  ");
      Serial.print(light_sensor_4);
      Serial.print("\n");
      Serial.print("x-  light_sensor_0  ");
      Serial.print(light_sensor_0);
      Serial.print("\n");
    delay(100);
  }

  while (( light_sensor_0 > (((light_sensor_2 + light_sensor_4) / 2)) + margin))
  {
    angle_y += 2;
    servo_y.write(angle_y);
    light_sensor_2 = analogRead(A2);
    light_sensor_4 = analogRead(A4);
    light_sensor_0 = analogRead(A0);
     Serial.print("y+ light_sensor_2  ");
      Serial.print(light_sensor_2);
      Serial.print("\n");
      Serial.print("y+  light_sensor_4  ");
      Serial.print(light_sensor_4);
      Serial.print("\n");
      Serial.print("y+  light_sensor_0  ");
      Serial.print(light_sensor_0);
      Serial.print("\n");
    delay(100);
  }

  while (( ((light_sensor_2 + light_sensor_4) / 2) > light_sensor_0 + margin))
  {
    angle_y -= 2;
    servo_y.write(angle_y);
    light_sensor_2 = analogRead(A2);
    light_sensor_4 = analogRead(A4);
    light_sensor_0 = analogRead(A0);
     Serial.print("y- light_sensor_2  ");
      Serial.print(light_sensor_2);
      Serial.print("\n");
      Serial.print("y-  light_sensor_4  ");
      Serial.print(light_sensor_4);
      Serial.print("\n");
      Serial.print("y-  light_sensor_0  ");
      Serial.print(light_sensor_0);
      Serial.print("\n");
    delay(100);
  }
}
