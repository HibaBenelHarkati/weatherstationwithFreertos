#include<Arduino_FreeRTOS.h>
// urnit une bibliothèque complète orientée objet pour envoyer et recevoir des messages en paquets via une variété de radios
#include<SPI.h>   // spi protocole ed communication(interface entre deux microcontrolleers :ports 12 :tx, rx:11)       
#include<queue.h>
#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include<ESP8266mDNS.h>
#define slave 11
#define tx 2   //de l esp8666
#define rx 3     

const char *ssid= "WIFI_AIAC_Etudiants";
const char *password= "123456";
ESP8266WebServer espserver(80);
RH_ASK rf1;
//QueueHandle_t queue1;

void receiving(void *p);  // receiving chaine then la convertir vers array then afficher 
void SendToweb(void *p);

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  rf1.init();
  xTaskCreate(receiving,"reading",540,NULL,1,NULL);
  Serial.println(WiFi.localIP())
  delay(1000);
  espserver.on()
}

void loop() {
}

/-------------------HTML--------------------/
void sendToweb(void *p){
  String page="<!DOCTYPE html>\n\n";
  page+="<html lang="en">\n";
  page+="<head>\n";
  page+="<meta charset="UTF-8">\n";
  page+="<meta name="viewport" content="width=device-width, initial-scale=1.0">\n";
  page+="<style>\n";
  page+="#btn{display:inline;
            text-decoration: none;
            background-color: rgb(45, 155, 188);
            color:azure;
            font-size:20px;
            font-family: Arial, Helvetica, sans-serif;
            border-radius: 20px 20px 20px red;
            border: 2mm ridge rgb(76, 36, 36);
            cursor:pinter}\n";
  page+="body{font-family: Arial, Helvetica, sans-serif;background-color: antiquewhite}\n";
  page+="h1{color: black;text-align: center;font-size:50px}\n";
  page+="</style>\n";
  page+="</style>\n";
  page+="</head>\n";
  page+="<body>\n";
  page+="<h1>\n";
  page+="TEMPERATURE AND HUMIDITY Webpage<br>\n";
  page+="<a href="#" id="btn" >Temperature";
  page+= String(temp_rec)
  page+="</a><br>\n";
  page+="<a href="#" id="btn" >Humidity:";
  page+=String(hum_rec);
  page+="</a><br>";
  page+="<a href="#" id="btn" >";
  page+=String(qual_rec);
  page+="</a><br>\n"
  page+="</h1>\n";
  page+="</body>\n";
  page+="</html>\n";
  espserver.send("/",HTTP_GET,page);
}

void receiving(void *p){
  uint8_t arr1[6];
  uint8_t lenght=sizeof(arr1);
  int db[3];
  char *token;
  if(rf1.recv(arr1,&lenght)){
    for(int i;i<strlen(arr1);i++){
      Serial.print("la valeur recevee:");
      const char delimiter=" ";
      token=strtok(arr1,delimiter);   //get the first toke and convert it to int 
      int element= token-"0";                            //elemnts starting from temp ->humidity ->quality of the air
      xQueueSendToBack(queu1,element,portMAX_DELAY);
    }
  }
  
} 
