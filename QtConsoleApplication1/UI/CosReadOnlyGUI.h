#ifndef COSREADONLYGUI_H
#define COSREADONLYGUI_H
#define QT_NO_DEPRECATED_WARNINGS

#include <QWidget>
#include <QPaintEvent>
#include <vector>
#include "../Service/Observer.h"
#include "../Service/Service.h"
#include "WorkListModel.h"

class CosReadOnlyGUI : public QWidget, public Observer {
    Q_OBJECT
public:
    explicit CosReadOnlyGUI(Service& service, QWidget* parent = nullptr);
    ~CosReadOnlyGUI();
    void update() override;

protected:
    void paintEvent(QPaintEvent* ev) override;

private:
    Service& service;
    WorkListModel* model;
    struct Shape {
        int x, y, w, h;
        int r, g, b;
    };
    std::vector<Shape> shapes;
    void regenerateShapes();
};

#endif // COSREADONLYGUI_H