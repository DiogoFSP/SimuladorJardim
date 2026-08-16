#ifndef CMD_JARDIM_H
#define CMD_JARDIM_H

#include "../comandos.h"
#include "../../Gestor/gestorcmd.h"

class GestorCmd;
class Jardim;

class CmdJardim : public Comando {
private:
    Jardim** jardim;
    GestorCmd* gestor;
    bool* terminar;

public:
    CmdJardim(Jardim** j, GestorCmd* g, bool* t);

    ~CmdJardim();

    void executar(std::string* seg, int n) override;


};

#endif