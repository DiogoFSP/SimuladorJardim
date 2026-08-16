#include "jardim.h"
#include <iostream>
#include "../../Jardim/jardim.h"

CmdJardim::CmdJardim(Jardim** j, GestorCmd* g, bool* t): Comando("jardim", nullptr), jardim(j), gestor(g), terminar(t) {}

CmdJardim::~CmdJardim() {
}

void CmdJardim::executar(std::string* seg, int n) {

    if (n != 3) {
        std::cout << "[ERRO] Sintaxe: jardim <linhas> <colunas>\n";
        return;
    }

    if (*jardim != nullptr) {
        std::cout << "[ERRO] Ja existe um jardim criado.\n";
        return;
    }

    for (char c : seg[1]) {
        if (!isdigit(c)) {
            std::cout << "[ERRO] O numero de linhas tem de ser um valor inteiro positivo.\n";
            return;
        }
    }

    for (char l : seg[2]) {
        if (!isdigit(l)) {
            std::cout << "[ERRO] O numero de colunas tem de ser um valor inteiro positivo.\n";
            return;
        }
    }

    int l = std::stoi(seg[1]);
    int c = std::stoi(seg[2]);

    if (l < 1 || l > 26 || c < 1 || c > 26) {
        std::cout << "[ERRO] O jardim deve ter entre 1 e 26 linhas e colunas.\n";
        return;
    }

    *jardim = new Jardim(l, c);
    std::cout << "[OK] Jardim " << l << "x" << c << " criado.\n";

    gestor->prepararComandosJogo(jardim, terminar);
}