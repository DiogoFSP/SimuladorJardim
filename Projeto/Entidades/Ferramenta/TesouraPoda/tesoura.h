#ifndef TESOURAPODA_H
#define TESOURAPODA_H

#include "../ferramenta.h"
#include "../../../Solo/solo.h"
#include <iostream>

class TesouraPoda : public Ferramenta {
private:

public:
    TesouraPoda();

    ~TesouraPoda() override;

    bool usar(Solo &s) override;

    std::string info() const override;

    bool verfCap() const override;
};

#endif