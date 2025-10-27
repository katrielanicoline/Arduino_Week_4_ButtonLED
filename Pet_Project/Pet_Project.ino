const int buttonPin = 8;    
const int RledPin = 9;       
const int GledPin = 10; 
const int BledPin = 11;      

int mood = 10;              
const int neutralMood = 10; 
int buttonState = 0;         
bool ButtonPressed = false;  

unsigned long touchedTimer = 0;     
unsigned long reducedTimer = 0;     
const long unTouchInterval = 5000;
const long reducedInterval = 1000;  

// too fast
int pressCount = 0;
unsigned long pressWindowStart = 0;
const unsigned long pressWindowDuration = 1000; 

// reset
unsigned long buttonPressStart = 0;
const unsigned long longPressDuration = 1500; 


void showLEDState(int m){
  int r = 0, g = 0, b = 0;

  if(m <= 10){
    float t = m / 10.0;
    r = (1.0 - t) * 255;
    g = t * 255;
    b = 0;
  } else {
    float t = (m - 10) / 10.0;
    r = 0;
    g = (1.0 - t) * 255;
    b = t * 255;
  }

  analogWrite(RledPin, 255 - r);
  analogWrite(GledPin, 255 - g);
  analogWrite(BledPin, 255 - b);
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  showLEDState(mood);
  touchedTimer = millis();
  reducedTimer = millis();
}

void loop() {

  showLEDState(mood);
  buttonState = digitalRead(buttonPin);

  unsigned long now = millis();

  
  if(buttonState == LOW && ButtonPressed == false){
    ButtonPressed = true;
    buttonPressStart = now;        
    touchedTimer = now;

   
    if(pressCount == 0){
      pressWindowStart = now;
    }

    
    if(now - pressWindowStart > pressWindowDuration){
      pressCount = 0;
      pressWindowStart = now;
    }

    pressCount++;
  }

  
  if(ButtonPressed && buttonState == LOW){
    if(now - buttonPressStart >= longPressDuration){
      mood = neutralMood;
      pressCount = 0;  
      showLEDState(mood);
      while(digitalRead(buttonPin) == LOW);
      delay(50); 
      ButtonPressed = false;
      return;
    }
  }

 
  if(buttonState == HIGH && ButtonPressed == true){
    ButtonPressed = false;

   
    if(now - buttonPressStart < longPressDuration){
   
      if(pressCount >= 5){
        mood = 0;
        pressCount = 0;
      }
      else{
        
        mood++;
        if(mood > 20) mood = 20;
      }
    }
  }

 
  unsigned long currentTimer = millis();
  if(currentTimer - touchedTimer > unTouchInterval){
    if(currentTimer - reducedTimer > reducedInterval){
      mood--;
      if(mood < 0) mood = 0;
      reducedTimer = currentTimer;
    }
  }
}

