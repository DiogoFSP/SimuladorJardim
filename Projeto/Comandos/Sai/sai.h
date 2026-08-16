#ifndef SAI_H
#define SAI_H
#include "../../Gestor/gestorcmd.h"

class CmdSai : public Comando {

public:
    CmdSai(Jardim* j);

    ~CmdSai() override;

    void executar(std::string* seg, int n) override;
};
#endif
