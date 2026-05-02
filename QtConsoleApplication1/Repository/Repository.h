//
// Created by raulg on 3/27/2026.
//

#ifndef LAB67_REPOSITORY_H
#define LAB67_REPOSITORY_H
#include "../Domain/Masina.h"

#include <vector>
#include "Repo.h"

class Repository : public Repo {
private:
    std::vector<Masina> elements;
public:
    Repository();
    ~Repository() override;

    void add(const Masina& element) override;
    [[nodiscard]] const std::vector<Masina>& getAll() const override;
    [[nodiscard]] size_t getSize() const override;
    void remove(const char* nr) override;
    void update(const char* nr , const Masina& NewMasina) override;
    const Masina& find(const char* nr) const override;
};


#endif //LAB67_REPOSITORY_H