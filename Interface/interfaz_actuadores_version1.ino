#include <SPI.h>
#include <Client.h>
#include <Ethernet.h>
#include <Server.h>
#include <Udp.h>
#include <Servo.h>  
//#include <DHT.h> //cargamos la librería DHT
//#define DHTPIN 12
//#define DHTTYPE DHT11
//Seleccionamos el pin en el que se //conectará el sensor
//Se selecciona el DHT11 (hay //otros DHT)
//DHT dht(DHTPIN, DHTTYPE); //Se inicia una variable que será usada por Arduino para comunicarse con el sensor
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,0, 10);
// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
Servo myservo; // create servo object to control a servo
int PinLed1= 5; //esto sera actuador 1 en algun momento
int PinLed2= 4; //esto sera actuador 2 en algun momento
//int Entrada1= 5;
//int Entrada2=6;
String readString = String(30);
int analog_pin = 0;
float temperatura;
void setup()
{
// start the Ethernet connection and the server:
Ethernet.begin(mac, ip);
server.begin();
pinMode(PinLed1,OUTPUT);
pinMode(PinLed2,OUTPUT);
//pinMode(Entrada1,INPUT);
//pinMode(Entrada2,INPUT);
//dht.begin(); //Se inicia el sensor
//pinMode(2,INPUT_PULLUP);
pinMode(12, INPUT);
digitalWrite(12, HIGH); //pullup
pinMode(5, OUTPUT); //pin selected to control
myservo.attach(7); //the pin for the servo control
}
void loop()
{
//int h = dht.readHumidity(); //Se lee la humedad
//float t = dht.readTemperature(); //Se lee la temperatura
temperatura = analogRead(analog_pin);
temperatura = 5.0*temperatura*100.0/1024.0;
// listen for incoming clients
EthernetClient client = server.available();
if (client) {
// an http request ends with a blank line
boolean currentLineIsBlank = true;
while (client.connected()) {
if (client.available()) {
char c = client.read();
if (readString.length()<100) //leer peticion HTTP caracter por caracter
{
readString += c;
}
if (c=='\n') //Si la peticion HTTP ha finalizado
{
//Determinar lo que se recibe mediante GET para encender el Led o apagarlo
if(readString.indexOf("Led1=Encender")>0){
digitalWrite(PinLed1,HIGH);
}
if(readString.indexOf("Led1=Apagar")>0){
digitalWrite(PinLed1,LOW);
}
if(readString.indexOf("Led2=Encender")>0){
digitalWrite(PinLed2,HIGH);
}
if(readString.indexOf("Led2=Apagar")>0){
digitalWrite(PinLed2,LOW);
}

if(readString.indexOf("?on") >0)//checks for on
{
myservo.write(10);
digitalWrite(5, HIGH); // set pin 4 high
Serial.println("Led On");
}
if(readString.indexOf("?off") >0)//checks for off
{
myservo.write(110);
digitalWrite(5, LOW); // set pin 4 low
Serial.println("Led Off");
}



readString=""; //Vaciar el string que se uso para la lectura
//Enviar cabecera HTTP estandar
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
// client.println("Connection: close"); // the connection will be closed after completion of the response
// client.println("Refresh: 1"); // refresh the page automatically every 5 sec
client.println();
//Crear pagina web HTML
client.println("<html>");
client.println("<head>");
client.println("<title>Centro de control domestico 1.0</title>");
client.println("</head>");
client.println("<body>");
client.println("<h1>Centro de control domestico 1.0</h1>");
client.println("<hr><br>");
client.println("<h3>Encendido/Apagado de instrumentos</h3>");
client.println("<hr><br>");
client.println("<table>");
client.println("<tr><td>Iluminacion</td><td>Ventilacion</td></tr>");
client.println("<tr><td><form method=get><input type=submit name=Led1 value=Encender></form></td><td><form method=get><input type=submit name=Led2 value=Encender></form></td></tr>");
client.println("<tr><td><form method=get><input type=submit name=Led1 value=Apagar ></form></td><td><form method=get><input type=submit name=Led2 value=Apagar></form></td></tr>");
client.println("</table>");
client.println("<hr><br>");
client.println("<h3>Lectura de sensores</h3>");
client.println("La tempetara es");
client.println("<br>");
client.println(temperatura);
client.println("<hr><br>");
client.println("<H1>Control de servo para riego</H1>");
client.println("<a href=\"/?on\"\">IZQUIERDA</a>");
client.println("<a href=\"/?off\"\">DERECHA</a>");

//client.println("La humedad es");
//client.println("<br>");
//client.println(h);
//client.println("<hr> <br>");
client.println("</body>");
client.println("</html>");
client.stop();


}
}
}
}
}
