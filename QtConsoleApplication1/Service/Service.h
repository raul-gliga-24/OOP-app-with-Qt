//
// Created by raulg on 3/27/2026.
//

#ifndef LAB67_SERVICE_H
#define LAB67_SERVICE_H
#include "../Domain/Validator.h"
#include "../Repository/Repo.h"
#include "Undo.h"
#include <string>
#include <vector>
#include <memory>

class Service {
private:
    Repo& repo;
    MasinaValidator& val;
    std::vector<Masina> workList;
    std::vector<std::unique_ptr<ActiuneUndo>> undoStack;
public:
    Service(Repo& repo, MasinaValidator& val) : repo{repo}, val{val}{}

    void addMasina(const char *nr, const char *producator, int model, const char *tip);

    [[nodiscard]] const std::vector<Masina>& getAllMasini() const;
    [[nodiscard]] unsigned long long getSize() const;
    void removeMasina(const char *nr);
    void updateMasina(const char *nr, const Masina &NewMasina);
    void inchiriazaMasina(const char *nr);
    void returneazaMasina(const char *nr);

    void exportWorkList(const std::string& filename) const;

    Masina *filtreazaDupaProducator(const char *producator, int &dimensiuneRezultat) const;

    Masina *filtreazaDupaTip(const char *tip, int &dimensiuneRezultat) const;

    Masina *filtreazaDupaModel(int model, int &dimensiuneRezultat) const;

    Masina *sortMasini(const char *key, bool reverse, int &dimensiuneRezultat) const;

    void addToWorkList(const char* nr);
    void clearWorkList();
    void generateWorkList(int count);
    [[nodiscard]] const std::vector<Masina>& getWorkList() const;

    void undo();
    bool canUndo() const;
};


#endif //LAB67_SERVICE_H
