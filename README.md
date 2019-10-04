# Stream in Middleware

The evolution of the development of the Drones has given rise to some challenges, one of which is related to the distributed environment of the application support. This article presents a distributed architecture to support the construction of systems Drones based.

## Visão Geral do Stream in Middleware

O Middleware de Comunicação em Tempo Real (MCTR) é uma ferramenta criada para facilitar o desenvolvimento de aplicações que tenham como base a transmissão de imagens entre dois dispositivos. Seu funcionamento é similar ao de um sistema operacional, onde o serviço é solicitado por meio de “chamadas de sistemas”. Quando solicitado, o MCTR executa a ação desejada e retorna seu status. Ele contém dois níveis lógicos: nível usuário e nível de sistema. O
primeiro é usado para realizar solicitações de serviço ao MCTR . No Nível sistema, onde são, de fato, executadas as ações solicitadas pelo usuário. O MCTR tem as seguintes funcionalidades: tirar uma foto, tirar fotos periódicas, mostrar imagem da câmera em tempo real e gravar vídeo. O sistema roda em Linux e foi inteiramente escrito em linguagem C/C++. A comunicação entre os dispositivos ocorre via uma rede wireless e foi implementada com o uso de sockets. Com o intuito de facilitar a manipulação de imagens e a conexão com a câmera, foi usado a ferramenta “OpenCV”. 

O sistema desenvolvido é baseado no modelo cliente/servidor. O servidor executa em um Laptop com sistema operacional Linux, que é a base na terra. O cliente roda em um Raspberry embarcado no VANT, que possui uma câmera acoplada, O sistema operacional usado no Raspberry é o Raspbian, uma distribuição Linux criada para rodar no Raspberry Pi.

### Requisitos
* Opencv
* QT

### Instalação
* Opencv
  * Você pode fazer a instalação pelo script que se encontra na pasta outros
    ```
    bash Outros/install_opencv.sh
    ```
* QT
    * Siga as instruções do site [QT](https://www.qt.io/download)
    
### Iniciando
 * Cliente
 
 ```
 make clean
 
 make
 
 ./Executable/mctr_client.exe
 
 ```
 * Servidor
 > Execudado pelo QT na pasta /ProgInterface/Interface
 
 ### Observaçãos
 #### Se for Utilizar com a RaspCan.
 > Comente a linha 27 do arquivo /System/invoke.hpp
 
 > Descomente a linha 30 do arquivo /System/invoke.hpp
 
 > Ponha "$(FLAGOPENCV)" nas linhas 12,15,18 do "makefile" se nao existir
 #### Se for Utilizar com uma WebCan
 
 > Comente a linha 30 do arquivo /System/invoke.hpp
 
 > Descomente a linha 27 do arquivo /System/invoke.hpp
 
 > Tire "$(FLAGOPENCV)" nas linhas 12,15,18 do "makefile"
 
