#include <Time.h>
#include <TimeAlarms.h>

long randNumber;

int dirpin = 11; //small motor
int steppin = 12;

int dirpinb = 8; //big motor
int steppinb = 9;

int redled = 4; //red LED
int greenled = 5; //green LED

void setup()
{
  Serial.begin(9600); //initialize communication with chip
  setTime(17,31,30,1,13,14); //set time
  Alarm.alarmRepeat(7,30,0, FirstSham); //set first sham time
  Alarm.alarmRepeat(8,0,0, FirstAlarm); //set first alarm time
  Alarm.alarmRepeat(11,30,0, SecondSham); //set second sham time
  Alarm.alarmRepeat(12,0,0, SecondAlarm); //set second alarm time
  Alarm.alarmRepeat(15,30,0, ThirdSham); //set third sham time
  Alarm.alarmRepeat(16,0,0, ThirdAlarm); //set third alarm time
  Alarm.alarmRepeat(19,30,0, FourthSham); //set fourth sham time
  Alarm.alarmRepeat(20,0,0, FourthAlarm); //set fourth alarm time
  Alarm.timerRepeat(15, Repeats); //checks for time every 15 seconds
  Alarm.timerOnce(10, OnceOnly); //calls alarm once after 10 seconds
  
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);  
  pinMode(dirpin, OUTPUT);
  pinMode(steppin, OUTPUT);
  pinMode(dirpinb, OUTPUT);
  pinMode(steppinb, OUTPUT);
  randomSeed(analogRead(0)); //generate different random number
}

void loop()
{
  Alarm.delay(0);
}

void Repeats()
{
}

void OnceOnly()
{
}

void FirstSham()
{
  int i;
  
  randNumber = random(1, 3); //generate a random number: 1 or 2
  
  if (randNumber == 1)
  {
    digitalWrite(dirpinb, HIGH); //set the big motor to rotate clockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    delay(15000); //wait 15 seconds
  
    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    delay(30000); //wait 30 seconds
    
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO3|["); //gobetwino opens audio3
    Serial.println("]#");
    
    delay(10000);
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(10000); //wait 10 seconds
    
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);  //turn off red LED
    digitalWrite(greenled, LOW); //turn off green LED
    
    digitalWrite(dirpinb, LOW); //set the big motor to rotate counterclockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps to return to rest position
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }    
    
    delay(30000); //wait 1 minute
    Serial.println("#S|SENDK|[0&%{F4}~]#"); //gobetwino hits ALT+F4 to quit video capture software    
  }
  else if (randNumber == 2)
  {
    digitalWrite(dirpinb, LOW); //set the big motor to rotate clockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    delay(15000); //wait 15 seconds
  
    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    delay(30000); //wait 30 seconds
    
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO3|["); //gobetwino opens audio3
    Serial.println("]#");
    
    delay(10000);
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(10000); //wait 10 seconds    
    
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);  //turn off red LED
    digitalWrite(greenled, LOW); //turn off green LED
    
    digitalWrite(dirpinb, HIGH); //set the big motor to rotate counterclockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps to return to rest position
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }    
    
    delay(30000); //wait 1 minute
    Serial.println("#S|SENDK|[0&%{F4}~]#"); //gobetwino hits ALT+F4 to quit video capture software    
  }
}

