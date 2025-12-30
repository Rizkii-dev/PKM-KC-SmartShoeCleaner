/*
 * Project: Smart Shoe Exterior Cleaning Machine (PKM-KC)
 * Team: Kelompok 3 - Binus University
 * Description: Automated cleaning cycle based on IR sensor trigger.
 */

// --- PIN CONFIGURATION (Adjust these to match your wiring) ---
const int PIN_SENSOR    = 2;  // IR Sensor / Proximity Sensor Output
const int PIN_PUMP      = 3;  // Relay for Water Pump
const int PIN_MOTOR     = 4;  // Relay for Brush Motor
const int PIN_LED       = 13; // Indicator LED

// --- TIMING SETTINGS (Change these to tweak the process) ---
const int TIME_SPRAY    = 2000;  // How long pump runs (in milliseconds, 2000 = 2 sec)
const int TIME_BRUSH    = 10000; // How long brush spins (10000 = 10 sec)
const int TIME_DELAY    = 1000;  // Safety pause between steps

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);
  Serial.println("System Initializing...");

  // Set Pin Modes
  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_PUMP, OUTPUT);
  pinMode(PIN_MOTOR, OUTPUT);
  pinMode(PIN_LED, OUTPUT);

  // Ensure everything is OFF at startup
  // Note: Some relays are "Active LOW" (LOW = ON). 
  // If your relay turns on immediately, change LOW to HIGH below.
  digitalWrite(PIN_PUMP, LOW); 
  digitalWrite(PIN_MOTOR, LOW);
  digitalWrite(PIN_LED, LOW);

  Serial.println("System Ready. Waiting for shoe...");
}

void loop() {
  // Read Sensor Status (Assuming HIGH means object detected)
  // If your sensor works opposite (LOW when detected), change HIGH to LOW.
  int objectDetected = digitalRead(PIN_SENSOR);

  if (objectDetected == LOW) { // Change to HIGH if using a different sensor type
    Serial.println("Shoe Detected! Starting Cleaning Cycle...");
    runCleaningCycle();
  }
}

void runCleaningCycle() {
  // 1. Visual Indicator ON
  digitalWrite(PIN_LED, HIGH);

  // 2. SPRAY PHASE
  Serial.println("Phase 1: Spraying Water...");
  digitalWrite(PIN_PUMP, HIGH); // Turn Pump ON
  delay(TIME_SPRAY);
  digitalWrite(PIN_PUMP, LOW);  // Turn Pump OFF
  
  delay(TIME_DELAY); // Short pause

  // 3. BRUSH PHASE
  Serial.println("Phase 2: Brushing...");
  digitalWrite(PIN_MOTOR, HIGH); // Turn Motor ON
  delay(TIME_BRUSH);
  digitalWrite(PIN_MOTOR, LOW);  // Turn Motor OFF

  // 4. FINISH
  Serial.println("Cycle Complete. Please remove shoe.");
  digitalWrite(PIN_LED, LOW);
  
  // Wait 3 seconds to prevent immediate re-triggering
  delay(3000); 
}
