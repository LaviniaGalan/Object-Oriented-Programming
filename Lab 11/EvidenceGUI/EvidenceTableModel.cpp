#include "EvidenceTableModel.h"

EvidenceTableModel::EvidenceTableModel(Service& service, QObject* parent) : service{ service }
{
}

int EvidenceTableModel::rowCount(const QModelIndex& parent) const
{
	return this->service.getAllPhysicalCopiesService().size();
}

int EvidenceTableModel::columnCount(const QModelIndex& parent) const
{
	return NUMBER_OF_TOTAL_ATTRIBUTES;
}

QVariant EvidenceTableModel::data(const QModelIndex& indexOfData, int role) const
{

	int rowOfEvidence = indexOfData.row();
	int columnOfEvidenceData = indexOfData.column();

	std::vector<Evidence> evidenceList = this->service.getAllPhysicalCopiesService();
	if (rowOfEvidence == evidenceList.size())
	{
		return QVariant();
	}

	Evidence evidence = evidenceList.at(rowOfEvidence);

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		if (columnOfEvidenceData == INDEX_OF_EVIDENCE_ID)
			return QString::fromStdString(evidence.getEvidenceID());
		else if (columnOfEvidenceData == INDEX_OF_MEASUREMENT)
			return QString::fromStdString(evidence.getMeasurement());
		else if (columnOfEvidenceData == INDEX_OF_CLARITY_LEVEL)
			return QString::fromStdString(std::to_string(evidence.getImageClarityLevel()));
		else if (columnOfEvidenceData == INDEX_OF_QUANTITY)
			return QString::fromStdString(std::to_string(evidence.getQuantity()));
		else if (columnOfEvidenceData == INDEX_OF_PHOTOGRAPH)
			return QString::fromStdString(evidence.getPhotograph());
	}
	
	return QVariant{};
}

QVariant EvidenceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			if (section == INDEX_OF_EVIDENCE_ID)
				return QString{ "Evidence ID" };
			else if (section == INDEX_OF_MEASUREMENT)
				return QString{ "Measurement" };
			else if (section == INDEX_OF_CLARITY_LEVEL)
				return QString{ "Image Clarity Level" };
			else if (section == INDEX_OF_QUANTITY)
				return QString{ "Quantity" };
			else if (section == INDEX_OF_PHOTOGRAPH)
				return QString{ "Photograph" };
		}
	}
	return QVariant{};
}
