#ifndef CMDAPAGA_H
#define CMDAPAGA_H

#include "../comandos.h"
#include "../../Jardim/jardim.h"
#include "../comandos.h"


class CmdApaga : public Comando {
private:
    Jardim** jardim;

public:
    CmdApaga(Jardim** j);
    virtual ~CmdApaga();
    void executar(std::string* seg, int n) override;
};

#endif