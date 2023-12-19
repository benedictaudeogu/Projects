# Benedicta's Lab Notebook

## 2/20/23 - 2/26/23
While searching for parts, we discovered the Raspberry Pi we needed was sold out. As an alternative, we contacted the professor 
and TA of ECE 479 and received a Raspberry Pi 4 kit. 

Ordered some parts that we needed for the project.
* Parts ordered currently: 12VDC solenoid valve, DS18B20 temperature sensor probe, 128x64 oled display.
  * May switch to 16x2 LCD display as it's easier to connect to atmega328p

Spoke to the machine shop for initial build ideas. 
* Will provide tub and valve when it arrives for the build of our encasement.

Started working on the PCB schematic:

<img src=visuals/pcb1InitialDesign.png width=450>

* As of now, PCB will consist of atmega328p, LCD display and FTDI module for USB communication.
* Potential questions: 
  * Should we use a transistor rather than relay?
    * Silent and don't need to worry about mounting
  * Should interfacing with FTDI module occur on pcb or separate?
    * FT23RL chip currently sold out on Digikey and Mouser, so we may have to use a separate FTDI module. If so how does it connect to the PCB?

Post TA meeting: 
    Feedback included adding more tolerance analysis and bounds to proposal and design document.

---
## 2/27/23 - 3/5/23
Spoke to machine shop again about frame build and provided them with valve and tub.

Finished variation 1 of PCB schematic. Will attend the PCB review session on 2/28/23 to get feedback.

While working on PCB design and schematic, I realized that the oled display we were planning on using was a little small and couldnt find the exact components on kicad - need to import a library. I decided to switch to a 16x2 lcd display instead.

I also decided to use a transistor instead of a relay to control the solenoid valve. This will allow us to control the valve without having to worry about mounting the relay. 

We are not in need of an FTDI module anymore as we can directly connect the atmega328p to the Raspberry Pi using the UART pins and will use ISP programming to program the atmega328p.

We are keeping most components off the PCB to keep it simple.

Version 1 of PCB schematic:

<img src=visuals/pcb1FinalDesign.png width=450>

---
## 3/6/23 - 3/12/23
Presented for Design Review. We initially received feedback on our use of a raspberry pi over a wifi module, but after the weekly TA meeting, which included professor
Fliflet this week, confusions were cleared up, and we got permission to keep the raspberry pi in our design. 

All components have been ordered and most have arrived. We are still waiting on the headers and potentiometers to arrive in regards to changes I made to the PCB schematic after the design review.

I've completed the PCB layout and routing and Prannoy has ordered it. It did pass the audit and I requested a stencil.

<img src=visuals/routing.png width=450>

Our next step is to begin prototyping the demo using a breadboard and the DIP microcontrollers we have after spring break.

Machine shop has finished the frame build. Picture in Ethans or Nehas lab notebook.

---
## 3/13/23 - 3/19/23 Spring Break
---
## 3/20/23 - 3/26/23
Started working on the prototype using a breadboard and the DIP ATmega328P-PN we have. To start we are attempting to light up an led much like in the soldering assignment (without the button). Unfortunately we are having issues programming the ATmega328p using the ISP method. 

<img src=visuals/Error.png width=450>

We are using the USBasp programmer and the Arduino IDE to program the microcontroller. During our weekly TA meeting, we had Prannoy look at our setup but no immediate solutions were found. I sent a follow up email. We are going to go to office hours next week to see if we can get it working. I have also sent Jason an email as we will be missing his office hours slot. Once this is working, I will move on to displaying the DS18B20 temperature sensor probe on the LCD display and controlling the solenoid valve using the temperature. In the meantime, the PCBs are set to arrive next week.

