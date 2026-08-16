#ifndef MOVIMENTOS_H
#define MOVIMENTOS_H

#include "../../Gestor/gestorcmd.h"

class CmdEsquerda : public Comando {
public:
    CmdEsquerda(Jardim* j);

    ~CmdEsquerda() override;

    void executar(std::string* seg, int n) override;
};

class CmdDireita : public Comando {
public:
    CmdDireita(Jardim* j);

    ~CmdDireita() override;

    void executar(std::string* seg, int n) override;
};

class CmdCima : public Comando {
public:
    CmdCima(Jardim* j);

    ~CmdCima() override;

    void executar(std::string* seg, int n) override;
};

class CmdBaixo : public Comando {
public:
    CmdBaixo(Jardim* j);

    ~CmdBaixo() override;

    void executar(std::string* seg, int n) override;
};



#endif
