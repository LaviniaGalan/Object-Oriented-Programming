#include "Service.h"
#include "Validator.h"
#include <string>
#include <sstream>
#include <exception>
#include <algorithm>


void Service::addEvidence(const std::string& evidenceID, const std::string& measurement, double imageClarityLevel, int quantity, const std::string& photograph)
{
	Evidence evidenceToBeAdded{ evidenceID, measurement, imageClarityLevel, quantity, photograph };
	try
	{
		this->repository->addEvidenceToRepository(evidenceToBeAdded);
		std::unique_ptr<Action> addAction = std::make_unique<AddAction>(*this->repository, evidenceToBeAdded);
		this->undoStack.push_back(move(addAction));
	}
	catch (DuplicateIDException)
	{
		throw DuplicateIDException();
	}
	catch (ValidationException & exception)
	{
		throw ValidationException(exception.getMessageOfException());
	}
}

std::vector<Evidence> Service::getAllEvidenceService()
{
	return this->repository->getAllEvidenceFromRepository();
}

void Service::deleteEvidence(const std::string& evidenceID)
{
	try
	{
		Evidence removedEvidence = this->repository->findEvidenceByID(evidenceID);
		this->repository->deleteEvidenceFromRepository(evidenceID);
		std::unique_ptr<Action> removeAction = std::make_unique<RemoveAction>(*this->repository, removedEvidence);
		this->undoStack.push_back(move(removeAction));
	}
	catch (NonExistentIDException)
	{
		throw NonExistentIDException();
	}
}

void Service::updateEvidence(const std::string& evidenceID, const std::string& measurement, double imageClarityLevel, int quantity, const std::string& photograph)
{
	Evidence newEvidence{ evidenceID, measurement, imageClarityLevel, quantity, photograph };
	try
	{
		Evidence oldEvidence = this->repository->findEvidenceByID(evidenceID);
		this->repository->updateEvidenceInRepository(newEvidence);
		std::unique_ptr<Action> updateAction = std::make_unique<UpdateAction>(*this->repository, oldEvidence, newEvidence);
		this->undoStack.push_back(move(updateAction));
	}
	catch (NonExistentIDException)
	{
		throw NonExistentIDException();
	}
	catch (ValidationException & exception)
	{
		throw ValidationException(exception.getMessageOfException());
	}
}

void Service::setAccessMode(char accessMode)
{
	this->accessMode = accessMode;
	indexOfNextEvidenceToBeDisplayed = 0;
}

char Service::getAccessMode()
{
	return this->accessMode;
}

int Service::indexOfNextEvidenceToBeDisplayed = 0;

std::vector<Evidence> Service::getAllPhysicalCopiesService() 
{
	return this->standardUserDatabase->getAllEvidenceFromRepository();
}

Evidence Service::getNextEvidence()
{
	int numberOfEvidencesInRepository = this->getAllEvidenceService().size();
	if (numberOfEvidencesInRepository == 0)
		throw std::length_error("No evidence in the database!");
	Evidence nextEvidence = this->getAllEvidenceService().at(indexOfNextEvidenceToBeDisplayed);
	indexOfNextEvidenceToBeDisplayed++;
	if (indexOfNextEvidenceToBeDisplayed == numberOfEvidencesInRepository)
		indexOfNextEvidenceToBeDisplayed = 0;
	return nextEvidence;
}

void Service::saveEvidenceToUserDatabase(const std::string& evidenceID)
{
	int indexOfEvidenceInRepository = this->repository->findEvidenceIndexByID(evidenceID);
	if (indexOfEvidenceInRepository == -1)
		throw NonExistentIDException();
	Evidence evidenceToBeAdded = this->getAllEvidenceService().at(indexOfEvidenceInRepository);
	try
	{
		this->standardUserDatabase->addEvidenceToRepository(evidenceToBeAdded);
		std::unique_ptr<Action> addAction = std::make_unique<AddAction>(*this->standardUserDatabase, evidenceToBeAdded);
		this->mylistUndoStack.push_back(move(addAction));

		this->notify();
	}
	catch (DuplicateIDException)
	{
		throw DuplicateIDException();
	}
}

