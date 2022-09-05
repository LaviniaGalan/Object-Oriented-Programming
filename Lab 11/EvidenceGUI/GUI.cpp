#include "GUI.h"
#include <qlayout.h>
#include <qformlayout.h>
#include <qobject.h>
#include <qmessagebox.h>
#include <qpainter.h>

#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieLegendMarker>

QT_CHARTS_USE_NAMESPACE


MainApplicationWidget::MainApplicationWidget(Service service) : service{ service }
{
	this->initializeGUI();
	this->populateListOfEvidence();
	this->connectSignalsAndSlots();
}

void MainApplicationWidget::initializeGUI()
{

	QHBoxLayout* mainLayout = new QHBoxLayout{ this };

	QVBoxLayout* modeALayout = this->createModeALayout();
	QVBoxLayout* modeBLayout = this->createModeBLayout();

	this->switchButton = new QPushButton{ "Switch Mode" };
	this->chartButton = new QPushButton{ "View Chart" };

	QGridLayout* middleButtonsLayout = new QGridLayout{ this };
	middleButtonsLayout->addWidget(this->switchButton, 0, 0);
	middleButtonsLayout->addWidget(this->chartButton, 1, 0);

	mainLayout->addLayout(modeALayout);
	mainLayout->addLayout(middleButtonsLayout);
	mainLayout->addLayout(modeBLayout);
	
	setLayout(mainLayout);
}

QVBoxLayout* MainApplicationWidget::createModeALayout()
{
	this->modeALabel = new QLabel{"Mode A"};

	this->evidenceListWidget = new QListWidget{};

	this->evidenceIDLineEdit = new QLineEdit{};
	this->measurementLineEdit = new QLineEdit{};
	this->clarityLevelLineEdit = new QLineEdit{};
	this->quantityLineEdit = new QLineEdit{};
	this->photographLineEdit = new QLineEdit{};

	this->addButton = new QPushButton{ "Add" };
	this->deleteButton = new QPushButton{ "Delete" };
	this->updateButton = new QPushButton{ "Update" };

	QVBoxLayout* modeALayout = new QVBoxLayout{ this };

	modeALayout->addWidget(this->modeALabel);
	modeALayout->addWidget(this->evidenceListWidget);

	QFormLayout* evidenceFieldsLayout = new QFormLayout{ this };
	evidenceFieldsLayout->addRow("Evidence ID: ", this->evidenceIDLineEdit);
	evidenceFieldsLayout->addRow("Measurement: ", this->measurementLineEdit);
	evidenceFieldsLayout->addRow("Image Clarity Level: ", this->clarityLevelLineEdit);
	evidenceFieldsLayout->addRow("Quantity: ", this->quantityLineEdit);
	evidenceFieldsLayout->addRow("Photograph: ", this->photographLineEdit);
	modeALayout->addLayout(evidenceFieldsLayout);

	QGridLayout* buttonsLayout = new QGridLayout{ this };
	buttonsLayout->addWidget(this->addButton, 0, 0);
	buttonsLayout->addWidget(this->deleteButton, 0, 2);
	buttonsLayout->addWidget(this->updateButton, 1, 1);
	modeALayout->addLayout(buttonsLayout);

	return modeALayout;
}

QVBoxLayout* MainApplicationWidget::createModeBLayout()
{
	QVBoxLayout* modeBLayout = new QVBoxLayout{ this };

	this->modeBLabel = new QLabel{ "Mode B" };
	modeBLayout->addWidget(this->modeBLabel);

	this->evidenceModeBListWidget = new QListWidget{};
	modeBLayout->addWidget(this->evidenceModeBListWidget);

	QGridLayout* buttonsLayout = new QGridLayout{ this };
	this->saveButton = new QPushButton{ "Save" };
	this->nextButton = new QPushButton{ "Next" };
	buttonsLayout->addWidget(this->saveButton, 0, 0);
	buttonsLayout->addWidget(this->nextButton, 0, 2);

	modeBLayout->addLayout(buttonsLayout);

	this->myListLocationLineEdit = new QLineEdit{};
	QFormLayout* myListLocationLayout = new QFormLayout{ this };
	myListLocationLayout->addRow("My List Location: ", this->myListLocationLineEdit);
	
	modeBLayout->addLayout(myListLocationLayout);

	this->myListLocationButton = new QPushButton{ "Set location" };
	modeBLayout->addWidget(this->myListLocationButton);

	return modeBLayout;
}

void MainApplicationWidget::populateListOfEvidence()
{
	this->evidenceListWidget->clear();

	std::vector<Evidence> listOfEvidence = this->service.getAllEvidenceService();
	for (Evidence evidence : listOfEvidence)
	{
		this->evidenceListWidget->addItem(QString::fromStdString(evidence.evidenceDataToString()));
	}
}

void MainApplicationWidget::connectSignalsAndSlots()
{

	QObject::connect(this->evidenceListWidget, &QListWidget::itemSelectionChanged, [this]()
		{
			int indexOfSelectedEvidence = this->getIndexOfSelectedEvidence();
			if (indexOfSelectedEvidence == -1)
				return;
			Evidence selectedEvidence = this->service.getAllEvidenceService().at(indexOfSelectedEvidence);
			this->evidenceIDLineEdit->setText(QString::fromStdString(selectedEvidence.getEvidenceID()));
			this->measurementLineEdit->setText(QString::fromStdString(selectedEvidence.getMeasurement()));
			this->clarityLevelLineEdit->setText(QString::fromStdString(std::to_string(selectedEvidence.getImageClarityLevel())));
			this->quantityLineEdit->setText(QString::fromStdString(std::to_string(selectedEvidence.getQuantity())));
			this->photographLineEdit->setText(QString::fromStdString(selectedEvidence.getPhotograph()));;
		});

	QObject::connect(this->addButton, &QPushButton::clicked, this, &MainApplicationWidget::addEvidence);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &MainApplicationWidget::deleteEvidence);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &MainApplicationWidget::updateEvidence);
	QObject::connect(this->chartButton, &QPushButton::clicked, this, &MainApplicationWidget::displayChart);
}

