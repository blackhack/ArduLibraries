ArduLibraries
=============

Useful libraries for Arduino

You can download single libraries from "Releases" folder by clicking in the library and then clicking "raw".

DimmerOne
-------------

Implements a dimmer based on zero-crossing detection of an AC signal, with adjustable frequency and firing angle. Uses interrupts and TIMER1 for accurate timing. 

EasyButton
-------------

A button debouncing library. You can configure the debounce time, pullup options and a callback function that can be called on any combination of push, pushed, release and released.

The update() method must be called by the user's application at a greater rate than the set debounce time.

ShiftEasier
-------------

Sets/reads shift registers, like the Arduino shiftOut and shiftIn functions but combined into a class to support an arbitrary number of bytes

SimpleList
-------------

A class designed to act list std::vector from the C++ STL. Implements iterator semantics (for looping), but not [] operator access to the array.

TaskAction
-------------

A class that implements a repeating task every X milliseconds or microseconds. The task is set by passing a function pointer to the class constructor.
