#ifndef WORKLISTWINDOW_H
#define WORKLISTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QListWidget>

class Service;

class WorkListWindow : public QWidget {
    Q_OBJECT
public:
    explicit WorkListWindow(Service& service, QWidget* parent = nullptr);

private slots:
    void onAddClicked();
    void onClearClicked();
    void onGenerateClicked();

    void onExportClicked();

private:
    Service& service;

    QListWidget* workListWidget;
    QLineEdit* nrInput;
    QLineEdit* countInput;

    QPushButton* btnAdd;
    QPushButton* btnClear;
    QPushButton* btnGenerate;

    QPushButton* btnExport;

    void refreshList();
};

#endif // WORKLISTWINDOW_H
