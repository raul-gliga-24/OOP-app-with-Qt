//
// Created by raulg on 3/27/2026.
//

#include "UI.h"
#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::string;

void UI::add_ui() const {
    char nr[100];
    char producator[100];
    int model;
    char tip[100];

    cout << "Introduceti numarul de inmatriculare: ";
    cin >> nr;
    cout << "Introduceti producatorul: ";
    cin >> producator;
    cout << "Introduceti modelul(anul): ";
    cin >> model;
    cout << "Introduceti tipul masinii: ";
    cin >> tip;

    try {

        this->srv.addMasina(nr, producator, model, tip);
        cout << "Masina adaugata cu succes!";

    } catch (std::exception& e) {
        cout << "Eroare la adaugare: " << e.what() << "\n";
    }
}

void UI::print_ui() {
    cout << "==MENIU==\n";
    cout << "1. Adauga masina\n";
    cout << "2. Sterge masina\n";
    cout << "3. Actualizare masina \n";
    cout << "4. Afiseaza toate masinile\n";
    cout << "5. Inchiriaza masina \n";
    cout << "6. Returneaza masina \n";
    cout << "7. Adauga masini default \n";
    cout << "8. Filtreaza dupa model\n";
    cout << "9. Filtreaza dupa producator\n";
    cout << "10. Filtreaza dupa tip\n";
    cout << "11. Sorteaza masini\n";
    cout << "12. Meniu WorkList\n";
    cout << "13. Undo\n";
    cout << "0. Iesire\n";
}

void UI::sterge_ui() const {
    char to_del[100];
    cout << "Introduceti numarul de inmatriculare pe care doriti sa il stergeti: ";
    cin >> to_del;
    try {
        srv.removeMasina(to_del);
        cout << "Masina stearsa cu succes\n";

    } catch (std::exception& e) {
        cout << "Eroare la stergere: " << e.what() << "\n";
    }
}

void UI::update_ui() const {
    char to_update[100];
    char nr[100];
    char producator[100];
    int model;
    char tip[100];
    cout << "Introduceti numarul de inmatriculare pe care doriti sa il actualizati: \n";
    cin >> to_update;

    cout << "Introduceti numarul de inmatriculare: \n";
    cin >> nr;
    cout << "Introduceti producatorul: \n";
    cin >> producator;
    cout << "Introduceti modelul(anul): \n";
    cin>>model;
    cout<<"Introduceti tipul";
    cin >> tip;
    Masina m(nr, producator, model, tip);
    try {
        srv.updateMasina(to_update, m);
        cout << "Masina actualizata cu succes\n";
    } catch (std::exception& e) {
        cout << "Eroare la actualizare: " << e.what() << "\n";
    }
}

void UI::inchiriere_ui() {
    char nr[100];
    cout << "Introduceti numarul de inmatriculare al masinii pe care doriti sa o inchiriati: ";
    cin >> nr;

    try {
        this->srv.inchiriazaMasina(nr);
        cout << "Masina a fost inchiriata cu succes!\n";
    } catch (std::exception& e) {
        cout << "Eroare la inchiriere: " << e.what() << "\n";
    }
}

void UI::returneaza_ui() {
    char nr[100];
    cout << "Introduceti numarul de inmatriculare al masinii pe care o returnati: ";
    cin >> nr;

    try {
        this->srv.returneazaMasina(nr);
        cout << "Masina a fost returnata cu succes! Multumim!\n";
    } catch (const std::exception& e) {
        cout << "Eroare la returnare: " << e.what() << "\n";
    }
}

void UI::add_default_masini() {
    try {
        this->srv.addMasina("CJ01ABC", "Dacia", 2021, "Sedan");
        this->srv.addMasina("CJ02ABC", "BMW", 2026, "SUV");
        this->srv.addMasina("ZZ99ZZZ", "Mercedes", 1980, "Coupe");
        cout << "Masini adaugate cu succes!\n";
    } catch (std::exception& e) {
        cout << "Eroare la adaugarea masinilor default: " << e.what() << "\n";
    }
}

void UI::afiseaza_toate() const {
    const auto& all = srv.getAllMasini();
    for (const auto& it : all) {
        const char *stare = it.getAvailability() ? "FREE" : "INCHIRIATA";
        cout<<"Nr inmatriculare: "<<it.getNr()<<"  | Producator: "<<it.getProducator()<<" | Model(an): "<<it.getModel()<<" | Tip: "<<it.getTip()<<" | Disponibilitate: "<<stare<<"\n";
    }
    if (all.empty())
        cout<<"Lista de masini goala!!\n";
}

void UI::afiseaza_masini(const Masina* masini, int size) {
    for (int i = 0; i < size; i++) {
        const Masina& it = masini[i];
        const char *stare = it.getAvailability() ? "FREE" : "INCHIRIATA";
        cout<<"Nr inmatriculare: "<<it.getNr()<<"  | Producator: "<<it.getProducator()<<" | Model(an): "<<it.getModel()<<" | Tip: "<<it.getTip()<<" | Disponibilitate: "<<stare<<"\n";
    }
    if (size == 0)
        cout<<"Lista de masini goala!!\n";
}

