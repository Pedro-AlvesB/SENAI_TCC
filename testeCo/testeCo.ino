#include <esp_now.h>
#include <WiFi.h>

const int ledPin = 2;  // LED conectado ao pino 2 (ajustar conforme necessário)
bool ledState = false;

typedef struct struct_message {
  char command[32];
} struct_message;

struct_message msg;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&msg, incomingData, sizeof(msg));

  if (strcmp(msg.command, "ligar") == 0) {
    ledState = true;
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ligado");
  } 
  else if (strcmp(msg.command, "desligar") == 0) {
    ledState = false;
    digitalWrite(ledPin, LOW);
    Serial.println("LED desligado");
  }
}

void setup() {
  Serial.begin(115200);

  // Configura o LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Inicializa Wi-Fi em modo STA
  WiFi.mode(WIFI_STA);

  // Imprime o endereço MAC
  Serial.print("Endereço MAC do escravo: ");
  Serial.println(WiFi.macAddress());

  // Inicializa ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar ESP-NOW");
    return;
  }

  // Registra a função callback para receber dados
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Imprime o estado do LED e o endereço MAC a cada 2 segundos
  Serial.print("Endereço MAC: ");
  Serial.print(WiFi.macAddress());
  Serial.print(" | Estado do LED: ");
  Serial.println(ledState ? "Ligado" : "Desligado");
  
  delay(2000);
}
