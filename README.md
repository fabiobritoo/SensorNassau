# Conexão NodeMCU com a Plataforma da IBM CLOUD

O objetivo do projeto é conectar um dispositivo NodeMCU com a plataforma de internet das coisas disponibilizada pela IBM. Um sensor de temperatura e umidade, DHT11, será responsável por enviar dados para a aplicação A construção do código e o upload do mesmo foi realizado através da extensão da PlatformIO, utilizando o VSCode. Abaixo se encontram as etapas realizadas para concluir o projeto.

## Etapa 1: Criação da Aplicação em Node-RED

A aplicação em Node-RED será responsável por fazer a comunição do dispositivo que será criado na plataforma da IBM com o NodeMCU.

Dois módulos adicionais foram instalados para fazer a conexão da aplicação com o dispositivo:

    node-red-contrib-ibm-watson-iot: Utilizado para conexão com o Quickstart
    node-red-contrib-scx-ibmiotapp: Utilizado para conexão com o dispositivo registrado

A comunicação é realizada através de mensagens JSON, portanto, pode-se facilmente testar a conexão da aplicação com o Quickstart enviando um JSON de temperatura e verificar o resultado.

    {
        "d": {
            "temperatura": 23.0
        }
    }

Colocando o node de injeção para repetir essa mensagem em intervalos, percebe-se que os dados chegam normalmente na plataforma.

O próximo passo é criar um dispositivo na Plataforma de Internet das Coisas para receber os dados que serão enviados pelo NodeMCU.
## Etapa 2: Criação do Serviço na Plataforma de Internet das Coisas da IBM

Após seguir as etapas para a criação um dispositivo e a criação de uma aplicação para a autenticação deste dispositivo, já se tem agora todos os dados necessários para enviar e receber informações.

    Dispositivo

    Organization ID		        bfzzmh
    Device Type	            	sensortemp
    Device ID                       D1
    Authentication Method	        use-token-auth
    Authentication Token	        1z+H*A2hTbaykh1NHh

    API

    API Key		            	a-bfzzmh-5v9rsqqer2
    Authentication Token    	fmpfj)cBX8RA&TKhew

Algumas informações importantes para a realização da comunicação através do protocolo MQTT:

    Client Id =     a:{Organization ID}:{Device ID}
    Username =      {API Key}
    Password =      {API Authentication Token}
    Host =          {OrgID}.messaging.internetofthings.ibmcloud.com
    Tópico =        iot-2/type/{DeviceType}/id/{DeviceID}/evt/1-anl/fmt/json


Para o caso desta aplicação específica:

    Client Id =     a:bfzzmh:D1
    Username =      a-bfzzmh-5v9rsqqer2
    Password =      fmpfj)cBX8RA&TKhew
    Host =          bfzzmh.messaging.internetofthings.ibmcloud.com
    Tópico =        iot-2/type/sensortemp/id/D1/evt/1-anl/fmt/json

Usando estes valores, pode-se usar uma plataforma como o MQTTBox para testar o envio de informações para o tópico.
## Etapa 3: Implementação e Upload do Código no NodeMCU

Com o dispositivo criado e devidamente testado, o código foi desenvolvido com a extensão da PlatformIO do Visual Studio, usando a biclioteca <PubSubClient.h> para o envio de mensagens para o tópico criado.
## Etapa 4: Testes na Aplicação e no Quickstarter da IBM
