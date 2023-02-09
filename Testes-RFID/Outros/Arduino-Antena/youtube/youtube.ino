#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(7, 6); //232_TX,232_RX Serial connection between RS232 shield and microcontroller

unsigned char incomingBytes;
String code="";

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }
 
 
    Serial.println("Programmer4Rent!");
 
    // set the data rate for the SoftwareSerial port
    mySerial.begin(9600);
    mySerial.println("Hello, world?");
}
 
void loop() // run over and over and wait for  RF tag
{
    while (mySerial.available() >0)
    {
        incomingBytes = mySerial.read (); //reads the rf tag codes 

        code = code +  String(incomingBytes, HEX) + " "; //convert the code to readable form
    }
    if (code.length() >1 ) 
    {
        Serial.println (code);
    }

    code = "";
    delay (1000);
}