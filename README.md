# Conexão NodeMCU com a Plataforma da IBM CLOUD

O objetivo do projeto é conectar um dispositivo NodeMCU com a plataforma de internet das coisas disponibilizada pela IBM. Um sensor de temperatura e umidade, DHT11, será responsável por enviar dados para a aplicação A construção do código e o upload do mesmo foi realizado através da extensão da PlatformIO, utilizando o VSCode. Abaixo se encontram as etapas realizadas para concluir o projeto.

## Etapa 1: Criação da Aplicação em Node-RED

A aplicação em Node-RED será responsável por fazer a comunição do dispositivo que será criado na plataforma da IBM com o NodeMCU.

Dois módulos adicionais foram instalados para fazer a conexão da aplicação com o dispositivo:

    node-red-contrib-ibm-watson-iot: Utilizada para conexão com o Quickstart
    node-red-contrib-scx-ibmiotapp: Utilizada para conexão com o dispositivo registrado

A comunicação é realizada através de mensagens JSON, portanto, pode-se facilmente testar a conexão da aplicação com o Quickstart enviando um JSON de temperatura e verificando se o resultado pode ser observado.

    {
        "d": {
            "temperatura": 23.0
        }
    }

Colocando o node de injeção para repetir essa mensagem em intervalos, percebe-se que os dados estão chegando normalmente na plataforma.

O próximo passo é criar um dispositivo na Plataforma de Internet das Coisas para receber os dados que serão enviados pelo NodeMCU.
## Etapa 2: Criação do Serviço na Plataforma de Internet das Coisas da IBM

Após seguir as etapas para a criação um dispositivo, e a criação de uma aplicação para a autenticação
## Etapa 3: Implementação e Upload do Código no NodeMCU
## Etapa 4: Testes na Aplicação e no Quickstarter da IBM
