#ifndef LPLANTAS_H
#define LPLANTAS_H



#include <string>
#include <iostream>
#include "../../Jardim/jardim.h"
#include "../comandos.h"

class CmdLPlantas : public Comando {
public:
    CmdLPlantas(Jardim* j);

    ~CmdLPlantas() override;

    void executar(std::string* seg, int n);

};

#endif
