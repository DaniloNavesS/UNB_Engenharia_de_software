# Classificações de Sistemas Operacionais

## Podem ser classificados em três categorias

- Sistema Monoprogramáveis / Monotarefa
- Sistemas Multiprogramáveis / Multitarefa
- Sistemas com Múltiplos Processadores

## Sistemas Monoprogramáveis

- Sistemas voltados à execução de um único programa
- Processadir, memória, periféricos, permanecem dedicados à um único programa.

Ex: MS-DOS da Microsoft

## Sistemas multiprogramáveis

- Os recursos multiprogramáveis permitem que os recursos computacionais permitem que os recursos computacionais sejam compartilhados entre os diversos usuários e aplicações.

- Enquanto um programa espera um evento, outros podem utilizar o processamento.

- O sistema operacional é responsável por gerenciar acessos concorrentes aos mesmos recursos.

- Redução no tempo de resposta

Ex: Sistema Batch, Sistema de tempo compartilhado, Sistemas de tempo real.

### Sistema Batch

- Inspirados nos cartões perfuradados e fitas magnéticas.

- Não exige interação do usuário com a aplicação.

- As aplicações são organizadas e processadas em lote.

### Sistemas de tempo compartilhado

- Os sistemas de tempo compartilhado permitem que diferentes programas sejam executados a partir da divisão de tempo do processador em pequenas fatias de tempo (time-slice)

- Diversas mudanças são necessárias para permitir esse comportamento.

Ex: Windows 98, Linux 2.4

### Sistema em tempo real

- Semelhante ao tempo compartilhado, porém o tempo real exige a aplicações rígidos de limite de tempo a ser cumprido.

- Subclassificado em tempo real crítico: Caso ocorra = grandes prejuízos.

Ex: Controle de tráfego aéreo, controle de indústria automobilística.

## Sistemas com múltiplos processadores

- Possuem dois ou mais processadores interligados e
trabalhando em conjunto

- Permite que um programa seja executado mais
rapidamente (se o programa for multithreaded)

- Herdaram vários fundamentos do time-sliced

Ex: Windows XP e posteriores, Linux 2.6 e posteriores

Ex de classicação de múltiplos processadores: Sistemas operacionais de computadores pessoais, Sistemas operacionais de servidores, Sistemas operacionais embarcados

### Computadores Pessoais

- Utilizado apenas por um único usuário

- Computadores domésticos

EX: Windows 10, ArchLinux, Debian

### Sistema Operacionais de Servidores

- Sistemas cujo objetivo é servir o maior número
de usuários ao mesmo tempo

- Pode incluir diferentes tipos de serviços:
servidor web, e-mail, servidor de autenticação,
servidor de backup, etc.

Ex: Ubuntu Server, Cent OS

### Sistema Operacionais Embarcados

- Sistemas operacionais que funcionam em
equipamentos que não aparentam ser um computador:
micro-ondas, TV, celulares e smartphones

EX: Android, IOS

