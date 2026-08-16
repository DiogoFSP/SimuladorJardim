#ifndef ADUBO_H
#define ADUBO_H

#include "../ferramenta.h"
#include "../../../Solo/solo.h"

class PacoteDeAdubo : public Ferramenta {
private:

public:
    PacoteDeAdubo();

    ~PacoteDeAdubo() override;

    bool usar(Solo &s) override;
    std::string info() const override;

    bool verfCap() const override;
};

#endif