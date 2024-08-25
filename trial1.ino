#include<Arduino_FreeRTOS.h>
#include<semphr.h>
#include<string.h>

#include<DHT.h>
 


#define DHTpin 4
#define air A0 


DHT dht11(DHTpin,DHT11);                             //initialiser le capteur dht 
SemaphoreHandle_t semaphore;


void task1(void *p);
void task2(void *p);

void setup() {
  Serial.begin(9600);
  pinMode(DHTpin,INPUT);
  pinMode(air,INPUT);
  dht11.begin();
  semaphore= xSemaphoreCreateBinary();
  Serial.println("hi1");
  xTaskCreate(task1,"temp",500,NULL,2,NULL);   //priority it was 150
  Serial.println("hi2");
  xTaskCreate(task2,"aur_qual",150,NULL,1,NULL);
  Serial.println("hi3");
  //xTaskCreate(gaz,"air quality",120,NULL,1,NULL);
  vTaskStartScheduler();

}

void loop() {
}

void task1(void *p){
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
      delay(1000);
      int humidity=dht11.readHumidity();
      Serial.println("l humidite est :");
      Serial.println(humidity);
      delay(1000);
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
   
      xSemaphoreGive(semaphore);
    //delay(1000);
  }
}