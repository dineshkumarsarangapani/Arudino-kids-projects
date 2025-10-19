# Wet & Dry Waste Segregator

## 1. Purpose
This project automatically sorts waste into "wet" and "dry" categories. It uses a moisture sensor to detect the waste type and a servo motor to direct it into the correct bin.

## 2. Components Needed
*   Arduino Uno
*   Soil Moisture Sensor
*   Servo Motor (e.g., SG90)
*   1x Red LED
*   1x Green LED
*   2x 220-ohm resistors (for the LEDs)
*   Jumper Wires
*   Breadboard

## 3. Architecture & Wiring
The Arduino Uno is the central controller. It reads data from the moisture sensor and then controls the LEDs and the servo motor based on that data.

### Pin Connections:
*   **Moisture Sensor:**
    *   `VCC` -> Arduino `5V` (or `A0` for power-saving)
    *   `GND` -> Arduino `GND`
    *   `AOUT` (Analog Output) -> Arduino Pin `A1`
    *   **Note:** The code uses pin `A0` to power the sensor only when taking a reading. This helps prevent corrosion of the sensor probes over time. To wire it this way, connect the sensor's `VCC` pin to the Arduino's `A0` pin instead of the `5V` pin.

*   **Servo Motor:**
    *   **Signal** (usually orange or yellow wire) -> Arduino Pin `9`
    *   `VCC` (red wire) -> Arduino `5V`
    *   `GND` (brown or black wire) -> Arduino `GND`

*   **LEDs:**
    *   **Red LED:**
        *   Long leg (anode) -> 220-ohm resistor -> Arduino Pin `8`
        *   Short leg (cathode) -> Arduino `GND`
    *   **Green LED:**
        *   Long leg (anode) -> 220-ohm resistor -> Arduino Pin `7`
        *   Short leg (cathode) -> Arduino `GND`

### Breadboard Connections:

**A Note on Jumper Wires:** This guide assumes you are using standard jumper wires.
*   For connections that go from one point on the breadboard to another (e.g., from the ground rail to a component's row), you will use **Male-to-Male** jumper wires (a pin on both ends).
*   If you are connecting a component that has male pins (like the moisture sensor or servo motor), you will use **Male-to-Female** jumper wires. The **female socket** of the wire connects to the component's pin, and the **male pin** of the wire plugs into the breadboard or Arduino.

1.  **Power Rails (Setting up Power and Ground):**
    *   **Goal:** The power rails on the side of the breadboard provide a convenient way to supply power and a common ground to all your components.
    *   **Step 1 (5V Power):** Take a jumper wire and connect it from the pin labeled `5V` on your Arduino Uno to any hole on the **red `(+)` rail** of your breadboard. This entire rail is now your 5V power source.
    *   **Step 2 (Ground):** Take another jumper wire and connect it from one of the pins labeled `GND` on your Arduino Uno to any hole on the **blue `(-)` rail** of your breadboard. This entire rail is now your common ground. All components that need to be grounded can connect to this rail.
    *   **Important Note:** You are correct! Any hole in the red `(+)` rail can be used for power, and any hole in the blue `(-)` rail can be used for ground. All the holes in each power rail are connected vertically, independent of the numbered rows.

2.  **LEDs and Resistors (Example using breadboard coordinates):**
    *   **Green LED:**
        1.  Place the green LED's **long leg** (anode) into hole `J10`.
        2.  Place the **short leg** (cathode) into hole `J9`.
        3.  Connect a jumper wire from the **blue `(-)` ground rail** to any hole in **row 9** (e.g., `G9`). This connects the short leg to ground.
        4.  Place one end of a 220-ohm resistor into hole `I10` (the same row as the long leg).
        5.  Place the other end of the resistor into a different hole in the same row, for example, `F10`.
        6.  Connect a jumper wire from any hole in **row 10** (e.g., `A10`) to **Arduino Pin `7`**.

    *   **Red LED:**
        1.  Place the red LED's **long leg** (anode) into hole `J15`.
        2.  Place the **short leg** (cathode) into hole `J14`.
        3.  Connect a jumper wire from the **blue `(-)` ground rail** to any hole in **row 14** (e.g., `G14`).
        4.  Place one end of a 220-ohm resistor into hole `I15` (the same row as the long leg).
        5.  Place the other end of the resistor into, for example, `F15`.
        6.  Connect a jumper wire from any hole in **row 15** (e.g., `A15`) to **Arduino Pin `8`**.

3.  **Moisture Sensor:**
    *   Since the sensor module itself doesn't plug into the breadboard, you'll use jumper wires.
    *   Connect a jumper wire from the sensor's `GND` pin to the **blue `(-)` ground rail** on the breadboard.
    *   Connect a jumper wire from the sensor's `VCC` pin directly to **Arduino Pin `A0`**.
    *   Connect a jumper wire from the sensor's `AOUT` pin directly to **Arduino Pin `A1`**.

4.  **Servo Motor:**
    *   Connect the servo's `GND` (brown or black) wire to the **blue `(-)` ground rail** on the breadboard.
    *   Connect the servo's `VCC` (red) wire to the **red `(+)` power rail** on the breadboard.
    *   Connect the servo's **Signal** (orange or yellow) wire directly to **Arduino Pin `9`**.

## 4. How It Works
1.  **Initialization:** When you power on the Arduino, the servo motor moves to a neutral, middle position (90 degrees).
2.  **Sensing:** The system powers the moisture sensor, takes a reading, and then immediately powers it down to conserve the sensor.
3.  **Decision Making:**
    *   The Arduino checks the moisture value against a `WET_THRESHOLD` (set to `500` in the code).
    *   **If Wet Waste:** If the reading is *above* the threshold, the code decides the waste is wet. It turns on the **red LED**, turns off the green one, and rotates the servo motor to the "wet" position (180 degrees).
    *   **If Dry Waste:** If the reading is *below* the threshold, the waste is considered dry. The **green LED** lights up, the red one turns off, and the servo moves to the "dry" position (0 degrees).
4.  **Loop:** The system waits for 2 seconds (`delay(2000)`) before repeating the process.

## 5. Usage
Upload the code from `wet_dry_segregator.ino` to your Arduino Uno. You may need to adjust the `WET_THRESHOLD` value based on how your specific sensor responds to different materials. You can view the sensor's real-time output by opening the **Serial Monitor** in the Arduino IDE (`Tools` > `Serial Monitor`).