void FirstAlarm()
{
  int i;
  
  Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
  Serial.println("]#");
  delay(15000); //wait 15 seconds
  
  Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
  delay(30000); //wait 30 seconds
  
  randNumber = random(1, 3); //generate a random number: 1 or 2
  
  if (randNumber == 1)
  {
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO1|["); //gobetwino opens audio1
    Serial.println("]#");
    
    delay(10000); //wait 10 seconds
    
    digitalWrite(dirpinb, HIGH); //set the big motor to rotate clockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(1000); //wait 1 second
  
    for (i = 0; i<200; i++) //feed the fish AKA rotate the small motor 200 steps
    {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(8000);
    }
      
  delay(2000); //wait 2 seconds
  
  digitalWrite(dirpinb, LOW); //change the direction of the big motor to counterclockwise
  
  for (i=0; i<50; i++) //return the big motor to its starting position
  {
    digitalWrite(steppinb, LOW);
    digitalWrite(steppinb, HIGH);
    delayMicroseconds(8000);
  }
  
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);
    digitalWrite(greenled, LOW);  
  
    delay(10000);
  }
  else if (randNumber == 2)
  {
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO2|["); //gobetwino opens audio2
    Serial.println("]#");
    
    delay(10000); //wait 10 seconds
    
    digitalWrite(dirpinb, LOW); //set the big motor to rotate counterclockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(1000); //wait 1 second
  
    for (i = 0; i<200; i++) //feed the fish AKA rotate the small motor 200 steps
    {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(8000);
    }
      
  delay(2000); //wait 2 seconds
  
  digitalWrite(dirpinb, HIGH); //change the direction of the big motor to counterclockwise
  
  for (i=0; i<50; i++) //return the big motor to its starting position
  {
    digitalWrite(steppinb, LOW);
    digitalWrite(steppinb, HIGH);
    delayMicroseconds(8000);
  }
  
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);
    digitalWrite(greenled, LOW);  
  
    delay(10000);
  }
   
  delay(60000); //wait 1 minute
  Serial.println("#S|SENDK|[0&%{F4}~]#"); //gobetwino hits ALT+F4 to quit video capture software
}

void SecondSham()
{
  int i;
  
  randNumber = random(1, 3); //generate a random number: 1 or 2
  
  if (randNumber == 1)
  {
    digitalWrite(dirpinb, HIGH); //set the big motor to rotate clockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    delay(15000); //wait 15 seconds
  
    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    delay(30000); //wait 30 seconds
    
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO3|["); //gobetwino opens audio3
    Serial.println("]#");
    
    delay(10000);
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(10000); //wait 10 seconds
    
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);  //turn off red LED
    digitalWrite(greenled, LOW); //turn off green LED
    
    digitalWrite(dirpinb, LOW); //set the big motor to rotate counterclockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps to return to rest position
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }    
    
    delay(30000); //wait 1 minute
    Serial.println("#S|SENDK|[0&%{F4}~]#"); //gobetwino hits ALT+F4 to quit video capture software    
  }
  else if (randNumber == 2)
  {
    digitalWrite(dirpinb, LOW); //set the big motor to rotate clockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    delay(15000); //wait 15 seconds
  
    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    delay(30000); //wait 30 seconds
    
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO3|["); //gobetwino opens audio3
    Serial.println("]#");
    
    delay(10000);
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(10000); //wait 10 seconds    
    
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);  //turn off red LED
    digitalWrite(greenled, LOW); //turn off green LED
    
    digitalWrite(dirpinb, HIGH); //set the big motor to rotate counterclockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps to return to rest position
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }    
    
    delay(30000); //wait 1 minute
    Serial.println("#S|SENDK|[0&%{F4}~]#"); //gobetwino hits ALT+F4 to quit video capture software    
  }
}

void SecondAlarm()
{
  int i;
  
  Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
  Serial.println("]#");
  delay(15000); //wait 15 seconds
  
  Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
  delay(30000); //wait 30 seconds
  
  randNumber = random(1, 3); //generate a random number: 1 or 2
  
  if (randNumber == 1)
  {
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO1|["); //gobetwino opens audio1
    Serial.println("]#");
    delay(10000); //wait 10 seconds
    
    digitalWrite(dirpinb, HIGH); //set the big motor to rotate clockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(1000); //wait 1 second
  
    for (i = 0; i<200; i++) //feed the fish AKA rotate the small motor 200 steps
    {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(8000);
    }
      
  delay(2000); //wait 2 seconds
  
  digitalWrite(dirpinb, LOW); //change the direction of the big motor to counterclockwise
  
  for (i=0; i<50; i++) //return the big motor to its starting position
  {
    digitalWrite(steppinb, LOW);
    digitalWrite(steppinb, HIGH);
    delayMicroseconds(8000);
  }
  
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);
    digitalWrite(greenled, LOW);  
  
    delay(10000);
  }
  else if (randNumber == 2)
  {
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO2|["); //gobetwino opens audio2
    Serial.println("]#");
    delay(10000); //wait 10 seconds
    
    digitalWrite(dirpinb, LOW); //set the big motor to rotate counterclockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(1000); //wait 1 second
  
    for (i = 0; i<200; i++) //feed the fish AKA rotate the small motor 200 steps
    {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(8000);
    }
      
  delay(2000); //wait 2 seconds
  
  digitalWrite(dirpinb, HIGH); //change the direction of the big motor to counterclockwise
  
  for (i=0; i<50; i++) //return the big motor to its starting position
  {
    digitalWrite(steppinb, LOW);
    digitalWrite(steppinb, HIGH);
    delayMicroseconds(8000);
  }
  
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);
    digitalWrite(greenled, LOW);  
  
    delay(10000);
  }
   
  delay(60000); //wait 1 minute
  Serial.println("#S|SENDK|[0&%{F4}~]#"); //gobetwino hits ALT+F4 to quit video capture software
}

