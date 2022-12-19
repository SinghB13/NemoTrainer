#include <Time.h>
#include <TimeAlarms.h>

int dirpin = 11; //small motor
int steppin = 12;

int dirpinb = 8; //big motor
int steppinb = 9;

int greenled = 5; //green LED
int redled = 3; //red LED

int redsensor = 2; //proximity sensor on "red" side
int greensensor = 10; //proximity sensor on "green" side

int redsensorvalue;
int greensensorvalue;

void setup()
{
  Serial.begin(9600); //initialize communication with chip

  setTime(1,27,45,1,1,11); //set time in 24 hr format (7:00:00 AM, January 1st, 2011)

//Set alarm times and dates relative to the time and date in the line above. The time can be changed to the actual time;
//however, the date must be left the same (Jan 1, 2011)

  Alarm.alarmRepeat(dowSaturday,7,41,0, Test); //TEST

  Alarm.alarmRepeat(dowSaturday,8,0,0, UptoUp); //set first alarm time 
  Alarm.alarmRepeat(dowSaturday,10,0,0, UptoDown); //set second alarm time
  Alarm.alarmRepeat(dowSaturday,12,0,0, DowntoUp); //set third alarm time
  Alarm.alarmRepeat(dowSaturday,17,0,0, UptoDown); //set fourth alarm time
  Alarm.alarmRepeat(dowSaturday,19,0,0, DowntoDown); //set fifth alarm time
  Alarm.alarmRepeat(dowSaturday,21,0,0, DowntoUp); //set sixth alarm time

  Alarm.alarmRepeat(dowSunday,8,0,0, UptoUp); //set first alarm time 
  Alarm.alarmRepeat(dowSunday,10,0,0, UptoDown); //set second alarm time
  Alarm.alarmRepeat(dowSunday,12,0,0, DowntoDown); //set third alarm time
  Alarm.alarmRepeat(dowSunday,17,0,0, DowntoUp); //set fourth alarm time
  Alarm.alarmRepeat(dowSunday,19,0,0, UptoDown); //set fifth alarm time
  Alarm.alarmRepeat(dowSunday,21,0,0, DowntoUp); //set sixth alarm time
  
  Alarm.alarmRepeat(dowMonday,8,0,0, UptoDown); //set first alarm time 
  Alarm.alarmRepeat(dowMonday,10,0,0, DowntoDown); //set second alarm time 
  Alarm.alarmRepeat(dowMonday,12,0,0, DowntoDown); //set third alarm time
  Alarm.alarmRepeat(dowMonday,17,0,0, DowntoUp); //set fourth alarm time
  Alarm.alarmRepeat(dowMonday,19,0,0, UptoDown); //set fifth alarm time
  Alarm.alarmRepeat(dowMonday,21,0,0, UptoUp); //set sixth alarm time  
  

  pinMode(redsensor, INPUT);
  pinMode(greensensor, INPUT);
  pinMode(greenled, OUTPUT); 
  pinMode(redled, OUTPUT);
  pinMode(dirpin, OUTPUT);
  pinMode(steppin, OUTPUT);
  pinMode(dirpinb, OUTPUT);
  pinMode(steppinb, OUTPUT);
}

void loop()
{
  Alarm.delay(0);
}

void Test()
{
  int i;

  Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
  Serial.println("]#");
  Alarm.delay(15000); //wait 15 seconds

  Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
  Alarm.delay(5000); //wait 5 seconds

  Serial.print("#S|AUDIOTEST|["); //gobetwino opens audiotest
  Serial.println("]#");

  Alarm.delay(5000); //wait 3 seconds

  Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
 
  Alarm.delay(10000); //wait 10 seconds
  Serial.println("#S|SENDK|[0&{F7}]#"); //gobetwino hits F7 to stop recording

}

