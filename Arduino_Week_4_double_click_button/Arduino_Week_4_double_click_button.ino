// === Pin Definitions ===
const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;
const int buttonPin = 8;

// === Mood Variables ===
int mood = 0;
const int neutralMood = 10;
int buttonState = 0;
bool ButtonPressed = false;

// === Timers ===
unsigned long reducedTimer = 0;
unsigned long touchedTimer = 0;

const long unTouchInterval = 5000;   // 5 seconds before mood drops
const long reducedInterval = 1000;   // Mood decreases every 1s after untouched

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Using internal pull-up resistor
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  mood = neutralMood;  // Start at neutral mood (10)
}

void loop() {
  showLEDState(mood);  // Update LED color based on current mood

  buttonState = digitalRead(buttonPin);

  // Button Press Detected (active LOW)
  if (buttonState == LOW && !ButtonPressed) {
    mood++;
    if (mood > 20) mood = 20;  // Limit to max mood
    touchedTimer = millis();   // Reset touch timer
    ButtonPressed = true;
  }

  // Button Released
  if (buttonState == HIGH && ButtonPressed) {
    ButtonPressed = false;
  }

  unsigned long currentTimer = millis();

  // If not touched for >5s, decrease mood every second
  if (currentTimer - touchedTimer > unTouchInterval) {
    if (currentTimer - reducedTimer > reducedInterval) {
      mood--;
      if (mood < 0) mood = 0;  // Don't go below 0
      reducedTimer = currentTimer;
    }
  }
}

void showLEDState(int mood) {
  int redValue = 0;
  int greenValue = 0;
  int blueValue = 0;

  if (mood <= 10) {
    // Transition from RED to GREEN (0 to 10)
    redValue = map(mood, 0, 10, 255, 0);
    greenValue = map(mood, 0, 10, 0, 255);
    blueValue = 0;
  } else {
    // Transition from GREEN to BLUE (10 to 20)
    redValue = 0;
    greenValue = map(mood, 10, 20, 255, 0);
    blueValue = map(mood, 10, 20, 0, 255);
  }

  // Invert for COMMON ANODE RGB LED
  analogWrite(RledPin, 255 - redValue);
  analogWrite(GledPin, 255 - greenValue);
  analogWrite(BledPin, 255 - blueValue);
}
