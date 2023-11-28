#include <ESP8266WiFi.h>  // Include the Wi-Fi library
#include <DHT.h>  // Include the DHT Sensor library
#include <ThingSpeak.h> // Include the ThingSpeak library
#define DHTPIN 0 // Select the pin to which the sensor will be connected
#define DHTTYPE DHT22 // DHT22 is selected (there are other DHTs)
DHT dht(DHTPIN, DHTTYPE); // A variable is started to be used by Arduino to communicate with the sensor

const char* ssid = "SSID"; // The SSID (name) of the Wi-Fi network you want to connect to, must be 2.4 GHz band
const char* password = "12345678";  // The password of the Wi-Fi
unsigned long myChannelNumber = 2319526;
const char * myWriteAPIKey = "IV5J49VTSJN0WILI";

WiFiClient  client; // Create an instance of the server
WiFiServer server(80);  // specify the port to listen on as an argument

void setup() {
  Serial.begin(9600); // Start the Serial communication to send messages to the computer (baud rate)
  delay(5000);
  dht.begin();  // Start the sensor
  Serial.println('\n');
  
  WiFi.begin(ssid, password); // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

  ThingSpeak.begin(client);
}

void loop() {
  float h = dht.readHumidity(); // The humidity is read
  float t = dht.readTemperature(); // The temperature is read
  Serial.println("Humidity: "); 
  Serial.println(h);
  Serial.println("Temperature: ");
  Serial.println(t);
  delay(2000);
 
  ThingSpeak.writeField(myChannelNumber, 1, h, myWriteAPIKey);  // Send humidity data to ThingSpeak
  delay(20000); 
  
  ThingSpeak.writeField(myChannelNumber, 2, t, myWriteAPIKey);  // Send temperature data to ThingSpeak
  delay(20000); 
}
