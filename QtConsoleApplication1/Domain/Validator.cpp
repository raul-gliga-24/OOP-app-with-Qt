//
// Created by raulg on 3/28/2026.
//

#include "Validator.h"
#include <regex>
#include <cstring>

#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

void MasinaValidator::validator(const Masina& m) {
    char errors[1000] = "";
    if (m.getNr() == nullptr || strlen(m.getNr()) == 0)
        strcat(errors, "Numarul de inmatriculare nu poate fi vid \n");

    if (m.getModel() < 1900 || m.getModel() > 2026)
        strcat(errors, "Anul modelului este invalid (1900-2026)\n");

    if (m.getProducator() == nullptr || strlen(m.getProducator()) == 0)
        strcat(errors, "Producatorul nu poate fi vid\n");

    if (m.getTip() == nullptr || strlen(m.getTip()) == 0)
        strcat(errors, "Tipul masinii nu poate fi vid\n");

    std::regex sablon("^[A-Z]{1,2}[0-9]{2,3}[A-Z]{3}");

    if (m.getNr() != nullptr && !std::regex_match(m.getNr(), sablon))
        strcat(errors, "Numar de inmatriculare invalid (XX111XXX)");

    if (strlen(errors) > 0)
        throw ValidationError(errors);
}