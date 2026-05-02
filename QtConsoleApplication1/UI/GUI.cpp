#include "GUI.h"
#include <qmessagebox.h>
#include <qstring.h>
#include <sstream>

MainWindow::MainWindow(Service& service, QWidget* parent) : QWidget(parent), service(service) {
	setWindowTitle("Management Masini");
	resize(600, 500);

	mainLayout = new QVBoxLayout(this);

	QLabel* displayLable = new QLabel("Masini in sistem:", this);
	mainLayout->addWidget(displayLable);

	carListWidget = new QListWidget(this);
	mainLayout->addWidget(carListWidget);

	refreshButton = new QPushButton("Refresh list:", this);
	mainLayout->addWidget(refreshButton);
	connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshCarList);
	//Indicator mod

	modeLabel = new QLabel("Mod: Adaugare", this);
	mainLayout->addWidget(modeLabel);


	QLabel* inputLabel = new QLabel("Adauga masina noua:", this);
	mainLayout->addWidget(inputLabel);

	//Input

	QHBoxLayout* inputLayout1 = new QHBoxLayout();
	QLabel* plateLabel = new QLabel("Nr inmatriculare:", this);
	nrInput = new QLineEdit(plateLabel);
	nrInput->setPlaceholderText("ex. AB123CD");
	inputLayout1->addWidget(plateLabel);
	inputLayout1->addWidget(nrInput);
	mainLayout->addLayout(inputLayout1);

	QHBoxLayout* inputLayout2 = new QHBoxLayout();
	QLabel* manufacturerLabel = new QLabel("Prodcator:", this);
	producatorInput = new QLineEdit(this);
	producatorInput->setPlaceholderText("ex. Toyota");
	inputLayout2->addWidget(manufacturerLabel);
	inputLayout2->addWidget(producatorInput);
	mainLayout->addLayout(inputLayout2);

	QHBoxLayout* inputLayout3 = new QHBoxLayout();
	QLabel* modelLabel = new QLabel("Model(an)", this);
	modelInput = new QSpinBox(this);
	modelInput->setMinimum(1980);
	modelInput->setMaximum(2100);
	modelInput->setValue(2024);
	inputLayout3->addWidget(modelLabel);
	inputLayout3->addWidget(modelInput);
	mainLayout->addLayout(inputLayout3);

	QHBoxLayout* inputLayout4 = new QHBoxLayout();
	QLabel* typeLabel = new QLabel("Tip:", this);
	tipInput = new QLineEdit(this);
	tipInput->setPlaceholderText("ex., SUV");
	inputLayout4->addWidget(typeLabel);
	inputLayout4->addWidget(tipInput);
	mainLayout->addLayout(inputLayout4);

	QHBoxLayout* buttonsLayout = new QHBoxLayout();
	addButton = new QPushButton("Adauga masina", this);
	deleteButton = new QPushButton("Sterge masina", this);
	updateButton = new QPushButton("Actualizeaza masina", this);
	clearButton = new QPushButton("Curata campuri", this);
	buttonsLayout->addWidget(addButton);
	buttonsLayout->addWidget(deleteButton);
	buttonsLayout->addWidget(updateButton);
	buttonsLayout->addWidget(clearButton);
	mainLayout->addLayout(buttonsLayout);

	connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddCarClicked);
	connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteCarClicked);
	connect(updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateCarClicked);
	connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearFieldsClicked);

	setLayout(mainLayout);

	refreshCarList();
}

MainWindow::~MainWindow() {
}

void MainWindow::onAddCarClicked() {

	QString nr = nrInput->text().trimmed();
	QString producator = producatorInput->text().trimmed();
	int model = modelInput->value();
	QString tip = tipInput->text().trimmed();

	if (nr.isEmpty() || producator.isEmpty() || tip.isEmpty()) {
		QMessageBox::warning(this, "Eroare la input", "Completati toate casutele!");
		return;
	}

	try {
		service.addMasina(nr.toStdString().c_str(), producator.toStdString().c_str(), model, tip.toStdString().c_str());
		QMessageBox::information(this, "Success", "Masina adaugata!");
		nrInput->clear();
		producatorInput->clear();
		tipInput->clear();
		modelInput->setValue(2026);
		refreshCarList();
	}
	catch (const std::exception& e) {
		QMessageBox::critical(this, "Eroare", QString::fromStdString(std::string(e.what())));
	}
}

