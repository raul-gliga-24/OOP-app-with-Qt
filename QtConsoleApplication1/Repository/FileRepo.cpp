//
// Created by raulg on 4/27/2026.
//

#include "FileRepo.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>


static std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

void FileRepo::load_from_file() {
    std::ifstream in(this->filename);

    if (! in.is_open()) {
        return;
    }

    std::string line;
    int lineCount = 0;
    (void) lineCount;

    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        std::vector<std::string> attribute;
        std::stringstream ss(line);
        std::string token;

        while (std::getline(ss, token, ',')) {
            attribute.push_back(trim(token));
        }


        if (attribute.size() >= 4) {
            try {
                Masina m(attribute[0].c_str(), attribute[1].c_str(), std::stoi(attribute[2]), attribute[3].c_str());
                Repository::add(m);
            } catch (const std::invalid_argument&) {
            } catch (std::runtime_error) {
            }
        }
    }

    in.close();
}

FileRepo::FileRepo(const std::string& filename) : Repository(),filename{filename} {
    this->load_from_file();
}

FileRepo::~FileRepo() = default;

void FileRepo::writeToFile() const {
    std::ofstream out(this->filename);

    if (!out.is_open()) {
        throw std::runtime_error("Eroare la deschiderea fisierului pentru scriere: " + this->filename);
    }

    const auto& masini = this->getAll();
    for (const auto& m : masini) {
        out << m.getNr() << ","
            << m.getProducator() << ","
            << m.getModel() << ","
            << m.getTip() << "\n";
    }

    out.close();
}

void FileRepo::add(const Masina &element) {
    Repository::add(element);
    this->writeToFile();
}

void FileRepo::remove(const char *nr) {
    Repository::remove(nr);
    this->writeToFile();
}

void FileRepo::update(const char *nr, const Masina &NewMasina) {
    Repository::update(nr, NewMasina);
    this->writeToFile();
}

