int minutePins[6] = {3,4,5,6,7,8};
int hourPins[4] = {9,10,11,12};

int loader[10] = {3,4,5,6,7,8,9,10,11,12};

int i = 0;
int x = 0;

void setup() {
  setPins();
}

void loop() {  
  if(millis() % 98 == 0) {
    turnOffLeds();
    if(i > 90) {i = 2;}
    else {i += 1;}
    x = i % 10;
    digitalWrite(loader[x],HIGH);
    digitalWrite(loader[x - 1],HIGH);
    digitalWrite(loader[x - 2],HIGH);
    delay(2);
  }    
}

/* This function sets all the pinmode for the hourPins */
void setPins() {
  for(int i = 0; i < sizeof(hourPins); i++) {
    pinMode(hourPins[i], OUTPUT);
  }
  for(int i = 0; i < sizeof(minutePins); i++) {
    pinMode(minutePins[i], OUTPUT);
  }
}

void turnOffLeds() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(loader[i], LOW);
  }
}
