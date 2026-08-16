#include "apaga.h"
#include <iostream>

#include "../../Backup/Backup.h"

CmdApaga::CmdApaga(Jardim** j) : Comando("apaga", nullptr), jardim(j) {}

CmdApaga::~CmdApaga() {
}

void CmdApaga::executar(std::string* seg, int n) {
    if (n != 2) {
        std::cout << "[ERRO] Sintaxe: apaga <nome_copia>\n";
        return;
    }

    std::string nome = seg[1];

    if (Backup::apagar(nome)) {
        std::cout << "[OK] Copia de memoria '" << nome << "' foi apagada e o espaco libertado.\n";
    } else {
        std::cout << "[ERRO] Nao existe nenhuma copia em memoria com o nome '" << nome << "'.\n";
    }
}