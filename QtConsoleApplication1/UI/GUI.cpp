#include "GUI.h"
#include <qmessagebox.h>
#include <qstring.h>
#include <sstream>
#include "WorkListWindow.h"

MainWindow::MainWindow(Service& service, QWidget* parent) : QWidget(parent), service(service) {
	setWindowTitle("Management Masini");
	resize(600, 500);

	mainLayout = new QVBoxLayout(this);

	QLabel* displayLable = new QLabel("Masini in sistem:", this);
	mainLayout->addWidget(displayLable);

	// carListWidget = new QListWidget(this);
	carTableWidget = new QTableWidget(this);
	carTableWidget->setColumnCount(4);
	QStringList headers;
	headers << "Nr" << "Producator" << "Model" << "Tip";
	carTableWidget->setHorizontalHeaderLabels(headers);
	carTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	carTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	mainLayout->addWidget(carTableWidget);
	// mainLayout->addWidget(carListWidget); 

	//Indicator mod

	modeLabel = new QLabel("Mod: Adaugare", this);
	mainLayout->addWidget(modeLabel);


	QLabel* inputLabel = new QLabel("Adauga masina noua:", this);
	mainLayout->addWidget(inputLabel);

	//Input

	QHBoxLayout* inputLayout1 = new QHBoxLayout();
	QLabel* plateLabel = new QLabel("Nr inmatriculare:", this);
	nrInput = new QLineEdit(this);
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
	modelInput = new QLineEdit(this);
	modelInput->setPlaceholderText("ex. 2024");
	modelInput->setValidator(new QIntValidator(1980, 2026, this));
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
	filterButton = new QPushButton("Mod Filtrare", this);
	buttonsLayout->addWidget(addButton);
	buttonsLayout->addWidget(deleteButton);
	buttonsLayout->addWidget(updateButton);
	buttonsLayout->addWidget(clearButton);
	buttonsLayout->addWidget(filterButton);
	mainLayout->addLayout(buttonsLayout);

	QHBoxLayout* sortLayout = new QHBoxLayout();
	sortButton = new QPushButton("Sortare model Crescator", this);
	sortLayout->addWidget(sortButton);
	mainLayout->addLayout(sortLayout);

	// Add Worklist and Undo buttons
	QHBoxLayout* extraLayout = new QHBoxLayout();
	workListButton = new QPushButton("Worklist", this);
	undoButton = new QPushButton("Undo", this);
	extraLayout->addWidget(workListButton);
	extraLayout->addWidget(undoButton);

	openCRUDBtn = new QPushButton("Cos CRUD", this);
	extraLayout->addWidget(openCRUDBtn);
	connect(openCRUDBtn, &QPushButton::clicked, this, &MainWindow::onOpenCRUDClicked);

	openReadOnlyBtn = new QPushButton("Cos ReadOnly", this);
	extraLayout->addWidget(openReadOnlyBtn);
	connect(openReadOnlyBtn, &QPushButton::clicked, this, &MainWindow::onOpenReadOnlyClicked);



	mainLayout->addLayout(extraLayout);

	connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddCarClicked);
	connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteCarClicked);
	connect(updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateCarClicked);
	connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearFieldsClicked);
	connect(filterButton, &QPushButton::clicked, this, &MainWindow::onToggleFilterMode);
	connect(sortButton, &QPushButton::clicked, this, &MainWindow::onSortButtonClicked);
	connect(workListButton, &QPushButton::clicked, this, &MainWindow::onWorkListButtonClicked);
	connect(undoButton, &QPushButton::clicked, this, &MainWindow::onUndoButtonClicked);

	connect(producatorInput, &QLineEdit::textChanged, this, &MainWindow::onFilterCriteriaChanged);

	connect(tipInput,&QLineEdit::textChanged, this,&MainWindow::onFilterCriteriaChanged);
	connect(modelInput, &QLineEdit::textChanged, this, &MainWindow::onFilterCriteriaChanged);

	connect(carTableWidget, &QTableWidget::itemSelectionChanged, this, &MainWindow::onCarListItemSelected);
	// connect(carListWidget, &QListWidget::itemSelectionChanged, this, &MainWindow::onCarListItemSelected);

	setLayout(mainLayout);

	refreshCarList();
}