void UptoDown()
{
  int i;
  int j = 0;

  Alarm.delay(5000); //wait 10 seconds

  greensensorvalue = digitalRead(greensensor); //get sensor reading
 
  while(greensensorvalue == HIGH) //only allow a maximum of 10 repetitions of this loop
  {
    if(j == 10)
    {
      goto endrun;
    }

    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    Alarm.delay(15000); //wait 15 seconds

    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    Alarm.delay(5000); //wait 5 seconds

    Serial.print("#S|AUDIO1|["); //gobetwino opens audio1
    Serial.println("]#");
    Alarm.delay(500);

    greensensorvalue = digitalRead(greensensor); //get sensor reading
    if(greensensorvalue == LOW)
    {
      goto feed; //if beam is broken, feed the fish
    }
    Alarm.delay(500);

    for(int m = 0; m < 700; m++) //get sensor reading while sound is playing
    {
      Alarm.delay(10); 
      greensensorvalue = digitalRead(greensensor);
      if(greensensorvalue == LOW)
      {
        goto feed; //if beam is broken, feed the fish
      }
    }
    
    Alarm.delay(5000);
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(greenled, LOW);
    Serial.println("#S|SENDK|[0&{F7}]#"); //gobetwino hits F7 to stop recording

    Alarm.delay(300000); //wait 5 minutes before running the loop again

    j++;
  }

feed:
  Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC  
  digitalWrite(greenled, LOW);  
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);


  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200); //wait 1 second
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);


  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200); 

endrun:
  Alarm.delay(12000); //wait 12 seconds
  Serial.println("#S|SENDK|[0&{F7}]#"); //gobetwino hits F7 to stop recording

  Alarm.delay(3000000); //wait 50 minutes

  digitalWrite(dirpinb, LOW); //change the direction of the big motor to counterclockwise

  for (i=0; i<100; i++) //move the big motor to the next position
  {
    digitalWrite(steppinb, LOW);
    digitalWrite(steppinb, HIGH);
    delayMicroseconds(8000);
  }
}

void UptoUp()
{
  int i;
  int j = 0;

  /*  for(int n = 0; n < 11; n++)
   {
   digitalWrite(whiteled, HIGH);
   Alarm.delay(500);
   digitalWrite(whiteled, LOW);
   Alarm.delay(500);
   } 
   */
  Alarm.delay(5000); //wait 10 seconds

  greensensorvalue = digitalRead(greensensor);

  while(greensensorvalue == HIGH)
  {
    if(j == 10)
    {
      goto endrun;
    }

    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    Alarm.delay(15000); //wait 15 seconds

    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    Alarm.delay(5000); //wait 5 seconds

    Serial.print("#S|AUDIO1|["); //gobetwino opens audio1
    Serial.println("]#");
    Alarm.delay(500);

    greensensorvalue = digitalRead(greensensor);
    if(greensensorvalue == LOW)
    {
      goto feed;
    }
    Alarm.delay(500);

    digitalWrite(greenled, LOW); //turn on green LED

    for(int m = 0; m < 700; m++)
    {
      Alarm.delay(10); 
      greensensorvalue = digitalRead(greensensor);
      if(greensensorvalue == LOW)
      {
        goto feed;
      }
    }
    
    Alarm.delay(5000);
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(greenled, LOW);
    Serial.println("#S|SENDK|[0&{F7}]#"); //gobetwino hits F7 to stop recording

    Alarm.delay(300000);

    j++;
  }

feed:
  Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC  
  digitalWrite(greenled, LOW);  
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);


  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200); //wait 1 second
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);


  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200); //wait 1 second

endrun:
  Alarm.delay(12000); //wait 10 seconds
  Serial.println("#S|SENDK|[0&{F7}]#"); //gobetwino hits F7 to stop recording
}

