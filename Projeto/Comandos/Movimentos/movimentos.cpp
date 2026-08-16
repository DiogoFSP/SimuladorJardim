#include "movimentos.h"
#include "../../Entidades/Jardineiro/jardineiro.h"



// --- Esquerda ---
CmdEsquerda::CmdEsquerda(Jardim* j) : Comando("e", j) {}

CmdEsquerda::~CmdEsquerda() {
}

void CmdEsquerda::executar(std::string* seg, int n) {
    if (n != 1) { std::cout << "[ERRO] Sintaxe: e\n"; return; }

    jardim->moverJardineiro(0, -1);
}

// --- Direita ---
CmdDireita::CmdDireita(Jardim* j) : Comando("d", j) {}

CmdDireita::~CmdDireita() {
}

void CmdDireita::executar(std::string* seg, int n) {
    if (n != 1) { std::cout << "[ERRO] Sintaxe: d\n"; return; }
    jardim->moverJardineiro(0, 1);
}

// --- Cima ---
CmdCima::CmdCima(Jardim* j) : Comando("c", j) {}

CmdCima::~CmdCima() {
}

void CmdCima::executar(std::string* seg, int n) {
    if (n != 1) { std::cout << "[ERRO] Sintaxe: c\n"; return; }
    jardim->moverJardineiro(-1, 0);
}

// --- Baixo ---
CmdBaixo::CmdBaixo(Jardim* j) : Comando("b", j) {}

CmdBaixo::~CmdBaixo() {
}
void CmdBaixo::executar(std::string* seg, int n) {
    if (n != 1) { std::cout << "[ERRO] Sintaxe: b\n"; return; }
    jardim->moverJardineiro(1, 0);
}