MainWindow::~MainWindow() {
}

void MainWindow::onAddCarClicked() {

	QString nr = nrInput->text().trimmed();
	QString producator = producatorInput->text().trimmed();
	int model = modelInput->text().toInt();
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
		modelInput->clear();
		refreshCarList();
		updateUndoButtonState();
	}
	catch (const std::exception& e) {
		QMessageBox::critical(this, "Eroare", QString::fromStdString(std::string(e.what())));
	}
}

void MainWindow::onDeleteCarClicked() {

	// QListWidgetItem* selectedItem = carListWidget->currentItem();
	QList<QTableWidgetItem*> selectedItems = carTableWidget->selectedItems();
	if (selectedItems.size() < 4) {
		QMessageBox::warning(this, "Eroare la selectare", "Va rog selectati ceva");
		return;
	}
	QString nr = selectedItems[0]->text();
	if (nr.isEmpty()) {
		QMessageBox::warning(this, "Error", "Extragere nr nereusita");
		return;
	}
	try {
		service.removeMasina(nr.toStdString().c_str());
		QMessageBox::information(this, "Success", "Masina stearsa!");
		refreshCarList();
		updateUndoButtonState();
	}
	catch(const std::exception& e){
		QMessageBox::critical(this, "Eroare", QString::fromStdString(std::string(e.what())));
	}

}

void MainWindow::refreshCarList() {
	// carListWidget->clear();
	carTableWidget->setRowCount(0);
	const auto& cars = service.getAllMasini();
	int row = 0;
	for (const auto& car : cars) {
		carTableWidget->insertRow(row);
		carTableWidget->setItem(row, 0, new QTableWidgetItem(car.getNr()));
		carTableWidget->setItem(row, 1, new QTableWidgetItem(car.getProducator()));
		carTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(car.getModel())));
		carTableWidget->setItem(row, 3, new QTableWidgetItem(car.getTip()));
		row++;
		// QString carInfo = QString::fromStdString(
		//     std::string("NR: ") + car.getNr() +
		//     "\nProducator: " + car.getProducator() +
		//     "\nModel: " + std::to_string(car.getModel()) +
		//     "\nTip: " + car.getTip()
		// );
		// carListWidget->addItem(carInfo); // Old list widget
	}
}

void MainWindow::onUpdateCarClicked() {
	QString nr = nrInput->text().trimmed();
	QString producator = producatorInput->text().trimmed();
	int model = modelInput->text().toInt();
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
		modelInput->clear();
		modeLabel->setText("Mod: Adaugare");
		refreshCarList();
		updateUndoButtonState();
	}
	catch (const std::exception& e) {
		QMessageBox::critical(this, "Eroare", QString::fromStdString(std::string(e.what())));
	}
}

void MainWindow::onCarListItemSelected() {

	if (isFilterMode) {
		return;
	}
	// QListWidgetItem* selectedItem = carListWidget->currentItem();
	QList<QTableWidgetItem*> selectedItems = carTableWidget->selectedItems();
	if (selectedItems.size() < 4) {
		return;
	}
	QString nr = selectedItems[0]->text();
	QString producator = selectedItems[1]->text();
	QString model = selectedItems[2]->text();
	QString tip = selectedItems[3]->text();
	nrInput->setText(nr);
	producatorInput->setText(producator);
	tipInput->setText(tip);
	modelInput->setText(model);
	modeLabel->setText("Mod: Modificare - NR: " + nr);
}

void MainWindow::onClearFieldsClicked() {
	nrInput->clear();
	producatorInput->clear();
	tipInput->clear();
	modelInput->clear();
	modeLabel->setText("Mod: Adaugare");
	// carListWidget->clearSelection();
	carTableWidget->clearSelection();
	updateUndoButtonState();
}

void MainWindow::onToggleFilterMode() {
	isFilterMode = !isFilterMode;

	if (isFilterMode) {
		modeLabel->setText("Mod: Filtrare");
		filterButton->setText("Iesire Filter Mode");
		addButton->setEnabled(false);
		updateButton->setEnabled(false);
		deleteButton->setEnabled(false);

		nrInput->clear();
		producatorInput->clear();
		tipInput->clear();
	}
	else {
		modeLabel->setText("Mod Adaugare");
		filterButton->setText("Mod Filtrare");

		addButton->setEnabled(true);
		updateButton->setEnabled(true);
		deleteButton->setEnabled(true);

		onClearFieldsClicked();
		refreshCarList();
	}
}

