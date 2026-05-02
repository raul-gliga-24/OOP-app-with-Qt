#include "TestFileRepo.h"
#include "../Repository/FileRepo.h"
#include <cassert>
#include <fstream>
#include <cstdio>
#include <cstring>

void test_file_repo_load_save() {
    const char* filename = "test_masini.csv";
    std::remove(filename);

    {
        FileRepo repo(filename);
        assert(repo.getSize() == 0);
        repo.add(Masina("CJ01ABC", "Test", 2020, "Test"));
        assert(repo.getSize() == 1);
    }

    {
        FileRepo repo2(filename);
        assert(repo2.getSize() == 1);
        assert(strcmp(repo2.getAll()[0].getNr(), "CJ01ABC") == 0);
        
        repo2.remove("CJ01ABC");
        assert(repo2.getSize() == 0);
    }

    {
        FileRepo repo3(filename);
        assert(repo3.getSize() == 0);
    }

    std::remove(filename);
}

void test_file_repo_invalid_file() {
    const char* filename = "invalid.csv";
    std::ofstream out(filename);
    out << "invalid,data,here\n";
    out << "CJ99ZZZ,Prod,2022,Tip\n";
    out.close();

    FileRepo repo(filename);
    assert(repo.getSize() == 1);
    assert(strcmp(repo.getAll()[0].getNr(), "CJ99ZZZ") == 0);

    std::remove(filename);
}

void test_file_repo_edge_cases() {
    const char* filename = "test_edges.csv";

    std::remove(filename);
    {
        FileRepo repo(filename);
        assert(repo.getSize() == 0);
    }
    {
        std::ofstream out(filename);
        out << "\n"; // Empty line
        out << "CJ01ABC,Dacia,2020\n"; // Too few attributes (3 < 4)
        out << "CJ02ABC,BMW,not_a_number,Sedan\n"; // stoi throws
        out << "CJ03ABC,Audi,2022,Coupe\n"; // Valid
        out << "CJ03ABC,Audi,2022,Coupe\n"; // Duplicate (add throws)
        out.close();

        FileRepo repo(filename);
        assert(repo.getSize() == 1);
        assert(strcmp(repo.getAll()[0].getNr(), "CJ03ABC") == 0);
    }
    std::remove(filename);
}

void test_file_repo_write_errors() {
    try {
        FileRepo repo("");
        repo.add(Masina("CJ01ABC", "Test", 2020, "Test"));
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(strstr(e.what(), "Eroare la deschiderea fisierului") != nullptr);
    }
}

void test_file_repo_update() {
    const char* filename = "test_update.csv";
    std::remove(filename);
    {
        FileRepo repo(filename);
        repo.add(Masina("CJ01ABC", "Test", 2020, "Test"));
    }
    {
        FileRepo repo(filename);
        repo.update("CJ01ABC", Masina("CJ01ABC", "Updated", 2021, "New"));
    }
    {
        FileRepo repo(filename);
        assert(repo.getSize() == 1);
        assert(strcmp(repo.getAll()[0].getProducator(), "Updated") == 0);
    }
    std::remove(filename);
}

void run_tests_file_repo() {
    test_file_repo_load_save();
    test_file_repo_invalid_file();
    test_file_repo_edge_cases();
    test_file_repo_write_errors();
    test_file_repo_update();
}
