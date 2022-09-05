#pragma once


void CreateProfile_ValidInput_ProfileCreated();

void MakeCopyOfProfile_ValidInput_aCopyIsMade();



void RepoHasGivenProfile_ValidInput_Returns1();

void RepoHasGivenProfile_InvalidInput_Returns0();

void FindProfileIndexByIdNumber_ValidInput_ReturnsIndex();

void FindProfileIndexByIdNumber_InvalidInput_ReturnsError();

void AddProfileToRepository_ValidInput_ProfileAdded();

void AddProfileToRepository_InvalidInput_ReturnError();

void DeleteProfileFromRepository_ValidInput_ProfileDeleted();

void DeleteProfileFromRepository_InvalidInput_ReturnsError();

void GetAllMatchingPsychologicalProfilesFromRepository_ValidInput_ReturnsContainerOfMatchingProfiles();

void GetAllMatchingProfilesMaximumYearsOfServiceFromRepository_ValidInput_ReturnsContainerOfMatchingProfiles();



void AddProfileService_ValidInput_Returns0();
void AddProfileService_InvalidInput_ReturnsError();

void DeleteProfileService_ValidInput_Returns0();
void DeleteProfileService_InvalidInput_ReturnsError();

void UpdateProfileService_ValidInput_Returns0();
void UpdateProfileService_InvalidInput_ReturnsError();

void ComparatorForPlaceOfBirth_ValidInput_ReturnsOrderOfPlacesOfBirth();
void SortProfiles_ValidInput_ReturnsContainerWithSortedProfiles();

void UndoService_ValidInputForAdding_UndoesTheAdding();
void UndoService_ValidInputForDeleting_UndoesTheDeletion();
void UndoService_ValidInputForUpdating_UndoesTheUpdate();
void UndoService_InvalidInput_ReturnsError();

void RedoService_ValidInputForAddingAndUndo_RedoesTheAdding();
void RedoService_ValidInputForDeletingAndUndo_RedoesTheDeletion();
void RedoService_ValidInputForUpdatingAndUndo_RedoesTheUpdate();
void RedoService_InvalidInput_ReturnsError();

void GetAllMatchingPsychologicalProfilesService_ValidInput_ReturnsContainerOfMatchingProfiles();

void GetAllMatchingProfilesMaximumYearsOfServiceSorted_ValidInput_ReturnsContainerOfMatchingProfiles();



void CreateOperation_ValidInput_OperationCreated();
void CopyOperation_ValidInput_CreatesACopyOfTheOperation();
void StackIsEmpty_ValidInput_Returns1();
void StackIsEmpty_InvalidInput_Returns0();
void StackIsFull_InvalidInput_Returns0();
void PopOperationFromStack_ValidInput_ReturnsOperation();
void PopOperationFromStack_InvalidInput_ReturnsNULL();

void CreateDynamicContainer_ValidInput_CreatesContainer();
void ResizeContainer_ValidInput_ResizesTheContainer();
void GetElementFromGivenIndex_ValidInput_ReturnsTheElement();
void GetElementFromGivenIndex_InvalidInput_ReturnsNULL();

void runTestsForDomain();
void runTestsForDynamicContainer();
void runTestsForRepository();
void runTestsForOperationStack();
void runTestsForService();
void runAllTests();
