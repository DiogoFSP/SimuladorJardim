#include "lferr.h"
#include "../../Entidades/Jardineiro/jardineiro.h"
#include <iostream>

CmdLFerr::CmdLFerr(Jardim* j) : Comando("lferr", j) {}

CmdLFerr::~CmdLFerr() {
}

void CmdLFerr::executar(std::string* segs, int n) {
    if (n != 1) {
        std::cout << "[ERRO] Sintaxe: lferr\n";
        return;
    }

    jardim->lferr();
}

