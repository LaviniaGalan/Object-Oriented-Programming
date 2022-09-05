#pragma once
#include "Service.h"
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qboxlayout.h>
#include <QtCharts/QChartView>

#define FIRST_SELECTED_INDEX 0


class MainApplicationWidget : public QWidget
{

private:
	Service& service;

	//items for mode A:
	QListWidget* evidenceListWidget;
	QLineEdit* evidenceIDLineEdit, * measurementLineEdit, * clarityLevelLineEdit, * quantityLineEdit, * photographLineEdit;
	QPushButton* addButton, * deleteButton, * updateButton;
	QLabel* modeALabel;

	//items for mode B:
	QListWidget* evidenceModeBListWidget;
	QPushButton* saveButton, * nextButton, *myListLocationButton;
	QLabel* modeBLabel;
	QLineEdit* myListLocationLineEdit;

	QPushButton* switchButton;

	QPushButton* chartButton;

public:
	MainApplicationWidget(Service service);
	
private:
	void initializeGUI();
	QVBoxLayout* createModeALayout();
	QVBoxLayout* createModeBLayout();
	void populateListOfEvidence();
	void connectSignalsAndSlots();

	int getIndexOfSelectedEvidence();

	void addEvidence();
	void deleteEvidence();
	void updateEvidence();

	QtCharts::QChartView* createChart();
	void displayChart();
};

