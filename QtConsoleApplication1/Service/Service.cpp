//
// Created by raulg on 3/27/2026.
//
#include "Service.h"
#include <cstring>
#include <random>
#include <algorithm>
#include <fstream>

void Service::addMasina(const char* nr, const char *producator, const int model, const char *tip) {

    const Masina m(nr,producator,model,tip);
    this->val.validator(m);
    this->repo.add(m);
    undoStack.push_back(std::make_unique<UndoAdauga>(repo, m));
}

const std::vector<Masina>& Service::getAllMasini() const {
    return this->repo.getAll();
}

unsigned long long Service::getSize() const {
    return this->repo.getSize();
}

void Service::removeMasina(const char* nr) {
    Masina m = this->repo.find(nr);
    this->repo.remove(nr);
    undoStack.push_back(std::make_unique<UndoSterge>(repo, m));
}

void Service::updateMasina(const char* nr, const Masina &NewMasina) {
    Masina m = this->repo.find(nr);
    this->repo.update(nr,NewMasina);
    undoStack.push_back(std::make_unique<UndoModifica>(repo, m, NewMasina));
}

void Service::inchiriazaMasina(const char* nr) {
    Masina m = this->repo.find(nr);

    if (!m.getAvailability()) {
        throw std::runtime_error("Eroare! Masina este deja inchiriata!");
    }
    m.setAvailability(false);
    this->repo.update(nr,m);
}

void Service::returneazaMasina(const char * nr) {
    Masina m = this->repo.find(nr);

    if (m.getAvailability()) {
        throw std::runtime_error("Eroare! Masina trebuie sa fie inchiriata!");
    }
    m.setAvailability(true);
    this->repo.update(nr,m);
}

Masina* Service::filtreazaDupaProducator(const char* producator, int& dimensiuneRezultat) const {
    const auto& all = this->repo.getAll();

    std::vector<Masina> rezultat;
    std::copy_if(all.begin(), all.end(), std::back_inserter(rezultat),
        [producator](const Masina& m) { return strcmp(m.getProducator(), producator) == 0; });

    dimensiuneRezultat = static_cast<int>(rezultat.size());
    Masina* result = new Masina[dimensiuneRezultat];
    std::copy(rezultat.begin(), rezultat.end(), result);
    return result;
}

Masina* Service::filtreazaDupaTip(const char* tip, int& dimensiuneRezultat) const {
    const auto& all = this->repo.getAll();

    std::vector<Masina> rezultat;
    std::copy_if(all.begin(), all.end(), std::back_inserter(rezultat),
        [tip](const Masina& m) { return strcmp(m.getTip(), tip) == 0; });

    dimensiuneRezultat = static_cast<int>(rezultat.size());
    Masina* result = new Masina[dimensiuneRezultat];
    std::copy(rezultat.begin(), rezultat.end(), result);
    return result;
}

Masina* Service::filtreazaDupaModel(int model,int& dimensiuneRezultat) const {
    const auto& all = this->repo.getAll();

    std::vector<Masina> rezultat;
    std::copy_if(all.begin(), all.end(), std::back_inserter(rezultat),
        [model](const Masina& m) { return m.getModel() == model; });

    dimensiuneRezultat = static_cast<int>(rezultat.size());
    Masina* result = new Masina[dimensiuneRezultat];
    std::copy(rezultat.begin(), rezultat.end(), result);
    return result;
}

Masina* Service::sortMasini(const char* key, const bool reverse, int& dimensiuneRezultat) const {
    const auto& all = this->repo.getAll();
    dimensiuneRezultat = static_cast<int>(all.size());

    std::vector<Masina> rezultat(all.begin(), all.end());

    for (size_t i = 0; i < rezultat.size() - 1; ++i) {
        for (size_t j = i + 1; j < rezultat.size(); ++j) {

            int cmp = 0;

            if (strcmp(key, "nr") == 0) {
                cmp = strcmp(rezultat[i].getNr(), rezultat[j].getNr());
            }
            else if (strcmp(key, "tip") == 0) {
                cmp = strcmp(rezultat[i].getTip(), rezultat[j].getTip());
            }
            else if (strcmp(key, "producator") == 0 || strcmp(key, "model") == 0) {
                cmp = strcmp(rezultat[i].getProducator(), rezultat[j].getProducator());
                if (cmp == 0) {
                    cmp = rezultat[i].getModel() - rezultat[j].getModel();
                }
            }

            if ((!reverse && cmp > 0) || (reverse && cmp < 0)) {
                std::swap(rezultat[i], rezultat[j]);
            }
        }
    }

    Masina* result = new Masina[dimensiuneRezultat];
    std::copy(rezultat.begin(), rezultat.end(), result);
    return result;
}

void Service::addToWorkList(const char* nr) {
    const Masina& masina = repo.find(nr);
    workList.push_back(masina);
    notifyObservers();
}

void Service::clearWorkList() {
    workList.clear();
    notifyObservers();
}

void Service::generateWorkList(int count) {
    const auto& all = repo.getAll();
    std::vector<Masina> allMasini(all.begin(), all.end());

    std::shuffle(allMasini.begin(), allMasini.end(), std::mt19937(std::random_device()()));

    workList.clear();
    for (int i = 0; i < count && i < static_cast<int>(allMasini.size()); i++) {
        workList.push_back(allMasini[i]);
    }
    notifyObservers();
}

const std::vector<Masina>& Service::getWorkList() const {
    return workList;
}

void Service::undo() {
    if (undoStack.empty()) {
        throw std::runtime_error("Nu se mai poate face undo!");
    }
    undoStack.back()->doUndo();
    undoStack.pop_back();
}

bool Service::canUndo() const {
    return !undoStack.empty();
}

void Service::exportWorkList(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Eroare! Nu s-a putut deschide fisierul pentru export!");
    }
    // Write all cars in the WorkList to the CSV file
    for (const auto& masina : workList) {
        out << masina.getNr() << ","
            << masina.getProducator() << ","
            << masina.getModel() << ","
            << masina.getTip() << "\n";
    }
    out.close();
}