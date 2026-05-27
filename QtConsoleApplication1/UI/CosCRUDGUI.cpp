#include "CosCRUDGUI.h"
#include <QMessageBox>

CosCRUDGUI::CosCRUDGUI(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    model = new WorkListModel(service.getWorkList(), this);
    tableView = new QTableView();
    tableView->setModel(model);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(tableView);

    QHBoxLayout* bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(new QLabel("Nr masini:"));
    countInput = new QLineEdit();
    bottomLayout->addWidget(countInput);

    btnGenerate = new QPushButton("Generate");
    bottomLayout->addWidget(btnGenerate);

    btnClear = new QPushButton("Clear");
    bottomLayout->addWidget(btnClear);
    bottomLayout->addStretch();

    mainLayout->addLayout(bottomLayout);

    connect(btnClear, &QPushButton::clicked, this, &CosCRUDGUI::onClearClicked);
    connect(btnGenerate, &QPushButton::clicked, this, &CosCRUDGUI::onGenerateClicked);

    service.addObserver(this);
}

CosCRUDGUI::~CosCRUDGUI() {
    service.removeObserver(this);
}

void CosCRUDGUI::update() {
    model->refresh();
}

void CosCRUDGUI::onClearClicked() {
    service.clearWorkList();
}

void CosCRUDGUI::onGenerateClicked() {
    bool ok;
    int count = countInput->text().toInt(&ok);
    if (!ok || count <= 0) {
        QMessageBox::warning(this, "Input Error", "Introduce-ti un nr pozitiv!");
        return;
    }
    try {
        service.generateWorkList(count);
        countInput->clear();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}