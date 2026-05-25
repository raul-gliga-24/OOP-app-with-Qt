#ifndef LAB67_GUI_H
#define LAB67_GUI_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qvboxlayout>
#include <qlineedit.h>
#include <qhboxlayout>
#include <qlistwidget.h>
#include <qspinbox.h>
#include <QTableWidget>
#include "../Service/Service.h"
#include <QIntValidator>
#include "WorkListWindow.h"

class MainWindow :public QWidget
{
	Q_OBJECT
public:
	MainWindow(Service& service,QWidget* parent = nullptr);
	~MainWindow();
private slots:
	void onAddCarClicked();
	void onDeleteCarClicked();
	void refreshCarList();
	void onUpdateCarClicked();
	void onCarListItemSelected();
	void onClearFieldsClicked();

	//Filters
	void onToggleFilterMode();
	void onFilterCriteriaChanged();
	//Sort
	void onSortButtonClicked();
	void onWorkListButtonClicked();
    void onUndoButtonClicked();
private:
	bool isFilterMode = false;
	Service& service;


	//features basic
	//QListWidget* carListWidget; // Old list widget
	QTableWidget* carTableWidget; // New table widget
	QLineEdit* nrInput;
	QLineEdit* producatorInput;
	QLineEdit* tipInput;
	QLineEdit* modelInput;
	QPushButton* addButton;
	QPushButton* updateButton;
	QPushButton* deleteButton;
	QPushButton* clearButton;
	QPushButton* filterButton;
	QPushButton* sortButton;
	QPushButton* workListButton;
	QPushButton* undoButton;
	WorkListWindow* workListWindow = nullptr;
	void updateUndoButtonState();
	QVBoxLayout* mainLayout;
	QLabel* modeLabel;
};

#endif //LAB67_GUI_H