#include <iostream>
#include "./Gestor/gestorcmd.h"
#include "./Comandos/Jardim/jardim.h"
#include "./Comandos/Executa/executa.h"
#include "./Comandos/Ajuda/Ajuda.h"
#include "./Backup/Backup.h"

int main() {
   bool terminar = false;
   Jardim* jardim = nullptr;
   GestorCmd gestor;

   gestor.registar(new CmdJardim(&jardim, &gestor, &terminar));
   gestor.registar(new CmdExecuta(jardim, &gestor));
   gestor.registar(new CmdAjuda(jardim));

   std::string linha;
   while (!terminar) {
      if (jardim) jardim->imprimir();
      std::cout << "> ";
      if (!std::getline(std::cin, linha)) break;
      gestor.interpretar(linha);
   }

   delete jardim;
   Backup::limparTudo();
   return 0;
}