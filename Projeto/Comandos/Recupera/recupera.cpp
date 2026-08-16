#include "recupera.h"
#include <iostream>

#include "../../Backup/Backup.h"

#include "../../Jardim/jardim.h"
#include "../../Entidades/Planta/planta.h"
#include "../../Entidades/Ferramenta/ferramenta.h"
#include "../../Entidades/Jardineiro/jardineiro.h"

#include "../../Entidades/Ferramenta/Regador/regador.h"
#include "../../Entidades/Ferramenta/PacoteAdubo/adubo.h"
#include "../../Entidades/Ferramenta/TesouraPoda/tesoura.h"
#include "../../Entidades/Ferramenta/EnxadaRotativa/enxadarotativa.h"
#include "../../Entidades/Planta/Cacto/cacto.h"
#include "../../Entidades/Planta/ErvaDaninha/erva.h"
#include "../../Entidades/Planta/PlantaExotica/sentinela.h"
#include "../../Entidades/Planta/Roseira/roseira.h"

CmdRecupera::CmdRecupera(Jardim** j, GestorCmd* g, bool* t) 
    : Comando("recupera", nullptr), jardim(j), gestor(g), terminar(t) 
{}

CmdRecupera::~CmdRecupera() {
}

// Fábrica auxiliar para criar a ferramenta correta baseada no char
Ferramenta* fabricarFerramenta(char tipo) {
    switch (tipo) {
        case 'g': return new Regador();
        case 'a': return new PacoteDeAdubo();
        case 't': return new TesouraPoda();
        case 'z': return new Enxada_Rotativa();
        default: return nullptr;
    }
}

Planta* fabricarPlanta(char tipo) {
    switch (tipo) {
        case 'c': return new Cacto();
        case 'r': return new Roseira();
        case 'e': return new Erva_Daninha();
        case 'x': return new Sentinela();
        default: return nullptr;
    }
}

void CmdRecupera::executar(std::string* seg, int n) {

    if (n != 2) {
        std::cout << "[ERRO] Sintaxe: recupera <nome_copia>\n";
        return;
    }

    std::string nome = seg[1];

    if (!Backup::existe(nome)) {
        std::cout << "[ERRO] Nao existe nenhuma copia chamada '" << nome << "'.\n";
        return;
    }

    CopiaJardim* dados = Backup::recuperar(nome);

    if (*jardim != nullptr) {
        delete *jardim;
        *jardim = nullptr;
    }

    std::cout << "A reconstruir jardim...\n";

    *jardim = new Jardim(dados->linhas, dados->colunas);
    Jardim* j = *jardim;

    // limpa as ferramentas aleatórias
    for(int l=0; l < j->getLinhas(); l++) {
        for(int c=0; c < j->getColunas(); c++) {
            Ferramenta* lixo = j->getSolo(l,c).getFerramenta();
            if(lixo != nullptr) {
                j->getSolo(l,c).setFerramenta(nullptr);
                delete lixo;
            }
        }
    }

    gestor->prepararComandosJogo(jardim, terminar);

    int maiorIdEncontrado = 0;

    for (const auto& solo : dados->s) {
        int l = solo.l;
        int c = solo.c;
        Solo& s = j->getSolo(l, c);

        //Restaurar Solo
        s.rmvagua(s.getAgua());
        s.addagua(solo.aguaSolo);

        s.rmvnutrientes(s.getNutrientes());
        s.addnutrientes(solo.nutSolo);

        // Restaurar Planta
        if (solo.temPlanta) {
            Planta* p = fabricarPlanta(solo.tipoPlanta);
            if (p != nullptr) {
                p->setAgua(static_cast<float>(solo.aguaPlanta));
                p->setNutri(static_cast<float>(solo.nutPlanta));
                s.setPlanta(p);
            }
        }

        if (solo.temFerramenta) {
            Ferramenta* f = fabricarFerramenta(solo.tipoFerramenta);
            if (f != nullptr) {
                f->setNumeroSerie(solo.idFerramenta);
                s.setFerramenta(f);
                if (solo.idFerramenta > maiorIdEncontrado) maiorIdEncontrado = solo.idFerramenta;
            }
        }
    }

    if (dados->jardineiroPresente) {
        if (dados->jL != -1) {
             j->entraJardineiro(dados->jL, dados->jC);
        }

        Jardineiro* boneco = j->getJardineiro();
        if (boneco != nullptr) {
            for (const auto& item : dados->inv) {
                Ferramenta* f = fabricarFerramenta(item.tipo);
                if (f != nullptr) {
                    f->setNumeroSerie(item.id);
                    boneco->adicionaFerramenta(f);

                    if (item.id > maiorIdEncontrado) maiorIdEncontrado = item.id;
                }
            }

            boneco->resetQuantidadesPorInstante();
        }
    }

    Ferramenta::atualizarContador(maiorIdEncontrado);

    delete dados;
    std::cout << "[OK] Jardim recuperado.\n";
}