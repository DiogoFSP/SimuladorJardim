#ifndef MINERALIZAR_HIDRICO_H

/*
=====================================================================
 * FERRAMENTAZ: Enxada Rotativa
 * =====================================================================
 * Descricao:
 * Ferramenta especial (FerramentaZ)
 * Ferramenta de gestao de solo usada em terrenos excessivamente alagados
 * converte o excesso de agua em nutrientes
 *
 * Funcionamento:
 * Atua uma vez por instante , quando esta na mao do jardineiro
 * Acao sobre a posicao onde o jardineiro se encontra
 *
 * Logica da Acao (a cada instante):
 * 1. A ferramenta verifica a quantidade de agua no solo da posicao atual.
 * 2. Se a agua for > [Settings/alagado]
 * - Reduz a agua do solo em [Settings/perca]
 * - Aumenta os nutrientes do solo em [Settings/ganho_nutrientes]
 *
 * Desgaste:
 * A ferramenta tem um numero finito de cargas (10).
 * Quando as cargas se esgotam, a ferramenta torna-se inutil e desaparece do simulador
 * =====================================================================
 */

#define MINERALIZAR_HIDRICO_H
#include "../ferramenta.h"
#include "../../../Solo/solo.h"


class Enxada_Rotativa : public Ferramenta {
private:

public:
    Enxada_Rotativa();

    ~Enxada_Rotativa() override;

    bool usar(Solo &s) override;
    std::string info() const override;

    bool verfCap() const override;
};
#endif //MINERALIZAR_HIDRICO_H
