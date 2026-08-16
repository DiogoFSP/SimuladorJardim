#include "planta.h"

#include "../../utilidades.h"
#include "../../Entidades/Planta/Cacto/cacto.h"

CmdPlanta::CmdPlanta(Jardim* j) : Comando("planta", j) {}

CmdPlanta::~CmdPlanta() {
}

void CmdPlanta::executar(std::string* seg, int n) {
    if (n < 3) {
        std::cout << "[ERRO] Sintaxe: planta <pos> <tipo>\n";
        return;
    }

    int l, c;

    if (!jardim->verpos(seg[1], l, c)) {
        return;
    }

    char tipo = seg[2][0];

    if (jardim->plantarPlanta(l, c, tipo)) {
        std::cout << "[OK] Planta " << tipo << " adicionada em " << seg[1] << ".\n";
    }

}