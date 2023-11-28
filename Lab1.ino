#include <dht.h>
#define dataPin 8 //Define el número de pin al que se encuentra el sensor conectado
dht DHT; // Crea un objeto DHT

void setup() 
{
    Serial.begin(9600);
}
void loop() 
{

    int readData = DHT.read22(dataPin); // DHT22/AM2302
    //int readData = DHT.read11(dataPin); //DHT11

    float t = DHT.temperature; // Obtiene los valores de la temperatura
    float h = DHT.humidity; // Obtiene los valores de la humedad

    // Impresión de los resultados en el monitor serie
    Serial.print("Temperature = ");
    Serial.print(t);
    Serial.print(" ");
    Serial.print((char)176);//Muestra el carácter de los grados
    Serial.print("C | ");
    Serial.print((t * 9.0) / 5.0 + 32.0);
    Serial.print(" ");
    Serial.print((char)176);//Muestra el carácter de los grados
    Serial.println("F ");
    Serial.print("Humidity = ");
    Serial.print(h);
    Serial.println(" % ");
    Serial.println("");

    delay(2000); //Retrasos 2 segundos
}
