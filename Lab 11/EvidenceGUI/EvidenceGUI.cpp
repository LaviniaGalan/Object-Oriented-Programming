#include "EvidenceGUI.h"
#include <qmessagebox.h>
#include <fstream>
#include <qshortcut.h>
#include <qtableview.h>

QT_CHARTS_USE_NAMESPACE

EvidenceGUI::EvidenceGUI(Service& service, QWidget *parent)
	: QMainWindow(parent), service {service}
{
	
	ui.setupUi(this);
	
	this->startProgramWithoutConfiguration();
}

void EvidenceGUI::startProgram()
{
	this->service.addObserver(this);

	this->ui.mainTabWidget->setTabEnabled(MODE_A_TAB_INDEX, true);
	this->ui.mainTabWidget->setTabEnabled(MODE_B_TAB_INDEX, true);
	this->ui.mainTabWidget->setTabEnabled(CHART_TAB_INDEX, true);

	this->ui.mainTabWidget->removeTab(CONFIGURATION_TAB_INDEX);

	this->connectSignalsAndSlots();
	this->populateListOfEvidence();
	this->populateMyList();
	this->displayChart();

	this->tableViewWindow = new EvidenceTableViewWindow{ this->service };
}

void EvidenceGUI::startProgramWithoutConfiguration()
{
	QObject::connect(this->ui.confirmButton, &QPushButton::clicked, this, &EvidenceGUI::setRepositoryConfiguration);
	this->ui.mainTabWidget->setTabEnabled(MODE_A_TAB_INDEX, false);
	this->ui.mainTabWidget->setTabEnabled(MODE_B_TAB_INDEX, false);
	this->ui.mainTabWidget->setTabEnabled(CHART_TAB_INDEX, false);
}

void EvidenceGUI::populateListOfEvidence()
{
	this->ui.evidenceListWidget->clear();

	std::vector<Evidence> listOfEvidence = this->service.getAllEvidenceService();
	for (Evidence evidence : listOfEvidence)
	{
		this->ui.evidenceListWidget->addItem(QString::fromStdString(evidence.evidenceDataToString()));
	}
}

void EvidenceGUI::connectSignalsAndSlots()
{
	QObject::connect(this->ui.evidenceListWidget, &QListWidget::itemSelectionChanged, [this]()
		{
			int indexOfSelectedEvidence = this->getIndexOfSelectedEvidence();
			if (indexOfSelectedEvidence == -1)
				return;
			Evidence selectedEvidence = this->service.getAllEvidenceService().at(indexOfSelectedEvidence);
			this->ui.evidenceIDLineEdit->setText(QString::fromStdString(selectedEvidence.getEvidenceID()));
			this->ui.measurementLineEdit->setText(QString::fromStdString(selectedEvidence.getMeasurement()));
			this->ui.clarityLevelLineEdit->setText(QString::fromStdString(std::to_string(selectedEvidence.getImageClarityLevel())));
			this->ui.quantityLineEdit->setText(QString::fromStdString(std::to_string(selectedEvidence.getQuantity())));
			this->ui.photographLineEdit->setText(QString::fromStdString(selectedEvidence.getPhotograph()));;
		});

	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &EvidenceGUI::addEvidence);
	QObject::connect(this->ui.deleteButton, &QPushButton::clicked, this, &EvidenceGUI::deleteEvidence);
	QObject::connect(this->ui.updateButton, &QPushButton::clicked, this, &EvidenceGUI::updateEvidence);
	QObject::connect(this->ui.nextButton, &QPushButton::clicked, this, &EvidenceGUI::displayNextEvidence);
	QObject::connect(this->ui.saveButton, &QPushButton::clicked, this, &EvidenceGUI::saveEvidence);
	QObject::connect(this->ui.openAppButton, &QPushButton::clicked, this, &EvidenceGUI::openDataInApplication);
	QObject::connect(this->ui.filterButton, &QPushButton::clicked, this, &EvidenceGUI::filterListOfEvidence);
	
	QObject::connect(this->ui.undoButton, &QPushButton::clicked, this, &EvidenceGUI::undo);
	QObject::connect(this->ui.redoButton, &QPushButton::clicked, this, &EvidenceGUI::redo);

	QShortcut* undoKeyShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this->ui.modeATabWidget);
	QObject::connect(undoKeyShortcut, &QShortcut::activated, this, &EvidenceGUI::undo);
	QShortcut* redoKeyShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this->ui.modeATabWidget);
	QObject::connect(redoKeyShortcut, &QShortcut::activated, this, &EvidenceGUI::redo);

	QObject::connect(this->ui.tableViewButton, &QPushButton::clicked, this, &EvidenceGUI::displayTableView);

	QObject::connect(this->ui.mylistUndoButton, &QPushButton::clicked, this, &EvidenceGUI::mylistUndo);
	QObject::connect(this->ui.mylistRedoButton, &QPushButton::clicked, this, &EvidenceGUI::mylistRedo);

	QShortcut* mylistUndoKeyShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this->ui.modeBTabWidget);
	QObject::connect(mylistUndoKeyShortcut, &QShortcut::activated, this, &EvidenceGUI::mylistUndo);
	QShortcut* mylistRedoKeyShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this->ui.modeBTabWidget);
	QObject::connect(mylistRedoKeyShortcut, &QShortcut::activated, this, &EvidenceGUI::mylistRedo);

}

