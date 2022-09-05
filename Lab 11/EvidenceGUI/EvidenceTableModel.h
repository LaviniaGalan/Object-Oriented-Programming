#pragma once
#include "Service.h"
#include <QAbstractTableModel>

class EvidenceTableModel : public QAbstractTableModel
{
private:
	Service& service;
public:

	EvidenceTableModel(Service& service, QObject* parent = NULL);

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

	QVariant data(const QModelIndex& indexOfData, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

};

