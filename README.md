# Suicide_scooter
Brushless mod for the Razor kiddy Scooter. It´s kinda dumb, because it´s way too fast for the little breaks and the stupid mecanic. But i got it cheap and also the other
parts... So i build it anyway :-)

<img src="/images/Scooter_done_side.jpg" alt="Sideview" title="finished project">

<img src="/images/Controller + Display.jpg" alt="Controller" title="finished controller">

For more Informations see the Wiki https://github.com/Shortcircuitboards/Suicide_scooter/wiki

Added the slow mode wich can be entered by just switching on. For unlocked speed, just push the break while switching on.

Actually done:
- Light switch
- Brakelight
- stop motor, when brake pulled
- Oled display with throttle
- smoothen out the max throttle to save the ESC from exploding
- gott the hardware ready to test out everything in real :-D (minor bugfixes comming soon)
- different speed modes while switching on (pull break, while switching on, for unlimited speed, all normal for limited [legal...] speed

Partitially done:
- configuration script

To be done:
- change color for the underfloor LED stirp with button combination

If you already want to play around with the Code virtually, you can do it here: https://wokwi.com/projects/341405340246475347


_**Assembly of the Controllerhardware:**_
![Schematic](https://github.com/Shortcircuitboards/Suicide_scooter/blob/main/images/Schem_Suicidescooter.jpg)
> A0 = Green wire of Thumbthrottle
 A1 = Brakecontact (NC Switch inside the brakelevel)   
 A2 = Voltagedivider    
 A3 = Currentsensor    
 A4 = SDA OLED    
 A5 = SCK OLED    
 D2 = Button for Light On/Off (NO)
 D5 = Signal pin of ESC        
 D9 = Output for relais Brakelight    
 D10= Output for relais for Front/Backlight    
 Red wire of ESC comes to 5V Pin   

