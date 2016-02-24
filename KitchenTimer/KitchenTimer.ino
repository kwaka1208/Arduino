enum STATE {
  STATE_WAIT,   // Wait for start
  STATE_COUNT,    // Counting down
  STATE_COMPLETE  // Timer 
};

volatile int currentState = STATE_WAIT;     // Status
volatile int count = 0;         // Timer Value 1 = 1min
volatile unsigned long startTime = 0; // Start Time

void setup(){
	pinMode(13, OUTPUT);	// LED
	pinMode(11, INPUT_PULLUP);	// Switch
	attachInterrupt(0, SwitchPressed, FALLING);
  Serial.begin(9600);
}

#define UNIT_TIME (60*1000)


void loop() {
	switch(currentState) {
		case STATE_COUNT:
      Serial.println("COUNT:" + count);
			Blink(1000, 1000);
			break;
		case STATE_COMPLETE:
      Serial.println("COMPLETE");
			Blink(200, 200);
			break;
		case STATE_WAIT:
		default:
      Serial.println("WAIT");
			break;
	}
}
/** 
	Judge Timeout
*/
bool IsTimeOut(int count, unsigned long start) {
	bool ret = false;
	unsigned long now;
	long elapsed = (long)millis() - startTime;
	if ((long)(elapsed / UNIT_TIME) > (long)count) {
		ret = true;
		currentState = STATE_COMPLETE;
	}
	return ret;
}

void Blink(int onInverval, int offInverval) {
	if (IsTimeOut(count, startTime)) return;
	// Turn on the LED
	digitalWrite(13, HIGH);
	delay(onInverval);

	digitalWrite(13, LOW);
	if (IsTimeOut(count, startTime)) return;
	// Turn off the LED
	delay(offInverval);
}

/**
	Switch Interupt
*/

void SwitchPressed() {
  Serial.println("PRESSED");
	switch(currentState) {
		case STATE_COUNT:
			count++;
			break;
		case STATE_COMPLETE:
			currentState = STATE_WAIT;
			// Turn off the LED
			digitalWrite(13, LOW);
			count = 0;
			break;
		case STATE_WAIT:
			currentState = STATE_COUNT;
			startTime = millis();
			count++;
			break;
		default:
			break;
	}
}