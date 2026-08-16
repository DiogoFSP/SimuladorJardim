#ifndef LAREA_H
#define LAREA_H

#include "../../Gestor/gestorcmd.h"


class CmdLArea : public Comando {
public:
    CmdLArea(Jardim* j);

    ~CmdLArea() override;

    void executar(std::string* seg, int n) override;
};

#endif