void ThirdSham()
{
  int i;
  
  randNumber = random(1, 3); //generate a random number: 1 or 2
  
  if (randNumber == 1)
  {
    digitalWrite(dirpinb, HIGH); //set the big motor to rotate clockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    delay(15000); //wait 15 seconds
  
    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    delay(30000); //wait 30 seconds
    
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO3|["); //gobetwino opens audio3
    Serial.println("]#");
    
    delay(10000);
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(10000); //wait 10 seconds
    
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);  //turn off red LED
    digitalWrite(greenled, LOW); //turn off green LED
    
    digitalWrite(dirpinb, LOW); //set the big motor to rotate counterclockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps to return to rest position
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }    
    
    delay(30000); //wait 1 minute
    Serial.println("#S|SENDK|[0&%{F4}~]#"); //gobetwino hits ALT+F4 to quit video capture software    
  }
  else if (randNumber == 2)
  {
    digitalWrite(dirpinb, LOW); //set the big motor to rotate clockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    delay(15000); //wait 15 seconds
  
    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    delay(30000); //wait 30 seconds
    
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO3|["); //gobetwino opens audio3
    Serial.println("]#");
    
    delay(10000);
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(10000); //wait 10 seconds    
    
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);  //turn off red LED
    digitalWrite(greenled, LOW); //turn off green LED
    
    digitalWrite(dirpinb, HIGH); //set the big motor to rotate counterclockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps to return to rest position
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }    
    
    delay(30000); //wait 1 minute
    Serial.println("#S|SENDK|[0&%{F4}~]#"); //gobetwino hits ALT+F4 to quit video capture software    
  }
}

void ThirdAlarm()
{
  int i;
  
  Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
  Serial.println("]#");
  delay(15000); //wait 15 seconds
  
  Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
  delay(30000); //wait 30 seconds
  
  randNumber = random(1, 3); //generate a random number: 1 or 2
  
  if (randNumber == 1)
  {
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO1|["); //gobetwino opens audio1
    Serial.println("]#");
    delay(10000); //wait 10 seconds
    
    digitalWrite(dirpinb, HIGH); //set the big motor to rotate clockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(1000); //wait 1 second
  
    for (i = 0; i<200; i++) //feed the fish AKA rotate the small motor 200 steps
    {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(8000);
    }
      
  delay(2000); //wait 2 seconds
  
  digitalWrite(dirpinb, LOW); //change the direction of the big motor to counterclockwise
  
  for (i=0; i<50; i++) //return the big motor to its starting position
  {
    digitalWrite(steppinb, LOW);
    digitalWrite(steppinb, HIGH);
    delayMicroseconds(8000);
  }
  
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);
    digitalWrite(greenled, LOW);  
  
    delay(10000);
  }
  else if (randNumber == 2)
  {
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO2|["); //gobetwino opens audio2
    Serial.println("]#");
    delay(10000); //wait 10 seconds
    
    digitalWrite(dirpinb, LOW); //set the big motor to rotate counterclockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(1000); //wait 1 second
  
    for (i = 0; i<200; i++) //feed the fish AKA rotate the small motor 200 steps
    {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(8000);
    }
      
  delay(2000); //wait 2 seconds
  
  digitalWrite(dirpinb, HIGH); //change the direction of the big motor to counterclockwise
  
  for (i=0; i<50; i++) //return the big motor to its starting position
  {
    digitalWrite(steppinb, LOW);
    digitalWrite(steppinb, HIGH);
    delayMicroseconds(8000);
  }
  
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);
    digitalWrite(greenled, LOW);  
  
    delay(10000);
  }
   
  delay(60000); //wait 1 minute
  Serial.println("#S|SENDK|[0&%{F4}~]#"); //gobetwino hits ALT+F4 to quit video capture software
}

