#include <ESP8266WiFi.h>
int IN1 = 16;    
int IN2 = 5;
int IN3 = 4;    
int IN4 = 0; 
int IN5 = 14;    
int IN6 = 12;
int IN7 = 13;    
int IN8 = 15; 

int trigger=3;
int echo=2;
int opcion =5; 
int cm=0;
String request="";
//a que red se conecta, en este ejemplo es la red de mi celular
const char* ssid = "APX";
const char* password = "12354678";
//const char* ssid = "INFINITUM743N_2.4";
//const char* password = "2wnjJqUMFP";
int ledPin = 13; // GPIO13
WiFiServer server(80);
void setup() {
  //inicializa el serial para evitar pedos
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  detenerse();
  // Conectado con  Red WiFi
  Serial.println();
  Serial.print("Conectando con ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectada ");
  // Start the server
  server.begin();
  Serial.println("Servidor Conectado");
  // imprime la ip que define
  Serial.print("Use la siguiente URL para conectarse : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
   
}
void loop() {
  
  WiFiClient client = server.available();
  if(client.available()>0){
    request = client.readStringUntil('\r');
  }
  if (request.indexOf("/front") != -1)  {
    opcion=1;
  }
  if (request.indexOf("/back") != -1)  {
    opcion=2;
  }
  if (request.indexOf("/left") != -1)  {
    opcion=3;
  }
  if (request.indexOf("/right") != -1)  {
    opcion=4;
  }
  if (request.indexOf("/stop") != -1)  {
    opcion=5;
  }
  if (request.indexOf("/sensor") != -1)  {
    cm = ping(trigger, echo);
    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  Comillas importantes.
    if (cm <= 30){
        client.print(cm);  
    }else{
      client.print("....");
    }
    client.println(" cm");
  }
    
  
  switch(opcion){
    case 1: avanza(); break;
    case 2: reversa(); break;
    case 3: giro_IZQ(); break;
    case 4: giro_DER(); break;
    case 5: detenerse(); break;
    default: detenerse(); break;
    
  }
  
}

void reversa(){
    digitalWrite (IN1, HIGH);
    digitalWrite (IN2, LOW);
    digitalWrite (IN3, HIGH);
    digitalWrite (IN4, LOW);
    digitalWrite (IN5, HIGH);
    digitalWrite (IN6, LOW);
    digitalWrite (IN7, HIGH);
    digitalWrite (IN8, LOW);
}
void avanza(){
    digitalWrite (IN2, HIGH);
    digitalWrite (IN1, LOW);
    digitalWrite (IN4, HIGH);
    digitalWrite (IN3, LOW);
    digitalWrite (IN6, HIGH);
    digitalWrite (IN5, LOW);
    digitalWrite (IN8, HIGH);
    digitalWrite (IN7, LOW);
}

void giro_IZQ(){
      digitalWrite (IN1, LOW);
      digitalWrite (IN2, LOW); 
      digitalWrite (IN3, LOW);
      digitalWrite (IN4, HIGH);
      
      digitalWrite (IN6, HIGH);
      digitalWrite (IN5, LOW); 
      digitalWrite (IN7, LOW);
      digitalWrite (IN8, LOW);
}

void giro_DER(){
      digitalWrite (IN1, LOW);
      digitalWrite (IN2, HIGH); 
      digitalWrite (IN3, LOW);
      digitalWrite (IN4, LOW);
      
      digitalWrite (IN6, LOW);
      digitalWrite (IN5, LOW); 
      digitalWrite (IN8, HIGH);
      digitalWrite (IN7, LOW);
}

void detenerse(){
    digitalWrite (IN1, LOW);
    digitalWrite (IN2, LOW);
    digitalWrite (IN3, LOW);
    digitalWrite (IN4, LOW);
     digitalWrite (IN5, LOW);
    digitalWrite (IN6, LOW);
    digitalWrite (IN7, LOW);
    digitalWrite (IN8, LOW);
}

int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   digitalWrite(TriggerPin,LOW);
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   duration = pulseIn(EchoPin, HIGH); 
   distanceCm = duration * 10 / 292/ 2;  
   return distanceCm;
}
