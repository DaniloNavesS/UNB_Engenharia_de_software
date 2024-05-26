# Processos

## Definição

- Um processo é um programa em execução acompanhando de valores de tempo de execução

- O processo deve ser visto como uma unidade de contexto, ou seja, um contêiner de recursos utilizados por uma ou mais tarefas para sua execução: áreas de memória (código, dados, pilha), informações de contexto e descritores de recursos
do núcleo (arquivos abertos, conexões de rede, etc).

![Processo na maquina](./img/processos/processos.png)

## Elementos de um processo

- Código executável
- Pilha de execução: contendo valores de variáveis locais
- Apontador para pilha: registrador da CPU que
armazena em qual área de memória está a pilha
- Contador de programa: registrador da CPU que
armazena a próxima instrução a ser executada
- Valores dos registradores gerais da máquina

## Classificação dos modelos

 - Processos quanto ao custo de troca de contexto e de manutenção

- Heavyweight(Processo tradicional)
- Lightweight(threads)

## Heavyweight

- O processo é composto tanto pelo ambiente como pela a execução

Os processos são criados:

- Início do sistema
- Execução de uma chamada ao sistema de criação de processo por um processo em execução
- Requisição do usuário
- Início de um job de lote

## Inicializar do SO

- Alguns executam em primeiro plano e interagem
com usuários

- Outros executam em segundo plano: chamados
de daemons

Daemons: é um processo em segundo plano que executa tarefas específicas de forma autônoma e contínua, sem a necessidade de interação direta com o usuário.

- Geralmente os processos são criados por outro

Hierarquia em árvore:

![Hierarquia em árvore](img/processos/processos_arvores.png)

## Criação de processo no Unix

```
fork();
```

![Fork](/img/processos/processo_fork.png)

- Clone idêntico ao processo que chamou
- Normalmente, executa execve depois da chamada para mudar o "programa" em execução

## Condições de término de processos:

- Saída normal (voluntária)
- Saída por erro (voluntária)
- Erro fatal (involuntário)
- Cancelamento por outro processo (involuntário)

## Hierarquia de processos

- Quando um processo é criado por outro, eles continuam assoaciados.
- Em alguns sistemas, é possivel listar o ppid (parent pid)
- Todos os processos são filhos ou descendentes dos processos init.

## Estados dos processos

Estados de um processo: Rodando, Bloqueado, Pronto

- Quando o processo está esperando um evento, dizemos que ele está bloqueado:

Leitura em disco -> Leitura de rede -> Esperando entrada de usuário

Representação de estados de um processo

![Estados](/img/processos/processo_estados.png)

(1) O processo bloqueia-se aguardando uma entrada

(2) O evento aguardado pelo processo ocorreu, pode-se iniciar a executar.

(3) O tempo de posse do processador esgotou-se

(4) O processo é escolhido pelo escalonador para executar

## CPU Bound e I/O Bound

- CPU Bound: são tarefas que usam intensivamente o processador na maior parte de sua existência. Essas tarefas passam a maior parte do tempo nos estados pronta ou executando.

- I/O Bound: São tarefas que dependem muito mais dos dispositivos de entrada/saída que do processador. Essas tarefas ficam boa parte de suas existências no estado suspenso, aguardando respostas às suas solicitações de leitura e/ou escrita de dados nos dispositivos de entrada/saída.

## Implementação de processos

### Troca de contexto: 

- Operação de salvamento dos registradores de um processo e posterior restauração de registradores de outro processo.

- A troca de contexto permite a troca de processador entre os processos

- Cada dispositivo de E/S possui possui uma área
de memória chamada vetor de interrupções

#### Diagrama temporal 

Principais passos envolvidos em uma troca de contexto:

1. Uma tarefa A está executando;
2. Ocorre uma interrupção do temporizador do hardware e a execução desvia para
a rotina de tratamento, no núcleo;
3. A rotina de tratamento ativa o despachante;
4. O despachante salva o estado da tarefa A em seu TCB e atualiza suas informações
de gerência;
5. Opcionalmente, o despachante consulta o escalonador para escolher a próxima
tarefa a ativar (B);
6. O despachante resgata o estado da tarefa B de seu TCB e a reativa.

![Diagrama Troca de contexto](/img/processos/processo_diagrama.png)

## Escalonador de Processos

- O Sistema Operacional é responsável por gerenciar o(s) recurso(s) de processamento de um computador por meio de sua atividade chamada <strong>Escalonador de Processador</strong>

- Os escalonadores podem ser classificados como Preemptivos ou Cooperativo(Não-Preemptivos).

