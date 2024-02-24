#include <Arduino.h>
#include <SPI.h>

#define PIN_CS 5
#define PIN_MOSI 23
#define PIN_SCK 18

SPIClass vspi(VSPI);

void setup()
{
  // Inizializza il monitor seriale
  Serial.begin(115200);

  // Configura lo shift register
  pinMode(PIN_CS, OUTPUT);
  pinMode(PIN_MOSI, OUTPUT);
  pinMode(PIN_SCK, OUTPUT);

  // Inizializza lo SPI
  vspi.begin();
  vspi.beginTransaction(SPISettings(1000000, LSBFIRST, SPI_MODE0));
}

void loop()
{
  int num;
  String nums;
  // Legge un numero dal terminale seriale
  if (Serial.available())
  {
    nums = Serial.readStringUntil('\n');
    Serial.print("Stringa ");
    Serial.println(nums);
    num = nums.toInt();
    Serial.print("Numero ");
    Serial.println(num);

    // Controlla che il numero sia valido
    if (num < 0 || num > 255)
    {
      Serial.println("Il numero deve essere compreso tra 0 e 255");
      return;
    }

    // for (num = 0; num < 255; num++)
    // {
    // num = 6;
    uint8_t data = (uint8_t)num;

    // Invia il dato allo shift register
    digitalWrite(PIN_CS, LOW);
    vspi.transfer(data);
    digitalWrite(PIN_CS, HIGH);

    // Stampa il numero in binario sul terminale seriale
    Serial.print("Binario: ");
    Serial.println(data, BIN);
    // delay(100);
  }
}