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
#include "../Service/Service.h"


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
private:
	Service& service;


	//features basic
	QListWidget* carListWidget;
	QLineEdit* nrInput;
	QLineEdit* producatorInput;
	QLineEdit* tipInput;
	QSpinBox* modelInput;
	QPushButton* addButton;
	QPushButton* updateButton;
	QPushButton* deleteButton;
	QPushButton* clearButton;
	QPushButton* refreshButton;


	//more advanced
	QVBoxLayout* mainLayout;
	QLabel* modeLabel;
};

#endif //LAB67_GUI_H