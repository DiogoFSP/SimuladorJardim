#ifndef AVANCA_H
#define AVANCA_H

#include "../../Gestor/gestorcmd.h"
#include "../../utilidades.h"
#include <iostream>

class CmdAvanca : public Comando {
public:
    CmdAvanca(Jardim* j);

    ~CmdAvanca() override;

    void executar(std::string* seg, int n) override;
};

#endif //AVANCA_H