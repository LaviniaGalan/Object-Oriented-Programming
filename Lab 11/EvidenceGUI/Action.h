#pragma once
#include "Repository.h"
class Action
{
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
};

class AddAction : public Action
{
private:
	Repository& repository;
	Evidence addedEvidence;
public:
	AddAction(Repository& repo, Evidence evidence) : repository(repo), addedEvidence(evidence) {};
	void executeUndo() override;
	void executeRedo() override;
};


class RemoveAction : public Action
{
private:
	Repository& repository;
	Evidence removedEvidence;
public:
	RemoveAction(Repository& repo, Evidence evidence) : repository(repo), removedEvidence(evidence) {};
	void executeUndo() override;
	void executeRedo() override;
};


class UpdateAction : public Action
{
private:
	Repository& repository;
	Evidence oldEvidence;
	Evidence newEvidence;
public:
	UpdateAction(Repository& repo, Evidence oldEvidence, Evidence newEvidence) : repository(repo), oldEvidence(oldEvidence), newEvidence(newEvidence) {};
	void executeUndo() override;
	void executeRedo() override;
};