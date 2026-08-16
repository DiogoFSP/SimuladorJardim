#ifndef LSOLO_H
#define LSOLO_H

#include "../../Gestor/gestorcmd.h"

class CmdLSolo : public Comando {
public:
    CmdLSolo(Jardim* j);

    ~CmdLSolo() override;

    void executar(std::string* segs, int n) override;
};

#endif