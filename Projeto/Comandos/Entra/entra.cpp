#include "entra.h"

CmdEntra::CmdEntra(Jardim* j) : Comando("entra", j) {}

CmdEntra::~CmdEntra() {
}

void CmdEntra::executar(std::string* seg, int n) {
    if (n != 2) {
        std::cout << "[ERRO] Sintaxe: entra <l><c>\n";
        return;
    }

    int l, c;

    if (!jardim->verpos(seg[1], l, c)) {
        return;
    }

    if (jardim->entraJardineiro(l, c)) {
        std::cout << "[OK] O jardineiro entrou no jardim em " << seg[1] << "\n";
    }

}