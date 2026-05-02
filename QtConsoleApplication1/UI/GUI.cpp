
#include "GUI.h"
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent){
	
	setWindowTitle("My first QT app");
	resize(400, 300);

	myLable = new QLabel("Hello qt", this);
	MytextBox = new QLineEdit(this);
	MytextBox->setPlaceholderText("Enter text here");

	mybtn = new QPushButton("Click me", this);
	secondbtn = new QPushButton("Second button", this);

	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(myLable);
	mainLayout->addWidget(MytextBox);
	mainLayout->addWidget(mybtn);
	mainLayout->addWidget(secondbtn);

	setLayout(mainLayout);

	connect(mybtn, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
	connect(secondbtn, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

}

MainWindow::~MainWindow() {

}

void MainWindow::onButtonClicked() {
	QString text = MytextBox->text();
	myLable->setText("You entered: " + text);

}
void MainWindow::onSecondButtonClicked()
{
	QMessageBox::information(this, "Button Clicked", "You clicked the second button!");
}