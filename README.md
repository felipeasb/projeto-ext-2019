# projeto-ext-2019
Código de um dispositivo móvel para monitoramento de eficiência energética em ambientes internos
![712d6885-43bf-4add-aaf8-664487f5dfad](https://user-images.githubusercontent.com/79610980/190223191-e033cf29-9732-4378-be6d-8b0730c5001d.jpg)
O projeto de extensão foi desenvolvido com auxílio do Departamento de Tecnologia da Informação do CEFET/RJ. O objetivo principal era programar um Node MCU com ESP8266 para que fizesse o monitoramento de algumas variáveis presentes em um ambiente escolhido dentro da instituição.


Escolheu-se trabalhar com a IDE do Arduino devido ao suporte para o ESP8266, então a programação foi toda feita em C/C++. Os sensores utilizados para testar o projeto foram de umidade e temperatura, presença e luminosidade.


Para consolidar o caráter móvel do dispositivo, explorou-se a possibilidade de conexão WiFi presente no Node MCU junto ao protocolo MQTT para fazer a comunicação entre a placa e um smartphone. Desta forma, o Node transmitia os dados coletados para um broker MQTT e o smartphone acessava essas informações através de um aplicativo. 
