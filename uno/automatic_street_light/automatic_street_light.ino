// Define pins for the ultrasonic sensor and the LED
const int TRIGGER_PIN = 7;
const int ECHO_PIN = 6;
const int LED_PIN_1 = 12;
const int LED_PIN_2 = 11;
const int LED_PIN_3 = 10;
const int LED_PIN_4 = 9;

// How long the lights should stay on (in milliseconds) after an object is last detected
const long LIGHT_ON_DURATION = 3000; // 3 seconds

// Variable to store the time when an object was last detected
unsigned long lastDetectionTime = 0;


// Define the distance threshold in centimeters (cm)
// When an object is closer than this, the light will turn on.
const int DISTANCE_THRESHOLD = 50; // 50 cm

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);

  // Set up the pin modes
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
}

void loop() {
  long duration, distance;

  // --- Step 1: Trigger the Ultrasonic Sensor ---
  // To get a clean reading, first set the trigger pin to LOW for a brief moment.
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  // Now, send a 10-microsecond high pulse to the trigger pin to start the sensor.
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // --- Step 2: Read the Echo from the Sensor ---
  // The echo pin will go HIGH for the duration of the sound wave's travel time.
  // The pulseIn() function measures how long this pulse is in microseconds.
  duration = pulseIn(ECHO_PIN, HIGH);

  // --- Step 3: Calculate the Distance ---
  // The speed of sound is approximately 343 meters per second, which is 0.0343 cm/microsecond.
  // The sound wave travels to the object and back, so we need to divide the total travel time by 2.
  // Formula: Distance = (Duration * Speed of Sound) / 2
  distance = (duration * 0.0343) / 2;

  // Print the measured distance to the Serial Monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // --- Step 4: Control the LED ---
  // Check if the measured distance is less than our threshold.
  if (distance < DISTANCE_THRESHOLD && distance > 0) {
    // If an object is detected, update the time of the last detection.
    lastDetectionTime = millis();
  }

  // --- Step 5: Control the LEDs based on time ---
  // Check if the time since the last detection is less than our desired duration.
  if (millis() - lastDetectionTime < LIGHT_ON_DURATION) {
    // If it has been less than 3 seconds since the last detection, turn the lights ON.
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, HIGH);
    digitalWrite(LED_PIN_3, HIGH);
    digitalWrite(LED_PIN_4, HIGH);
    Serial.println("Streetlights ON");
  } else {
    // If it has been more than 3 seconds, turn the lights OFF.
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(LED_PIN_3, LOW);
    digitalWrite(LED_PIN_4, LOW);
    Serial.println("Streetlights OFF");
  }

  // A shorter delay makes the sensor more responsive.
  delay(100); // 0.1-second delay
}