int MainApplicationWidget::getIndexOfSelectedEvidence()
{
	QModelIndexList listOfSelectedIndexes = this->evidenceListWidget->selectionModel()->selectedIndexes();

	if (listOfSelectedIndexes.size() == 0)
	{
		this->evidenceIDLineEdit->clear();
		this->measurementLineEdit->clear();
		this->clarityLevelLineEdit->clear();
		this->quantityLineEdit->clear();
		this->photographLineEdit->clear();
		return -1;
	}
	return listOfSelectedIndexes.at(FIRST_SELECTED_INDEX).row();
}

void MainApplicationWidget::addEvidence()
{
	std::string evidenceID, measurement, photograph;
	double imageClarityLevel;
	int quantity;
	evidenceID = this->evidenceIDLineEdit->text().toStdString();
	measurement = this->measurementLineEdit->text().toStdString();
	imageClarityLevel = atof(this->clarityLevelLineEdit->text().toStdString().c_str());
	quantity = atoi(this->quantityLineEdit->text().toStdString().c_str());
	photograph = this->photographLineEdit->text().toStdString();

	try
	{
		this->service.addEvidence(evidenceID, measurement, imageClarityLevel, quantity, photograph);
		this->populateListOfEvidence();
	}
	catch (ValidationException & exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.getMessageOfException()));
	}
	catch (InvalidIDException & exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
	
}

void MainApplicationWidget::deleteEvidence()
{
	int indexOfSelectedEvidence = this->getIndexOfSelectedEvidence();
	if (indexOfSelectedEvidence == -1)
	{

		QMessageBox::critical(this, "Error", "No evidence was selected!");
		return;
	}
	std::string evidenceID = this->evidenceIDLineEdit->text().toStdString();
	try
	{
		this->service.deleteEvidence(evidenceID);
		this->populateListOfEvidence();
	}
	catch (InvalidIDException & exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
}

void MainApplicationWidget::updateEvidence()
{
	std::string evidenceID, newMeasurement, newPhotograph;
	double newImageClarityLevel;
	int newQuantity;
	evidenceID = this->evidenceIDLineEdit->text().toStdString();
	newMeasurement = this->measurementLineEdit->text().toStdString();
	newImageClarityLevel = atof(this->clarityLevelLineEdit->text().toStdString().c_str());
	newQuantity = atoi(this->quantityLineEdit->text().toStdString().c_str());
	newPhotograph = this->photographLineEdit->text().toStdString();

	try
	{
		this->service.updateEvidence(evidenceID, newMeasurement, newImageClarityLevel, newQuantity, newPhotograph);
		this->populateListOfEvidence();
	}
	catch (ValidationException & exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.getMessageOfException()));
	}
	catch (InvalidIDException & exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
}

QChartView* MainApplicationWidget::createChart()
{ 
	QPieSeries* seriesOfEvidence = new QPieSeries();
	std::vector<QPieSlice*> slicesOfEvidence;
	std::vector<Evidence> listOfEvidence = this->service.getAllEvidenceService();
	// adding all evidence in the pie
	for (int index = 0; index < listOfEvidence.size(); index++) {
		seriesOfEvidence->append(QString::fromStdString("ID: " + listOfEvidence.at(index).getEvidenceID() + " - Quantity: " + std::to_string(listOfEvidence.at(index).getQuantity()) + "\n"), listOfEvidence.at(index).getQuantity());
		slicesOfEvidence.push_back(seriesOfEvidence->slices().at(index));
	}
	seriesOfEvidence->setLabelsVisible();
	seriesOfEvidence->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

	QChart* chart = new QChart();
	chart->addSeries(seriesOfEvidence);
	chart->setTitle("Evidence Percentage By Quantity");
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignRight);

	// set the markers of the legend
	QList<QLegendMarker*> listOfLegendMarkers = chart->legend()->markers(seriesOfEvidence);

	for (QLegendMarker* evidenceLegendMarker : listOfLegendMarkers) 
	{
		QPieLegendMarker* evidencePieMarkerInTheLegend = qobject_cast<QPieLegendMarker*>(evidenceLegendMarker);
		{
		     evidencePieMarkerInTheLegend->setLabel(QString("%1").arg(evidencePieMarkerInTheLegend->slice()->label()));
		}
	}

	// modify the slices so that they contain the percentage of each evidence 
	for (QPieSlice* evidenceSlice : seriesOfEvidence->slices())
	{
		evidenceSlice->setLabelBrush(QBrush(Qt::white));
		evidenceSlice->setLabel(QString::number(evidenceSlice->percentage()*100, 'f', 1) + "%");
	}

	QChartView* chartView = new QChartView(chart);

	return chartView;
}

void MainApplicationWidget::displayChart()
{
	QWidget* windowForChart = new QWidget;
	QChartView* chartView = this->createChart();

	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->resize(600, 600);
	chartView->show();
}