void MainWindow::onFilterCriteriaChanged() {
	if (!isFilterMode) {
		return;
	}
	QString filterProducator = producatorInput->text().trimmed().toLower();
	QString filterTip = tipInput->text().trimmed().toLower();
	QString filterModel = modelInput->text().trimmed();
	// carListWidget->clear(); 
	carTableWidget->setRowCount(0);
	const auto& cars = service.getAllMasini();
	int row = 0;
	for (const auto& car : cars) {
		QString prod = QString::fromStdString(car.getProducator()).toLower();
		QString tip = QString::fromStdString(car.getTip()).toLower();
		QString model = QString::number(car.getModel());

		bool matchProducator = filterProducator.isEmpty() || prod.contains(filterProducator);
		bool matchTip = filterTip.isEmpty() || tip.contains(filterTip);
		bool matchModel = filterModel.isEmpty() || model == filterModel;


		if (matchProducator && matchTip && matchModel) {
			carTableWidget->insertRow(row);
			carTableWidget->setItem(row, 0, new QTableWidgetItem(car.getNr()));
			carTableWidget->setItem(row, 1, new QTableWidgetItem(car.getProducator()));
			carTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(car.getModel())));
			carTableWidget->setItem(row, 3, new QTableWidgetItem(car.getTip()));
			row++;
			// QString carInfo = QString::fromStdString(std::string("NR: ") + car.getNr() + "\n Producator: " + car.getProducator() + "\n Model: " + std::to_string(car.getModel()) + "\n Tip: " + car.getTip());
			// carListWidget->addItem(carInfo);
		}
	}
}

void MainWindow::onSortButtonClicked() {
	int dim = 0;

	const Masina* masiniSortate = service.sortMasini("model", false, dim);
	// carListWidget->clear();
	carTableWidget->setRowCount(0);
	for (int i = 0; i < dim; ++i) {
		const Masina& car = masiniSortate[i];
		carTableWidget->insertRow(i);
		carTableWidget->setItem(i, 0, new QTableWidgetItem(car.getNr()));
		carTableWidget->setItem(i, 1, new QTableWidgetItem(car.getProducator()));
		carTableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(car.getModel())));
		carTableWidget->setItem(i, 3, new QTableWidgetItem(car.getTip()));
		// QString carInfo = QString::fromStdString(
		//     std::string("NR: ") + car.getNr() +
		//     "\nProducator: " + car.getProducator() +
		//     "\nModel: " + std::to_string(car.getModel()) +
		//     "\nTip: " + car.getTip()
		// );
		// carListWidget->addItem(carInfo); // Old list widget
	}
	delete[] masiniSortate;



}

void MainWindow::onWorkListButtonClicked() {
	if (!workListWindow) {
		workListWindow = new WorkListWindow(service, nullptr);
	}
	workListWindow->show();
	workListWindow->raise();
	workListWindow->activateWindow();
}

void MainWindow::onUndoButtonClicked() {
	try {
		service.undo();
		refreshCarList();
		updateUndoButtonState();
	} catch (const std::exception& e) {
		QMessageBox::warning(this, "Undo", e.what());
	}
}

void MainWindow::updateUndoButtonState() {
    if (service.canUndo()) {
        undoButton->setEnabled(true);
        undoButton->setStyleSheet("background-color: yellow; font-weight: bold;");
    } else {
        undoButton->setEnabled(false);
        undoButton->setStyleSheet("");
    }
}
void MainWindow::onOpenCRUDClicked() {
	CosCRUDGUI* window = new CosCRUDGUI(service, nullptr);
	window->setAttribute(Qt::WA_DeleteOnClose);
	window->show();
}

void MainWindow::onOpenReadOnlyClicked() {
	CosReadOnlyGUI* window = new CosReadOnlyGUI(service, nullptr);
	window->setAttribute(Qt::WA_DeleteOnClose);
	window->show();
}