// Example for use of PushButtonDebounced
// Use for debounced read-out of a pushbutton press
// Refer to PushButtonDebounced.h for description
// Thomas Schultz, July 2019

#include "PushButtonDebounced.h"      // Library for reading pushbuttons

#define pushbuttonPinA 2              // Choose the pushbutton pin (pulldown puchbuttons)
#define pushbuttonPinB 3              // Choose the pushbutton pin (pulldown puchbuttons)
#define pushbuttonPinC 4              // Choose the pushbutton pin (pulldown puchbuttons)

// Initialize pushbutton instance
pushButton pbA(pushbuttonPinA, 0);    // A: act upon button release
pushButton pbB(pushbuttonPinB, 1);    // B: act upon button press
pushButton pbC(pushbuttonPinC, 2);    // C: act during button press

void setup()
{
  Serial.begin(115200);               // Serial for feedback to user
  Serial.println("Reading pulldown push-buttons");
}

void loop()
{
  long duration;
  if (duration = pbA.check()){        // Check pushbutton A
    Serial.print("Button A was released after (ms): ");
    Serial.println(duration);
  }
  if (duration = pbB.check()){        // Check pushbutton B
    Serial.print("Button B was pressed after (ms): ");
    Serial.println(duration);
  }
  if (duration = pbC.check()){        // Check pushbutton C
    Serial.print("Button C was pressed for (ms): ");
    Serial.println(duration);
  }
}
