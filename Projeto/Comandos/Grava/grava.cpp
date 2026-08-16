#include "grava.h"
#include <iostream>

#include "../../Backup/Backup.h"

#include "../../Jardim/jardim.h"
#include "../../Entidades/Planta/planta.h"
#include "../../Entidades/Ferramenta/ferramenta.h"
#include "../../Entidades/Jardineiro/jardineiro.h"

CmdGrava::CmdGrava(Jardim** j) : Comando("grava", nullptr), jardim(j) {}

CmdGrava::~CmdGrava() {
}

void CmdGrava::executar(std::string* seg, int n) {
    if (n != 2) {
        std::cout << "[ERRO] Sintaxe: grava <nome_copia>\n";
        return;
    }

    if (*jardim == nullptr) {
        std::cout << "[ERRO] Nao existe jardim para gravar.\n";
        return;
    }

    std::string nome = seg[1];
    Jardim* j = *jardim;

    CopiaJardim* copia = new CopiaJardim();

    copia->linhas = j->getLinhas();
    copia->colunas = j->getColunas();

    for (int l = 0; l < j->getLinhas(); l++) {
        for (int c = 0; c < j->getColunas(); c++) {
            
            DadosSolo solo;
            solo.l = l;
            solo.c = c;

            solo.aguaSolo = j->getSolo(l, c).getAgua();
            solo.nutSolo = j->getSolo(l, c).getNutrientes();

            Planta* p = j->getSolo(l, c).getPlanta();
            if (p != nullptr) {
                solo.temPlanta = true;
                solo.tipoPlanta = p->getSimbolo();
                solo.aguaPlanta = p->getAgua();
                solo.nutPlanta = p->getNutrientes();
            } else {
                solo.temPlanta = false;
                solo.tipoPlanta = ' ';
                solo.aguaPlanta = 0;
                solo.nutPlanta = 0;
            }

            Ferramenta* f = j->getSolo(l, c).getFerramenta();
            if (f != nullptr) {
                solo.temFerramenta = true;
                solo.tipoFerramenta = f->getSimbolo();
                solo.idFerramenta = f->getNumeroSerie();
            } else {
                solo.temFerramenta = false;
                solo.tipoFerramenta = ' ';
                solo.idFerramenta = 0;
            }

            copia->s.push_back(solo);
        }
    }

    if (j->getJardineiro() != nullptr) {
        copia->jardineiroPresente = j->getJardineiroPresente();
        
        if (copia->jardineiroPresente) {
            copia->jL = j->getlinhaJardineiro();
            copia->jC = j->getcolunaJardineiro();
        } else {
            copia->jL = -1;
            copia->jC = -1;
        }

        std::vector<Ferramenta*> invAtual = j->getJardineiro()->getInventario();
        
        for (auto ferr : invAtual) {
            if (ferr != nullptr) {
                DadosItem item;
                item.tipo = ferr->getSimbolo();
                item.id = ferr->getNumeroSerie();
                
                copia->inv.push_back(item);
            }
        }
    } else {
        copia->jardineiroPresente = false;
        copia->jL = -1;
        copia->jC = -1;
    }

    Backup::guardar(nome, copia);

    std::cout << "[OK] Jardim gravado em memoria com o nome '" << nome << "'.\n";
}