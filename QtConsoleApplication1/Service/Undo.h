#ifndef LAB67_UNDO_H
#define LAB67_UNDO_H

#include "../Domain/Masina.h"
#include "../Repository/Repo.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
    Masina masinaAdaugata;
    Repo& repo;
public:
    UndoAdauga(Repo& repo, const Masina& m) : masinaAdaugata{m}, repo{repo} {}
    void doUndo() override {
        repo.remove(masinaAdaugata.getNr());
    }
};

class UndoSterge : public ActiuneUndo {
private:
    Masina masinaStearsa;
    Repo& repo;
public:
    UndoSterge(Repo& repo, const Masina& m) : masinaStearsa{m}, repo{repo} {}
    void doUndo() override {
        repo.add(masinaStearsa);
    }
};

class UndoModifica : public ActiuneUndo {
private:
    Masina masinaVeche;
    Masina masinaNoua;
    Repo& repo;
public:
    UndoModifica(Repo& repo, const Masina& veche, const Masina& noua)
        : masinaVeche{veche}, masinaNoua{noua}, repo{repo} {}
    void doUndo() override {
        repo.update(masinaNoua.getNr(), masinaVeche);
    }
};

#endif //LAB67_UNDO_H
