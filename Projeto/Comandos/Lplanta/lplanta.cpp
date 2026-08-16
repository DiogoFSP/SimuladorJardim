#include "lplanta.h"

CmdLPlanta::CmdLPlanta(Jardim* j) : Comando("lplanta", j) {}

CmdLPlanta::~CmdLPlanta() {
}

void CmdLPlanta::executar(std::string* seg, int n){
    if (n != 2) {
        std::cout << "[ERRO] Sintaxe: lplanta <lc>\n";
        return;
    }

    std::string pos = seg[1];
    if (pos.size() != 2 || pos[0] < 'a' || pos[0] > 'z' || pos[1] < 'a' || pos[1] > 'z'){
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

    Solo& s = jardim->getSolo(linha, coluna);
    Planta* p = s.getPlanta();

    if (p == nullptr) {
        std::cout << "[ERRO] Nao existe planta na posicao " << pos << ".\n";
        return;
    }

    bool encontrou = jardim->infoPlanta(linha, coluna);

    if (!encontrou) {
        std::cout << "[ERRO] Nao existe palavra na posicao" << pos << ".\n";
    }
}