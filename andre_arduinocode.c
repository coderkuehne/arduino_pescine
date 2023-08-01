#include <Adafruit_LEDBackpack.h>
#include <unistd.h>
int switchstate = 1;
# define GREEN 1
# define RED 3
# define YELLOW 5
# define IN_7 7
# define IN_9 9
# define IN_10 10
int counter = 0;
int mode = 0;
void setup()
{
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(IN_7, INPUT);
  pinMode(IN_9, INPUT);
  pinMode(IN_10, INPUT);
}
int check_mode()
{
  if(digitalRead(IN_9) == HIGH && digitalRead(IN_10) == LOW)
    return(1);
  else if(digitalRead(IN_10) == HIGH && digitalRead(IN_9) == LOW)
	return(2);
  else
    return (0);
}
int check_in_7()
{
  if(digitalRead(IN_7) == HIGH)
	{
      delay(1000);
      if(digitalRead(IN_7) == LOW)
        counter ++;
    }
   	return (counter);
}
void mandatory()
{
  counter= check_in_7();
  if(mode == 2)
  	return ;
  if(counter %2 ==0)
  {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
  	digitalWrite(YELLOW, LOW);
    counter= check_in_7();
  }
  if(counter %2 !=0)
  {
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, HIGH);
      digitalWrite(YELLOW, HIGH);
      delay(500);
      delay(500);
      if(mode == 2)
        return ;
      delay(500);
      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, LOW);
      delay(500);
      if(mode != 1)
        return ;
      counter= check_in_7();
      delay(500);
   }
}
void bonus_1()
{		
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, HIGH);
 digitalWrite(YELLOW, HIGH);
}
void loop()
{
  mode = check_mode();
  if(mode == 1)
    mandatory();
  if(mode == 2)
    bonus_1();
  if(mode == 0)
  {
    digitalWrite(GREEN, LOW);
  	digitalWrite(RED, LOW);
 	digitalWrite(YELLOW, LOW);
  }
}
