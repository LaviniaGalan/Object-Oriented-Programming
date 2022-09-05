#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EvidenceGUI.h"
#include "Service.h"
#include  "EvidenceTableViewWindow.h"

#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieLegendMarker>
#include <QtCharts/QChartView>

#define FIRST_SELECTED_INDEX 0
#define CONFIGURATION_TAB_INDEX 0
#define MODE_A_TAB_INDEX 1
#define MODE_B_TAB_INDEX 2
#define CHART_TAB_INDEX 3

class EvidenceGUI : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	EvidenceGUI(Service& service, QWidget *parent = Q_NULLPTR);

private:
	Ui::EvidenceGUIClass ui;
	Service& service;
	EvidenceTableViewWindow* tableViewWindow;

	void startProgram();
	void startProgramWithoutConfiguration();

	void populateListOfEvidence();
	void connectSignalsAndSlots();

	void populateMyList();

	void setRepositoryConfiguration();

	int getIndexOfSelectedEvidence();

	void addEvidence();
	void deleteEvidence();
	void updateEvidence();

	void displayNextEvidence();
	void saveEvidence();
	void openDataInApplication();
	void filterListOfEvidence();

	void undo();
	void redo();

	void mylistUndo();
	void mylistRedo();

	void update() override;

	void displayTableView();

	QtCharts::QChartView* createChart();
	void displayChart();
};

