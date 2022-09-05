#include "Action.h"

void AddAction::executeUndo()
{
	this->repository.deleteEvidenceFromRepository(addedEvidence.getEvidenceID());
}

void AddAction::executeRedo()
{
	this->repository.addEvidenceToRepository(addedEvidence);
}

void RemoveAction::executeUndo()
{
	this->repository.addEvidenceToRepository(removedEvidence);
}

void RemoveAction::executeRedo()
{
	this->repository.deleteEvidenceFromRepository(removedEvidence.getEvidenceID());
}

void UpdateAction::executeUndo()
{
	this->repository.updateEvidenceInRepository(this->oldEvidence);
}

void UpdateAction::executeRedo()
{
	this->repository.updateEvidenceInRepository(this->newEvidence);
}