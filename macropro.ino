#include <Keyboard.h> // Incluir la libreria keyboard.h
 
uint8_t button_val[11];
bool down[11];
bool press_next[11];

int modePushCounter = 0;       // Contador de los modos
int buttonState = 0;           // Estado actual del boton
int lastButtonState = 0;       // Estado anterior del Boton
const int ModeButton = A1;     // Pin al que esta conectado el FN
 
uint8_t button_pins[11] = { 2, 3, 4, 5, 6, 7, 8, 9, 14, 16, 10 }; // Arrays con los pines del arduino que usa el teclado

void setup() {

    pinMode(ModeButton, INPUT_PULLUP);  // Configura ModeButton como entrada

    for(uint8_t i = 0; i < 11; i++) { // Recorre el array button_pins
        pinMode(button_pins[i], INPUT_PULLUP); // Configura los pines como entradas
    }
 
    Keyboard.begin(); // Inicializando al libreria
}

void checkModeButton(){
  buttonState = digitalRead(ModeButton);
  if (buttonState != lastButtonState) { // Compara el estado del boton con su estado anterior
    if (buttonState == LOW) { // Si el estado cambio aumenta el contador
      // Si el estado actual es LOW, entonces el boton cumple un ciclo:
      modePushCounter++;
      Serial.println("Presionado");
      Serial.print("Estado Actual: ");
      Serial.println(modePushCounter);
    } 
    delay(50);
  }
  lastButtonState = buttonState;  // Guarda el estado actual como el ultimo estado
   if (modePushCounter >1){       // Reseteo
      modePushCounter = 0;}
}

 
void loop()
{
  checkModeButton();
  
    for(uint8_t i = 0; i < 11; i++) {
        button_val[i] = digitalRead(button_pins[i]); // Lee el valor de los pines si es LOW o  HIGH
        press_next[i] = false;
 
        if (button_val[i] == 0 && !down[i]) {
            down[i] = true;
            press_next[i] = true;
        } else if (button_val[i] == 1 && down[i]) {
            down[i] = false;
        }
    }
    
    for(uint8_t i = 0; i < 11; i++) {
        if (press_next[i]) {
            // Si el estado es 0
            if (modePushCounter == 0) {
             switch (i) {
              case 0: 
                Keyboard.press('a');
              break;            
              case 1: 
                Keyboard.press('a');
                break;
              case 2: 
                Keyboard.press('b');
                break;             
              case 3: 
                Keyboard.press('c');   
                break;
              case 4: 
                Keyboard.press('d');   
                break;  
              case 5: 
                Keyboard.press('f');   
                break; 
              case 6: 
                Keyboard.press('g');   
                break;    
              case 7: 
                Keyboard.press('h');   
                break;
              case 8: 
                Keyboard.press('i');   
                break;
              case 9: 
                Keyboard.press('j');   
                break;
              case 10: 
                Keyboard.press('k');   
                break;
               }
          // Si el estado es 1
          } else if (modePushCounter == 1) {
           switch (i) {
            case 0: 
              Keyboard.press('a');
            break;            
            case 1: 
              Keyboard.press('a');
              break;
            case 2: 
              Keyboard.press('b');
              break;             
            case 3: 
              Keyboard.press('c');   
              break;
            case 4: 
              Keyboard.press('d');   
              break;  
            case 5: 
              Keyboard.press('f');   
              break; 
            case 6: 
              Keyboard.press('g');   
              break;    
            case 7: 
              Keyboard.press('h');   
              break;
            case 8: 
              Keyboard.press('i');   
              break;
            case 9: 
              Keyboard.press('j');   
              break;
            case 10: 
              Keyboard.press('k');   
              break;
             }
          }
          delay(250);
          Keyboard.releaseAll(); // Deja de precionar todas las teclas cada vez que una es tocada
 
        }
    }
}
