#ifndef PEGA_H
#define PEGA_H

#include "../../Gestor/gestorcmd.h"

class CmdPega : public Comando {
public:
    CmdPega(Jardim* j);

    ~CmdPega() override;

    void executar(std::string* seg, int n) override;
};
#endif
