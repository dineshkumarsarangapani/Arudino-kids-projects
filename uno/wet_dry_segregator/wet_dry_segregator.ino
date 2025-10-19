#include <Servo.h>

// Define pins
const int MOISTURE_SENSOR_POWER_PIN = A0;
const int MOISTURE_SENSOR_INPUT_PIN = A1;
const int SERVO_PIN = 9;
const int RED_LED_PIN = 8;
const int GREEN_LED_PIN = 7;

// Define moisture threshold
// This value may need to be calibrated based on your sensor and environment
const int WET_THRESHOLD = 500;

Servo wasteServo;
int servoPosition = 90; // Start at a neutral position

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);

  // Setup pins
  pinMode(MOISTURE_SENSOR_POWER_PIN, OUTPUT);
  digitalWrite(MOISTURE_SENSOR_POWER_PIN, LOW); // Keep sensor off initially
  pinMode(MOISTURE_SENSOR_INPUT_PIN, INPUT);
  
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  
  // Attach the servo motor
  wasteServo.attach(SERVO_PIN);
  wasteServo.write(servoPosition); // Move to neutral position
}

void loop() {
  // Power the moisture sensor
  digitalWrite(MOISTURE_SENSOR_POWER_PIN, HIGH);
  delay(10); // Allow sensor to stabilize

  // Read the moisture value
  int moistureValue = analogRead(MOISTURE_SENSOR_INPUT_PIN);

  // Power off the sensor to prevent corrosion
  digitalWrite(MOISTURE_SENSOR_POWER_PIN, LOW);

  Serial.print("Moisture Level: ");
  Serial.println(moistureValue);

  // Check if the waste is wet or dry and take action
  if (moistureValue > WET_THRESHOLD) {
    // --- WET WASTE ---
    Serial.println("Result: WET");

    // Turn on RED LED, turn off GREEN LED
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);

    // Rotate servo 90 degrees to the left (e.g., to position 180)
    wasteServo.write(180); 
  } else {
    // --- DRY WASTE ---
    Serial.println("Result: DRY");

    // Turn on GREEN LED, turn off RED LED
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);

    // Rotate servo 90 degrees to the right (e.g., to position 0)
    wasteServo.write(0);
  }

  // Wait before the next reading
  delay(2000); 
}
