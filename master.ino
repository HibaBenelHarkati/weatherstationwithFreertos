#include<Arduino_FreeRTOS.h>
#include<semphr.h>
#include<string.h>
#include <RH_ASK.h>
#include <SPI.h>

#include<DHT.h>
 


#define DHTpin 4
#define air A0 
#define TX 11 

RH_ASK rf_driver;
DHT dht11(DHTpin,DHT11);                             

SemaphoreHandle_t semaphore;


void task1(void *p);
void task2(void *p);



void setup() {
  Serial.begin(9600);
  pinMode(DHTpin,INPUT);
  pinMode(air,INPUT);
  rf_driver.init();
  dht11.begin();

  Serial.println("hi1");
  xTaskCreate(task1,"temp",500,NULL,2,NULL);   //priority was 150
  Serial.println("hi2");
  xTaskCreate(task2,"aur_qual",150,NULL,1,NULL);
  Serial.println("hi3");
  //xTaskCreate(gaz,"air quality",120,NULL,1,NULL);
  semaphore= xSemaphoreCreateBinary();
  if(semaphore==NULL){
      Serial.println("the sem wasnt created");
  }
   else{
      Serial.print("sem created");
  }
  vTaskStartScheduler();

}

void loop() {
}

void task1(void *p){  //task1 : managing hum and temp reading values
  //Serial.println("hello");
  //delay(1000);    // kant ka tprint hel then after i added a delay it printed hello
  for(;;){
      xSemaphoreTake(semaphore,0);
      Serial.println("i took the semaphore1");
      Serial.println("hi");
      delay(1000);
      int temp= dht11.readTemperature();
      delay(1000);
      Serial.println("la temp est :");
      Serial.println(temp);
      rf_driver.send((uint8_t *)&temp, sizeof(temp));
      rf_driver.waitPacketSent(); 
      Serial.println("send1");
      delay(2000);

      int humidity=dht11.readHumidity();
      Serial.println("l humidite est :");
      Serial.println(humidity);
      //delay(1000);
      rf_driver.send((uint8_t *)&humidity, sizeof(humidity));
      rf_driver.waitPacketSent();
      Serial.println("send2");
      delay(1900);
      xSemaphoreGive(semaphore);
      delay(1900);
  }
    
  //delay(1000);
  
}


void task2(void *p){

  for(;;){
      delay(1000);
      xSemaphoreTake(semaphore,portMAX_DELAY);
      Serial.println("i took semaphore 2");
      int smoke=digitalRead(air);
      delay(1000);
      Serial.println("smoke est :");
      Serial.println(smoke);
      delay(1000);
      rf_driver.send((uint8_t *)&smoke, sizeof(smoke));
      rf_driver.waitPacketSent();
      Serial.println("send2");

      xSemaphoreGive(semaphore);
    //delay(1000);
  }
}
