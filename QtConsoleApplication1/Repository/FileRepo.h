//
// Created by raulg on 4/27/2026.
//

#ifndef LAB67_FILEREPO_H
#define LAB67_FILEREPO_H

#include "Repository.h"
#include <string>

class FileRepo : public Repository {
private:
    std::string filename;
    void load_from_file();

    void writeToFile() const;

public:


    explicit FileRepo(const std::string &filename);



    ~FileRepo() override;

    void add(const Masina& element) override;
    void remove(const char* nr) override;
    void update(const char* nr, const Masina& NewMasina) override;
};

#endif //LAB67_FILEREPO_H
