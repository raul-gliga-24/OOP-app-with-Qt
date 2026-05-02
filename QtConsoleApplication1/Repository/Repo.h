#ifndef LAB67_REPO_H
#define LAB67_REPO_H
#include "../Domain/Masina.h"
#include <vector>
#include <cstddef>

class Repo {
public:
    virtual ~Repo() = default;
    virtual void add(const Masina& element) = 0;
    virtual const std::vector<Masina>& getAll() const = 0;
    virtual size_t getSize() const = 0;
    virtual void remove(const char* nr) = 0;
    virtual void update(const char* nr, const Masina& NewMasina) = 0;
    virtual const Masina& find(const char* nr) const = 0;
};

#endif //LAB67_REPO_H

