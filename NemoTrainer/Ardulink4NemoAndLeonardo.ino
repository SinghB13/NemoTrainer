#define CLOCKWISE HIGH
#define COUNTERCLOCKWISE LOW

#define FEEDER_DIRPIN 11
#define FEEDER_STEPPIN 12

#define ARM_DIRPIN 8
#define ARM_STEPPIN 9

#define digitalPinListeningNum 14 // Change 14 if you have a different number of pins.

boolean digitalPinListening[digitalPinListeningNum]; // Array used to know which pins on the Arduino must be listening.
int digitalPinListenedValue[digitalPinListeningNum]; // Array used to know which value is read last time.

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string message from Ardulink is complete

void setup() {
  // initialize serial
  Serial.begin(115200);
  while(!Serial); // Wait until Serial not connected (because difference between Leonardo and Micro with UNO and others)

  //set to false all listen variable
  int index = 0;
  for (index = 0; index < digitalPinListeningNum; index++) {
    digitalPinListening[index] = false;
    digitalPinListenedValue[index] = -1;
  }

  // Turn off everything (not on RXTX)
  for (index = 2; index < digitalPinListeningNum; index++) {
    pinMode(index, OUTPUT);
    digitalWrite(index, LOW);
  }
  
  // Setup ARM and FEEDER pins
  pinMode(FEEDER_DIRPIN, OUTPUT);
  pinMode(FEEDER_STEPPIN, OUTPUT);  
  pinMode(ARM_DIRPIN, OUTPUT);
  pinMode(ARM_STEPPIN, OUTPUT);
}

void loop() {
  
  while (Serial.available() && !stringComplete) {
     // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  
  // when a newline arrives:
  if (stringComplete) {
    
    if(inputString.startsWith("alp://")) { // OK is a message I know
    
      boolean msgRecognized = true;
      
      if(inputString.substring(6,10) == "ppsw") { // Power Pin Switch (used to turn on/off LEDs)
          int separatorPosition = inputString.indexOf('/', 11 );
          String pin = inputString.substring(11,separatorPosition);
          String power = inputString.substring(separatorPosition + 1);
          pinMode(pin.toInt(), OUTPUT);
          if(power.toInt() == 1) {
            digitalWrite(pin.toInt(), HIGH);
          } else if(power.toInt() == 0) {
            digitalWrite(pin.toInt(), LOW);
          }
      } else if(inputString.substring(6,10) == "srld") { // Start Listen Digital Pin (used for sensors)
          String pin = inputString.substring(11);
          digitalPinListening[pin.toInt()] = true;
          digitalPinListenedValue[pin.toInt()] = -1; // Ensure a message back when start listen happens.
          pinMode(pin.toInt(), INPUT);
      } else if(inputString.substring(6,10) == "spld") { // Stop Listen Digital Pin (used for sensors)
          String pin = inputString.substring(11);
          digitalPinListening[pin.toInt()] = false;
          digitalPinListenedValue[pin.toInt()] = -1; // Ensure a message back when start listen happens.
      } else if(inputString.substring(6,10) == "cust") { // Custom Message
        // Used to activate feeder and arm
        int separatorPosition = inputString.indexOf('/', 11 );
        int messageIdPosition = inputString.indexOf('?', 11 );
        String customId = inputString.substring(11,separatorPosition);
        String value = inputString.substring(separatorPosition + 1, messageIdPosition);
        String value2 = value; // actually I need just to define a value2 variable...
        int valueSeparatorPosition = value.indexOf('_');
        if(valueSeparatorPosition != -1) {
                value2 = String(value); // I need another object (message contains two information)
        	value  = value.substring(0, valueSeparatorPosition);
        	value2 = value2.substring(valueSeparatorPosition + 1);
        }
        int steps = value.toInt() * 5 / 9; // 360 degrees = 200 steps so multiply for 5 and divide for 9
        if(customId == "simpleFeed") {
          move(FEEDER_DIRPIN, FEEDER_STEPPIN, steps, CLOCKWISE);
        } else if(customId == "enhancedFeed") {
          int repete = value2.toInt();
          for(int i = 0; i < repete; i++) {
	          move(FEEDER_DIRPIN, FEEDER_STEPPIN, steps, CLOCKWISE);
	          delayMicroseconds(8000);
	          move(FEEDER_DIRPIN, FEEDER_STEPPIN, 2*steps, COUNTERCLOCKWISE);
	          delayMicroseconds(8000);
	          move(FEEDER_DIRPIN, FEEDER_STEPPIN, steps, CLOCKWISE);
          }
        } else if(customId == "arm_clockwise") {
          move(ARM_DIRPIN, ARM_STEPPIN, steps, CLOCKWISE);
        } else if(customId == "arm_counter") {
          move(ARM_DIRPIN, ARM_STEPPIN, steps, COUNTERCLOCKWISE);
        } else {
          msgRecognized = false; // this sketch doesn't know other messages in this case command is ko (not ok)
        }
      } else {
        msgRecognized = false; // this sketch doesn't know other messages in this case command is ko (not ok)
      }
      
      // Prepare reply message if caller supply a message id (this is general code you can reuse)
      int idPosition = inputString.indexOf("?id=");
      if(idPosition != -1) {
        String id = inputString.substring(idPosition + 4);
        // print the reply
        Serial.print("alp://rply/");
        if(msgRecognized) { // this sketch doesn't know other messages in this case command is ko (not ok)
          Serial.print("ok?id=");
        } else {
          Serial.print("ko?id=");
        }
        Serial.print(id);
        Serial.write(255); // End of Message
        Serial.flush();
      }
    }
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  // Send listen messages
  int index = 0;
  for (index = 0; index < digitalPinListeningNum; index++) {
    if(digitalPinListening[index] == true) {
      int value = digitalRead(index);
      if(value != digitalPinListenedValue[index]) {
        digitalPinListenedValue[index] = value;
        Serial.print("alp://dred/");
        Serial.print(index);
        Serial.print("/");
        Serial.print(value);
        Serial.write(255); // End of Message
        Serial.flush();
      }
    }
  }
    
}

void move(int dirpin, int steppin, int steps, int direct) { // Move arm or feeder

  digitalWrite(dirpin, direct); // Set direction
  int i;
  for (i = 0; i < steps; i++) {
   digitalWrite(steppin, LOW);
   digitalWrite(steppin, HIGH);
   delayMicroseconds(8000);
  }
}
