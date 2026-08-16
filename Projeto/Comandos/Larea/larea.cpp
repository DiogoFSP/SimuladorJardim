#include "larea.h"
#include "../../Gestor/gestorcmd.h"
#include "../../Solo/solo.h"
#include "../../Entidades/Planta/planta.h"
#include "../../Entidades/Ferramenta/ferramenta.h"
#include <iostream>

CmdLArea::CmdLArea(Jardim* j) : Comando("larea", j) {}

CmdLArea::~CmdLArea() {
}

void CmdLArea::executar(std::string* seg, int n){
    if (n != 1) {
        std::cout << "[ERRO] Sintaxe: larea\n";
        return;
    }

    jardim->larea();
}