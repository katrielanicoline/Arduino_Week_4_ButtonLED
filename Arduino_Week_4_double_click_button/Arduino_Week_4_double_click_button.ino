const int buttonPin = 2; 
const int RledPin = 3; 
const int GledPin = 4; 
const int BledPin = 5; 

int buttonState = 0; 
int ledcolor = 0;
bool ButtonPressed = false;

unsigned long lastPressTime = 0;   // for double click timing
unsigned long doubleClickGap = 400; // max gap (ms) between clicks
bool ledsOff = false;              // flag to keep LEDs OFF

void setup() {
  pinMode(RledPin, OUTPUT); 
  pinMode(GledPin, OUTPUT); 
  pinMode(BledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && !ButtonPressed) {
    unsigned long now = millis();

    // check double click
    if (now - lastPressTime < doubleClickGap) {
      ledsOff = !ledsOff; 
      ledcolor = 0;        
    } else {
      if (!ledsOff) {
        ledcolor = ledcolor + 1;
      }
    }
    lastPressTime = now;
    ButtonPressed = true;
  }

  if (buttonState == LOW && ButtonPressed) {
    ButtonPressed = false;
  }

  if (ledsOff) {
    // force OFF
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
    return;
  }

  if (ledcolor == 0){
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 1) {
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if(ledcolor == 2) {
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
  else if(ledcolor == 3){
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }
  else if(ledcolor == 4){
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
  else if(ledcolor == 5){
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor == 6){
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }
  else if(ledcolor == 7){
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor == 8){
    ledcolor = 0;
  }
}
