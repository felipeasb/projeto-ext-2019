# projeto-ext-2019
Projeto de extensão com a proposta de prototipar um dispositivo móvel para monitoramento de eficiência energética em ambientes internos.
Participação do aluno Felipe Barbosa (eu), do curso de Engenharia Eletrônica do CEFET/RJ.
![712d6885-43bf-4add-aaf8-664487f5dfad](https://user-images.githubusercontent.com/79610980/190223191-e033cf29-9732-4378-be6d-8b0730c5001d.jpg)
O projeto de extensão foi desenvolvido com auxílio do Departamento de Tecnologia da Informação do CEFET/RJ. O objetivo principal era programar um Node MCU com ESP8266 para que fizesse o monitoramento de algumas variáveis presentes em um ambiente escolhido dentro da instituição.


Escolheu-se trabalhar com a IDE do Arduino devido ao suporte para o ESP8266, então a programação foi toda feita em C/C++. Os sensores utilizados para testar o projeto foram de umidade e temperatura, presença e luminosidade.


Para consolidar o caráter móvel do dispositivo, explorou-se a possibilidade de conexão WiFi presente no Node MCU junto ao protocolo MQTT para fazer a comunicação entre a placa e um smartphone. Desta forma, o Node transmitia os dados coletados para um broker MQTT e o smartphone acessava essas informações através de um aplicativo.

![5d5fa277-dd2f-491d-9f4a-2e3bedc61b67](https://user-images.githubusercontent.com/79610980/190234904-dd2b8d04-0295-4ea3-9b9b-46af78496275.jpg)

![f390b54f-af72-43e9-9d94-9fcdc7884941](https://user-images.githubusercontent.com/79610980/190234948-c1558add-6d89-4f88-9333-da580aaf784a.jpg)

![b855b944-2164-4f4d-bf61-c895bd8506c8](https://user-images.githubusercontent.com/79610980/190235103-efaeae8d-bee2-4230-8506-7147a1b94c07.jpg)
