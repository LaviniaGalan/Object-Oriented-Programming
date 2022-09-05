#pragma once

#include <QWidget>
#include "ui_EvidenceTableViewWindow.h"
#include "EvidenceTableModel.h"
#include "PictureDelegate.h"

class EvidenceTableViewWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	EvidenceTableViewWindow(Service& service, QWidget *parent = Q_NULLPTR);
	~EvidenceTableViewWindow();

	void setupTableView();
	void update() override;

private:
	Service& service;
	EvidenceTableModel* evidenceTableModel;
	Ui::EvidenceTableViewWindow ui;
};
