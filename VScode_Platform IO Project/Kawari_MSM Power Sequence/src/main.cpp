/*  ; MIT License
;
; Copyright (c) 2025 William Manganaro sMs Retro Electronics
;
; Permission is hereby granted, free of charge, to any person obtaining a copy of this software
; and associated documentation files (the "Software"), to deal in the Software without
; restriction, including without limitation the rights to use, copy, modify, merge, publish,
; distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom
; the Software is furnished to do so, subject to the following conditions:
;
; The above copyright notice and this permission notice shall be included in all copies or
; substantial portions of the Software.
;
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
; BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
; NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
; DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// Firmware operation
//
// The purpose of this software is to allow fro the Kawari VICII hardware emulator to switch 
// between NTSC and PAL video modes when commanded by an Retrospective EVO64 MSM controller without
// the need to recycle the computer power. It also provides an OVER CURRENT feature that will switch
// the power OFF to the Kawari if the current is >= 750 milliamperes. 
//Operation
//
// This firmware monitors any
// change from the NTSC (or the PAL) logic output from the MSM and electronically cycles the power
// to the Kawari Vcc pin. This cycle is as follows: Turn power OFF when a change is detected 
// , keep the power off until the boards RESET is asserted, at this point the power is returned to ON.
// Overcurrent is latching. If an over current condition is detected, the firmware will turn the power 
// OFF to the Kawari Vcc pin and remain OFF until the next system power cycle.
// all status is indicated with different color LED's 

#include <Arduino.h>

// pin defines
#define shdn 0
#define oc 1
#define sreset 2
#define edge_det 3
#define oc_led 4

// isr here:

ISR(PCINT0_vect) // this is the Interrupt Service Routine
{
  delay(20);                       // wait 20 milliseconds after switch over
  digitalWrite(shdn, LOW);         // turn the power OFF to the Kawari
  while (digitalRead(sreset) == 1) // wait for reset to get issued
  {
  }
  digitalWrite(shdn, HIGH); // turn power ON to Kawari
}

void setup()
{

  pinMode(shdn, OUTPUT);
  delay(100);
  digitalWrite(shdn, HIGH); // turn power ON to Kawari
  pinMode(oc_led, OUTPUT);
  digitalWrite(oc_led, LOW);
  pinMode(oc, INPUT_PULLUP);
  pinMode(sreset, INPUT_PULLUP);
  pinMode(edge_det, INPUT_PULLUP);
  PCMSK |= bit(PCINT3);  // eNABLE PIN CHANGE INTERRUPT ON pin D3 (PIN 2 OF mcu)
  GIFR = 0;              // clear any outstanding interrupt flags
  GIMSK |= bit(PCIE);    // globally enable pin change interrupts
  SREG |= (1 << SREG_I); // globally enable interrupts
}

void loop()
{
  digitalWrite(shdn, HIGH);    // turn power ON to Kawari
  while (digitalRead(oc) == 1) // just sit here while no over current condition exists
  {
  }
  SREG = (0 << SREG_I);       // globally disable interrupts
  digitalWrite(shdn, LOW);    // turn the power OFF to the Kawari
  digitalWrite(oc_led, HIGH); // turn overcurrect indicator on
  while (1)
    ; // do nothing until next power cycle, overcurrent condition will remain latched
}
