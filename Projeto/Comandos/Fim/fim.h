#ifndef FIM_H
#define FIM_H
#include "../comandos.h"

class CmdFim : public Comando {
    bool* terminar;

public:
    CmdFim(Jardim* j, bool* t);

    ~CmdFim() override;

    void executar(std::string* seg, int n) override;
};

#endif