//
// Created by raulg on 3/28/2026.
//

#include "TestValidator.h"
#include "../Domain/Masina.h"
#include <cassert>

#include "../Domain/Validator.h"

void test_validator() {
    MasinaValidator val;
    const Masina m_val("CJ01ABC","Dacia",2021,"Sedan");
    try {
        val.validator(m_val);
        assert(true);

    }catch (ValidationError&) {
        assert(false);
    }

    const Masina m_inval("","Dacia",2021,"Sedan");
    try {
        val.validator(m_inval);
        assert(false);

    }catch (ValidationError&) {
        assert(true);
    }

    const Masina m_inval2("CJ01ABC","",2021,"Sedan");
    try {
        val.validator(m_inval2);
        assert(false);

    }catch (ValidationError&) {
        assert(true);
    }

    const Masina m_inval3("CJ01ABC","Dacia",2027,"Sedan");
    try {
        val.validator(m_inval3);
        assert(false);

    }catch (ValidationError&) {
        assert(true);
    }

    const Masina m_inval4("CJ01ABC","Dacia",1899,"Sedan");
    try {
        val.validator(m_inval4);
        assert(false);
    } catch (ValidationError&) {
        assert(true);
    }

    const Masina m_inval5("CJ01ABC", "Dacia", 2021, "Sedan");
    const Masina m_inval6("CJ1ABC", "Dacia", 2021, "Sedan");
    try {
        val.validator(m_inval6);
        assert(false);
    } catch (ValidationError&) {
        assert(true);
    }

    const Masina m_inval7("CJ1234ABC", "Dacia", 2021, "Sedan");
    try {
        val.validator(m_inval7);
        assert(false);
    } catch (ValidationError&) {
        assert(true);
    }

    const Masina m_inval8("CJ01ABC", "Dacia", 2021, "");
    try {
        val.validator(m_inval8);
        assert(false);
    } catch (ValidationError&) {
        assert(true);
    }
}

void run_validator_tests() {
    test_validator();
}