void EvidenceGUI::populateMyList()
{
	this->ui.evidenceMyListWidget->clear();

	std::vector<Evidence> listOfEvidence = this->service.getAllPhysicalCopiesService();
	for (Evidence evidence : listOfEvidence)
	{
		this->ui.evidenceMyListWidget->addItem(QString::fromStdString(evidence.evidenceDataToString()));
	}
}

void EvidenceGUI::setRepositoryConfiguration()
{
	std::string configurationFile = this->ui.configurationFileLineEdit->text().toStdString();
	std::string mylistFileName = this->ui.mylistLocationLineEdit->text().toStdString();

	if (mylistFileName == "")
		this->service.setMemoryStandardUserDatabase();
	else
	{
		try
		{
			this->service.setFileStandardUserDatabase(mylistFileName);
		}
		catch (ValidationException & exception)
		{
			QMessageBox::critical(this, "Error", QString::fromStdString(exception.getMessageOfException()));
			return;
		}
	}
	
	std::ifstream fileInputStream(configurationFile.c_str());
	std::string readLineOfTheFile;
	while (fileInputStream >> readLineOfTheFile)
	{
		if (readLineOfTheFile.find("repository=") != std::string::npos)
		{
			std::string repositoryConfiguration = readLineOfTheFile.erase(0, strlen("repository="));
			if (repositoryConfiguration == "memory")
				this->service.setMemoryRepository();
			else
			{
				try
				{
					this->service.setFileRepository(repositoryConfiguration);
					break;
				}
				catch (ValidationException & exception)
				{
					QMessageBox::critical(this, "Error", QString::fromStdString(exception.getMessageOfException()));
					return;
				}
			}
					
		}
	}

	this->startProgram();
}

int EvidenceGUI::getIndexOfSelectedEvidence()
{
	QModelIndexList listOfSelectedIndexes = this->ui.evidenceListWidget->selectionModel()->selectedIndexes();

	if (listOfSelectedIndexes.size() == 0)
	{
		this->ui.evidenceIDLineEdit->clear();
		this->ui.measurementLineEdit->clear();
		this->ui.clarityLevelLineEdit->clear();
		this->ui.quantityLineEdit->clear();
		this->ui.photographLineEdit->clear();
		return -1;
	}
	return listOfSelectedIndexes.at(FIRST_SELECTED_INDEX).row();
}

