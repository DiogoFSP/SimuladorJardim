#ifndef COMPRA_H
#define COMPRA_H
#include "../../Gestor/gestorcmd.h"


class CmdCompra : public Comando{
public:
  CmdCompra(Jardim* j);

  ~CmdCompra() override;

  void executar(std::string *seg, int n) override;
};
#endif //COMPRA_H
