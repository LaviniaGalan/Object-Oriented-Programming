#include "EvidenceTableViewWindow.h"
#include <QSortFilterProxyModel>

EvidenceTableViewWindow::EvidenceTableViewWindow(Service& service, QWidget *parent)
	: service{ service }, QWidget(parent)
{
	ui.setupUi(this);

	this->service.addObserver(this);

	this->evidenceTableModel = new EvidenceTableModel{ this->service };
	this->setupTableView();

}

void EvidenceTableViewWindow::setupTableView()
{
	ui.evidenceTableView->setModel(this->evidenceTableModel);
	ui.evidenceTableView->setItemDelegate(new PictureDelegate{});

	ui.evidenceTableView->resizeColumnsToContents();
	ui.evidenceTableView->resizeRowsToContents();
	ui.evidenceTableView->verticalHeader()->hide();
	ui.evidenceTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void EvidenceTableViewWindow::update()
{
	this->evidenceTableModel = new EvidenceTableModel{ this->service };
	this->setupTableView();
}

EvidenceTableViewWindow::~EvidenceTableViewWindow()
{
}