//
// Created by raulg on 3/27/2026.
//

#ifndef LAB67_UI_H
#define LAB67_UI_H



#include "../Service/Service.h"

class UI {
private:
    Service& srv;
    void add_ui() const;
    static void print_ui();
    void afiseaza_toate() const;

    static void afiseaza_masini(const Masina* masini, int size);
    void sterge_ui() const;
    void update_ui() const;
    void inchiriere_ui();
    void returneaza_ui();
    void add_default_masini();
    void filter_tip() const;
    void filter_model() const;
    void filter_prod() const;
    void sort_masini() const;
    void undo_ui();

    void worklist_menu();
    void add_to_worklist_ui();
    void clear_worklist_ui();
    void generate_worklist_ui();
    void afiseaza_worklist() const;

public:
    UI(Service& srv) : srv{srv}{}
    void run();
};


#endif //LAB67_UI_H

