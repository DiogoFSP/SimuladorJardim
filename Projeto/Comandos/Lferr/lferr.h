#ifndef LFERR_H
#define LFERR_H

#include "../../Gestor/gestorcmd.h"

class CmdLFerr : public Comando {
public:
    CmdLFerr(Jardim* j);

    ~CmdLFerr() override;

    void executar(std::string* segs, int n) override;
};


#endif
