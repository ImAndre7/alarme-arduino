#include <Adafruit_LiquidCrystal.h>

int sensor = A0;         // Pino analógico para o sensor de presença
int valor_do_sensor = 0; // Variável para armazenar o valor lido do sensor de presença
int gas = A1;            // Pino analógico para o sensor de gás
int valor_do_gas = 0;    // Variável para armazenar o valor lido do sensor de gás
int alarme = 2;          // Pino digital para o alarme sonoro
int led_1 = 5;           // Pino digital para o LED 1
int led_2 = 6;           // Pino digital para o LED 2
int led_3 = 7;           // Pino digital para o LED 3

Adafruit_LiquidCrystal lcd(0); // Objeto para controlar o display LCD

void setup() {
  pinMode(sensor, INPUT);  // Configura o pino do sensor como entrada
  pinMode(alarme, OUTPUT); // Configura o pino do alarme como saída
  Serial.begin(9600);      // Inicializa a comunicação serial
  lcd.begin(16, 2);      // Inicializa o LCD
  lcd.print(" ");        // Limpa o LCD
}

void loop() {
  // Lê o valor do sensor de presença
  valor_do_sensor = analogRead(sensor);
  Serial.println(valor_do_sensor);

  // Verifica se há presença detectada
  if (valor_do_sensor > 0) {
    lcd.setCursor(0, 1);
    lcd.print("Pessoa detectada");
    digitalWrite(alarme, HIGH);
    tone(alarme, 1000);
    delay(100);
    noTone(alarme);
    delay(500);
  }

  // Lê o valor do sensor de gás
  valor_do_gas = analogRead(gas);
  Serial.println(valor_do_gas);

  // Verifica se há gás detectado
  if (valor_do_gas > 95) {
    lcd.setCursor(0, 1);
    lcd.print(" Alarme acionado ");
    digitalWrite(alarme, HIGH);
    tone(alarme, 1000);
    delay(500);
    noTone(alarme);
    delay(1000);

    // Acende os LEDs e desliga o alarme após um curto período
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, HIGH);
    delay(100);
    digitalWrite(alarme, LOW);
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
    delay(100);
  } else {
    // Exibe "..." no LCD quando não há gás detectado
    lcd.setCursor(1, 1);
    lcd.print("    ...          ");
    delay(100);
    digitalWrite(alarme, LOW);
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
    delay(100);
  }
}