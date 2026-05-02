//
// Created by raulg on 3/28/2026.
//

#include "TestDomain.h"
#include "../Domain/Masina.h"
#include <cassert>
#include <cstring>

void test_getters() {
    const Masina m("CJ01ABC","BMW",2025,"Sedan");
    assert(m.getModel()==2025);
    assert(strcmp(m.getNr(),"CJ01ABC")==0);
    assert(strcmp(m.getProducator(),"BMW")==0);
    assert(strcmp(m.getTip(),"Sedan")==0);
    assert(m.getAvailability()==true);
}

void test_default_constructor() {
    const Masina m;
    assert(m.getNr() == nullptr);
    assert(m.getTip() == nullptr);
    assert(m.getModel() == 0);
    assert(m.getAvailability() == true);
}

void test_copy_constructor() {
    const Masina m1("CJ01ABC", "BMW", 2025, "Sedan");
    const Masina& m2 = m1;
    assert(strcmp(m2.getNr(),"CJ01ABC")==0);
    assert(strcmp(m2.getProducator(),"BMW")==0);
    assert(strcmp(m2.getTip(),"Sedan")==0);
    assert(m2.getModel() == 2025);
    (void) m2;
}

void test_assignment_operator() {
    const Masina m1("CJ01ABC", "BMW", 2025, "Sedan");
    const Masina& m2 = m1;
    assert(strcmp(m2.getNr(),"CJ01ABC")==0);
    assert(strcmp(m2.getProducator(),"BMW")==0);
    assert(strcmp(m2.getTip(),"Sedan")==0);
    assert(m2.getModel() == 2025);
    (void) m2;
}

void test_set_availability() {
    Masina m("CJ01ABC", "BMW", 2025, "Sedan");
    assert(m.getAvailability() == true);
    m.setAvailability(false);
    assert(m.getAvailability() == false);
    m.setAvailability(true);
    assert(m.getAvailability() == true);
}

void run_tests_domain() {
    test_default_constructor();
    test_getters();
    test_copy_constructor();
    test_assignment_operator();
    test_set_availability();
}
