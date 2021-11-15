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
//                cortar
                Serial.println("Cortar");
                Keyboard.press(KEY_LEFT_CTRL);  
                Keyboard.print('x');
              break;            
              case 1: 
//                Captura de pantalla
                  Keyboard.press (KEY_LEFT_GUI);
                  Keyboard.press (KEY_LEFT_SHIFT);
                  Keyboard.print('s');    
                break;
              case 2: 
//                Pegar
                Serial.println("Pegar");
                Keyboard.press(KEY_LEFT_CTRL);  
                Keyboard.print('v');
                break;             
              case 3: 
//                Copiar
                Serial.println("Copiar");
                Keyboard.press(KEY_LEFT_CTRL);  
                Keyboard.print('c'); 
                break;
              case 4: 
//                Guardar  
                Serial.println("Guardar");
                Keyboard.press(KEY_LEFT_CTRL);  
                Keyboard.print('s');  
                break;  
              case 5: 
                Serial.println("F13");
                Keyboard.press(KEY_F13);    
                break; 
              case 6: 
                Serial.println("F14");
                Keyboard.press(KEY_F14);   
                break;    
              case 7:
                Serial.println("F15"); 
                Keyboard.press(KEY_F15);   
                break;
              case 8: 
                Serial.println("F18");
                Keyboard.press(KEY_F18);   
                break;
              case 9: 
                Serial.println("F17");
                Keyboard.press(KEY_F17);   
                break;
              case 10: 
                Serial.println("F16");
                Keyboard.press(KEY_F16);   
                break;
               }
          // Si el estado es 1
          } else if (modePushCounter == 1) {
           switch (i) {
            case 0: 
//            Cortar
              Keyboard.press(KEY_LEFT_GUI);
              Keyboard.print('x');
            break;            
            case 1: 
//            Captura de pantalla
              Keyboard.press (KEY_LEFT_GUI);
              Keyboard.press (KEY_LEFT_SHIFT);
              Keyboard.print(3);
              break;
            case 2: 
//            Pegar
              Keyboard.press(KEY_LEFT_GUI);
              Keyboard.print('x');
              break;             
            case 3: 
//            Copiar
              Keyboard.press(KEY_LEFT_GUI);
              Keyboard.print('x');  
              break;
            case 4: 
//            Guardar
              Keyboard.press(KEY_LEFT_GUI);
              Keyboard.print('s');   
              break;  
            case 5: 
                Keyboard.press(KEY_F13);   
              break; 
            case 6: 
                Keyboard.press(KEY_F14);
              break;    
            case 7: 
                Keyboard.press(KEY_F15);
              break;
            case 8: 
                Keyboard.press(KEY_F18);   
              break;
            case 9: 
                Keyboard.press(KEY_F17);
              break;
            case 10: 
                Keyboard.press(KEY_F16);     
              break;
             }
          }
          delay(250);
          Keyboard.releaseAll(); // Deja de precionar todas las teclas cada vez que una es tocada
 
        }
    }
}
