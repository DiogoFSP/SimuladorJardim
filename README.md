# Simulador de Jardim

Simulador de um jardim em linha de comandos, escrito em C++ para a cadeira de
**Programação Orientada a Objetos** (LEI · DEIS · ISEC · IPC, 2025/2026).

Trabalho de grupo de **[Diogo Pinto](https://github.com/DiogoFSP)** e
**[Rafael Marques](https://github.com/Rafael-Marques-960)**.

O jardim é uma grelha retangular (máximo 26×26) onde cada posição tem solo com
água e nutrientes próprios, e pode conter uma planta e/ou uma ferramenta. O
utilizador é o jardineiro (`*`), move-se pela grelha, planta, colhe e usa
ferramentas. O tempo não corre sozinho: avança em **instantes**, por ordem do
utilizador, e é nesses instantes que as plantas absorvem, crescem, multiplicam-se
ou morrem.

```
   ABCDEFGHIJ
 A ..c.......
 B ...*r.....
 C ..e....g..
 D .....x....
```

## Restrição central

O enunciado proíbe o uso de qualquer coleção da biblioteca padrão na
implementação da área do jardim — sem `std::vector`, sem vetores de vetores. A
grelha é por isso uma matriz alocada à mão (`Solo** solos`): um array de
apontadores para linhas, cada um a apontar para um array de colunas, com a
libertação de memória feita explicitamente no destrutor.

A mesma regra se aplica ao registo de comandos: o `GestorCmd` guarda os comandos
num `Comando**` que cresce por realocação manual.

## Arquitetura

O código está dividido em três responsabilidades:

| Camada | Classes | Papel |
| --- | --- | --- |
| Interpretação | `GestorCmd`, `Comando` e derivadas | Lê a linha, parte em segmentos, encontra o comando e delega-lhe a validação |
| Ambiente | `Jardim`, `Solo`, `Backup` | Aloca e gere a grelha, a prioridade visual e as cópias de segurança |
| Entidades | `Planta`, `Ferramenta`, `Jardineiro` | Hierarquias polimórficas com o comportamento de cada espécie e de cada ferramenta |

**Padrão de Comando.** Cada comando é uma classe própria (`CmdPlanta`,
`CmdAvanca`, `CmdCompra`, …) registada no `GestorCmd`. A validação de sintaxe e
de parâmetros não está centralizada: vive dentro do comando a que diz respeito,
o que torna o conjunto extensível sem tocar no interpretador.

**Ownership.** A posição de solo é dona da planta e da ferramenta que contém e
liberta-as no seu destrutor. O jardineiro é gerido pela classe `Jardim` — o solo
guarda apenas uma referência, para não haver dupla libertação.

**Prioridade visual.** Quando várias entidades partilham a mesma posição, o
`Solo::getSimbolo()` decide o que aparece, pela ordem jardineiro → planta →
ferramenta.

## Plantas

Todas as plantas têm reserva interna de água e nutrientes, absorvem do solo onde
estão e têm um atributo de beleza. Os valores concretos vivem todos em
`Settings/Settings.h`.

| Símbolo | Espécie | Comportamento |
| --- | --- | --- |
| `c` | Cacto | Absorve 25% da água da posição e até 5U de nutrientes por instante; morre com água a mais ou nutrientes a zero durante 3 instantes seguidos; ao morrer devolve ao solo os nutrientes acumulados |
| `r` | Roseira | Perde 4U de cada por instante e absorve 5U de água e 8U de nutrientes do solo; morre por fome, por excesso de nutrientes ou por ficar sem vizinhos livres |
| `e` | Erva-daninha | Começa com 5U/5U, absorve 1U de cada por instante, morre sozinha aos 60 instantes e propaga-se por cima da planta vizinha |
| `x` | Sentinela | A planta exótica do grupo |

### A planta exótica: Sentinela

Cada grupo define a sua própria espécie exótica. A nossa é a **Sentinela**: uma
planta que se alimenta como as outras, mas conta abates — só se multiplica depois
de ter matado duas ervas-daninhas, gastando 50U de nutrientes para o fazer. É a
contramedida natural à erva-daninha, que de outra forma toma o jardim inteiro.

## Ferramentas

Aparecem no jardim (três, em posições aleatórias) ou compram-se com o comando
`compra`. São apanhadas automaticamente ao passar por cima, têm número de série e
atuam sozinhas, a cada instante, na posição onde o jardineiro está — desde que
estejam na mão dele.

| Símbolo | Ferramenta | Efeito | Capacidade |
| --- | --- | --- | --- |
| `g` | Regador | +10U de água no solo | 200U |
| `a` | Pacote de adubo | +10U de nutrientes no solo | 100U |
| `t` | Tesoura de poda | Elimina plantas feias na posição | Sem desgaste |
| `z` | Enxada rotativa | A ferramenta Z do grupo | 10 cargas |

### A ferramenta Z: Enxada rotativa

Ferramenta de gestão de solo para terrenos alagados. Se a água da posição passar
das 120U, retira 20U de água e converte-as em 10U de nutrientes. Serve para
recuperar posições encharcadas depois de excesso de rega — e gasta uma das dez
cargas de cada vez que atua.

## Comandos

```
jardim <l> <c>        cria a grelha (só pode ser usado uma vez)
avanca [n]            avança n instantes (1 por omissão)
ajuda                 lista os comandos disponíveis
fim                   liberta os recursos e sai

entra <lc>            entra no jardim, ou teletransporta-se
sai                   sai do jardim
c / b / e / d         move cima / baixo / esquerda / direita
planta <lc> <tipo>    planta c, r, e ou x
colhe <lc>            remove a planta da posição
compra <tipo>         compra a ferramenta g, a, t ou z
pega <sn>             põe na mão a ferramenta com aquele número de série
larga                 guarda a ferramenta da mão na mochila

larea                 conteúdo e propriedades das posições não vazias
lplantas              todas as plantas, com estado interno e estado do solo
lplanta <lc>          detalhes da planta naquela posição
lsolo <lc> [n]        detalhes do solo, opcionalmente num quadrado de raio n
lferr                 ferramentas na mochila e na mão

grava <nome>          guarda uma cópia do jardim em memória
recupera <nome>       repõe a cópia guardada
apaga <nome>          elimina a cópia
executa <ficheiro>    lê e executa comandos de um ficheiro, um por linha
```

As posições escrevem-se como duas letras — linha e coluna. `CE` é a linha 3,
coluna 5. Entre instantes o jardineiro tem limites: 10 movimentos, 5 colheitas,
2 plantações, 1 entrada e 1 saída.

## Compilar e correr

Projeto CLion / CMake, C++20:

```bash
cd Projeto
cmake -B build
cmake --build build
./build/Projeto
```

O ficheiro `Projeto/teste.txt` serve de guião para o comando `executa`.

## Estado

Meta 1 entregue. O `Relatorio-POO-Meta1.pdf` neste repositório descreve as
opções de estrutura de dados e a arquitetura de classes. Para lá do que a meta 1
exigia (leitura e validação de comandos, planeamento das classes, organização em
`.h`/`.cpp`), já estão a funcionar a criação do jardim, o movimento e as ações do
jardineiro, as plantações e colheitas, todas as listagens, as cópias de segurança
e a libertação de memória no `fim`.

## Autoria

Feito a dois, por [Diogo Pinto](https://github.com/DiogoFSP) e
[Rafael Marques](https://github.com/Rafael-Marques-960). A arquitetura de
classes, a estrutura da grelha e a divisão dos comandos foram decididas em
conjunto, e o trabalho foi desenvolvido no repositório privado da cadeira,
alojado pelo Rafael — este repositório é apenas uma publicação do resultado, num
único commit, e por isso não traz o histórico partilhado.
