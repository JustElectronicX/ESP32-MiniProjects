/*
  ==============================================================================
   Project       : Serial Controlled Servo
   Version       : 1.0
   Board         : ESP32 DevKit v1
   File          : 1-Serial_Servo.ino
   Author        : JustElectronicX (Dhaivat Joshi)
   Created On    : [14-09-2025]
   Description   : Control a servo motor by entering angle (0–180) through
                   Serial Monitor. Servo position updates immediately when
                   new input is given.

   Status        : Working (tested with ESP32 MG90S servo)

   Purpose       :
     This firmware allows real-time manual control of a servo motor from
     the Arduino IDE Serial Monitor. User inputs an angle, and the servo
     rotates accordingly.

   Features:
     - Input servo angle (0–180) via Serial Monitor.
     - Servo position feedback printed back on Serial.
     - Input validation (rejects invalid values).
     - Compatible with most hobby servos.

   Circuit Connection (ESP32 → Servo):
     - Servo Signal (Orange/Yellow) -> GPIO13
     - Servo VCC (Red)              -> 5V (recommended external supply if high torque)
     - Servo GND (Brown/Black)      -> GND (must be common with ESP32 GND)

   How to Run:
     1. Connect servo as per circuit diagram above.
     2. Open Arduino IDE → Select Board: "ESP32 Dev Module".
     3. Upload the sketch to ESP32.
     4. Open Serial Monitor (Ctrl+Shift+M).
     5. Set baud rate = 115200.
     6. Enter a number between 0 and 180 → Press Enter.
     7. Observe servo movement + feedback in Serial Monitor.

   Common Errors & Fixes:
     - Servo jitters or resets:
         → Use a separate 5V supply for servo (ESP32 5V pin may be weak).
         → Connect grounds (ESP32 GND + Servo GND) together.
     - Random "0" angle input:
         → Serial Monitor may send extra line breaks. Use "No line ending"
           or filter input as already handled in code.
     - Servo not moving:
         → Check pin connection (must be GPIO13 in code).
         → Ensure servo power supply can provide enough current.

   Dependencies:
     - Arduino core for ESP32
     - ESP32Servo library

   Credits:
     - Author: Dhaivat Joshi (JustElectronicX)
     - GitHub: https://github.com/JustElectronicX
     - Instagram: https://www.instagram.com/justelectronicx
     - YouTube : https://www.youtube.com/@justelectronicx
     - Linktree: https://linktr.ee/justelectronicx

   Additional Notes:
     - Modify `servoPin` to use other GPIO if needed.
     - Suitable for robotics, pan-tilt systems, or basic servo experiments.
     - Always ensure external servo power for stability.

  ------------------------------------------------------------------------------
  ==============================================================================
*/


#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo

int servoPin = 13;
int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(115200);   // Start Serial Monitor (115200)
  while (!Serial) {
    ; // wait for serial port to connect (for native USB)
  }
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400); // attach servo on pin
  myservo.write(pos);
  Serial.println("Enter angle (0 - 180):");
}

void loop() {

  while (Serial.available() && !isDigit(Serial.peek())) {
    Serial.read(); // discard '\r' or '\n' etc.
  }
  if (Serial.available() > 0) {
    int angle = Serial.parseInt(); // read integer from Serial
    if (angle >= 0 && angle <= 180) {
      myservo.write(angle);        // move servo
      Serial.print("Servo moved to: ");
      Serial.println(angle);
    } else {
      Serial.println("Invalid angle! Please enter a value between 0 and 180.");
    }
  }
}
