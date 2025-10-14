const int buttonPin = 9;
const int RledPin = 2;
const int GledPin = 3;
const int BledPin = 4;

int buttonState = HIGH;
int lastButtonState = HIGH;
int ledcolor = 0;
int pressCount = 0;
unsigned long lastPressTime = 0;

void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); 
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading == LOW && lastButtonState == HIGH) {
    pressCount++;
    lastPressTime = millis();
    delay(200); 
  }
  lastButtonState = reading;

  if (pressCount > 0 && millis() - lastPressTime > 500) {
    if (pressCount == 1) {
      ledcolor++;
      if (ledcolor > 10) ledcolor = 0; 
    } 
    else if (pressCount == 2) {
      ledcolor = 0; 
    }
    pressCount = 0;
  }

  switch (ledcolor) {
    case 0: setColor(HIGH, HIGH, HIGH); break; 
    case 1: setColor(LOW, HIGH, HIGH); break;  
    case 2: setColor(LOW, LOW, HIGH); break;  
    case 3: setColor(HIGH, LOW, LOW); break;  
    case 4: setColor(LOW, HIGH, LOW); break;
    case 5: setColor(LOW, LOW, LOW); break;   
    case 6: setColor(HIGH, HIGH, LOW); break; 
    case 7: setColor(LOW, HIGH, LOW); break;   
    case 8: setColor(HIGH, LOW, HIGH); break;  
  }
}

void setColor(int r, int g, int b) {
  digitalWrite(RledPin, r);
  digitalWrite(GledPin, g);
  digitalWrite(BledPin, b);
}
