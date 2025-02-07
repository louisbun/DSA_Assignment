#include "ArrayList.h"

template class ArrayList<Actor>;

template <class T>
// constructor
ArrayList<T>::ArrayList() { size = 0; }

// add an item to the back of the list (append)
template <class T>
bool ArrayList<T>::add(T item)
{
	bool success = size < MAX_SIZE;
	if (success)
	{
		items[size] = item;    // add to the end of the list
		size++;                // increase the size by 1
	}
	return success;
}

// add an item at a specified position in the list (insert)
template <class T>
bool ArrayList<T>::add(int index, T item)
{
	bool success = (index >= 0) && (index <= size) && (size < MAX_SIZE);
	if (success)
	{  // make room for the item by shifting all items at
	   // positions >= index toward the end of the
	   // List (no shift if index == size + 1)
		for (int pos = size; pos >= index; pos--)
			items[pos] = items[pos - 1];
		// insert the item
		items[index] = item;
		size++;  // increase the size by 1
	}
	return success;
}

// remove an item at a specified position in the list
template <class T>
void ArrayList<T>::remove(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
	{  // delete item by shifting all items at positions >
	   // index toward the beginning of the list
	   // (no shift if index == size)
		for (int pos = index; pos < size; pos++)
			items[pos] = items[pos + 1];
		size--;  // decrease the size by 1
	}

}

// get an item at a specified position of the list (retrieve)
template <class T>
T ArrayList<T>::get(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
		return items[index];
	else
		return T(0, "not found", 0);
}

// check if the list is empty
template <class T>
bool ArrayList<T>::isEmpty() { return size == 0; }

// check the size of the list
template <class T>
int ArrayList<T>::getLength() { return size; }


// display the items in the list
template <class T>
void ArrayList<T>::print()
{
	for (int i = 0; i < size; i++) {
		T item = items[i];
		cout << "Actor " << i << ". " << item.getName()  << endl;
	}
}

// replace the  item in the specified index in the list
template <class T>
void ArrayList<T>::replace(int index, T item)
{
	items[index] = item;
}