void MainWindow::onDeleteCarClicked() {

	QListWidgetItem* selectedIitem = carListWidget->currentItem();

	if (!selectedIitem) {
		QMessageBox::warning(this, "Eroare la selectare", "Va rog selectati ceva");
		return;
	}

	QString itemText = selectedIitem->text();
	QStringList lines = itemText.split("\n");
	if (lines.isEmpty()) {
		QMessageBox::warning(this, "Eroare", "Parsing nereusit");
		return;
	}

	QString linienr = lines[0];
	QString nr = linienr.split(": ").value(1, "");

	if (nr.isEmpty()) {
		QMessageBox::warning(this, "Error", "Extragere nr nereusita");
		return;
	}

	try {
		service.removeMasina(nr.toStdString().c_str());
		QMessageBox::information(this, "Success", "Masina stearsa!");
		refreshCarList();
	}
	catch(const std::exception& e){
		QMessageBox::critical(this, "Eroare", QString::fromStdString(std::string(e.what())));
	}

}

void MainWindow::refreshCarList() {

	carListWidget->clear();

	const auto& cars = service.getAllMasini();

	for (const auto& car : cars) {
		QString carInfo = QString::fromStdString(
			std::string("NR: ") + car.getNr() +
			"\nProducator: " + car.getProducator() +
			"\nModel: " + std::to_string(car.getModel()) +
			"\nTip: " + car.getTip()
		);
		carListWidget->addItem(carInfo);
	}
}

void MainWindow::onUpdateCarClicked() {
	QString nr = nrInput->text().trimmed();
	QString producator = producatorInput->text().trimmed();
	int model = modelInput->value();
	QString tip = tipInput->text().trimmed();


	if (nr.isEmpty() || producator.isEmpty() || tip.isEmpty()) {
		QMessageBox::warning(this, "Eroare la input", "Completati toate casutele!");
		return;
	}
	try {
		Masina newMasina(nr.toStdString().c_str(), producator.toStdString().c_str(), model, tip.toStdString().c_str());
		service.updateMasina(nr.toStdString().c_str(), newMasina);
		QMessageBox::information(this, "Success", "Masina actualizata!");
		nrInput->clear();
		producatorInput->clear();
		tipInput->clear();
		modelInput->setValue(2026);
		modeLabel->setText("Mod: Adaugare");
		refreshCarList();
	}
	catch (const std::exception& e) {
		QMessageBox::critical(this, "Eroare", QString::fromStdString(std::string(e.what())));
	}
}

void MainWindow::onCarListItemSelected() {
	QListWidgetItem* selectedItem = carListWidget->currentItem();

	if (!selectedItem) {
		return;
	}

	QString itemText = selectedItem->text();
	QStringList lines = itemText.split("\n");

	if (lines.size() < 4) {
		QMessageBox::warning(this, "Eroare", "Parsing nereusit");
		return;
	}

	//"NR: AB123CD", "Producator: Toyota", "Model: 2024", "Tip: SUV"
	QString nr = lines[0].split(": ").value(1, "");
	QString producator = lines[1].split(": ").value(1, "");
	QString model = lines[2].split(": ").value(1, "");
	QString tip = lines[3].split(": ").value(1, "");

	nrInput->setText(nr);
	producatorInput->setText(producator);
	tipInput->setText(tip);
	modelInput->setValue(model.toInt());

	modeLabel->setText("Mod: Modificare - NR: " + nr);
}

void MainWindow::onClearFieldsClicked() {
	nrInput->clear();
	producatorInput->clear();
	tipInput->clear();
	modelInput->setValue(2026);
	modeLabel->setText("Mod: Adaugare");
	carListWidget->clearSelection();
}
