enum STATE {
	STATE_WAIT,   // Wait for start
	STATE_COUNT,  // Counting down
	STATE_COMPLETE  // Timer 
};

#define UNIT_TIME 60
volatile int currentState = STATE_WAIT;			// Status
volatile unsigned long countSec = 0;			// Timer Value 1 = 1sec
volatile unsigned long startTime = 0;			// Start Time
volatile unsigned long lastInteruptTime = 0;	// The time that last interupt occured.

void setup(){
	pinMode(13, OUTPUT);    // LED
	pinMode(2, INPUT_PULLUP); // Switch
	attachInterrupt(0, OnSwitchPress, FALLING);
	Serial.begin(9600);
}

//#define UNIT_TIME (60*1000) //

void loop() {
	switch(currentState) {
	case STATE_COUNT:
		Blink(1000, 1000);
		break;

	case STATE_COMPLETE:
		Blink(200, 200);
		break;

	case STATE_WAIT:
		default:
		break;
	}
}
/** 
Judge Timeout
*/
bool IsTimeOut(int count, unsigned long start) {
	bool ret = false;
	if (currentState != STATE_COUNT) return ret;
	unsigned long elapsedSec = (millis() - startTime) / 1000;
	Serial.print("elapsedSec is ");
	Serial.println(elapsedSec, DEC);
	if (elapsedSec >= count) {
		ret = true;
		currentState = STATE_COMPLETE;
	}
	return ret;
}

/**
* Blink LED
*/
void Blink(int onInverval, int offInverval) {
	if (IsTimeOut(countSec, startTime)) return;
	// Turn on the LED
	if (onInverval != 0) {
		digitalWrite(13, HIGH);
		delay(onInverval);
	}

	if (offInverval != 0) {
		digitalWrite(13, LOW);
		if (IsTimeOut(countSec, startTime)) return;
		// Turn off the LED
		delay(offInverval);
	}
}

/**
* Debug information output
*/
void debugInfo() {
	Serial.print("Count is ");
	Serial.println(countSec, DEC);
	Serial.print("Start Time is ");
	Serial.println(startTime, DEC);
	Serial.print("Current Time is ");
	Serial.println(millis(), DEC);
}

/**
* Switch Interupt
*/
void OnSwitchPress() {
	if (millis() - lastInteruptTime < 500 ) {
		return;
	}
	lastInteruptTime = millis();
	Serial.println("PRESSED");
	switch(currentState) {
	case STATE_COUNT:
		countSec += UNIT_TIME;
		debugInfo();
		break;

	case STATE_COMPLETE:
		currentState = STATE_WAIT;
		// Turn off the LED
		digitalWrite(13, LOW);
		countSec = 0;
		break;

	case STATE_WAIT:
		currentState = STATE_COUNT;
		countSec = 1 * UNIT_TIME;
		startTime = millis();
		debugInfo();
		break;

	default:
		break;
	}
}



