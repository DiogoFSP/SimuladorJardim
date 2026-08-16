#ifndef CMD_GRAVA_H
#define CMD_GRAVA_H

#include "../comandos.h"
#include <fstream>

class CmdGrava : public Comando {
private:
    Jardim** jardim;

public:
    CmdGrava(Jardim** j);

    ~CmdGrava();

    void executar(std::string* seg, int n) override;
};

#endif