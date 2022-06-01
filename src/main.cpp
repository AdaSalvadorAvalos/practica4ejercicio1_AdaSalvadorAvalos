#include <Arduino.h>

const int led1 = 16; 
const int led2 = 17; 

void toggleLED(void * parameter);
void uploadToAWS(void * parameter);
void setup(){
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

xTaskCreatePinnedToCore(
    uploadToAWS,      
    "Upload to AWS",    
    1000,               
    NULL,               
    1,                  
    NULL,
    0         

);
    xTaskCreate(
    toggleLED,    
    "Toggle LED",  
    1000,            
    NULL,           
    1,               
    NULL         
  );
  


}


void toggleLED(void * parameter){
  for(;;){ 
 
    digitalWrite(led1, HIGH);

 
    vTaskDelay(500 / portTICK_PERIOD_MS);


    digitalWrite(led1, LOW);

    
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}





void uploadToAWS(void * parameter){
    // Implement your custom logic here
    Serial.print("Task is running on: ");
  Serial.println(xPortGetCoreID());

    // Turn the LED off
    // Turn the LED off
    digitalWrite(led2, HIGH);
    // Pause the task again for 500ms
    vTaskDelay(500 / portTICK_PERIOD_MS);

    digitalWrite(led2, LOW);
    
    // Pause the task again for 500ms
    vTaskDelay(500 / portTICK_PERIOD_MS);
    

    // When you're done, call vTaskDelete. Don't forget this!
    vTaskDelete(NULL);
}


void loop(){

}