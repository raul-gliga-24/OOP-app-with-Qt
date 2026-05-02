//
// Created by raulg on 3/26/2026.
//

#ifndef LAB67_MASINA_H
#define LAB67_MASINA_H

class Masina {
private:
    char* nrInmatriculare;
    char* producator;
    int model;
    char* tip;
    bool available;
public:
    Masina();
    Masina(const char* nr, const char* prod, int mod, const char* tip);
    Masina(const Masina& other);
    Masina& operator=(const Masina& other);
    Masina(Masina&& other) noexcept;
    Masina& operator=(Masina&& other) noexcept;
    const char* getNr() const;
    const char* getProducator() const;
    int getModel() const;
    const char* getTip() const;
    bool getAvailability() const;
    void setAvailability(bool status);

    ~Masina();
};

#endif //LAB67_MASINA_H
