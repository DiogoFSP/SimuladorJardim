#include "gestorcmd.h"
#include "../utilidades.h"
#include <iostream>

// Includes de TODOS os comandos de jogo
#include "../Comandos/Avanca/avanca.h"
#include "../Comandos/Planta/planta.h"
#include "../Comandos/Lplanta/lplanta.h"
#include "../Comandos/Larea/larea.h"
#include "../Comandos/Fim/fim.h"
#include "../Comandos/Lferr/lferr.h"
#include "../Comandos/Lsolo/lsolo.h"
#include "../Comandos/Lplantas/lplantas.h"
#include "../Comandos/Larga/larga.h"
#include "../Comandos/Colhe/colhe.h"
#include "../Comandos/Movimentos/movimentos.h"
#include "../Comandos/Sai/sai.h"
#include "../Comandos/Entra/entra.h"
#include "../Comandos/Pega/pega.h"
#include "../Comandos/Compra/compra.h"
#include "../Comandos/Executa/executa.h"
#include "../Comandos/Ajuda/Ajuda.h"
#include "../Comandos/Recupera/recupera.h"
#include "../Comandos/Grava/grava.h"
#include "../Comandos/Apaga/apaga.h"

GestorCmd::GestorCmd() : capacidade(1), quantidade(0) {
    comandos = new Comando*[capacidade];
}

GestorCmd::~GestorCmd() {
    for (int i = 0; i < quantidade; i++) delete comandos[i];
    delete[] comandos;
}

void GestorCmd::expandir() {
    int novaCap = capacidade + 1;
    Comando** novo = new Comando*[novaCap];
    for (int i = 0; i < quantidade; i++)
        novo[i] = comandos[i];
    delete[] comandos;
    comandos = novo;
    capacidade = novaCap;
}

void GestorCmd::registar(Comando* cmd) {
    if (quantidade == capacidade) expandir();
    comandos[quantidade++] = cmd;
}

void GestorCmd::interpretar(const std::string& linha){
    const int MAX_SEG = 10;
    std::string segmentos[MAX_SEG];
    Utilidades util;
    int n = util.separarSegmentos(linha, segmentos, MAX_SEG);

    if (n == 0) return;

    for (int i = 0; i < quantidade; ++i) {
        if (comandos[i]->getNome() == segmentos[0]) {
            comandos[i]->executar(segmentos, n);
            return;
        }
    }
    std::cout << "Comando desconhecido: " << segmentos[0] << "\n";
}

int GestorCmd::getNumeroComandos() {
    return quantidade;
}

Comando* GestorCmd::getComando(int i) {
    if (i < 0 || i >= quantidade) return nullptr;
    return comandos[i];
}

void GestorCmd::prepararComandosJogo(Jardim** jardimRef, bool* terminarPtr) {

    bool comandosExistem = false;
    for (int i = 0; i < quantidade; i++) {
        if (comandos[i]->getNome() == "avanca") {
            comandosExistem = true;
            break;
        }
    }

    if (!comandosExistem) {
        std::cout << "A registar comandos...\n";

        registar(new CmdEntra(*jardimRef));
        registar(new CmdEsquerda(*jardimRef));
        registar(new CmdDireita(*jardimRef));
        registar(new CmdCima(*jardimRef));
        registar(new CmdBaixo(*jardimRef));
        registar(new CmdSai(*jardimRef));
        registar(new CmdPlanta(*jardimRef));
        registar(new CmdColhe(*jardimRef));
        registar(new CmdLPlanta(*jardimRef));
        registar(new CmdLArea(*jardimRef));
        registar(new CmdLSolo(*jardimRef));
        registar(new CmdLFerr(*jardimRef));
        registar(new CmdLPlantas(*jardimRef));
        registar(new CmdLarga(*jardimRef));
        registar(new CmdPega(*jardimRef));
        registar(new CmdCompra(*jardimRef));
        registar(new CmdAvanca(*jardimRef));
        registar(new CmdFim(*jardimRef, terminarPtr));
        registar(new CmdAjuda(*jardimRef));

        registar(new CmdRecupera(jardimRef, this, terminarPtr));
        registar(new CmdGrava(jardimRef));
        registar(new CmdApaga(jardimRef));
    }
    else {
        // substituir os objetos antigos pelos novos.
        std::cout << "A atualizar comandos para o novo jardim...\n";

        for (int i = 0; i < quantidade; i++) {
            std::string nome = comandos[i]->getNome();

            if (nome == "entra") { delete comandos[i]; comandos[i] = new CmdEntra(*jardimRef); }
            else if (nome == "esquerda") { delete comandos[i]; comandos[i] = new CmdEsquerda(*jardimRef); }
            else if (nome == "direita") { delete comandos[i]; comandos[i] = new CmdDireita(*jardimRef); }
            else if (nome == "cima") { delete comandos[i]; comandos[i] = new CmdCima(*jardimRef); }
            else if (nome == "baixo") { delete comandos[i]; comandos[i] = new CmdBaixo(*jardimRef); }
            else if (nome == "sai") { delete comandos[i]; comandos[i] = new CmdSai(*jardimRef); }
            else if (nome == "planta") { delete comandos[i]; comandos[i] = new CmdPlanta(*jardimRef); }
            else if (nome == "colhe") { delete comandos[i]; comandos[i] = new CmdColhe(*jardimRef); }
            else if (nome == "lplanta") { delete comandos[i]; comandos[i] = new CmdLPlanta(*jardimRef); }
            else if (nome == "larea") { delete comandos[i]; comandos[i] = new CmdLArea(*jardimRef); }
            else if (nome == "lsolo") { delete comandos[i]; comandos[i] = new CmdLSolo(*jardimRef); }
            else if (nome == "lferr") { delete comandos[i]; comandos[i] = new CmdLFerr(*jardimRef); }
            else if (nome == "lplantas") { delete comandos[i]; comandos[i] = new CmdLPlantas(*jardimRef); }
            else if (nome == "larga") { delete comandos[i]; comandos[i] = new CmdLarga(*jardimRef); }
            else if (nome == "pega") { delete comandos[i]; comandos[i] = new CmdPega(*jardimRef); }
            else if (nome == "compra") { delete comandos[i]; comandos[i] = new CmdCompra(*jardimRef); }
            else if (nome == "avanca") { delete comandos[i]; comandos[i] = new CmdAvanca(*jardimRef); }
            else if (nome == "fim") { delete comandos[i]; comandos[i] = new CmdFim(*jardimRef, terminarPtr); }
            else if (nome == "ajuda") { delete comandos[i]; comandos[i] = new CmdAjuda(*jardimRef); }
            else if (nome == "recupera") { delete comandos[i]; comandos[i] = new CmdRecupera(jardimRef, this, terminarPtr); }
            else if (nome == "grava") { delete comandos[i]; comandos[i] = new CmdGrava(jardimRef); }
            else if (nome == "apaga") { delete comandos[i]; comandos[i] = new CmdApaga(jardimRef); }

        }
    }

    for (int i = 0; i < quantidade; i++) {
        if (comandos[i]->getNome() == "executa") {
            CmdExecuta* cmdExec = dynamic_cast<CmdExecuta*>(comandos[i]); //converte o ponteiro de Comando para CmdExecuta
            if (cmdExec) {
                cmdExec->setJardim(*jardimRef);
            }
            break;
        }
    }
}