std::vector<Evidence> Service::filterByMeasurementAndQuantity(const std::string& measurement, const int quantity)
{
	std::vector<Evidence> listOfFilteredEvidence;
	std::vector<Evidence> listOfAllEvidence = this->getAllEvidenceService();
	std::copy_if(listOfAllEvidence.begin(), listOfAllEvidence.end(), std::back_inserter(listOfFilteredEvidence),
		[quantity, measurement](Evidence evidenceFromList)
		{ return evidenceFromList.getQuantity() >= quantity && (measurement == "" || evidenceFromList.getMeasurement() == measurement); });
	return listOfFilteredEvidence;
}

void Service::setFileRepository(std::string fileName)
{
	try
	{
		StandardFileNameValidator::validateFileName(fileName);
		std::string fileExtension = fileName.substr(fileName.size() - DIMENSION_OF_EXTENSION, fileName.size() - 1);
		if (fileExtension == ".csv" || fileExtension == ".txt")
		{
			this->repository = new CSVRepository{ fileName };
		}
		else
		{
			this->repository = new HTMLRepository{ fileName };
		}

	}
	catch (ValidationException & exception)
	{
		throw ValidationException(exception.getMessageOfException());
	}
}

void Service::setMemoryRepository()
{
	this->repository = new MemoryRepository{};
}

void Service::setFileStandardUserDatabase(std::string fileName)
{
	try
	{
		StandardFileNameValidator::validateFileName(fileName);
		std::string fileExtension = fileName.substr(fileName.size() - DIMENSION_OF_EXTENSION, fileName.size() - 1);
		if ( fileExtension == ".csv")
		{
			this->standardUserDatabase = new CSVRepository{ fileName };
		}
		else
		{
			this->standardUserDatabase = new HTMLRepository{ fileName };
		}
			
	}
	catch (ValidationException & exception)
	{
		throw ValidationException(exception.getMessageOfException());
	}
}

void Service::setMemoryStandardUserDatabase()
{
	this->standardUserDatabase = new MemoryRepository{};
}


void Service::openDataInApplication()
{
	this->standardUserDatabase->openFileInApplication();
}

void Service::undo()
{
	int lastPositionInStack = this->undoStack.size() - 1;
	if (lastPositionInStack < 0)
		throw std::exception("No more undos!\n");
	this->undoStack.at(lastPositionInStack)->executeUndo();
	this->redoStack.push_back(move(this->undoStack.at(lastPositionInStack)));
	this->undoStack.erase(this->undoStack.begin() + lastPositionInStack);

}

void Service::redo()
{
	int lastPositionInStack = this->redoStack.size() - 1;
	if (lastPositionInStack < 0)
		throw std::exception("No more redos! \n");
	this->redoStack.at(lastPositionInStack)->executeRedo();
	this->undoStack.push_back(move(this->redoStack.at(lastPositionInStack)));
	this->redoStack.erase(this->redoStack.begin() + lastPositionInStack);
}

void Service::mylistUndo()
{
	int lastPositionInStack = this->mylistUndoStack.size() - 1;
	if (lastPositionInStack < 0)
		throw std::exception("No more undos!\n");
	this->mylistUndoStack.at(lastPositionInStack)->executeUndo();
	this->mylistRedoStack.push_back(move(this->mylistUndoStack.at(lastPositionInStack)));
	this->mylistUndoStack.erase(this->mylistUndoStack.begin() + lastPositionInStack);

	this->notify();
}

void Service::mylistRedo()
{
	int lastPositionInStack = this->mylistRedoStack.size() - 1;
	if (lastPositionInStack < 0)
		throw std::exception("No more undos!\n");
	this->mylistRedoStack.at(lastPositionInStack)->executeRedo();
	this->mylistUndoStack.push_back(move(this->mylistRedoStack.at(lastPositionInStack)));
	this->mylistRedoStack.erase(this->mylistRedoStack.begin() + lastPositionInStack);

	this->notify();
}


Service::~Service()
{
	delete this->repository;
	delete this->standardUserDatabase;
}