**Reminders for future reference:**
* OneWire library to interface with the probe
* LiquidCrystal library to interface with the LCD display
---
## 3/27/23 - 4/2/23
This past week I worked on building the prototype on a breadboard. The programming issue was due to the Reset pin of the microcontroller not being wired correctly. The board programs now. Issues faced this week included not being able to display to serial monitor and lcd not working beyond turning on. We discovered the serial monitor issue was due to the USBasp not having a serial port. The lcd issue has still not been resolved. I was able to see half of the black rectangles that are supposed to appear when the contrast has been adjusted, but I am not sure why the lcd only shows half of the character rectangles and why text is still not displaying. One thing I did find out after going to office hours is that the USBasp alone is not enough to power the lcd. A secondary 5v power supply was needed before I could see those character blocks.

Pivoting, I decided to work on the solenoid valve control. I was able to get the solenoid to turn on and off using the microcontroller and an NPN transistor. I tested the valve with our temperature probe and it works as it should. This coming week, we will test our first version of the pcb and make adjustments as needed before the next order date on wednesday. 

Here is a picture of the prototype almost fully working:

<img src=visuals/prototype.png height=450>

We will continue to troubleshoot the lcd issue as well as test the other displays we have.

---
## 4/3/23 - 4/9/23
This week we were able to complete the breadboard prototype of our project. The lcd issue was due to weak connections from not having soldered the header to the display pins. Once we did, it started working as expected.

<img src=visuals/lcd.png height=450>

We also tested the solenoid valve with the temperature probe and it works as it should and displays the temperature on the lcd display. Here is a video.

https://user-images.githubusercontent.com/98714655/230257294-079cafc1-4f0f-4d5e-8ee6-96ab4c292e82.mp4


We moved on to testing the PCB and found a short in the circuit that is stemming from the microcontroller. It is not a complete short where the voltage drops to 0V but rather it drops to about half the inputted 5V. While the issue is not clear, we will try to debug it. We are also going to order a new PCB. I recreated our breadboard design for the second order pcb in hopes that it will work, since each component has been previously tested. 

<img src=visuals/pcb2.png width=450>

As a safety, we will fall back to the breadboard prototype if the PCB does not work. What remains now is to incorporate the push notification feature. This will be done in parallel to the PCB testing.

---
## 4/10/23 - 4/16/23
Since we have completed our protoype on the breadboard and are currently waiting for the second PCB, we did not have much to do this week. Attempting to debug the first pcb was not fruitful. What we thought was a soft short was actually a hard short but it is not as obvious since it's current limited (this is what I understood from attending office hours). I did attempt to trace back the short but the voltages appeared to be getting to the various components of the pcb correctly (though there was ~1V drop for some components - lcd, voltage regulator) so I was a bit confused. As the demo and presentaion are approaching, we have signed up for time slots and will start working on the presentation soon.

---
## 4/17/23 - 4/23/23
This week the second PCB arrived and we were able to program it properly. We put together all subsytems and have the demo working as it should. During our mock demo, one issue we found was that because the temperature sensor is a one wire device, the atmega and the raspberry pi cannot both read the temperature at the same time. As a result, once the temperature bus detected two actions were trying to happen at once, it would stop the pi program and needed a second before displaying to the lcd again. Ethan fixed this by adding exception handling to the pi program. On the mcu end, the lcd prints a message indicating that the sensor is already in use.

Since the valve is controlled only by the temperature and will continuously turn on and off once the sensor dips below 55°F when we add ice, we are going to add a wait time of 30s after the valve has ran a cycle. This is to prevent the valve from turning on and off repeatedly during the demo which can raise its and the transistors temperature.

Front and side view of demo:

<img src=visuals/front.jpeg width=450 height=550>
<img src=visuals/side.jpeg width=450 height=550> 

PCB is hard to see but is taped close to the lcd display. We are using 2 wall adapters, one 5v and one 12v, to power the system.

---
## 4/24/23 - 4/30/23
---
Last entry. This week we had our demo, which went well. We were able to show the system working as it should. We are left with the final report and presentation. Demo sketch updated and uploaded to github. Extra credit video also submitted.