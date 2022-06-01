MATERIALES
· 2 LEDs
· ESP32
· 2 resistencias de 470ohms

Presentación:
En esta práctica aprendemos a crear tareas para poder utilizar diferentes cores de manera que todo vaya más rápido y usemos 
mejor el ESP32. A la pregunta, ¿qué sucede si está utilizando una pantalla de tinta electrónica que tarda unos segundos en actualizarse?
Pues que tardará mucho más y posiblemente se solape.

Explicación del código:

```
#include <Arduino.h>

const int led1 = 16; // Pin LED
const int led2 = 17; // Pin LED

void toggleLED(void * parameter); //llamada de las tareas
void uploadToAWS(void * parameter);//llamada de las tareas
void setup(){
  Serial.begin(115200); //Establece la velocidad de datos en bits por segundo para la transmisión de datos en serie
  pinMode(led1, OUTPUT);// inicializa el pin del LED como OUTPUT
  pinMode(led2, OUTPUT);// inicializa el pin del LED como OUTPUT

xTaskCreatePinnedToCore(
    uploadToAWS,      // funcion que se tiene que llamar
    "Upload to AWS",    // Nombre de la tarea para poder debuggear
    1000,               // tamaño pila(bytes)
    NULL,               
    1,                  // prioridad de la tarea
    NULL,		//identificador de tareas
    0         		//core que se usa

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
  for(;;){ //bucle infinito
  // enciende el LED
    digitalWrite(led1, HIGH);

    // Pausa la tarea por 500ms
    vTaskDelay(500 / portTICK_PERIOD_MS);

    // Apaga el LED
    digitalWrite(led1, LOW);

    // Pausa la tarea otra vez por la tarea 2: pinMode(led2, OUTPUT);500ms
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
// Al acabar llamar a vTaskDelete: para matar la tarea
   vTaskDelete(NULL);
}





void uploadToAWS(void * parameter){ //tarea 2
    Serial.print("Task is running on: "); //enseña por la terminal 
  Serial.println(xPortGetCoreID()); //enseña por la terminal 

  
    // Enciende el LED
    digitalWrite(led2, HIGH);
    // Pausa la tarea por 500ms
    vTaskDelay(500 / portTICK_PERIOD_MS);
	  // Apaga el LED
    digitalWrite(led2, LOW);
    
   // Pausa la tarea por 500ms
    vTaskDelay(500 / portTICK_PERIOD_MS);
    

    // Al acabar llamar a vTaskDelete: para matar la tarea
    vTaskDelete(NULL);
}


void loop(){

}

```
En el video se ven las salidas: podemos ver como un LED se enciende y apaga durante un rato, y el otro solo se enciende una vez.