void UptoDownLED()
{
  int i;
  int j = 0;

  /*  for(int n = 0; n < 11; n++)
   {
   digitalWrite(whiteled, HIGH);
   Alarm.delay(500);
   digitalWrite(whiteled, LOW);
   Alarm.delay(500);
   } 
   */
  Alarm.delay(5000); //wait 10 seconds

  greensensorvalue = digitalRead(greensensor);

  while(greensensorvalue == HIGH)
  {
    if(j == 10)
    {
      goto endrun;
    }

    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    Alarm.delay(15000); //wait 15 seconds

    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    Alarm.delay(5000); //wait 5 seconds

    Serial.print("#S|AUDIO1|["); //gobetwino opens audio1
    Serial.println("]#");
    Alarm.delay(500);

    greensensorvalue = digitalRead(greensensor);
    if(greensensorvalue == LOW)
    {
      goto feed;
    }
    Alarm.delay(500);

    digitalWrite(greenled, HIGH); //turn on green LED

    for(int m = 0; m < 700; m++)
    {
      Alarm.delay(10); //wait 1 seconds
      greensensorvalue = digitalRead(greensensor);
      if(greensensorvalue == LOW)
      {
        goto feed;
      }
    }
    
    Alarm.delay(5000);
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(greenled, LOW);
    Serial.println("#S|SENDK|[0&{F7}]#"); //gobetwino hits F7 to stop recording

    Alarm.delay(300000);

    j++;
  }

feed:
  Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC  
  digitalWrite(greenled, LOW);  
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);


  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200); //wait 1 second
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);


  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);

endrun:
  Alarm.delay(12000); //wait 10 seconds
  Serial.println("#S|SENDK|[0&{F7}]#"); //gobetwino hits F7 to stop recording

  Alarm.delay(3000000);

  digitalWrite(dirpinb, LOW); //change the direction of the big motor to counterclockwise

  for (i=0; i<100; i++) //return the big motor to its starting position
  {
    digitalWrite(steppinb, LOW);
    digitalWrite(steppinb, HIGH);
    delayMicroseconds(8000);
  }
}

void DowntoUp()
{
  int i;
  int j = 0;

  /*  for(int n = 0; n < 11; n++)
   {
   digitalWrite(whiteled, HIGH);
   Alarm.delay(500);
   digitalWrite(whiteled, LOW);
   Alarm.delay(500);
   } 
   */  Alarm.delay(5000); //wait 10 seconds

  redsensorvalue = digitalRead(redsensor);

  while(redsensorvalue == HIGH)
  {
    if(j == 10)
    {
      goto endrun;
    }

    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    Alarm.delay(15000); //wait 15 seconds

    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    Alarm.delay(5000); //wait 5 seconds

    Serial.print("#S|AUDIO2|["); //gobetwino opens audio1
    Serial.println("]#");
    Alarm.delay(500);

    redsensorvalue = digitalRead(redsensor);
    if(redsensorvalue == LOW)
    {
      goto feed;
    }
    Alarm.delay(500);

    digitalWrite(redled, LOW); //turn on green LED

    for(int m = 0; m < 700; m++)
    {
      Alarm.delay(10); //wait 1 seconds
      redsensorvalue = digitalRead(redsensor);
      if(redsensorvalue == LOW)
      {
        goto feed;
      }
    }
    
    Alarm.delay(5000);
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);
    Serial.println("#S|SENDK|[0&{F7}]#"); //gobetwino hits F7 to stop recording

    Alarm.delay(300000);

    j++;
  }

feed:
  Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC  
  digitalWrite(redled, LOW);  
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);


  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200); //wait 1 second
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);


  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);

endrun:
  Alarm.delay(12000); //wait 10 seconds
  Serial.println("#S|SENDK|[0&{F7}]#"); //gobetwino hits F7 to stop recording

  Alarm.delay(3000000);

  digitalWrite(dirpinb, HIGH); //change the direction of the big motor to counterclockwise

  for (i=0; i<100; i++) //return the big motor to its starting position
  {
    digitalWrite(steppinb, LOW);
    digitalWrite(steppinb, HIGH);
    delayMicroseconds(8000);
  }
}

