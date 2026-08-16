#ifndef COLHE_H
#define COLHE_H
#include "../../Gestor/gestorcmd.h"
#include "../../Solo/solo.h"
#include "../../Entidades/Planta/planta.h"
#include <iostream>


class CmdColhe : public Comando {
public:
    CmdColhe(Jardim* j);

    ~CmdColhe() override;

    void executar(std::string* seg, int n) override;
};




#endif //COLHE_H
