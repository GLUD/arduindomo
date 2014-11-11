#include "DHT.h" //cargamos la librería DHT
#define DHTPIN 12

int analog_pin = 0;
float temperatura;

//Seleccionamos el pin en el que se //conectará el sensor
#define DHTTYPE DHT11 //Se selecciona el DHT11 (hay //otros DHT)
DHT dht(DHTPIN, DHTTYPE); //Se inicia una variable que será usada por Arduino para comunicarse con el sensor
void setup() {
Serial.begin(9600); //Se inicia la comunicación serial 
dht.begin(); //Se inicia el sensor

pinMode(12, INPUT);
digitalWrite(12, HIGH); //pullup
  
}
void loop() {
float h = dht.readHumidity(); //Se lee la humedad
float t = dht.readTemperature(); //Se lee la temperatura
//Se imprimen las variables
Serial.println("Humedad: "); 
Serial.println(h);
Serial.println("Temperatura: ");
delay(2000); //Se espera 2 segundos para seguir leyendo //datos
 temperatura = 5.0*temperatura*100.0/1024.0;
 temperatura = analogRead(analog_pin);
  
  Serial.print(temperatura);
  Serial.println(" oC");
  delay(1000);
  
}
