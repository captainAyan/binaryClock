int minutePins[6] = {3,4,5,6,7,8};
int hourPins[4] = {9,10,11,12};

int minCounter = 0;
int hourCounter = 0;

int timeChangeButton = 2;
boolean changeTimeOn;

void setup() {
  Serial.begin(9600);
  setPins();
  pinMode(timeChangeButton, INPUT);
}

void loop() {
  
  if(millis() % 998 == 0) {
    if(minCounter < 59) {
      minCounter += 1;
    }
    else {
      minCounter = 0;
      if(hourCounter < 14) {
        hourCounter += 1;
      }
      else {
        hourCounter = 0;
      }
    }
    delay(2);
  }

  if(digitalRead(timeChangeButton) == HIGH) {
    if(changeTimeOn) {
      Serial.println("-----------");
      changeTimeOn = false;
      changeTime();
    }
  }
  else if(digitalRead(timeChangeButton) == LOW) {
    changeTimeOn = true;
  }
  
  decimalToBinary(hourCounter, 4);
  decimalToBinary(minCounter, 6);
   
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

/* Converts decimal to binary */
void decimalToBinary(int p, int len) {
  int res[len];
  for(int i=0; i<len; i++){
    res[i] = 0;
  }
  int l; // result of division
  int k; // remainder of division

  if(p == 0) {res[0] = 0;}
  if(p == 1) {res[0] = 1;}
  if(p >= 2) {
    for(int i = 0; true; i++) {
      l = (int) (p/2);
      k = (p-(2*l));
      res[i] = k;
      if(l >= 2) {
        p = l;
      }
      else {
        res[i+1] = l;
        break;
      }
    }
  }
  if(len == 4) {
    updateHourLeds(res);
  }
  else if(len == 6) {
    updateMinuteLeds(res);
  }
}

void updateHourLeds(int bin[4]) {
  for(int i = 0; i<4; i++) {  // iterating over all the bits
    if(bin[i] == 1){
      digitalWrite(hourPins[i], HIGH);
    }
    else if(bin[i] == 0){
      digitalWrite(hourPins[i], LOW);
    }
  }
}

void updateMinuteLeds(int bin[6]) {
  for(int i = 0; i<6; i++) {  // iterating over all the bits
    if(bin[i] == 1){
      digitalWrite(minutePins[i], HIGH);
    }
    else if(bin[i] == 0){
      digitalWrite(minutePins[i], LOW);
    }
  }
}

void changeTime() {
  hourCounter += 1;
  Serial.println("changing time");
}
