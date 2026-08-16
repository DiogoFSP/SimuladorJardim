#ifndef REGADOR_H
#define REGADOR_H

#include "../ferramenta.h"

class Regador : public Ferramenta {
private:

public:
    Regador();

    ~Regador() override;

    bool usar(Solo &s) override;

    std::string info() const override;

    bool verfCap() const override;
};

#endif