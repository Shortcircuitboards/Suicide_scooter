/*
 * Oled controllerboard for the brushless mod of the Razor Kiddy Scooter 
 * 
 * For more informations see my Github (Wiring diagram, pictures of the mod and my other stupid projects
 *  https://github.com/shortcircuitboards
 * 
 * Code by //moe, included scripts are the standard Arduino libarys Servo.h and the Ardafruit SSD1306 libarys from the libary manager and so belong to them. All the other stuff is selfmade/out of other projects i did
 * 
 */

#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   64
#define LOGO_WIDTH    64
static const unsigned char PROGMEM logo_bmp[] =
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0x08, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xff, 0xfe, 0x08, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0x88, 0x00, 0x00, 
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xc8, 0x00, 0x00, 0x03, 0xf8, 0x1f, 0xff, 0xff, 0xe8, 0x7f, 0x80, 
  0x00, 0xfc, 0x3f, 0xff, 0xff, 0xe8, 0xfe, 0x00, 0x00, 0x7e, 0x3f, 0xff, 0xff, 0xf9, 0xf8, 0x00, 
  0x00, 0x7e, 0x3f, 0xff, 0xff, 0xf9, 0xf8, 0x00, 0x00, 0x7e, 0x6c, 0x7f, 0xff, 0xf9, 0xf8, 0x00, 
  0x30, 0xfe, 0x20, 0x7f, 0xff, 0xf9, 0xfc, 0x00, 0x1f, 0xff, 0x30, 0x7f, 0xff, 0xfb, 0xfe, 0x18, 
  0x0f, 0xff, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x07, 0xfe, 0x10, 0x00, 0x00, 0x29, 0xff, 0xe0, 
  0x01, 0xfd, 0xff, 0xff, 0xff, 0xee, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xef, 0xff, 0x80, 
  0x00, 0x03, 0xff, 0xff, 0xff, 0xef, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
  0x00, 0x03, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 
  0x00, 0x01, 0xff, 0xfa, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf7, 0xff, 0xfc, 0x00, 0x00, 
  0x00, 0x01, 0x0f, 0xdf, 0xdf, 0x86, 0x00, 0x00, 0x00, 0x01, 0xef, 0xfc, 0xff, 0xdc, 0x00, 0x00, 
  0x00, 0x01, 0xff, 0xf2, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xff, 0xea, 0x5f, 0xff, 0x00, 0x00, 
  0x00, 0x03, 0xff, 0xcf, 0xcf, 0xff, 0x00, 0x00, 0x00, 0x04, 0xff, 0xbf, 0xe7, 0xf9, 0x00, 0x00, 
  0x00, 0x07, 0x3e, 0x7f, 0xfb, 0xf3, 0x00, 0x00, 0x00, 0x03, 0xbd, 0xff, 0xfe, 0xe7, 0x00, 0x00, 
  0x00, 0x03, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
  0x00, 0x03, 0xff, 0xff, 0xff, 0xfa, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 0xff, 0xfc, 0x00, 0x00, 
  0x00, 0x01, 0xff, 0xf0, 0x7f, 0xfc, 0x00, 0x00, 0x00, 0x01, 0xff, 0xf0, 0x3f, 0xfd, 0x00, 0x00, 
  0x00, 0x02, 0xfc, 0xf0, 0x39, 0xfd, 0x80, 0x00, 0x00, 0x06, 0xfc, 0x20, 0x31, 0xff, 0xc0, 0x00, 
  0x00, 0x1f, 0x7d, 0xe0, 0x17, 0xfb, 0xfc, 0x00, 0x00, 0x3f, 0x7e, 0x60, 0x39, 0xf7, 0xff, 0xe0, 
  0x00, 0x7f, 0xbf, 0xf0, 0x7f, 0xe3, 0xff, 0xf0, 0x07, 0xff, 0x0f, 0xe0, 0x3f, 0x81, 0xff, 0xf8, 
  0x18, 0x7e, 0x00, 0x00, 0x00, 0x00, 0xff, 0x18, 0x10, 0x1c, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 
  0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 
  0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x80, 
  0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

Servo myservo1,myservo2;  // create 2 servo objects to control servos

#define blight 10      // digital pin for breaklight
#define nightlight 9   // digiral pin for LED Light
#define lightbutton  2  // digital pin for Light button
int potpin = A0;      // analog pin used to connect the potentiometer
int butonpin = A1;    // analog pin used to connect the push buton
int vdiff = A2;       // analog pin for the Voltagedivider 
int isens = A3;       // analog pin for the Currentsensor
bool lightb=LOW;      //bool for light status
bool light=LOW;           // light on or off
int val;              // variable to read the value from the analog pin
int throttle;         // Variable for the throttle 
float vol;              // Variabe for the Batteryvoltage
float curr;             // Variable for the BatteryCurrent
bool press=LOW;       // variable to store the buton press 
int pos = 0;          // variable to store the servo position
int speedlock;        // create variable for speedlock to set while booting