void EvidenceGUI::addEvidence()
{
	std::string evidenceID, measurement, photograph;
	double imageClarityLevel;
	int quantity;
	evidenceID = this->ui.evidenceIDLineEdit->text().toStdString();
	measurement = this->ui.measurementLineEdit->text().toStdString();
	imageClarityLevel = atof(this->ui.clarityLevelLineEdit->text().toStdString().c_str());
	quantity = atoi(this->ui.quantityLineEdit->text().toStdString().c_str());
	photograph = this->ui.photographLineEdit->text().toStdString();

	try
	{
		this->service.addEvidence(evidenceID, measurement, imageClarityLevel, quantity, photograph);
		this->populateListOfEvidence();
		this->displayChart();
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

void EvidenceGUI::deleteEvidence()
{
	int indexOfSelectedEvidence = this->getIndexOfSelectedEvidence();
	if (indexOfSelectedEvidence == -1)
	{

		QMessageBox::critical(this, "Error", "No evidence was selected!");
		return;
	}
	std::string evidenceID = this->ui.evidenceIDLineEdit->text().toStdString();
	try
	{
		this->service.deleteEvidence(evidenceID);
		this->populateListOfEvidence();
		this->displayChart();
	}
	catch (InvalidIDException & exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
}

void EvidenceGUI::updateEvidence()
{
	std::string evidenceID, newMeasurement, newPhotograph;
	double newImageClarityLevel;
	int newQuantity;
	evidenceID = this->ui.evidenceIDLineEdit->text().toStdString();
	newMeasurement = this->ui.measurementLineEdit->text().toStdString();
	newImageClarityLevel = atof(this->ui.clarityLevelLineEdit->text().toStdString().c_str());
	newQuantity = atoi(this->ui.quantityLineEdit->text().toStdString().c_str());
	newPhotograph = this->ui.photographLineEdit->text().toStdString();

	try
	{
		this->service.updateEvidence(evidenceID, newMeasurement, newImageClarityLevel, newQuantity, newPhotograph);
		this->populateListOfEvidence();
		this->displayChart();
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

void EvidenceGUI::displayNextEvidence()
{
	this->populateMyList();
	try
	{
		Evidence evidenceToBeDisplayed = this->service.getNextEvidence();
		this->ui.currentEvidenceLineEdit->setText(QString::fromStdString(evidenceToBeDisplayed.evidenceDataToString()));
		this->ui.evidenceIDModeBLineEdit->setText(QString::fromStdString(evidenceToBeDisplayed.getEvidenceID()));
		
	}
	catch (std::exception& exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
}

void EvidenceGUI::saveEvidence()
{
	
	std::string evidenceID = this->ui.evidenceIDModeBLineEdit->text().toStdString();
	try
	{
		this->service.saveEvidenceToUserDatabase(evidenceID);
		//this->populateMyList();
		//this->tableViewWindow->resetTable();
	}
	catch (InvalidIDException & exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
}

void EvidenceGUI::openDataInApplication()
{
	this->service.openDataInApplication();
}

void EvidenceGUI::filterListOfEvidence()
{
	this->ui.evidenceMyListWidget->clear();

	std::string measurement = this->ui.measurementFilterLineEdit->text().toStdString();
	int quantity = atoi(this->ui.quantityFilterLineEdit->text().toStdString().c_str());
	std::vector<Evidence> listOfFilteredEvidence = this->service.filterByMeasurementAndQuantity(measurement, quantity);

	for (Evidence evidence : listOfFilteredEvidence)
	{
		this->ui.evidenceMyListWidget->addItem(QString::fromStdString(evidence.evidenceDataToString()));
	}

}

void EvidenceGUI::undo()
{
	try
	{
		this->service.undo();
		this->populateListOfEvidence();
	}
	catch (std::exception& exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
}

void EvidenceGUI::redo()
{
	try
	{
		this->service.redo();
		this->populateListOfEvidence();
	}
	catch (std::exception& exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
}

void EvidenceGUI::mylistUndo()
{
	try
	{
		this->service.mylistUndo();
		//this->populateMyList();
		//this->tableViewWindow->resetTable();
	}
	catch (std::exception & exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
}

void EvidenceGUI::mylistRedo()
{
	try
	{
		this->service.mylistRedo();
		//this->populateMyList();
		//this->tableViewWindow->resetTable();
	}
	catch (std::exception & exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
}

void EvidenceGUI::update()
{
	this->populateMyList();
}

void EvidenceGUI::displayTableView()
{
	this->tableViewWindow = new EvidenceTableViewWindow{ this->service };
	this->tableViewWindow->show();
}



// bonus - chart

QChartView* EvidenceGUI::createChart()
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
		evidenceSlice->setLabel(QString::number(evidenceSlice->percentage() * 100, 'f', 1) + "%");
	}

	QChartView* chartView = new QChartView(chart);

	return chartView;
}

void EvidenceGUI::displayChart()
{
	
	QLayoutItem* oldChart = this->ui.pieChartLayout->layout()->takeAt(0);
	delete oldChart;
	QChartView* chartView = this->createChart();
	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->resize(600, 600);
	this->ui.pieChartLayout->addWidget(chartView);
}