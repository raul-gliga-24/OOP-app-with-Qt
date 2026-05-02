//
// Created by raulg on 3/28/2026.
//

#include "TestRepository.h"
#include <cassert>
#include <cstring>
#include "../Repository/Repository.h"
#include "../Domain/Masina.h"
#include <stdexcept>
Repository setup_test_repo() {
    Repository repo;
    repo.add(Masina("CJ01ABC", "Dacia", 2021, "Sedan"));
    repo.add(Masina("CJ02ABC", "BMW", 2025, "SUV"));
    repo.add(Masina("B99ZZZ", "Audi", 2020, "Coupe"));
    return repo;
}
void test_add() {

    const Masina m1("CJ01ABC","Dacia",2021,"Sedan");
    const Masina m2("CJ02ABC","BMW",2025,"SUV");
    Repository repo;
    assert(repo.getSize()==0);
    repo.add(m1);
    assert(repo.getSize()==1);

    assert(strcmp(repo.getAll()[0].getNr(), "CJ01ABC") == 0);
    assert(strcmp(repo.getAll()[0].getProducator(), "Dacia") == 0);
    assert(strcmp(repo.getAll()[0].getTip(), "Sedan") == 0);
    assert(repo.getAll()[0].getModel()==2021);

    repo.add(m2);

    assert(repo.getSize()==2);

    assert(strcmp(repo.getAll()[1].getNr(), "CJ02ABC") == 0);
    assert(strcmp(repo.getAll()[1].getProducator(), "BMW") == 0);
    assert(strcmp(repo.getAll()[1].getTip(), "SUV") == 0);
    assert(repo.getAll()[1].getModel()==2025);


}

void test_remove() {
    const Masina m1("CJ01ABC","Dacia",2021,"Sedan");
    const Masina m2("CJ02ABC","BMW",2025,"SUV");
    Repository repo;

    repo.add(m1);
    repo.add(m2);
    assert(repo.getSize()==2);

    repo.remove("CJ01ABC");
    assert(repo.getSize()==1);

   try {
       repo.remove("AB11ABC");
       assert(false);


   }catch (std::runtime_error&) {

       assert(true);
   }

    repo.remove("CJ02ABC");
    assert(repo.getSize()==0);

}

void test_update() {
    Repository repo = setup_test_repo();
    const Masina m4("CJ99ZZZ","BMW",2026,"SUV");
    repo.update("CJ01ABC",m4);
    assert(strcmp(repo.getAll()[0].getNr(), "CJ99ZZZ") == 0);
    assert(strcmp(repo.getAll()[0].getProducator(), "BMW") == 0);
    assert(strcmp(repo.getAll()[0].getTip(), "SUV") == 0);
    assert(repo.getAll()[0].getModel()==2026);
    
    try {
        repo.update("AB99ZZZ",m4);
        assert(false);
    }catch (std::runtime_error&) {
        assert(true);
    }
    
}

void test_find() {
    Repository repo = setup_test_repo();
    const Masina& found = repo.find("CJ01ABC");
    assert(strcmp(found.getProducator(), "Dacia") == 0);
    assert(strcmp(found.getTip(), "Sedan") == 0);
    assert(found.getModel()==2021);
    (void) found;

    try {
        (void)repo.find("IMPOSIBIL");
        assert(false);
    }catch (std::runtime_error&) {
        assert(true);
    }

}

void test_add_duplicate() {
    Repository repo = setup_test_repo();
    const Masina m5("CJ01ABC","BMW",2025,"SUV");
    try {
        repo.add(m5);
        assert(false);
    }catch (std::runtime_error&) {
        assert(true);
    }
}

void test_copy_constructor_and_assignment() {
    const Repository repo = setup_test_repo();

    Repository repo2(repo);
    assert(repo2.getSize() == 3);
    assert(strcmp(repo2.getAll()[0].getNr(), "CJ01ABC") == 0);

    repo2.remove("CJ01ABC");
    assert(repo2.getSize() == 2);
    assert(repo.getSize() == 3);

    Repository repo3;
    repo3.add(Masina("TEMP123", "Temp", 2000, "Sedan"));
    assert(repo3.getSize() == 1);

    repo3 = repo;
    assert(repo3.getSize() == 3);
    assert(strcmp(repo3.getAll()[0].getNr(), "CJ01ABC") == 0);

    repo3.remove("CJ02ABC");
    assert(repo3.getSize() == 2);
    assert(repo.getSize() == 3);

}

void run_tests_repository() {
    test_add();
    test_remove();
    test_update();
    test_find();
    test_add_duplicate();
    test_copy_constructor_and_assignment();
}
