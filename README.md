## Weather monitoring station
This project aims to create a weather station that collects data from DHT11 sensor (temperature and humidity) as well as a gaz sensor(MQ-2) and sending using RF module(RX & TX) using SPI as a communication procole
## TOOLS
FreeRtos and Arduino
## FreeRtos
Real time operating system for embedded devices, it offers many key functionalities:
   - Creating and deleting multiple tasks where each task has its own stack, priority over other tasks
   - Scheduler : is a routine that decides which task should be in the running state, and it s preemptive meaning the scheduler always runs the task that has the highest priority
   - Communication between tasks : using some integrated functionalities such as queue, semaphore and mutex
   - timers: executing tasks after delays
    
