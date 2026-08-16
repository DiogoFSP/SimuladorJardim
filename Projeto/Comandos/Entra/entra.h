#ifndef ENTRA_H
#define ENTRA_H
#include "../../Gestor/gestorcmd.h"


class CmdEntra : public Comando{
public:
  CmdEntra(Jardim* j);

  ~CmdEntra() override;

  void executar(std::string* seg, int n) override;
};
#endif
