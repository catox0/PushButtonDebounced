# PushButtonDebounced
Class for debounced readout of Pushbuttons with Arduino. 
Create a separate instance for each pushbutton.

The function sets the pinMode to INPUT_PULLUP and assumes that the pushbutton pulls the pin from High to Low. 

Mode 0 returns millisecond duration of pushbutton High state after transition to Low (default).
       (Duration of button push)\
Mode 1 returns millisecond duration of pushbutton Low state after transition to High.
       (Time since preceding button push)\
Mode 2 returns millisecond duration of pushbutton Low state after transition to Low.
       (Time since start of button push; values start after DebounceDelay value)

The routine requires reasonably fast calling of check() to ensure a responsive behavior. If the delays in the main loop are too large, consider using interrupt-driven read-out.

Thomas Schultz, July 2019

---------------------------

Use by creating and then reading out an instance for each button, e.g.:

pushButton pbA(pushbuttonPinA);       &nbsp;&nbsp;// A: act upon button release\
pushButton pbB(pushbuttonPinB, 1);    &nbsp;&nbsp;// B: act upon button press\
pushButton pbC(pushbuttonPinC, 2);    &nbsp;&nbsp;// C: act during button press

void loop()\
{  if (long duration = pbA.check()){   &nbsp;&nbsp;// Check pushbutton A\
    Serial.print("Button A was released after (ms): ");\
    Serial.println(duration);  }\
  if (long duration = pbB.check()){   &nbsp;&nbsp;// Check pushbutton B\
    Serial.print("Button B was pressed after (ms): ");\
    Serial.println(duration);  }\
  if (long duration = pbC.check()){   &nbsp;&nbsp;// Check pushbutton C\
    Serial.print("Button C was pressed for (ms): ");\
    Serial.println(duration);  }\
}
