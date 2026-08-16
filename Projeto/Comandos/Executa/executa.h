#ifndef EXECUTA_H
#define EXECUTA_H

#include "../comandos.h"
#include "../../Gestor/gestorcmd.h"


class CmdExecuta : public Comando {
    GestorCmd* gestor;
public:
    CmdExecuta(Jardim* j, GestorCmd* g);

    ~CmdExecuta() override;

    void executar(std::string* seg, int n) override;

    void setJardim(Jardim * jardim);
};

#endif
