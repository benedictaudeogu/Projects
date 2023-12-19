# Neha

## Friday 02/24/2023

This week I have been responsible for fleshing out the problem, solution, high level requirements, subsystem requirements, tolerace analysis, and ethics of  our proposal and design document. This included finalizing and calculating the temperature threshold we will be utilizing for this project which was determined to be 13.0-14.0 degrees Celsius. This satisfies both the requirement of needing the water in the pipe to be above 55 degrees which is what is considered the ideal temperature for households to maintain to prevent frozen pipe burts and the requirement of accounting for the +/- 0.5 degrees Celsius tolerance of the digital thermometer.

## Monday 02/27/2023

Today we visited the machine shop and talked to Greg to drop off our tub and solenoid valve that came in last week. During the initial discussion 2 weeks ago he had proposed using plastic tubing but today he suggested that a PVC pipe would be more suitable to accomodate the plastic water solenoid valve we will be using. This is ideal as a PVC pipe was part of our original proposal as that is what is used in many residences/buildings in the real-world. We also discussed choosing the height at which the opening of the pipe would be off the floor and decided upon 4 inches. 

In addition, visited the electronic services shop to pick up some of the resistors and capacitors that will be required for our PCB.

I also fulfilled placing the order for the rest of the parts that will be required for the completion of this project.


## Wednesday 02/29/2023

Today, we had our design review with Professor Fliflet and our TA Prannoy. We received very helpful and constructive feedback during the process. For example, Professor suggested creating a separate section in our block diagram for powering our solenoid valve which requires 12V as opposed to the 5V needed to power the PCB and the rest of the components. The professor also had suggestions to improve the impact of our project, such as decreasing or increasing the rate of flow of the water flowing through the pipe depending on the temperature so that lower temperatures would result in increased water flow and higher temperatures would result in a trickle.

## Friday 03/10/2023

Today, we picked up our project apparatus from the ECEB machine shop as pictured below:

![IMG_3070](https://user-images.githubusercontent.com/124634335/229401086-c0c9132d-3574-47d7-b3f8-c3e83bb6cc2d.jpeg)

During today's meeting, Professor Fliflet greenlit the use of our Raspberry Pi to serve as Wi-Fi server for our notification subsystem which to reiterate is our additional preventative measure of sending a notification to the designated resident's upon detection of the temperature dropping below what we consider to be the safe threshold.

## Wednesday 03/29/2023

We were able to fix the breadboard implmentation of our PCB by correctly connecting the RESET pin of the microcontroller to the RESET pin of the USB adapter when programming the board, resulting in the correct expected behavior of the LED (flashing).

![IMG_3344](https://user-images.githubusercontent.com/124634335/234364609-2d5dced8-a3a3-4842-b004-61fa625a2702.jpeg)

## Monday 04/03/2023

Today we were able to successfully integrate the LCD and displaying the temperature into our project. At first we did not understand why nothing was being displayed but we quickly realized that the pins needed to be soldered to the LCD and was not sufficient to just have them positioned through the through holes.

![IMG_4687](https://user-images.githubusercontent.com/124634335/234368644-a177e18c-8673-4166-85f9-c45980bea1ef.jpeg)

We were also able to succesfully integrate our valve subsystem into the project.

![IMG_4688](https://user-images.githubusercontent.com/124634335/234370817-7ceffa0b-c95d-4e27-8d43-616b363dd875.jpeg)

Ethan soldered our first PCB which had arrived, but unfortunately upon further inspection we realized that there was a short due to the routing.

![IMG_3412](https://user-images.githubusercontent.com/124634335/234371672-173e6573-99dd-48bc-a11e-fd6de74223cb.jpeg)




