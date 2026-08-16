#include "lplantas.h"

CmdLPlantas::CmdLPlantas(Jardim* j) : Comando("lplantas", j) {}

CmdLPlantas::~CmdLPlantas() {
}

void CmdLPlantas::executar(std::string* seg, int n) {
    if (n != 1) {
        std::cout << "[ERRO] Sintaxe: lplantas\n";
        return;
    }

    bool encontrou = false;

    for (int linha = 0; linha < jardim->getLinhas(); linha++) {
        for (int coluna = 0; coluna < jardim->getColunas(); coluna++) {
            if (encontrou == false) {
                encontrou = jardim->infoPlanta(linha, coluna);
            } else {
                jardim->infoPlanta(linha, coluna);
            }
        }
    }

    if (!encontrou) {
        std::cout << "[ERRO] Nao existem plantas no jardim.\n";
    }
}