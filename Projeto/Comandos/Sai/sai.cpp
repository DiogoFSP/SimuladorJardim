#include "sai.h"

CmdSai::CmdSai(Jardim* j) : Comando("sai", j) {}

CmdSai::~CmdSai() {
}

void CmdSai::executar(std::string* seg, int n) {
    if (n != 1) {
        std::cout << "[ERRO] Sintaxe: sai\n";
        return;
    }

    if (!jardim->getJardineiroPresente()) {
        std::cout << "[ERRO] Nao ha jardineiro no jardim.\n";
        return;
    }

    int linha = jardim->getlinhaJardineiro();
    int coluna = jardim->getcolunaJardineiro();
    Jardineiro* j = jardim->getJardineiro();

    jardim->saiJardineiro(j, linha, coluna);
}

