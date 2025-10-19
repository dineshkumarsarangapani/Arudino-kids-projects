# Automatic Street Light with Ultrasonic Sensor

## 1. Purpose
This project simulates an automatic street light that turns on when a vehicle (like a toy car) approaches and turns off when it moves away. It uses an HC-SR04 ultrasonic distance sensor to detect objects and controls an LED to represent the street light.

## 2. Components Needed
*   Arduino Uno
*   HC-SR04 Ultrasonic Sensor
*   4x LEDs (any color, to act as the street lights)
*   4x 220-ohm resistors
*   Breadboard
*   Jumper Wires (Male-to-Male and Male-to-Female)

## 3. Architecture & Wiring
The Arduino Uno serves as the brain, sending out ultrasonic pulses and listening for the echo to calculate distance. Based on this distance, it decides whether to turn the LED on or off.

### Pin Connections:
*   **HC-SR04 Ultrasonic Sensor:**
    *   `VCC` -> Arduino `5V`
    *   `GND` -> Arduino `GND`
    *   `Trig` (Trigger) -> Arduino Pin `7`
    *   `Echo` -> Arduino Pin `6`
*   **LEDs:**
    *   LED 1 -> 220-ohm resistor -> Arduino Pin `12`
    *   LED 2 -> 220-ohm resistor -> Arduino Pin `11`
    *   LED 3 -> 220-ohm resistor -> Arduino Pin `10`
    *   LED 4 -> 220-ohm resistor -> Arduino Pin `9`

### Breadboard Connections:
**A Note on Jumper Wires:**
*   For breadboard-to-breadboard connections, use **Male-to-Male** wires.
*   For connecting the ultrasonic sensor (which has male pins), use **Male-to-Female** wires.

1.  **Power Rails (Setting up Power and Ground):**
    *   **Goal:** To use the breadboard's side rails as a convenient power and ground source for all components.
    *   **Step 1 (5V Power):** Use a **Male-to-Male** jumper wire to connect the `5V` pin on the Arduino to any hole on the **red `(+)` rail** of the breadboard.
    *   **Step 2 (Ground):** Use another **Male-to-Male** jumper wire to connect a `GND` pin on the Arduino to any hole on the **blue `(-)` rail** of the breadboard.
    *   **Important Note:** All holes in the red `(+)` rail are now connected to 5V power. All holes in the blue `(-)` rail are now a common ground.

2.  **LEDs and Resistors (Example using breadboard coordinates):**
    *   This example places the four LEDs in rows 10, 15, 20, and 25.
    *   **LED 1 (Pin 12):**
        1. Place the long leg into `J10` and the short leg into `J9`.
        2. Ground it by connecting a wire from row `9` to the blue `(-)` rail.
        3. Connect a 220-ohm resistor from `I10` to `F10`.
        4. Connect a wire from row `10` to **Arduino Pin 12**.
    *   **LED 2 (Pin 11):**
        1. Place the long leg into `J15` and the short leg into `J14`.
        2. Ground it by connecting a wire from row `14` to the blue `(-)` rail.
        3. Connect a 220-ohm resistor from `I15` to `F15`.
        4. Connect a wire from row `15` to **Arduino Pin 11**.
    *   **LED 3 (Pin 10):**
        1. Place the long leg into `J20` and the short leg into `J19`.
        2. Ground it by connecting a wire from row `19` to the blue `(-)` rail.
        3. Connect a 220-ohm resistor from `I20` to `F20`.
        4. Connect a wire from row `20` to **Arduino Pin 10**.
    *   **LED 4 (Pin 9):**
        1. Place the long leg into `J25` and the short leg into `J24`.
        2. Ground it by connecting a wire from row `24` to the blue `(-)` rail.
        3. Connect a 220-ohm resistor from `I25` to `F25`.
        4. Connect a wire from row `25` to **Arduino Pin 9**.

3.  **Ultrasonic Sensor:**
    *   Use **Male-to-Female** jumper wires for these connections.
    *   Connect the **female end** of a wire to the sensor's `GND` pin and the **male end** to the **blue `(-)` ground rail** on the breadboard.
    *   Connect the **female end** of a wire to the sensor's `VCC` pin and the **male end** to the **red `(+)` power rail** on the breadboard.
    *   Connect the **female end** of a wire to the sensor's `Trig` pin and the **male end** directly to **Arduino Pin `7`**.
    *   Connect the **female end** of a wire to the sensor's `Echo` pin and the **male end** directly to **Arduino Pin `6`**.

## 4. How It Works
1.  **Trigger Pulse:** The Arduino sends a very short (`10-microsecond`) pulse of sound from the sensor's `Trig` pin. This sound wave is too high-frequency for humans to hear.
2.  **Listen for Echo:** The Arduino then immediately starts listening on the `Echo` pin.
3.  **Measure Time:** When the sound wave hits an object (like your toy car) and bounces back, the `Echo` pin detects it. The Arduino measures the total time the sound wave was traveling.
4.  **Calculate Distance:** Knowing the speed of sound, the Arduino calculates how far away the object is. The formula is `Distance = (Travel Time / 2) * Speed of Sound`. We divide by 2 because the sound traveled to the object *and* back.
5.  **Control the Light:**
    *   If the calculated distance is **less than** the `DISTANCE_THRESHOLD` (set to 50 cm in the code), the Arduino knows an object is near and turns the LED **ON**.
    *   If the distance is **greater than** the threshold, the Arduino turns the LED **OFF**.
6.  **Loop:** The system waits for half a second and then repeats the whole process, constantly checking for approaching objects.

## 5. Usage
1.  Assemble the circuit according to the breadboard instructions.
2.  Upload the code from `automatic_street_light.ino` to your Arduino Uno.
3.  Open the Serial Monitor (`Tools` > `Serial Monitor`) to see the real-time distance measurements.
4.  Move your hand or a toy car towards and away from the sensor to see the street light turn on and off! You can adjust the `DISTANCE_THRESHOLD` variable in the code to make it more or less sensitive.
