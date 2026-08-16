#ifndef AJUDA_H
#define AJUDA_H
#include "../comandos.h"
#include <vector>


class CmdAjuda : public Comando {
public:
    CmdAjuda(Jardim* j);
    virtual ~CmdAjuda();

    void executar(std::string* segs, int n) override;
};
#endif
