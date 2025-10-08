const int buttonPin = 2;
const int RledPin = 3;
const int GledPin = 4;
const int BledPin = 5;

int ledcolor = 0;              // current color index
bool buttonPressed = false;    // tracks button press state
bool ledColorOrder = true;     // true = forward, false = reverse
unsigned long previousMillis = 0;
const long interval = 1000;    // 1 second per color

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // button to GND
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // toggle color order on button press
  if (buttonState == LOW && !buttonPressed) { 
    ledColorOrder = !ledColorOrder;
    buttonPressed = true;
    delay(200); // debounce
  }
  if (buttonState == HIGH && buttonPressed) {
    buttonPressed = false;
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ledColorOrder) {
      ledcolor++;
      if (ledcolor > 3) ledcolor = 0;
    } else {
      ledcolor--;
      if (ledcolor < 0) ledcolor = 3;
    }

    // set LED color (LOW = ON for common anode)
    if (ledcolor == 0) {
      // Red
      digitalWrite(RledPin, LOW);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, HIGH);
    } 
    else if (ledcolor == 1) {
      // Green
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, LOW);
      digitalWrite(BledPin, HIGH);
    } 
    else if (ledcolor == 2) {
      // Blue
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, LOW);
    } 
    else if (ledcolor == 3) {
      // White
      digitalWrite(RledPin, LOW);
      digitalWrite(GledPin, LOW);
      digitalWrite(BledPin, LOW);
    }
  }
}


