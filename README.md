
![](media/banner.png)


The Kawari Power Sequencer, known from here on as the “KPS”, is an electronically switched 5V regulator module that has been designed specifically for the EVO64 motherboard to work along side a Kawari VIC II and MSM. The KPS is a reliable, efficient, low noise, high frequency 5V switching regulator which remains very cool unlike linear regulators IC’s such as the common 7805. 

The KPS is installed onto the EVO64 motherboard’s 5V “CAN” regulator location that supplies power only to the VIC II 5V VCC socket pin.

The KPS allows the user to switch video standards on your EVO64 Commodore 64 between NTSC and PAL via the “Multi-Switch Module” MSM and a Kawari VIC II LARGE or SMALL board using a simple keyboard command. It will switch the video standard and recycle the Kawari’s power in one operation. No longer will the user have to manually switch the computers power OFF and ON after setting the video standard with an MSM. 


The KPS incorporates an over current sensing circuit that will sense when the output current goes above 780 mA and turns the 5V output off. A RED LED will indicate this condition. The KPS will remain latched in over current state until the input voltage is turned off and the over current condition is removed.  

sMs Retro Electronics A Division of sMs Electronics 2025
# LED Indicators: 

|LED|COLOR|DESCRIPTION
|:--:|:--|:--|
|D1|BLUE|REGULATOR 5V
|D2|RED|OVER CURRENT 
|D3|GREEN|KAWARI 5V   

 # KPS wiring details

![](media/bigview.png)
# Detailed Wiring:

![](media/connections.png)

 # KPS Firmware operation

The purpose of the KPS firmware is to allow the Kawari VICII hardware emulator to switch between NTSC and PAL video modes when commanded by an Retrospective EVO64 MSM controller without the need to recycle the computer power. It also provides an OVER CURRENT feature that will switch the power OFF to the Kawari if the current is >= 780 milliamperes. 

The firmware is essentially a state machine that monitors for any change, either a rising or falling edge, from the NTSC (or the PAL) logic output of the MSM and electronically cycles the power OFF then ON to the Kawari Vcc pin. This cycle is as follows: Turn power OFF when a change is detected, keep the power off until the boards RESET is asserted, at this point the power is returned to ON. The NTSC (or the PAL) logic output from the MSM is also routed to the Kawari video select pin header via an open drain MOSFET for 5V to 3.3V translation. 

Over current is latching. If an over current condition is detected, the firmware will turn the power OFF to the Kawari Vcc pin and remain OFF until the next system power cycle. all status is indicated with different color LED's 

 # KPS Build Notes & Cautions 

![](media/BUILD_NOTES.png)

 If you are building your own KPS, make sure you flash U2 MCU with the firmware provided. All the instructions are provided in the "Flashing and HEX File" folder. When building your KPS, *it is recommended that you populate all components except your programmed U2 ATtiny85V-10S MCU and U3 AP2152A electronic power switch.* This is to prevent damage to these chips in cases where the regulator is not working properly due to errors in construction. These errors can lead to over voltage conditions that will easily damage your chips. It is recommended on first power up to check if the BLUE LED is ON and to measure the core regulator output voltage and check if its 5V +/- 5%. If it is not, then investigate why.    
  
![](media/MEASURE_5V.png)

# PCB V1.0 Silkscreen Errata 

Silkscreen anode indication for D3 is incorrect. If D3 is installed as per the silkscreen, the diode will not illuminate. 

# Change FROM:
  ![](media/diode_from.png)
# Change TO:
  ![](media/diode_to.png)

Be sure to check out the full documentation ! PCB's will be available soon on my KoFi shop. 