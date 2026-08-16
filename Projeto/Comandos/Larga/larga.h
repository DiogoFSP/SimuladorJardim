#ifndef LARGA_H
#define LARGA_H

#include "../../Gestor/gestorcmd.h"

class CmdLarga : public Comando {
public:
    CmdLarga(Jardim* j);

    ~CmdLarga() override;

    void executar(std::string* seg, int n) override;
};

#endif