void FourthSham()
{
  int i;
  
  randNumber = random(1, 3); //generate a random number: 1 or 2
  
  if (randNumber == 1)
  {
    digitalWrite(dirpinb, HIGH); //set the big motor to rotate clockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    delay(15000); //wait 15 seconds
  
    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    delay(30000); //wait 30 seconds
    
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO3|["); //gobetwino opens audio3
    Serial.println("]#");
    
    delay(10000);
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(10000); //wait 10 seconds
    
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);  //turn off red LED
    digitalWrite(greenled, LOW); //turn off green LED
    
    digitalWrite(dirpinb, LOW); //set the big motor to rotate counterclockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps to return to rest position
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }    
    
    delay(30000); //wait 1 minute
    Serial.println("#S|SENDK|[0&%{F4}~]#"); //gobetwino hits ALT+F4 to quit video capture software    
  }
  else if (randNumber == 2)
  {
    digitalWrite(dirpinb, LOW); //set the big motor to rotate clockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    delay(15000); //wait 15 seconds
  
    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    delay(30000); //wait 30 seconds
    
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO3|["); //gobetwino opens audio3
    Serial.println("]#");
    
    delay(10000);
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(10000); //wait 10 seconds    
    
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);  //turn off red LED
    digitalWrite(greenled, LOW); //turn off green LED
    
    digitalWrite(dirpinb, HIGH); //set the big motor to rotate counterclockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps to return to rest position
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }    
    
    delay(30000); //wait 1 minute
    Serial.println("#S|SENDK|[0&%{F4}~]#"); //gobetwino hits ALT+F4 to quit video capture software    
  }
}

void FourthAlarm()
{
  int i;
  
  Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
  Serial.println("]#");
  delay(15000); //wait 15 seconds
  
  Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
  delay(30000); //wait 30 seconds
  
  randNumber = random(1, 3); //generate a random number: 1 or 2
  
  if (randNumber == 1)
  {
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO1|["); //gobetwino opens audio1
    Serial.println("]#");
    delay(10000); //wait 10 seconds
    
    digitalWrite(dirpinb, HIGH); //set the big motor to rotate clockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(1000); //wait 1 second
  
    for (i = 0; i<200; i++) //feed the fish AKA rotate the small motor 200 steps
    {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(8000);
    }
      
  delay(2000); //wait 2 seconds
  
  digitalWrite(dirpinb, LOW); //change the direction of the big motor to counterclockwise
  
  for (i=0; i<50; i++) //return the big motor to its starting position
  {
    digitalWrite(steppinb, LOW);
    digitalWrite(steppinb, HIGH);
    delayMicroseconds(8000);
  }
  
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);
    digitalWrite(greenled, LOW);  
  
    delay(10000);
  }
  else if (randNumber == 2)
  {
    digitalWrite(redled, HIGH);  //turn on red LED
    digitalWrite(greenled, HIGH); //turn on green LED
    
    Serial.print("#S|AUDIO2|["); //gobetwino opens audio2
    Serial.println("]#");
    delay(10000); //wait 10 seconds
    
    digitalWrite(dirpinb, LOW); //set the big motor to rotate counterclockwise
    digitalWrite(dirpin, LOW); //set the small motor to rotate clockwise
    
    for (i = 0; i<50; i++) //rotate the big motor 50 steps
    {
     digitalWrite(steppinb, LOW);
     digitalWrite(steppinb, HIGH);
     delayMicroseconds(8000);
    }
    
    delay(1000); //wait 1 second
  
    for (i = 0; i<200; i++) //feed the fish AKA rotate the small motor 200 steps
    {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(8000);
    }
      
  delay(2000); //wait 2 seconds
  
  digitalWrite(dirpinb, HIGH); //change the direction of the big motor to counterclockwise
  
  for (i=0; i<50; i++) //return the big motor to its starting position
  {
    digitalWrite(steppinb, LOW);
    digitalWrite(steppinb, HIGH);
    delayMicroseconds(8000);
  }
  
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);
    digitalWrite(greenled, LOW);  
  
    delay(10000);
  }
   
  delay(60000); //wait 1 minute
  Serial.println("#S|SENDK|[0&%{F4}~]#"); //gobetwino hits ALT+F4 to quit video capture software
}
