//
// Created by raulg on 3/28/2026.
//

#include "TestService.h"
#include "../Domain/Validator.h"
#include "../Domain/Masina.h"
#include "../Repository/Repository.h"
#include "../Service/Service.h"
#include <cassert>
#include <cstring>
void populate_service(Service& srv) {
    srv.addMasina("CJ01ABC", "Dacia", 2021, "Sedan");
    srv.addMasina("CJ02ABC", "BMW", 2026, "SUV");
    srv.addMasina("ZZ99ZZZ", "Audi", 1990, "Coupe");
}

void test_add_srv() {
    MasinaValidator val;
    Repository repo;
    Service srv(repo,val);
    populate_service(srv);

    assert(srv.getSize() == 3);

    srv.addMasina("B111AAA", "Mercedes", 2024, "Sedan");
    assert(srv.getSize() == 4);

}

void test_remove_srv() {
    MasinaValidator val;
    Repository repo;
    Service srv(repo,val);
    populate_service(srv);

    assert(srv.getSize() == 3);

    srv.removeMasina("CJ01ABC");

    assert(srv.getSize() == 2);

    try {
        srv.removeMasina("ZZ999ZZZ");
        assert(false);
    }catch (std::runtime_error&) {
        assert(true);
    }
}

void test_update_srv() {
    MasinaValidator val;
    Repository repo;
    Service srv(repo,val);
    populate_service(srv);
    const Masina m5("ZZ999ZZZ","Mercedes",2026,"Convertible");
    srv.updateMasina("CJ01ABC",m5);
    assert(strcmp(srv.getAllMasini()[0].getNr(), "ZZ999ZZZ") == 0);
    assert(srv.getAllMasini()[0].getModel()==2026);
    assert(strcmp(srv.getAllMasini()[0].getProducator(), "Mercedes") == 0);
    assert(strcmp(srv.getAllMasini()[0].getTip(), "Convertible") == 0);

    try {
        srv.updateMasina("NONEXISTENT", m5);
        assert(false);
    } catch (std::runtime_error&) {
        assert(true);
    }
}

void test_rent_return_srv() {
    MasinaValidator val;
    Repository repo;
    Service srv(repo, val);
    populate_service(srv);

    srv.inchiriazaMasina("CJ01ABC");
    assert(srv.getAllMasini()[0].getAvailability() == false);

    try {
        srv.inchiriazaMasina("CJ01ABC");
        assert(false);
    } catch (std::runtime_error&) {
       assert(true);
    }
    srv.returneazaMasina("CJ01ABC");
    assert(srv.getAllMasini()[0].getAvailability() == true);
    try {
        srv.returneazaMasina("CJ01ABC");
        assert(false);
    } catch (std::runtime_error&) {
        assert(true);
    }
    try {
        srv.inchiriazaMasina("NONEXISTENT");
        assert(false);
    } catch (std::runtime_error&) {
        assert(true);
    }

    try {
        srv.returneazaMasina("NONEXISTENT");
        assert(false);
    } catch (std::runtime_error& ) {
        assert(true);
    }
}

void test_add_invalid_srv() {
    MasinaValidator val;
    Repository repo;
    Service srv(repo, val);

    try {
        srv.addMasina("", "", 0, "");
        assert(false);
    } catch (ValidationError&) {
        assert(true);
    }

    srv.addMasina("CJ01ABC", "Dacia", 2021, "Sedan");
    try {
        srv.addMasina("CJ01ABC", "BMW", 2022, "SUV");
        assert(false);
    } catch (std::runtime_error&) {
        assert(true);
    }
}

void test_filtru_producator() {
    MasinaValidator val;
    Repository repo;
    Service srv(repo,val);
    populate_service(srv);
    assert(srv.getSize()==3);
    int len=0;
    const Masina* rez = srv.filtreazaDupaProducator("Dacia",len);
    assert(rez->getModel()==2021);
    assert(strcmp(rez->getNr(),"CJ01ABC")==0);

    delete[] rez;


}
void test_filtru_model() {
    MasinaValidator val;
    Repository repo;
    Service srv(repo,val);
    populate_service(srv);
    assert(srv.getSize()==3);
    int len=0;
    const Masina *rez = srv.filtreazaDupaModel(2021,len);
    assert(strcmp(rez->getNr(),"CJ01ABC")==0);
    assert(strcmp(rez->getProducator(),"Dacia")==0);

    delete[] rez;

}