void DowntoDown()
{
  int i;
  int j = 0;

  /*  for(int n = 0; n < 11; n++)
   {
   digitalWrite(whiteled, HIGH);
   Alarm.delay(500);
   digitalWrite(whiteled, LOW);
   Alarm.delay(500);
   } 
   */  Alarm.delay(5000); //wait 10 seconds

  redsensorvalue = digitalRead(redsensor);

  while(redsensorvalue == HIGH)
  {
    if(j == 10)
    {
      goto endrun;
    }

    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    Alarm.delay(15000); //wait 15 seconds

    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    Alarm.delay(5000); //wait 5 seconds

    Serial.print("#S|AUDIO2|["); //gobetwino opens audio1
    Serial.println("]#");
    Alarm.delay(500);

    redsensorvalue = digitalRead(redsensor);
    if(redsensorvalue == LOW)
    {
      goto feed;
    }
    Alarm.delay(500);

    digitalWrite(redled, LOW); //turn on green LED

    for(int m = 0; m < 700; m++)
    {
      Alarm.delay(10); //wait 1 seconds
      redsensorvalue = digitalRead(redsensor);
      if(redsensorvalue == LOW)
      {
        goto feed;
      }
    }
    
    Alarm.delay(5000);
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);
    Serial.println("#S|SENDK|[0&{F7}]#"); //gobetwino hits F7 to stop recording

    Alarm.delay(300000);

    j++;
  }

feed:
  Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC  
  digitalWrite(redled, LOW);  
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);


  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200); //wait 1 second
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);


  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);

endrun:
  Alarm.delay(12000); //wait 10 seconds
  Serial.println("#S|SENDK|[0&{F7}]#"); //gobetwino hits F7 to stop recording
}

void DowntoUpLED()
{
  int i;
  int j = 0;

  /*  for(int n = 0; n < 11; n++)
   {
   digitalWrite(whiteled, HIGH);
   Alarm.delay(500);
   digitalWrite(whiteled, LOW);
   Alarm.delay(500);
   } 
   */

  Alarm.delay(5000); //wait 10 seconds

  redsensorvalue = digitalRead(redsensor);

  while(redsensorvalue == HIGH)
  {
    if(j == 10)
    {
      goto endrun;
    }

    Serial.print("#S|OPENVID|["); //gobetwino opens video capture software
    Serial.println("]#");
    Alarm.delay(15000); //wait 15 seconds

    Serial.println("#S|SENDK|[0&{F5}]#"); //gobetwino hits F5 to start recording
    Alarm.delay(5000); //wait 5 seconds

    Serial.print("#S|AUDIO2|["); //gobetwino opens audio1
    Serial.println("]#");
    Alarm.delay(500);

    redsensorvalue = digitalRead(redsensor);
    if(redsensorvalue == LOW)
    {
      goto feed;
    }
    Alarm.delay(500);

    digitalWrite(redled, HIGH); //turn on green LED

    for(int m = 0; m < 700; m++)
    {
      Alarm.delay(10); //wait 1 seconds
      redsensorvalue = digitalRead(redsensor);
      if(redsensorvalue == LOW)
      {
        goto feed;
      }
    }
    
    Alarm.delay(5000);    
    Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC
    digitalWrite(redled, LOW);
    Serial.println("#S|SENDK|[0&{F7}]#"); //gobetwino hits F7 to stop recording

    Alarm.delay(300000);

    j++;
  }

feed:
  Serial.println("#S|SENDK|[1&^q]#"); //gobetwino quits VLC  
  digitalWrite(redled, LOW);  
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);


  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200); //wait 1 second
  digitalWrite(dirpin, HIGH);

  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200);
  digitalWrite(dirpin, LOW);


  for (i = 0; i<4; i++) //feed the fish AKA rotate the small motor 200 steps
  {
    digitalWrite(steppin, LOW);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(5000);
  }

  Alarm.delay(200); //wait 1 second

endrun:
  Alarm.delay(12000); //wait 10 seconds
  Serial.println("#S|SENDK|[0&{F7}]#"); //gobetwino hits F7 to stop recording

  Alarm.delay(3000000);

  digitalWrite(dirpinb, HIGH); //change the direction of the big motor to counterclockwise

  for (i=0; i<100; i++) //return the big motor to its starting position
  {
    digitalWrite(steppinb, LOW);
    digitalWrite(steppinb, HIGH);
    delayMicroseconds(8000);
  }
}




