/************************************************************************
Class for debounced read-out of pushbuttons. 
Create a separate instance for each pushbutton.

The function sets the pinMode to INPUT_PULLUP and assumes that the 
pushbutton pulls the pin from High to Low. 

Mode 0 returns millisecond duration of pushbutton High state after transition to Low (default).
       (Duration of button push)
Mode 1 returns millisecond duration of pushbutton Low state after transition to High.
       (Time since preceding button push)
Mode 2 returns millisecond duration of pushbutton Low state after transition to Low.
       (Time since start of button push; values start after DebounceDelay value)

The routine requires reasonably fast calling of check() to ensure a responsive behavior. If the delays in the main loop are too large, consider using interrupt-driven read-out.

Thomas Schultz, July 2019
Use according to the MIT license (http://opensource.org/licenses/MIT)
***********************************************************************/

#ifndef PB_debounce_h
#define PB_debounce_h
#define DebounceDelay 100          // Debounce delay in milliseconds

//-----------------
// Defines for fast port read 
//(see: http://masteringarduino.blogspot.kr/2013/10/fastest-and-smallest-digitalread-and.html)
//-----------------
#define pinOfPin(P)    (((P)>=0&&(P)<8)?&PIND:(((P)>7&&(P)<14)?&PINB:&PINC))
#define pinIndex(P)    ((uint8_t)(P>13?P-14:P&7))
#define pinMask(P)     ((uint8_t)(1<<pinIndex(P)))
#define isHigh(P)      ((*(pinOfPin(P))& pinMask(P))>0)
#define isLow(P)       ((*(pinOfPin(P))& pinMask(P))==0)

class pushButton
{
  public:
	pushButton(int pin, int mode);	// Initialize pushbutton pin and operation mode
	pushButton(int pin);						// Initialize pushbutton pin with mode 0
  long check();  			            // Read button, return True or push duration if value changed

 private:   
  int _mode;
	int _pbPin;							        // Digital pin for pushbutton
	int _lastState;						      // Last state of PB
	long _lastTime;				          // Last time of PB change
	bool _flagTime = false;        // Flag to track time in mode 3
};

#endif