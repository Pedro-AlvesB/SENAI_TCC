# TCC-SENAI-Programming-C
Este projeto consiste em uma comunicação de 2 microcontroladores via ESPnow Mestre e Servo 
CÓDIGO:
*Este projeto integra dois microcontroladores por meio da biblioteca de comunicação ESPnow para que o Mestre tome controle do Servo, onde o código Mentre envia comandos para o Servo conectar e seus movimentos para que o servo o repita*

# PROJETO "MGZRD"

## Dupla de robôs AGV acopláveis controlados remotamente

**Escola e Faculdade de Tecnologia SENAI Anchieta**\
**Curso Técnico em Mecatrônica**

**Autores:**\
- Kauã Neves Souza\
- Kevin Martins Devasio\
- Lucas Beck Cândido\
- Miguel Silva Souza\
- Pedro Alves Barreto\
- Pedro de Almeida Crocceli

**Orientador:** Professor Kléber do Nascimento\
**Ano:** 2024\
**Local:** São Paulo

------------------------------------------------------------------------

# Resumo

Este documento apresenta todas as etapas do desenvolvimento do Trabalho
de Conclusão de Curso (TCC), desde a projeção e planejamento até a
execução e conclusão.

O projeto consiste em dois robôs AGVs simples controlados remotamente
por aplicativo de telefone celular.

O robô Mestre possui eletroímãs em suas faces. O robô Servo possui
chapas metálicas correspondentes.

A principal inovação é a capacidade de acoplagem, permitindo que ambos
operem como uma única unidade, transportando cargas maiores.

Os robôs são alimentados por um banco de baterias de 24V responsável por
alimentar o microcontrolador ESP-32, circuito de acionamento dos
eletroímãs, motores DC e servo, sensores Hall e botões de emergência.

Palavras-chave: robôs AGVs, acoplagem, ESP-32

------------------------------------------------------------------------

# Abstract

This document presents all development stages of the Course Completion
Project.

The project consists of two AGV robots remotely controlled via a mobile
application.

The master robot has electromagnets, while the slave robot has metal
plates.

The differential is the ability to couple both robots and operate as a
single unit.

They are powered by a 24V battery bank supplying ESP-32 microcontroller,
electromagnets, DC and servo motors, hall sensors and emergency buttons.

Keywords: AGV robots, coupling, ESP-32

------------------------------------------------------------------------

# 1. Introdução

## 1.1 Justificativa

Os processos logísticos industriais vêm se modernizando. A demanda por
entregas rápidas e eficiência exige soluções automatizadas. O projeto
MGZRD propõe uma ferramenta capaz de auxiliar na automação logística com
maior versatilidade.

## 1.2 Objetivo Geral

Desenvolver dois robôs AGV controlados via Bluetooth com capacidade de
acoplamento magnético.

Capacidade de carga: - 10 kg individualmente - 20 kg acoplados

Integração das áreas: - Mecânica - Eletrônica - Programação - IoT

------------------------------------------------------------------------

# 2. Desenvolvimento

## 2.1 Lógica de Programação

Desenvolvida na Arduino IDE utilizando bibliotecas: - ESP32Servo -
BluetoothSerial - WiFi - ESP-NOW

Estrutura utilizada:

``` cpp
struct struct_message {
  int motorSpeed;
  int servoAngle;
  bool acoplarStatus;
};
```

O mestre envia comandos ao servo via ESP-NOW garantindo sincronização em
tempo real.

------------------------------------------------------------------------

## 2.2 Eletrônica

Componentes principais: - ESP32 - Ponte H BTS7960 - 4 Eletroímãs -
Reguladores LM2596 - Motor DC RS775 - Servo Motor - Módulo de Relés -
Sensores Hall - Bateria 12V 8A - Botão de emergência

Circuito desenvolvido na plataforma EasyEDA.

------------------------------------------------------------------------

## 2.3 Mecânica

Estrutura composta por: - Cantoneiras de aço - Barras roscadas - Chapas
MDF - Rodízios - Chapa acrílica superior

Peças impressas em 3D: - Suportes - Caixa de engrenagens - Engrenagens
(relação 124:1)

------------------------------------------------------------------------

## 2.4 Gestão e Monitoramento

Ferramentas utilizadas: - Ciclo PDCA - Diagrama de blocos - Gráfico de
Gantt

------------------------------------------------------------------------

## 2.5 Custos Totais

Total Geral do Projeto: **R\$ 962,69**

------------------------------------------------------------------------

# 3. Conclusão

Apesar das dificuldades técnicas e de planejamento, o grupo concluiu com
sucesso dois robôs AGVs funcionais com operação independente e acoplada,
desenvolvendo competências técnicas e interpessoais essenciais.

------------------------------------------------------------------------

# 4. Referências

-   Arduino Documentation
-   Espressif ESP-NOW Documentation
-   Autodesk Spur Gear Generator
-   KIVNON AGV Guide
-   MECALUX AGV Article
-   NBR 6023:2018

------------------------------------------------------------------------

# 5. Anexo 1

Gráfico de Gantt

------------------------------------------------------------------------

# 6. Anexo 2

Esquema elétrico do robô mestre

