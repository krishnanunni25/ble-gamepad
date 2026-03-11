#include <BleGamepad.h>

BleGamepad bleGamepad("ESP32 Gamepad", "ESP32", 100);
// BleGamepad(Device Name, Manufacturer Name, Initial Battery Level %)

#define JOY_X 34
#define JOY_Y 35

#define BTN_TRIANGLE 26
#define BTN_CIRCLE   33
#define BTN_CROSS    32
#define BTN_SQUARE   25

bool lastTriangle = false;
bool lastCircle   = false;
bool lastCross    = false;
bool lastSquare   = false;

// Calibration values
int joyXCenter = 0;
int joyYCenter = 0;
int joyDeadzone = 200; 
// Deadzone in raw ADC units

void setup() {
  Serial.begin(115200);

  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  pinMode(BTN_TRIANGLE, INPUT_PULLUP);
  pinMode(BTN_CIRCLE, INPUT_PULLUP);
  pinMode(BTN_CROSS, INPUT_PULLUP);
  pinMode(BTN_SQUARE, INPUT_PULLUP);

  bleGamepad.begin();

  delay(1000); 
  // Time delay before calibration

  // Take initial readings from joystick as center position
  joyXCenter = analogRead(JOY_X);
  joyYCenter = analogRead(JOY_Y);

  Serial.print("Calibrated center X: ");
  Serial.println(joyXCenter);
  Serial.print("Calibrated center Y: ");
  Serial.println(joyYCenter);
}

void loop() {
  if (bleGamepad.isConnected()) {
    int rawX = analogRead(JOY_X);
    int rawY = analogRead(JOY_Y);

    // Offset from center
    int offsetX = rawX - joyXCenter;
    int offsetY = rawY - joyYCenter;

    // Apply deadzone
    if (abs(offsetX) < joyDeadzone) offsetX = 0;
    if (abs(offsetY) < joyDeadzone) offsetY = 0;

    // Map offsets to full HID range
    int16_t xValue = 0;
    int16_t yValue = 0;

    if (offsetX >= 0)
      xValue = map(offsetX, 0, 4095 - joyXCenter, 0, 32767);
    else
      xValue = map(offsetX, -joyXCenter, 0, -32767, 0);

    if (offsetY >= 0)
      yValue = map(offsetY, 0, 4095 - joyYCenter, 0, -32767); // Inverted Y
    else
      yValue = map(offsetY, -joyYCenter, 0, 32767, 0);

    bleGamepad.setLeftThumb(xValue, yValue);

    // --- Triangle Button (1) ---
    bool triState = (digitalRead(BTN_TRIANGLE) == LOW);
    if (triState != lastTriangle) {
      if (triState) bleGamepad.press(1);
      else bleGamepad.release(1);
      lastTriangle = triState;
    }

    // --- Circle Button (2) ---
    bool cirState = (digitalRead(BTN_CIRCLE) == LOW);
    if (cirState != lastCircle) {
      if (cirState) bleGamepad.press(2);
      else bleGamepad.release(2);
      lastCircle = cirState;
    }

    // --- Cross Button (3) ---
    bool crossState = (digitalRead(BTN_CROSS) == LOW);
    if (crossState != lastCross) {
      if (crossState) bleGamepad.press(3);
      else bleGamepad.release(3);
      lastCross = crossState;
    }

    // --- Square Button (4) ---
    bool squareState = (digitalRead(BTN_SQUARE) == LOW);
    if (squareState != lastSquare) {
      if (squareState) bleGamepad.press(4);
      else bleGamepad.release(4);
      lastSquare = squareState;
    }

    bleGamepad.sendReport();
  }

  delay(10);
}
