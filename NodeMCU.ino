#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "VT5byghv9RIy3scIO3J9uvjF8VwRppfW";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "KOKO_NEW";
char pass[] = "dom_kogutow";

BlynkTimer timer;
String myString;
String myText;
char rdata;

int myValue;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, millis() / 1000);
  Blynk.virtualWrite(V2, "dupa");
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, sensorvalue1);
  timer.setInterval(1000L, sensorvalue2);
}

void loop()
{
  if (Serial.available() == 0)
  {
    Blynk.run();
    timer.run(); // Initiates BlynkTimer
  }
  if (Serial.available() > 0)
  {
    rdata = Serial.read();
    myString = myString + rdata;
    // Serial.print(rdata);
    if (rdata == '\n')
    {
      String Value = getValue(myString, ',', 0);
      String Text = getValue(myString, ',', 1);
      myValue = Value.toInt();
      myText = Text;
      myString = "";
    }
  }
}

void sensorvalue1()
{
  int sdata = myValue;
  Blynk.virtualWrite(V3, sdata);
  Serial.println("----");
  Serial.println(sdata);
  //Serial.println("----");
}
void sensorvalue2()
{
  Blynk.virtualWrite(V4, myText);
  //Serial.println("----");
  Serial.println(myText);
  Serial.println("----");
}
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
