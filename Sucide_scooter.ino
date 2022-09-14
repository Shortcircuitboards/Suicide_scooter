/*
 * Oled controllerboard for the brushless mod of the Razor Kiddy Scooter 
 * 
 * For more informations see my Github (Wiring diagram, pictures of the mod and my other stupid projects
 *  https://github.com/shortcircuitboards
 * 
 * Code by //moe, included scripts are the standard Arduino libarys Servo.h and the Ardafruit SSD1306 libarys from the libary manager and so belong to them
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

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

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

void setup() {
Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(500); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(500);
  
  myservo1.attach(3);  // attaches the servo1 on pin 3 to the servo1 object
  myservo2.attach(5);  // attaches the servo2 on pin 5 to the servo1 object
  Serial.begin(9600);  // generates serial connection

pinMode(blight, OUTPUT);
pinMode(nightlight, OUTPUT); 
pinMode(lightbutton, INPUT);
}

void loop() {
  
  int vol_t = analogRead(vdiff);           //Read the Value of the Analog Input of Bat 1 and write it to the temp Variable
  int curr_t = analogRead(isens);           //Read the Value of the Analog Input of Bat 2 and write it to the temp Variable
  
  float vol = vol_t * (40 / 1023.0);    //Scale the Input to the displayed (Real) Value 36V on the Voltage divider are 3,3V on the Arduino
  float curr = curr_t * (148 / 1023.0);    //Scale the Input to the displayed (Real) Value 36V on the Voltage divider are 3,3V on the Arduino
 

  
    press=digitalRead(butonpin);       // reads the value of the buton (HIGH or LOW)
    lightb=digitalRead(lightbutton);    // reads the value of the Lightbutton
    Serial.println(press);
    
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setTextSize(1);
  display.setCursor(3,5);
  display.println("Moes Suicide Scooter");
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


  if (press == 1) {                   // if push buton pressed automatic mode starts
    myservo1.write(0);                // tell servo1 to go to Zero (brake if switch is enabled
    myservo2.write(0); 
    throttle = 0; 
    digitalWrite(blight, HIGH);       // switch on the breaklight            
    delay(15);                        // waits 15ms for the servo to reach the position
  }
  
  else {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 260);     // scale it to use it with the servo (value between 0 and 180)
  throttle = map(val, 0, 180, 0, 100);     // generate throttle Value 0 to 100% for the oled
  myservo1.write(val);                 // sets the servo1 position according to the scaled value
  myservo2.write(val);                 // sets the servo2 position according to the scaled value
  digitalWrite(blight, LOW);           // switch the breaklight off
  delay(15);                           // waits for the servo to get there

  }

if ((lightb == 1) && (light == LOW)){
  light = HIGH;
  digitalWrite(nightlight, HIGH);
  delay(150);
}

else if ((lightb == 1) && (light == HIGH)){
  light = LOW;
  digitalWrite(nightlight, LOW);
  delay(150);
}
  }
