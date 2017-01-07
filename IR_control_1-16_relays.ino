#include "IRremote.h"
IRrecv irrecv(11); //Pin IR / Дата пин ИК датчикка
decode_results results;

unsigned long Value[] = {   // Buttons / Кнопки пульта
0xFFE817, 0xFF48B7, 0xFF6897, 0xFF02FD, 0xFF32CD, 0xFF20DF, 0xFF50AF, 0xFF7887}; 
unsigned long Value21 = 0xFF708F;    // All toggle / Все переключает
unsigned long Value22 = 0xFF28D7;    // All off / Все выключает
unsigned long Value23 = 0xFF38C7;    // Up and doun / Лесенка
unsigned long Value24 = 0xFFF00F;    // Up and doun 1000 times Лесенка 1000 раз

int pin[] = {22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0};  //  Set pins / Установка пинов

int relay[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // State of relays / Переменные состояния реле

int rel = 8;  // Q-ty of relays / Количество реле (1-16)

void setup() {
  for (int i=0; i < rel; i++){
    pinMode(pin[i],OUTPUT);  // Set pins as output / Делаем пины выходами
  }

  for (int i=0; i<rel; i++){
    relay[i] =  1;
    digitalWrite(pin[i], relay[i]);   // Setting default relay state / Установка начального состояния реле
    }
      
  Serial.begin(9600);
  irrecv.enableIRIn();
}
void loop() {
  if ( irrecv.decode( &results )) { 
  Serial.println(results.value, HEX);
 
  for (int i=0; i<rel; i++){ 
    if (results.value==Value[i]){
      relay[i] =  !relay[i];
      digitalWrite(pin[i], relay[i]);
      results.value=0;
    }    
  }

  if (results.value==Value21){
    for (int i=0; i<=rel; i++){
      relay[i] =  !relay[i];
      digitalWrite(pin[i], relay[i]);
    }
  }
  
    if (results.value==Value22){
    for (int i=0; i<rel; i++){
      relay[i] =  1;
      digitalWrite(pin[i], relay[i]);
    }
  }
  
  if (results.value==Value23){
  for (int i=0; i<rel; i++){
    relay[i] =  1;
    digitalWrite(pin[i], 0); 
    delay(50);
    digitalWrite(pin[i], relay[i]); 
    }
  
  for (int i=rel; i>=0; i--){
    relay[i] =  1;
    digitalWrite(pin[i], 0); 
    delay(50);
    digitalWrite(pin[i], relay[i]); 
    }
  }
  
  if (results.value==Value24){
for (int i=0; i<1000; i++){    // 1000 times / 1000 раз
  for (int i=0; i<rel; i++){
    relay[i] =  1;
    digitalWrite(pin[i], 0); 
    delay(50);
    digitalWrite(pin[i], relay[i]); 
    }
  
  for (int i=rel; i>=0; i--){
    relay[i] =  1;
    digitalWrite(pin[i], 0); 
    delay(50);
    digitalWrite(pin[i], relay[i]); 
    }
  }
}  
 irrecv.resume();   
  }
  
}