void UI::filter_model() const {
    int model;
    cout<<"Introduceti modelul(anul) dupa care doriti sa filtrati: ";
    cin>>model;
    int dimensiune;
    const Masina *rez = srv.filtreazaDupaModel(model, dimensiune);

    afiseaza_masini(rez, dimensiune);
    delete[] rez;
}

void UI::filter_prod() const {
    char producator[100];
    cout<<"Introduceti producatorul dupa care doriti sa filtrati: ";
    cin>>producator;
    int dimensiune;
    Masina *rez = srv.filtreazaDupaProducator(producator, dimensiune);

    afiseaza_masini(rez, dimensiune);
    delete[] rez;
}

void UI::filter_tip() const {
    char tip[100];
    cout<<"Introduceti tipul dupa care doriti sa filtrati: ";
    cin>>tip;
    int dimensiune;
    const Masina *rez = srv.filtreazaDupaTip(tip, dimensiune);

    afiseaza_masini(rez, dimensiune);
    delete[] rez;
}

void UI::sort_masini() const {
    char cheie[100];
    cout << "Introduceti cheia de sortare (nr, tip, producator, model): ";
    cin >> cheie;

    char ordine[100];
    cout << "Introduceti ordinea (crescator, descrescator): ";
    cin >> ordine;

    bool reverse = false;
    if (strcmp(ordine, "descrescator") == 0) {
        reverse = true;
    }

    int dimensiune;
    const Masina *rez = srv.sortMasini(cheie, reverse, dimensiune);

    afiseaza_masini(rez, dimensiune);
    delete[] rez;
}

void UI::worklist_menu() {
    int optiune;
    while (true) {
        afiseaza_worklist();
        cout << "1. Adauga masina in worklist\n";
        cout << "2. Goleste worklist\n";
        cout << "3. Genereaza worklist\n";
        cout << "0. Inapoi la meniul principal\n";
        cin >> optiune;

        if (optiune == 1) {
            add_to_worklist_ui();
        } else if (optiune == 2) {
            clear_worklist_ui();
        } else if (optiune == 3) {
            generate_worklist_ui();
        } else if (optiune == 0) {
            break;
        } else {
            cout << "Optiune invalida\n";
        }
    }
}

void UI::add_to_worklist_ui() {
    char nr[100];
    cout << "Introduceti numarul de inmatriculare: ";
    cin >> nr;
    try {
        srv.addToWorkList(nr);
        cout << "Masina adaugata in worklist!\n";
    } catch (std::exception& e) {
        cout << "Eroare: " << e.what() << "\n";
    }
}

void UI::clear_worklist_ui() {
    srv.clearWorkList();
    cout << "Worklist-ul a fost golit!\n";
}

void UI::generate_worklist_ui() {
    int count;
    cout << "Cate masini sa se genereze in worklist? ";
    cin >> count;
    srv.generateWorkList(count);
    cout << "Worklist generat!\n";
}

void UI::afiseaza_worklist() const {
    const auto& worklist = srv.getWorkList();
    cout << "\n=== WORKLIST ===\n";
    if (worklist.empty()) {
        cout << "Worklist-ul este gol!\n";
    } else {
        cout << "Masini in worklist (" << worklist.size() << "):\n";
        for (const auto& masina : worklist) {
            const char *stare = masina.getAvailability() ? "FREE" : "INCHIRIATA";
            cout << "Nr inmatriculare: " << masina.getNr()
                 << "  | Producator: " << masina.getProducator()
                 << " | Model(an): " << masina.getModel()
                 << " | Tip: " << masina.getTip()
                 << " | Disponibilitate: " << stare << "\n";
        }
    }
    cout << "================\n";
}

void UI::undo_ui() {
    try {
        srv.undo();
        cout << "Undo realizat cu succes!\n";
    } catch (const std::exception& e) {
        cout << e.what() << "\n";
    }
}

void UI::run() {
    int optiune;
    while (true) {
        afiseaza_worklist();
        print_ui();
        cin>>optiune;
        
        if (optiune==1) {
            add_ui();
        }
        else if (optiune == 2) {
            sterge_ui();
        }
        else if (optiune == 3) {
            update_ui();
        }
        else if (optiune == 4) {
            afiseaza_toate();
        }
        else if (optiune == 5) {
            inchiriere_ui();
        }
        else if (optiune == 6) {
            returneaza_ui();
        }
        else if (optiune == 7) {
            add_default_masini();
        }
        else if (optiune == 8) {
            filter_model();
        }
        else if (optiune == 9) {
            filter_prod();
        }
        else if (optiune == 10) {
            filter_tip();
        }
        else if (optiune == 11) {
            sort_masini();
        }
        else if (optiune == 12) {
            worklist_menu();
        }
        else if (optiune == 13) {
            undo_ui();
        }
        else if (optiune == 0) {
            break;
        }
        else {
            cout<<"Optiune invalida\n";
            continue;
        }
        
    }
}