void setup() {
  Serial.begin(9600);
  press=digitalRead(butonpin);
  Serial.println(press);

  myservo1.attach(5);  // attaches the servo1 on pin 3 to the servo1 object
 
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  myservo1.write(20);       //Set the Servo output to 20?? to prevent the ESC from going to IDLE and lock
  delay(100); // Pause for 0,8 seconds
  display.clearDisplay();
  // Clear the buffer
  myservo1.write(20);       //Set the Servo output to 20?? to prevent the ESC from going to IDLE and lock
  delay(3500); // Pause for 0.5 seconds
  display.drawBitmap(32, 0, logo_bmp, 64, 64, 1); //show the Moe Bootscreen
  display.display();
  myservo1.write(20);       //Set the Servo output to 20?? to prevent the ESC from going to IDLE and lock
  delay(1000); // Pause for 4 seconds
  display.clearDisplay();
   myservo1.write(20);      //Set the Servo output to 20?? to prevent the ESC from going to IDLE and lock
if (press == 0) {           //if brake is pressed after the Bootscreen
  speedlock = 0 ;            //set Speedlock to zero
}
  else {
  speedlock = 1;            //if break is not pressed, lock the max speed 
  }

pinMode(blight, OUTPUT);
pinMode(nightlight, OUTPUT); 
pinMode(lightbutton, INPUT);
}

void loop() {
  
  int vol_t = analogRead(vdiff);           //Read the Value of the Analog Input of Bat 1 and write it to the temp Variable
  int curr_t = analogRead(isens);           //Read the Value of the Analog Input of Bat 2 and write it to the temp Variable
  
  float vol = vol_t * (40 / 1023.0);    //Scale the Input to the displayed (Real) Value 36V on the Voltage divider are 3,3V on the Arduino
  float curr = curr_t * (25 / 1023.0);    //Scale the Input to the displayed (Real) Value 36V on the Voltage divider are 3,3V on the Arduino
 

  
    press=digitalRead(butonpin);       // reads the value of the buton (HIGH or LOW)
    lightb=digitalRead(lightbutton);    // reads the value of the Lightbutton
    Serial.println(press);
    
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setTextSize(1);
  display.setCursor(3,5);
  if (speedlock == 0){
  display.println("Moes Suicide Scooter");
  }
  else {
  display.println("Moes E-Scooter");
  }
  display.setTextSize(2);
  display.setCursor(1,18);
  display.println("V:");
  display.setCursor(25,18);
  display.print(vol,1);            //Enter Value for temp here after read and round
  display.println(" V"); 
  display.setCursor(1,36);
  display.println("I:");
  display.setCursor(25,36);
  display.print(curr,1);            //Enter Value for druck here after read and round
  display.println(" A"); 
  display.setTextSize(1);
  display.setCursor(1,55);
  display.println("T  :");
  display.setCursor(25,55);
  display.print(throttle); 
  display.println(" %"); 
    if (light == HIGH){
      display.setTextSize(2);
      display.setCursor(100,50);
      display.write(15);
      }
      else { 
           } 
  display.display();


  delay(15);


  if (press == 0) {                   // if push buton pressed automatic mode starts
    myservo1.write(20);                // tell servo1 to go to Zero (brake if switch is enabled
   
    throttle = 0; 
    digitalWrite(blight, HIGH);       // switch on the breaklight            
    delay(15);                        // waits 15ms for the servo to reach the position
  }
  
  else if (speedlock == 0) {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 195, 1023, 0, 300);     // scale it to use it with the servo (value between 20 and 160 becaus ESC can??t read values lower than 20 and higher than 160)
  val = constrain(val, 20 , 160);       // kinda expo so that the throttle flickering at fullspeed stops
  throttle = map(val, 20, 160, 0, 100);     // generate throttle Value 0 to 100% for the oled
  myservo1.write(val);                 // sets the servo1 position according to the scaled value

  digitalWrite(blight, LOW);           // switch the breaklight off
  delay(30);                           // waits for the servo to get there
  }
  else {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 195, 1023, 00, 95);     // scale it to use it with the servo (value between 20 and 160 becaus ESC can??t read values lower than 20 and higher than 160)
  val = constrain(val, 20 , 50);       // kinda expo so that the throttle flickering at fullspeed stops
  throttle = map(val, 20, 50, 0, 100);     // generate throttle Value 0 to 100% for the oled
  myservo1.write(val);                 // sets the servo1 position according to the scaled value

  digitalWrite(blight, LOW);           // switch the breaklight off
  delay(30); 
  }



if ((lightb == 1) && (light == LOW)){
  light = HIGH;
  digitalWrite(nightlight, HIGH);
  delay(250);
}

else if ((lightb == 1) && (light == HIGH)){
  light = LOW;
  digitalWrite(nightlight, LOW);
  delay(250);
}
  }
