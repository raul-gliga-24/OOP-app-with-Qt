
#ifndef LAB67_GUI_H
#define LAB67_GUI_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qvboxlayout>
#include <qlineedit.h>

class MainWindow :public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();
private slots:
	void onButtonClicked();
	void onSecondButtonClicked();
private:
	QPushButton* mybtn;
	QPushButton* secondbtn;
	QLabel* myLable;
	QLineEdit* MytextBox;

	QVBoxLayout* mainLayout;
};

#endif //LAB67_GUI_H