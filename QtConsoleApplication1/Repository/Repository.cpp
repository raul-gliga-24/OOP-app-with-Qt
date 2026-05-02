//
// Created by raulg on 3/27/2026.
//

#include "Repository.h"

#include <cstring>
#include <stdexcept>
#include <algorithm>

Repository::Repository() = default;

Repository::~Repository() = default;

const Masina &Repository::find(const char* nr) const {
    auto it = std::find_if(elements.begin(), elements.end(),
        [nr](const Masina& m) { return strcmp(m.getNr(), nr) == 0; });

    if (it != elements.end())
        return *it;

    throw std::runtime_error("Masina cu numarul dat nu a fost gasita");
}

void Repository::add(const Masina& element) {
    auto it = std::find_if(elements.begin(), elements.end(),
        [element](const Masina& m) { return strcmp(m.getNr(), element.getNr()) == 0; });

    if (it != elements.end())
        throw std::runtime_error("Aceasta masina exista deja");

    elements.push_back(element);
}

size_t Repository::getSize() const {
    return elements.size();
}

const std::vector<Masina>& Repository::getAll() const {
    return elements;
}



void Repository::remove(const char* nr) {
    auto it = std::find_if(elements.begin(), elements.end(),
        [nr](const Masina& m) { return strcmp(m.getNr(), nr) == 0; });

    if (it != elements.end()) {
        elements.erase(it);
        return;
    }

    throw std::runtime_error("Masina cu numarul dat nu a putut fi stearsa");
}

void Repository::update(const char* nr, const Masina &NewMasina) {
    auto it = std::find_if(elements.begin(), elements.end(),
        [nr](const Masina& m) { return strcmp(m.getNr(), nr) == 0; });

    if (it != elements.end()) {
        *it = NewMasina;
        return;
    }

    throw std::runtime_error("Masina cu numarul dat nu a putut fi actualizata");
}
