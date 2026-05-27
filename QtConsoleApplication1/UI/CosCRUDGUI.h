#ifndef COSCRUDGUI_H
#define COSCRUDGUI_H
#define QT_NO_DEPRECATED_WARNINGS
#include <QWidget>
#include <QTableView>
#include <QHeaderView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include "../Service/Observer.h"
#include "../Service/Service.h"
#include "WorkListModel.h"

class CosCRUDGUI : public QWidget, public Observer {
    Q_OBJECT
public:
    explicit CosCRUDGUI(Service& service, QWidget* parent = nullptr);
    ~CosCRUDGUI();
    void update() override;

private slots:
    void onClearClicked();
    void onGenerateClicked();

private:
    Service& service;
    QTableView* tableView;
    WorkListModel* model;
    QLineEdit* countInput;
    QPushButton* btnClear;
    QPushButton* btnGenerate;
};

#endif // COSCRUDGUI_H