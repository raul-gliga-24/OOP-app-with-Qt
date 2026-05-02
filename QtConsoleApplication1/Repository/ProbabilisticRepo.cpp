#include "ProbabilisticRepo.h"
#include <stdexcept>
#include <cstring>

ProbabilisticRepo::ProbabilisticRepo(double probability)
    : probability(probability), rng(random_device{}()), dist(0.0, 1.0) {
    using namespace std;
}

void ProbabilisticRepo::maybeThrow() const {
    if (dist(rng) < probability) {
        throw runtime_error("random failure");
    }
}

void ProbabilisticRepo::add(const Masina& element) {
    maybeThrow();
    string nr(element.getNr());
    if (elements.find(nr) != elements.end()) {
        throw runtime_error("Aceasta masina exista deja");
    }
    elements[nr] = element;
}

const vector<Masina>& ProbabilisticRepo::getAll() const {
    maybeThrow();
    cache.clear();
    for (const auto& pair : elements) {
        cache.push_back(pair.second);
    }
    return cache;
}

size_t ProbabilisticRepo::getSize() const {
    maybeThrow();
    return elements.size();
}

void ProbabilisticRepo::remove(const char* nr) {
    maybeThrow();
    string key(nr);
    auto it = elements.find(key);
    if (it != elements.end()) {
        elements.erase(it);
        return;
    }
    throw runtime_error("Masina cu numarul dat nu a putut fi stearsa");
}

void ProbabilisticRepo::update(const char* nr, const Masina& NewMasina) {
    maybeThrow();
    string key(nr);
    auto it = elements.find(key);
    if (it != elements.end()) {
        it->second = NewMasina;
        return;
    }
    throw runtime_error("Masina cu numarul dat nu a putut fi actualizata");
}

const Masina& ProbabilisticRepo::find(const char* nr) const {
    maybeThrow();
    string key(nr);
    auto it = elements.find(key);
    if (it != elements.end()) {
        return it->second;
    }
    throw runtime_error("Masina cu numarul dat nu a fost gasita");
}

