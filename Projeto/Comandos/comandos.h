#ifndef COMANDO_H
#define COMANDO_H
#include <string>
#include "../Jardim/jardim.h"


class Comando {
protected:
    std::string nome;
    Jardim* jardim;   // ponteiro para o único jardim

public:
    Comando(const std::string& n, Jardim* j);

    virtual ~Comando();

    std::string getNome() const;

    virtual void executar(std::string* segmentos, int nSegmentos) = 0;
};

#endif


