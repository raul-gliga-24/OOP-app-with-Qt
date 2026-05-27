#include "WorkListModel.h"

WorkListModel::WorkListModel(const std::vector<Masina>& workList, QObject* parent)
    : QAbstractTableModel(parent), workList(workList) {}

int WorkListModel::rowCount(const QModelIndex&) const {
    return static_cast<int>(workList.size());
}

int WorkListModel::columnCount(const QModelIndex&) const {
    return 4;
}

QVariant WorkListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant{};

    const Masina& m = workList[index.row()];
    switch (index.column()) {
        case 0: return QString(m.getNr());
        case 1: return QString(m.getProducator());
        case 2: return QString::number(m.getModel());
        case 3: return QString(m.getTip());
        default: return QVariant{};
    }
}

QVariant WorkListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant{};

    switch (section) {
        case 0: return QString("Nr");
        case 1: return QString("Producator");
        case 2: return QString("Model");
        case 3: return QString("Tip");
        default: return QVariant{};
    }
}

void WorkListModel::refresh() {
    beginResetModel();
    endResetModel();
}
