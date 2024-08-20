#include <Arduino.h>

// constants won't change. Used here to set a pin number:
const int ledPin = LED_BUILTIN;  // the number of the LED pin
const int clockPin = 8;          // entrada do pulso de clock
const int sensorPin = A0;        // entrada do sinal analógico
const int Total = 350;           // total de amostras

// Variables will change:
unsigned long tempo_ms;
int ledState = LOW;      // ledState used to set the LED
int count;               // contador de amostras
int readValues[Total+1]; // valores de amostras lidas
bool pronto;             // sinaliza o fim das amostras

// the setup routine runs once when you press reset:
void setup() {
  count = 0;
  pronto = false;

  pinMode(clockPin, INPUT); 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);      

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // prints title with ending line break
  Serial.println("\n\n*** Sample & Hold 2024 ***\n");
  delay(3000);
  tempo_ms = millis();
}

// the loop routine runs over and over again forever:
void loop() {

  while(digitalRead(clockPin) == LOW)  {}
  // Espera pulso do gerador de clock
  while(digitalRead(clockPin) == HIGH) {}
 
  // leitura da entrada analógica:
  readValues[count] = analogRead(sensorPin);
  
  if (count < Total) {
    count++;
  }
  else {
    if (pronto == false) {
      pronto = true;  // a última amostra já foi feita
      tempo_ms = millis() - tempo_ms; // calcula tempo gasto

      Serial.print("Tempo (ms) = ");
      Serial.println(tempo_ms);
      Serial.print("Amostras   = ");
      Serial.println(count);

      for (count = 0; count < Total; count++) {
        Serial.println(readValues[count]);
      }

      digitalWrite(ledPin, HIGH);
    }

  }
  
}