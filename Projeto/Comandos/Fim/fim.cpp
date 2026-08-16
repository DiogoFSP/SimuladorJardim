#include "fim.h"
#include <iostream>

CmdFim::CmdFim(Jardim* j, bool* t) : Comando("fim", j), terminar(t) {}

CmdFim::~CmdFim() {
}

void CmdFim::executar(std::string* seg, int n) {
    if (n != 1) {
        std::cout << "[ERRO] Sintaxe: fim\n";
        return;
    }

    std::cout << "A terminar...\n";
    *terminar = true;
}