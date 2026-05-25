#include "WorkListWindow.h"
#include "../Service/Service.h"
#include <QMessageBox>

WorkListWindow::WorkListWindow(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {

    setWindowTitle("Work List");
    setGeometry(100, 100, 600, 400);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* inputLayout = new QHBoxLayout();

    inputLayout->addWidget(new QLabel("NR:"));
    nrInput = new QLineEdit();
    inputLayout->addWidget(nrInput);

    btnAdd = new QPushButton("Adauga la lista ");
    inputLayout->addWidget(btnAdd);

    mainLayout->addLayout(inputLayout);

    // Create list widget
    mainLayout->addWidget(new QLabel("Work List:"));
    workListWidget = new QListWidget();
    mainLayout->addWidget(workListWidget);

    // Create generate section
    QHBoxLayout* generateLayout = new QHBoxLayout();

    generateLayout->addWidget(new QLabel("Nr de masini:"));
    countInput = new QLineEdit();
    countInput->setMaximumWidth(100);
    generateLayout->addWidget(countInput);

    btnGenerate = new QPushButton("Generate Random");
    generateLayout->addWidget(btnGenerate);

    generateLayout->addStretch();

    mainLayout->addLayout(generateLayout);

    btnClear = new QPushButton("Clear List");
    mainLayout->addWidget(btnClear);

    btnExport = new QPushButton("Export");
    mainLayout->addWidget(btnExport);
    connect(btnExport, &QPushButton::clicked, this, &WorkListWindow::onExportClicked);

    connect(btnAdd, &QPushButton::clicked, this, &WorkListWindow::onAddClicked);
    connect(btnClear, &QPushButton::clicked, this, &WorkListWindow::onClearClicked);
    connect(btnGenerate, &QPushButton::clicked, this, &WorkListWindow::onGenerateClicked);

    refreshList();
}

void WorkListWindow::onAddClicked() {
    QString carNumber = nrInput->text().trimmed();

    if (carNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a car number");
        return;
    }

    try {
        service.addToWorkList(carNumber.toStdString().c_str());
        nrInput->clear();
        refreshList();
        QMessageBox::information(this, "Success", "Car added to work list");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to add car: %1").arg(e.what()));
    }
}

void WorkListWindow::onClearClicked() {
    service.clearWorkList();
    refreshList();
    QMessageBox::information(this, "Success", "Work list cleared");
}

void WorkListWindow::onGenerateClicked() {
    QString countStr = countInput->text().trimmed();

    if (countStr.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a count");
        return;
    }

    bool ok;
    int count = countStr.toInt(&ok);

    if (!ok || count <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid positive number");
        return;
    }

    try {
        service.generateWorkList(count);
        countInput->clear();
        refreshList();
        QMessageBox::information(this, "Success", QString("Generated %1 random cars").arg(count));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to generate: %1").arg(e.what()));
    }
}

void WorkListWindow::onExportClicked() {
    try {
        service.exportWorkList("masini1.csv");
        QMessageBox::information(this, "Success", "Lista de lucru a fost exportata in masini1.csv");
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Eroare la export: %1").arg(e.what()));
    }
}

void WorkListWindow::refreshList() {
    workListWidget->clear();

    const auto& workList = service.getWorkList();

    for (const auto& masina : workList) {
        QString item = QString("%1 - %2 (%3) %4")
            .arg(masina.getNr())
            .arg(masina.getProducator())
            .arg(masina.getModel())
            .arg(masina.getTip());
        workListWidget->addItem(item);
    }
}
