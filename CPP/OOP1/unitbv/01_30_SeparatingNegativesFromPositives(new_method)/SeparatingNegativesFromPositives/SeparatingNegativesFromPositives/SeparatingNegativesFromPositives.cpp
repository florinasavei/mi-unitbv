// This program separates negative numbers from positives number from an array that is read from the keyboard

using namespace std;
#include <iostream>

void separation(int nrElem, int *&initialList, int &positivesCounter, int *&potivesList, int &negativesCounter, int *&negativesList)
{
	positivesCounter = 0;
	negativesCounter = 0;
	for (int i = 0; i < nrElem; i++)
	{
		if (initialList[i] >= 0)
		{
			positivesCounter++;
		}
		else
		{
			negativesCounter++;
		}
	}

	potivesList = new int[positivesCounter];
	negativesList = new int[negativesCounter];

	int k = 0, h = 0;

	for (int i = 0; i < nrElem; i++)
	{
		if (initialList[i] >= 0)
		{
			potivesList[k++] = initialList[i];
		}
		else
		{
			negativesList[h++] = initialList[i];
		}
	}

	delete[]initialList;

}

void main()
{
	int i, nrElem, positivesCount, negativesCount, *elementsArray, *positivesArray, *negativesArray;
	cout << "Number of elements in the array : ";
	cin >> nrElem;
	elementsArray = new int[nrElem];
	cout << "Enter elements of the array " << endl;
	for (i = 0; i < nrElem; i++)
	{
		cout << "a[" << i + 1 << "]= ";
		cin >> elementsArray[i];
	}
	separation(nrElem, elementsArray, positivesCount, positivesArray, negativesCount, negativesArray);;//seding by reference
	cout << "The list of positive numbers: ";
	for (i = 0; i < positivesCount; i++)
	{
		cout << positivesArray[i] << " ";
	}
	cout << endl << "The list of negative numbers: ";
	for (i = 0; i < negativesCount; i++)
	{
		cout << negativesArray[i] << " ";
	}
	cout << endl;
	delete[]positivesArray;
	delete[]negativesArray;
	cin.get(); // wait for keypress
}