void test_filtru_tip() {
    MasinaValidator val;
    Repository repo;
    Service srv(repo,val);
    populate_service(srv);
    assert(srv.getSize()==3);
    int len=0;
    const Masina* rez = srv.filtreazaDupaTip("Sedan",len);
    assert(strcmp(rez->getNr(),"CJ01ABC")==0);
    assert(strcmp(rez->getProducator(),"Dacia")==0);
    delete[] rez;
}

void test_sort() {

    MasinaValidator val;
    Repository repo;
    Service srv(repo,val);
    populate_service(srv);
    // Masinile adaugate:
    // "CJ01ABC", "Dacia", 2021, "Sedan"
    // "CJ02ABC", "BMW", 2026, "SUV"
    // "ZZ99ZZZ", "Audi", 1990, "Coupe"

    int len=0;

    const Masina* rez = srv.sortMasini("nr",false,len);
    assert(strcmp(rez[0].getNr(),"CJ01ABC")==0);
    assert(strcmp(rez[1].getNr(),"CJ02ABC")==0);
    assert(strcmp(rez[2].getNr(),"ZZ99ZZZ")==0);
    delete[] rez;

    const Masina* rez2 = srv.sortMasini("nr",true,len);
    assert(strcmp(rez2[0].getNr(),"ZZ99ZZZ")==0);
    assert(strcmp(rez2[1].getNr(),"CJ02ABC")==0);
    assert(strcmp(rez2[2].getNr(),"CJ01ABC")==0);
    delete[] rez2;

    const Masina* rez3 = srv.sortMasini("tip",false,len);
    // tip: Coupe, SUV, Sedan
    assert(strcmp(rez3[0].getNr(),"ZZ99ZZZ")==0);
    assert(strcmp(rez3[1].getNr(),"CJ02ABC")==0);
    assert(strcmp(rez3[2].getNr(),"CJ01ABC")==0);
    delete[] rez3;

    const Masina* rez4 = srv.sortMasini("tip",true,len);
    assert(strcmp(rez4[0].getNr(),"CJ01ABC")==0);
    assert(strcmp(rez4[1].getNr(),"CJ02ABC")==0);
    assert(strcmp(rez4[2].getNr(),"ZZ99ZZZ")==0);
    delete[] rez4;

    const Masina* rez5 = srv.sortMasini("producator",false,len);
    // producator: Audi, BMW, Dacia
    assert(strcmp(rez5[0].getNr(),"ZZ99ZZZ")==0);
    assert(strcmp(rez5[1].getNr(),"CJ02ABC")==0);
    assert(strcmp(rez5[2].getNr(),"CJ01ABC")==0);
    delete[] rez5;

    const Masina* rez6 = srv.sortMasini("model",true,len);
    // model producator reverse: Dacia, BMW, Audi
    assert(strcmp(rez6[0].getNr(),"CJ01ABC")==0);
    assert(strcmp(rez6[1].getNr(),"CJ02ABC")==0);
    assert(strcmp(rez6[2].getNr(),"ZZ99ZZZ")==0);
    delete[] rez6;

    srv.addMasina("AA01AAA", "Audi", 1980, "Sedan");
    const Masina* rez7 = srv.sortMasini("producator",false,len);
    // Audi (1980), Audi (1990), BMW (2026), Dacia (2021)
    assert(strcmp(rez7[0].getNr(),"AA01AAA")==0);
    assert(strcmp(rez7[1].getNr(),"ZZ99ZZZ")==0);
    assert(strcmp(rez7[2].getNr(),"CJ02ABC")==0);
    assert(strcmp(rez7[3].getNr(),"CJ01ABC")==0);
    delete[] rez7;

    const Masina* rez8 = srv.sortMasini("producator",true,len);
    // Dacia (2021), BMW (2026), Audi (1990), Audi (1980)
    assert(strcmp(rez8[0].getNr(),"CJ01ABC")==0);
    assert(strcmp(rez8[1].getNr(),"CJ02ABC")==0);
    assert(strcmp(rez8[2].getNr(),"ZZ99ZZZ")==0);
    assert(strcmp(rez8[3].getNr(),"AA01AAA")==0);
    delete[] rez8;
}


void run_service_tests() {
    test_add_srv();
    test_remove_srv();
    test_update_srv();
    test_rent_return_srv();
    test_add_invalid_srv();
    test_filtru_producator();
    test_filtru_model();
    test_filtru_tip();
    test_sort();
}
