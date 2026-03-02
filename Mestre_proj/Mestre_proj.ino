#include <esp_now.h>
#include <WiFi.h>
#include <BluetoothSerial.h>
#include <ESP32Servo.h>

// Definindo pinos para o BTS7960
#define LPWM 14
#define RPWM 15
#define L_EN 17
#define R_EN 16

// Pino do servo motor
#define servoPin 22

// Pino do sensor Hall
#define hallPin1 28
#define hallPin2 27
#define hallPin3 26
#define hallPin4 25

// Cria o servo
Servo myServo;

bool acoplado = false;

// Estrutura para receber dados do mestre
typedef struct struct_message {
    int motorSpeed;
    int servoAngle;
    bool acoplarStatus;
} struct_message;

struct_message myData;

void setup() {
    // Configurando os pinos do motor como saída
    pinMode(LPWM, OUTPUT);
    pinMode(RPWM, OUTPUT);
    pinMode(L_EN, OUTPUT);
    pinMode(R_EN, OUTPUT);
    digitalWrite(L_EN, HIGH);
    digitalWrite(R_EN, HIGH);

    // Inicializando o servo motor
    myServo.attach(servoPin);
    myServo.write(90);  // Posição inicial

    // Configurando os sensores Hall como entrada
    pinMode(hallPin1, INPUT);
    pinMode(hallPin2, INPUT);
    pinMode(hallPin3, INPUT);
    pinMode(hallPin4, INPUT);

    // Inicializando ESP-NOW
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Erro ao inicializar ESP-NOW");
        return;
    }

    // Definindo callback para receber dados
    esp_now_register_recv_cb(OnDataRecv);

    Serial.begin(115200);
    Serial.println("Setup concluído - Mestre");
}

// Nova assinatura da função callback para ESP-NOW
void OnDataRecv(const esp_now_recv_info *recvInfo, const uint8_t *incomingData, int len) {
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.println("Dados recebidos do mestre");
}

void loop() {
    // Se o mestre estiver aguardando o acoplamento
    if (!acoplado && myData.acoplarStatus) {
        if (analogRead(hallPin1) == HIGH || analogRead(hallPin2) == HIGH || 
            analogRead(hallPin3) == HIGH || analogRead(hallPin4) == HIGH) {
            Serial.println("Acoplamento detectado");
            acoplado = true;
        }
    } else if (Serial.available()) {
        char command = Serial.read();

        if (command == 'A') {
            // Verifica o estado de acoplamento e alterna entre acoplar e desacoplar
            if (!acoplado) {
                Serial.println("Iniciando acoplamento...");
                enviarComandoAcoplar(true);
                acoplado = true;
            } else {
                Serial.println("Desacoplando...");
                enviarComandoAcoplar(false);
                acoplado = false;
            }
        } else {
            // Controla o movimento com outros comandos
            switch (command) {
                case 'F': moveForward(); break;
                case 'T': moveBackward(); break;
                case 'E': moveLeft(); break;
                case 'D': moveRight(); break;
                case 'P': stopMotor(); break;
            }
        }
    }

    // Se estiver acoplado, segue os comandos do mestre
    if (acoplado) {
        seguirMovimentosDoMestre();
    }
}

// Função para seguir os movimentos do mestre
void seguirMovimentosDoMestre() {
    // Configura o ângulo do servo com base nos dados recebidos
    myServo.write(myData.servoAngle);

    // Configura a direção e a velocidade do motor com base nos dados recebidos
    if (myData.motorSpeed > 0) {
        analogWrite(LPWM, myData.motorSpeed);
        analogWrite(RPWM, 0);
    } else if (myData.motorSpeed < 0) {
        analogWrite(LPWM, 0);
        analogWrite(RPWM, abs(myData.motorSpeed));
    } else {
        analogWrite(LPWM, 0);
        analogWrite(RPWM, 0);
    }

    // Se o mestre enviar comando para desacoplar
    if (!myData.acoplarStatus) {
        Serial.println("Desacoplamento detectado");
        acoplado = false;
    }
}

// Funções de movimento
void moveForward() {
    myServo.write(90); // Servo para frente
    analogWrite(LPWM, 255); // Velocidade máxima
    analogWrite(RPWM, 0);
    delay(500);
}

void moveBackward() {
    myServo.write(90); // Servo para trás
    analogWrite(LPWM, 0);
    analogWrite(RPWM, 255); // Velocidade máxima para trás
    delay(500);
}

void moveLeft() {
    myServo.write(0); // Servo para esquerda
    analogWrite(LPWM, 100); // Velocidade reduzida
    analogWrite(RPWM, 0);
    delay(500);
}

void moveRight() {
    myServo.write(180); // Servo para direita
    analogWrite(LPWM, 0);
    analogWrite(RPWM, 100); // Velocidade reduzida
    delay(500);
}

void stopMotor() {
    analogWrite(LPWM, 0);
    analogWrite(RPWM, 0);
}

// Função para enviar comando de acoplamento
void enviarComandoAcoplar(bool acoplarStatus) {
    myData.acoplarStatus = acoplarStatus;
    // Código para enviar via ESP-NOW (se necessário)
}
