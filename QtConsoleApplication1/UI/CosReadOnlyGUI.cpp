#include "CosReadOnlyGUI.h"
#include <QPainter>
#include <cstdlib>

CosReadOnlyGUI::CosReadOnlyGUI(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {
    setWindowTitle("Cos - Read Only");
    setGeometry(300, 300, 500, 400);

    model = new WorkListModel(service.getWorkList(), this);

    service.addObserver(this);
    regenerateShapes();
}

CosReadOnlyGUI::~CosReadOnlyGUI() {
    service.removeObserver(this);
}

void CosReadOnlyGUI::update() {
    model->refresh();
    regenerateShapes();
    repaint();
}

void CosReadOnlyGUI::regenerateShapes() {
    shapes.clear();
    int count = model->rowCount();
    int w = width() > 60 ? width() - 60 : 400;
    int h = height() > 60 ? height() - 60 : 300;

    for (int i = 0; i < count; i++) {
        Shape s;
        s.x = std::rand() % w;
        s.y = std::rand() % h;
        s.w = 20 + std::rand() % 60;
        s.h = 20 + std::rand() % 60;
        s.r = std::rand() % 256;
        s.g = std::rand() % 256;
        s.b = std::rand() % 256;
        shapes.push_back(s);
    }
}

void CosReadOnlyGUI::paintEvent(QPaintEvent* ev) {
    (void)ev;
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawText(10, 20, QString("Cos: %1 elemente").arg(model->rowCount()));

    for (const auto& s : shapes) {
        p.setBrush(QColor(s.r, s.g, s.b));
        p.drawRect(s.x, s.y, s.w, s.h);
    }
}