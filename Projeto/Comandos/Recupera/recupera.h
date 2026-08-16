#ifndef CMD_RECUPERA_H
#define CMD_RECUPERA_H

#include "../comandos.h"
#include "../../Gestor/gestorcmd.h"
#include <fstream>

class CmdRecupera : public Comando {
private:
    Jardim** jardim;
    GestorCmd* gestor;
    bool* terminar;

public:
    CmdRecupera(Jardim** j, GestorCmd* g, bool* t);

    ~CmdRecupera();

    void executar(std::string* seg, int n) override;
};

#endif