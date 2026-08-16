#include "avanca.h"

CmdAvanca::CmdAvanca(Jardim* j) : Comando("avanca", j){}

CmdAvanca::~CmdAvanca() {
}

void CmdAvanca::executar(std::string* seg, int nSegmentos) {
    if (nSegmentos > 2) {
        std::cout << "[ERRO] Sintaxe: avanca [n]\n";
        return;
    }

    int n = 1; // valor por defeito

    if (nSegmentos == 2) {
        if (!Utilidades::soDigitos(seg[1])) {
            std::cout << "[ERRO] O parametro deve ser um numero inteiro positivo.\n";
            return;
        }
        n = std::stoi(seg[1]);
    }

    jardim->avancaInstantes(n);
    jardim->getJardineiro()->resetQuantidadesPorInstante(); //reset

    std::cout << "[OK] Comando 'avanca' valido. Instantes a avancar = " << n << "\n";
}