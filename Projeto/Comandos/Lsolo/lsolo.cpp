#include "lsolo.h"
#include "../../Solo/solo.h"
#include "../../Entidades/Planta/planta.h"
#include "../../Entidades/Ferramenta/ferramenta.h"
#include "../../utilidades.h"
#include <iostream>

CmdLSolo::CmdLSolo(Jardim* j) : Comando("lsolo", j) {}

CmdLSolo::~CmdLSolo() {
}

void CmdLSolo::executar(std::string* segs, int n) {
    if (n < 2 || n > 3) {
        std::cout << "[ERRO] Sintaxe: lsolo <lc> [n]\n";
        return;
    }

    std::string pos = segs[1];
    if (pos.size() != 2 || pos[0] < 'a' || pos[0] > 'z' || pos[1] < 'a' || pos[1] > 'z') {
        std::cout << "[ERRO] Posicao invalida. Use formato <linha><coluna> (ex: fb)\n";
        return;
    }

    int linha = pos[0] - 'a';
    int coluna = pos[1] - 'a';

    if (linha < 0 || linha >= jardim->getLinhas() ||
        coluna < 0 || coluna >= jardim->getColunas()) {
        std::cout << "[ERRO] Posicao fora dos limites do jardim.\n";
        return;
    }

    int raio = 0;
    if (n == 3) {
        if (!Utilidades::soDigitos(segs[2])) {
            std::cout << "[ERRO] O parametro n deve ser um numero inteiro positivo.\n";
            return;
        }
        raio = std::stoi(segs[2]);
        if (raio < 0) raio = 0;
    }

    // Percorrer a posição central e vizinhas dentro do raio
    for (int i = linha - raio; i <= linha + raio; i++) {
        for (int j = coluna - raio; j <= coluna + raio; j++) {
            if (i < 0 || i >= jardim->getLinhas() ||
                j < 0 || j >= jardim->getColunas())
                continue;
            //infos do solo
            jardim->infoSolo(i,j);
        }
    }
}

