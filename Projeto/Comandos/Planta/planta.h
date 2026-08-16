#ifndef PROJETO_PLANTA_H
#define PROJETO_PLANTA_H
#include "../../Gestor/gestorcmd.h"

class CmdPlanta : public Comando {
public:
    CmdPlanta(Jardim* j);

    ~CmdPlanta() override;

    void executar(std::string* seg, int n) override;
};

#endif