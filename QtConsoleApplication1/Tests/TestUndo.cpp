#include "TestUndo.h"
#include "../Service/Service.h"
#include "../Repository/Repository.h"
#include "../Domain/Validator.h"
#include <cassert>
#include <stdexcept>
#include <cstring>

void test_undo_add() {
    Repository repo;
    MasinaValidator val;
    Service srv(repo, val);

    srv.addMasina("CJ01ABC", "Prod", 2020, "Tip");
    assert(srv.getSize() == 1);

    srv.undo();
    assert(srv.getSize() == 0);
}

void test_undo_remove() {
    Repository repo;
    MasinaValidator val;
    Service srv(repo, val);

    srv.addMasina("CJ01ABC", "Prod", 2020, "Tip");
    srv.removeMasina("CJ01ABC");
    assert(srv.getSize() == 0);

    srv.undo();
    assert(srv.getSize() == 1);
    assert(strcmp(srv.getAllMasini()[0].getNr(), "CJ01ABC") == 0);
}

void test_undo_update() {
    Repository repo;
    MasinaValidator val;
    Service srv(repo, val);

    srv.addMasina("CJ01ABC", "Prod", 2020, "Tip");
    srv.updateMasina("CJ01ABC", Masina("CJ01ABC", "New", 2021, "New"));
    assert(strcmp(srv.getAllMasini()[0].getProducator(), "New") == 0);

    srv.undo();
    assert(strcmp(srv.getAllMasini()[0].getProducator(), "Prod") == 0);
}

void test_undo_exception() {
    Repository repo;
    MasinaValidator val;
    Service srv(repo, val);

    try {
        srv.undo();
        assert(false);
    } catch (const std::runtime_error&) {
        assert(true);
    }
}

void run_tests_undo() {
    test_undo_add();
    test_undo_remove();
    test_undo_update();
    test_undo_exception();
}