A preempção é a suspensão temporária da execução de um processo.

### Sistemas preemptivos:

- Nestes sistemas uma tarefa pode perder o processador caso termine seu quantum de tempo, caso execute uma chamada de sistema ou caso ocorra uma interrupção que acorde uma tarefa mais prioritária (que estava suspensa aguardando um evento). A cada interrupção, exceção ou chamada de sistema, o escalonador reavalia todas as tarefas da fila de prontas e decide se mantém ou substitui a tarefa atualmente em execução.

- Cada Processo tem seu tempo(time-slice) de posse do processador

- O controle de tempo de execução é feito por interrupção

### Sistemas cooperativos:

- A tarefa em execução permanece no processador tanto quanto possível, só liberando o mesmo caso termine de executar, solicite uma operação de entrada/saída ou libere explicitamente o processador1, voltando à fila de tarefas prontas. Esses sistemas são chamados de cooperativos por exigir a cooperação das tarefas entre si na gestão do processador, para que todas possam executar.

- Nenhuma entidade externa “tira a CPU à força”
do processo

### Critérios do Escalonador

- Justiça: garantir que todos os processos terão
chances justas de uso de processador.

- Eficiência: quando existir trabalho a fazer, o
processador deve estar ocupado.

- Minimizar o tempo de resposta: reduzindo o
tempo dos usuários interativos, reduz o tempo entre
a entrada de usuário e a resposta dada (não
considera tempo total de execução).

- Minimizar o turnaround: reduzir o tempo desde
o lançamento do processo até seu término. Soma de:
tempo de espera por recursos (memória,
processador, E/S) e tempo de utilização da CPU.
Mais utilizado em processamento batch.

- Minimizar waiting time: Esse critério visa
minimizar o tempo de espera pela CPU

- Maximizar throughtput: Maximizar o
número de tarefas executados em uma unidade
de tempo

## Algoritimos clássicos de escalonamento

Sendo eles: First Come First Served, Round-Robin, Prioridades, Shorteste Job First

### First Come First Served(FCFS)

- O processo obtém a CPU de acordo com a ordem da chegada das solicitações. o processo que pede a CPU primeiro, obtém a CPU em primeiro lugar

![First Come First Served](/img/processos/fcfs.png)

- O escalonador FCFS é <strong>Não-preemptivo</strong>

- Um processo CPU/bound pode fazer com que vários processos esperem por um tempo indeterminado.

#### Vantagens

- Simples de ser implementado
- Algoritmo efieciente: CPU sempre é utilizada

#### Desvantagens

- Impossibilidade de se prever quando um processo vai iniciar
- Tempo de espera não é priorizado

### Round-Robin

- Cada processo tem o direito de usar o processador por um intervalo de tempo pré-definido. Este intervalo de tempo é denominado quantum

![Round-Robin](/img/processos/round_robin.png)

- Algoritmo por alternância circular

![Round-Robin fila](/img/processos/round_fila.png)

- Algoritmo justo

- Dificuldade de determinar bom quantum para ser atribuído;

- Sendo assim, Quantum muito longo: FCFS e Quantum muito curto: perda de vários requisitos, tais como eficiência.

- Para o algoritmo ser eficiente é necessário que o tempo de troca de contexto seja consideravelmente menor que a execução do programa

### Escalonamento com prioridades

- Cada processo é atribuída uma prioridade. Processos com prioridade maior rodam primeiro

- Prioridades podem ser atribuídas de duas
formas: estática ou dinâmica

#### Estática

- Os processos são divididos em classes e a cada classe é atribuída uma prioridade. A cada prioridade existe uma fila de prontos associada

![Prioridade Fixa](/img/processos/prioridade_fixa.png)

#### Dinâmica 

- O sistema analisa o comportamento dos processos e atribui prioridades favorecendo um certo tipo de comportamento

- Processos I/O devem possuir prioridade alta
- Prioridade dinâmica: 1/f, onde f é a fração do
quantum de tempo usada na última rodada do
processo

### Shortest Job First

- Dado um conjunto de processos, execute os de menor tempo de execução antes.

![Shortest Job First](/img/processos/first_job.png)

#### Vantagens

- Projetado para sistemas em lotes
- Diminui o tempo de turnaround(tempo de
lançamento do processo até seu término)

#### Desvatagens

- Requer que o tempo total de execução do
processo seja conhecido antes do seu início

## Threads

### Definição:

- Uma thread é definida como sendo um fluxo de execução independente. Um processo pode conter uma ou mais threads, cada uma executando seu próprio código e compartilhando recursos com as demais threads localizadas no mesmo processo.













