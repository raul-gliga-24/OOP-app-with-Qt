#ifndef WORKLISTMODEL_H
#define WORKLISTMODEL_H
#define QT_NO_DEPRECATED_WARNINGS

#include <QAbstractTableModel>
#include <vector>
#include "../Domain/Masina.h"

class WorkListModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit WorkListModel(const std::vector<Masina>& workList, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void refresh();

private:
    const std::vector<Masina>& workList;
};

#endif // WORKLISTMODEL_H
