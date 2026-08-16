#include "colhe.h"

CmdColhe::CmdColhe(Jardim* j) : Comando("colhe", j) {}

CmdColhe::~CmdColhe() {
}

void CmdColhe::executar(std::string* seg, int n) {
    if (n != 2) {
        std::cout << "[ERRO] Sintaxe: colhe <lc>\n";
        return;
    }
    int l, c;

    if (!jardim->verpos(seg[1], l, c)) {
        return;
    }

    if (jardim->colhePlanta(l, c)) {
        std::cout << "[OK] Planta colhida em " << seg[1] << ".\n";
    }
}
