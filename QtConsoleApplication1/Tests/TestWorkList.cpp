//
// Created by raulg on 4/28/2026.
//

#include "TestWorkList.h"
#include "../Service/Service.h"
#include "../Repository/Repository.h"
#include "../Domain/Validator.h"
#include <cassert>
#include <cstring>

void test_add_to_worklist() {
    Repository repo;
    MasinaValidator val;
    Service srv(repo, val);

    srv.addMasina("CJ01ABC", "Dacia", 2021, "Sedan");
    srv.addMasina("CJ02ABC", "BMW", 2025, "SUV");

    assert(srv.getWorkList().empty());

    srv.addToWorkList("CJ01ABC");
    assert(srv.getWorkList().size() == 1);
    assert(strcmp(srv.getWorkList()[0].getNr(), "CJ01ABC") == 0);

    srv.addToWorkList("CJ02ABC");
    assert(srv.getWorkList().size() == 2);
    assert(strcmp(srv.getWorkList()[1].getNr(), "CJ02ABC") == 0);

    try {
        srv.addToWorkList("CJ99ZZZ");
        assert(false);
    } catch (const std::runtime_error&) {
        assert(true);
    }
}

void test_clear_worklist() {
    Repository repo;
    MasinaValidator val;
    Service srv(repo, val);

    srv.addMasina("CJ01ABC", "Dacia", 2021, "Sedan");
    srv.addToWorkList("CJ01ABC");
    assert(srv.getWorkList().size() == 1);

    srv.clearWorkList();
    assert(srv.getWorkList().empty());
}

void test_generate_worklist() {
    Repository repo;
    MasinaValidator val;
    Service srv(repo, val);

    srv.addMasina("CJ01ABC", "Dacia", 2021, "Sedan");
    srv.addMasina("CJ02ABC", "BMW", 2025, "SUV");
    srv.addMasina("ZZ99ZZZ", "Mercedes", 1980, "Coupe");

    srv.generateWorkList(2);
    assert(srv.getWorkList().size() == 2);

    srv.generateWorkList(10);
    assert(srv.getWorkList().size() == 3);

    srv.clearWorkList();
    srv.generateWorkList(0);
    assert(srv.getWorkList().empty());
}

void run_tests_worklist() {
    test_add_to_worklist();
    test_clear_worklist();
    test_generate_worklist();
}
