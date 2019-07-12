#include "PushButtonDebounced.h"
#include "Arduino.h"

//***********************************************
//  Initialize pushbutton pin
// **********************************************

pushButton::pushButton(int pbPin, int mode){
  _pbPin = pbPin;                     // Create private variable for each instance
  _mode = mode;
  pinMode(_pbPin, INPUT_PULLUP);      // Pushbutton pin mode
  _lastTime = millis();               // Init debounce timer
  _lastState = isHigh(_pbPin);        // Init pb state
}

pushButton::pushButton(int pbPin){
  _pbPin = pbPin;                     // Create private variable for each instance
  _mode = 0;
  pinMode(_pbPin, INPUT_PULLUP);      // Pushbutton pin mode
  _lastTime = millis();           	  // Init debounce timer
  _lastState = isHigh(_pbPin);		    // Init pb state
}

//******************************************************
//  Check pushbutton state, return value as set by mode
// *****************************************************
long pushButton::check()
{
  boolean newState = isHigh(_pbPin) ;
  if (newState == _lastState && !_flagTime) return 0;// No state change, return False
  long newTime = millis();
  if (newTime - _lastTime < DebounceDelay) return 0;
                                      //  DebounceDelay not complete, return False

  // ---- handle debounced state change ----
  if(_mode == 0){               	    // Mode 1: wait for Low-High transition
      if (newState == false) {		    // :( High-Low transition
          _lastTime = newTime;        // Reset _lastTime
          _lastState = newState;	    // Reset _lastState
          return 0;						      // Return False
          }
      else {							            // :) Low-High transition
          long pushDuration = newTime - _lastTime;	// Duration of High state
          _lastTime = newTime;        // Reset _lastTime
          _lastState = newState;      // Reset _lastState
          return pushDuration;			  // Return duration
          }
      }
  if(_mode == 1){               		  // Mode 1: wait for High-Low transition
      if (newState == true) {			  // :( Low-High transition
          _lastTime = newTime;        // Reset _lastTime
          _lastState = newState;		  // Reset _lastState
          return 0;						      // Return False
          }
      else {							            // :) High-Low transition
          long pushDuration = newTime - _lastTime;	// Duration of High state
          _lastTime = newTime;        // Reset _lastTime
          _lastState = newState;      // Reset _lastState
          return pushDuration;			  // Return duration
          }
      }
  if(_mode == 2){               	    // Mode 1: wait for High-Low transition
      if (newState == false) {		    // High-Low transition
          if (!_flagTime) {           // New button press
              _lastTime = newTime;    // Start measuring time now
              _flagTime = true;       // Set flag for time measurement
              return 0;
              } 
          else return newTime - _lastTime;// Return duration of Low state
          }
      else {							            // Low-High transition
          _lastTime = newTime;        // Reset _lastTime
          _lastState = newState;      // Reset _lastState
          _flagTime = false;
          return 0;			            // Button press is over
          }
      }
}

