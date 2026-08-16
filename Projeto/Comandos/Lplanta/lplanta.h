#ifndef LPLANTA_H
#define LPLANTA_H

#include "../../Gestor/gestorcmd.h"
#include "../../Solo/solo.h"
#include "../../Entidades/Planta/planta.h"
#include <iostream>

class CmdLPlanta : public Comando {
public:
    CmdLPlanta(Jardim* j);

    ~CmdLPlanta() override;

    void executar(std::string* seg, int n) override;
};

#endif