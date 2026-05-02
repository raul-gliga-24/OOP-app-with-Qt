//
// Created by raulg on 3/26/2026.
//

#include "Masina.h"

#include <cstring>
#include <iostream>

#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

using std::cout;
using std::endl;

Masina::Masina() : nrInmatriculare{nullptr},producator{nullptr},model{0},tip{nullptr},available{true}{
}

Masina::Masina(const char* nr,const char* prod,const int mod, const char* t):model{mod},available{true} {
    nrInmatriculare = new char[strlen(nr)+1];
    strcpy(nrInmatriculare,nr);

    producator = new char[strlen(prod)+1];
    strcpy(producator,prod);

    tip = new char[strlen(t)+1];
    strcpy(tip,t);
}

Masina::~Masina() {
    delete[] nrInmatriculare;
    delete[] producator;
    delete[] tip;
}

Masina::Masina(const Masina& other) : model{other.model},available{other.available} {
    std::cout << "COPIE FACUTA" << std::endl;
    nrInmatriculare = new char[strlen(other.nrInmatriculare)+1];
    strcpy(nrInmatriculare,other.nrInmatriculare);

    producator = new char[strlen(other.producator)+1];
    strcpy(producator,other.producator);

    tip = new char[strlen(other.tip)+1];
    strcpy(tip,other.tip);
}

Masina& Masina::operator=(const Masina& other) {
    if (this != &other) {
        delete[] nrInmatriculare;
        delete[] producator;
        delete[] tip;

        nrInmatriculare = new char[strlen(other.nrInmatriculare) + 1];
        strcpy(nrInmatriculare, other.nrInmatriculare);

        producator = new char[strlen(other.producator) + 1];
        strcpy(producator, other.producator);

        tip = new char[strlen(other.tip) + 1];
        strcpy(tip, other.tip);

        this->model = other.model;
        this->available = other.available;
    }
    return *this;
}

Masina::Masina(Masina&& other) noexcept : nrInmatriculare(other.nrInmatriculare), producator(other.producator), model(other.model), tip(other.tip), available(other.available) {
    other.nrInmatriculare = nullptr;
    other.producator = nullptr;
    other.tip = nullptr;
    other.model = 0;
    other.available = true;
}

Masina& Masina::operator=(Masina&& other) noexcept {
    if (this != &other) {
        delete[] nrInmatriculare;
        delete[] producator;
        delete[] tip;

        nrInmatriculare = other.nrInmatriculare;
        producator = other.producator;
        tip = other.tip;
        model = other.model;
        available = other.available;

        other.nrInmatriculare = nullptr;
        other.producator = nullptr;
        other.tip = nullptr;
        other.model = 0;
        other.available = true;
    }
    return *this;
}

const char *Masina::getNr() const {
    return this->nrInmatriculare;
}

const char *Masina::getProducator() const {
    return this->producator;
}

int Masina::getModel() const {
    return this->model;
}

const char *Masina::getTip() const {
    return this->tip;
}

bool Masina::getAvailability() const {
    return this->available;
}

void Masina::setAvailability(bool status) {
    this->available=status;
}
