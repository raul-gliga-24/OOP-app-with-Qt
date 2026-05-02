#ifndef LAB67_PROBABILISTICREPO_H
#define LAB67_PROBABILISTICREPO_H
#include "Repo.h"
#include <unordered_map>
#include <random>
#include <string>

using namespace std;

class ProbabilisticRepo : public Repo {
private:
    unordered_map<string, Masina> elements;
    double probability;
    mutable default_random_engine rng;
    mutable uniform_real_distribution<double> dist;
    void maybeThrow() const;
public:
    explicit ProbabilisticRepo(double probability);
    void add(const Masina& element) override;
    [[nodiscard]] const vector<Masina>& getAll() const override;
    [[nodiscard]] size_t getSize() const override;
    void remove(const char* nr) override;
    void update(const char* nr, const Masina& NewMasina) override;
    const Masina& find(const char* nr) const override;
    ~ProbabilisticRepo() override = default;
private:
    mutable vector<Masina> cache; // for getAll
};

#endif //LAB67_PROBABILISTICREPO_H

