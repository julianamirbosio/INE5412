======================================================
 Simulador de Escalonamento de CPU - Base para Trabalho de SO
======================================================

Este repositório contém a estrutura base para o desenvolvimento de um trabalho sobre algoritmos de escalonamento de CPU. O objetivo é que você, aluno, implemente seus próprios algoritmos de escalonamento sem se preocupar com a infraestrutura de simulação, leitura de arquivos ou cálculo de métricas.


## Estrutura do Projeto ##

O simulador está organizado em classes, cada uma com uma responsabilidade clara:

* Process: Representa um processo a ser escalonado. Contém atributos como ID, tempo de chegada, tempo de burst (execução) e prioridade.

* CPU: Simula uma CPU simples, gerenciando a troca de contexto entre processos.

* Scheduler: Orquestra a simulação. Ele é responsável por associar um algoritmo aos processos e executar a simulação passo a passo.

* SchedulingAlgorithm: É a classe base ABSTRATA da qual o seu algoritmo DEVE herdar. Ela fornece toda a infraestrutura necessária para a simulação.


## O Arquivo de Entrada: entrada.txt ##

Os processos que serão simulados são lidos do arquivo `entrada.txt`. Cada linha representa um processo e segue o formato:

[Tempo de Chegada] [Tempo de Burst] [Prioridade]

Exemplo:

0 5 2

0 2 3

Isto define dois processos:
1. Um que chega no tempo 0, precisa de 5 unidades de tempo para executar e tem prioridade 2.
2. Outro que chega no tempo 0, precisa de 2 unidades de tempo e tem prioridade 3.


## Sua Tarefa: Implementar um Algoritmo de Escalonamento ##

Sua tarefa é criar uma nova classe que herde de `SchedulingAlgorithm` e implemente dois métodos principais:

1. sortReadyProcesses(std::vector<Process*>& readyProcesses): Esta função recebe uma lista de processos que já chegaram e estão prontos para executar. Sua lógica deve ordenar essa lista ou simplesmente selecionar e retornar o próximo processo a ser executado, de acordo com o critério do seu algoritmo (menor tempo de burst, maior prioridade, etc.).

2. simulate(): Esta é a função principal que contém o loop da simulação. Você deve usar as funções de suporte da classe base para controlar o tempo, atualizar a fila de prontos, selecionar o próximo processo e executar o "burst" de tempo.


### Passo a Passo para a Implementação ###

1. Crie seu Diretório e Arquivos:
   - Na raiz do projeto, crie um novo diretório com o nome do seu algoritmo (ex: MySJF).
   - Dentro deste diretório, crie dois arquivos: um de cabeçalho (ex: `MySJF.h`) e um de implementação (ex: `MySJF.cc`).

2. Implemente sua Classe de Algoritmo:
   - No arquivo `.h`: Defina sua classe, certificando-se de que ela herda publicamente de `SchedulingAlgorithm` e declara os métodos `simulate()` e `sortReadyProcesses()` com a palavra-chave `override`.
   - No arquivo `.cc`: Implemente a lógica dos métodos declarados no `.h`.

3. Atualize o `makefile`:
   - Abra o arquivo `makefile`.
   - Adicione o caminho para o seu novo diretório de algoritmo na variável `CFLAGS`.
   - Adicione o caminho para o seu novo arquivo `.cc` na variável `SRC_FILES`.

   Exemplo de modificação no `makefile`:
   # ...
   CFLAGS = -Wall -std=c++11 -IReadFile -IScheduler -IProcess -ISchedulingAlgorithm -ICPU -IFCFS -ISJF -IPNP -IPP -IRoundRobin
   # ...
   SRC_FILES = Scheduler/Scheduler.cc Process/Process.cc CPU/CPU.cc FCFS/FCFS.cc SJF/SJF.cc PNP/PNP.cc PP/PP.cc RoundRobin/RoundRobin.cc read_file.cc
   # ...

4. Configure a Simulação em `read_file.cc`:
   - Abra o arquivo `read_file.cc`.
   - Inclua os arquivos de cabeçalho dos seus algoritmos, ex.: 
      #include "MySJF.h"

   - Na função `main`, instancie a sua classe de algoritmo e passe-a para o `Scheduler`, ex.:
      //======================================
     
      // PP Scheduling Algorithm
     
      //======================================
   
      // Setup scheduler with PP algorithm
     
      PP ppAlgorithm;
     
      scheduler.setAlgorithm(&ppAlgorithm);

      // Add processes to scheduler
     
      for(auto process : processes) {
         scheduler.addProcess(process);
      }

      // Run the scheduling simulation for PP
     
      scheduler.simulate();
      scheduler.resetProcesses(processes); 

5. Compile e Execute:
   - No terminal do WSL, navegue até a pasta do projeto.
   - Limpe compilações antigas: `make clean`
   - Compile seu projeto: `make`
   - Execute a simulação: `./main`

