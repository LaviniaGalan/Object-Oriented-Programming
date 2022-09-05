#pragma once

template <typename TypeElement>
class DynamicVector
{

private:
	TypeElement* elements;
	int sizeOfVector;
	int capacityOfVector;

public:
	DynamicVector(int capacityOfVector = 10);

	DynamicVector(const DynamicVector& vector);

	~DynamicVector();

	DynamicVector& operator=(const DynamicVector& vector);

	void addElement(const TypeElement& elementToBeAdded);
	void deleteElementFromIndex(int indexToBeRemoved);
	void updateElementFromIndex(int indexToBeUpdated, const TypeElement newElement);

	int getSizeOfVector() const;
	TypeElement getElementFromIndex(int index);
private:
	void resizeVector(double factorOfMultiplication = 2);

public:
	class iterator {
	private:
		TypeElement* pointerToCurrentElement;
	public:
		iterator() {}
		iterator(TypeElement* pointer) : pointerToCurrentElement{ pointer } {}
		TypeElement& operator*();
		bool operator!=(const iterator& iterator);
		bool operator==(const iterator& iterator);
		iterator operator++();
		iterator operator++(int);
	};

	typename iterator startOfVector();
	typename iterator endOfVector();

};


template <typename TypeElement>
inline DynamicVector<TypeElement>::DynamicVector(int capacityOfVector)
{
	this->sizeOfVector = 0;
	this->capacityOfVector = capacityOfVector;
	this->elements = new TypeElement[capacityOfVector];

}

template <typename TypeElement>
inline DynamicVector<TypeElement>::DynamicVector(const DynamicVector& vectorToBeCopied)
{
	this->sizeOfVector = vectorToBeCopied.sizeOfVector;
	this->capacityOfVector = vectorToBeCopied.capacityOfVector;
	this->elements = new TypeElement[this->capacityOfVector];
	for (int index = 0; index < this->sizeOfVector; index++)
		this->elements[index] = vectorToBeCopied.elements[index];
}

template <typename TypeElement>
inline DynamicVector<TypeElement>::~DynamicVector()
{
	delete[] this->elements;
}

template <typename TypeElement>
inline DynamicVector<TypeElement>& DynamicVector<TypeElement>::operator=(const DynamicVector& vector)
{
	if (this == &vector)
		return *this;

	this->sizeOfVector = vector.sizeOfVector;
	this->capacityOfVector = vector.capacityOfVector;
	delete[] this->elements;
	for (int index = 0; index < this->sizeOfVector; index++)
		this->elements[index] = vector.elements[index];
	return *this;
}

template <typename TypeElement>
inline void DynamicVector<TypeElement>::resizeVector(double factorOfMultiplication)
{
	this->capacityOfVector *= static_cast<int>(factorOfMultiplication);

	TypeElement* elements = new TypeElement[this->capacityOfVector];
	for (int index = 0; index < this->sizeOfVector; index++)
		elements[index] = this->elements[index];

	delete[] this->elements;
	this->elements = elements;
}

template <typename TypeElement>
void DynamicVector<TypeElement>::addElement(const TypeElement& elementToBeAdded)
{
	if (this->sizeOfVector == this->capacityOfVector)
		this->resizeVector();
	this->elements[this->sizeOfVector++] = elementToBeAdded;
}

template <typename TypeElement>
void DynamicVector<TypeElement>::deleteElementFromIndex(int indexToBeRemoved)
{
	for (int index = indexToBeRemoved; index < this->sizeOfVector - 1; index++)
		this->elements[index] = this->elements[index + 1];
	this->sizeOfVector--;
}

template <typename TypeElement>
inline void DynamicVector<TypeElement>::updateElementFromIndex(int indexToBeUpdated, const TypeElement newElement)
{
	this->elements[indexToBeUpdated] = newElement;
}

template <typename TypeElement>
inline int DynamicVector<TypeElement>::getSizeOfVector() const
{
	return this->sizeOfVector;
}

template <typename TypeElement>
inline TypeElement DynamicVector<TypeElement>::getElementFromIndex(int index)
{
	return this->elements[index];
}

template<typename T>
inline typename DynamicVector<T>::iterator DynamicVector<T>::startOfVector()
{
	return iterator{ this->elements };
}

template<typename T>
inline typename DynamicVector<T>::iterator DynamicVector<T>::endOfVector()
{
	return iterator{ this->elements + this->sizeOfVector };
}

template<typename TypeElement>
inline TypeElement& DynamicVector<TypeElement>::iterator::operator*()
{
	return *this->pointerToCurrentElement;
}


template<typename TypeElement>
inline bool DynamicVector<TypeElement>::iterator::operator!=(const iterator& iterator)
{
	return this->pointerToCurrentElement != iterator.pointerToCurrentElement;
}

template<typename TypeElement>
inline bool DynamicVector<TypeElement>::iterator::operator==(const iterator& iterator)
{
	return this->pointerToCurrentElement == iterator.pointerToCurrentElement;
}

template<typename TypeElement>
inline typename DynamicVector<TypeElement>::iterator DynamicVector<TypeElement>::iterator::operator++()
{
	this->pointerToCurrentElement++;
	return *this;
}

template<typename TypeElement>
inline typename DynamicVector<TypeElement>::iterator DynamicVector<TypeElement>::iterator::operator++(int)
{
	iterator auxiliaryIterator{ *this };
	this->pointerToCurrentElement++;
	return auxiliaryIterator;
}