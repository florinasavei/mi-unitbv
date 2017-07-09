#include <iostream>
using namespace std;

void separation(int nrElem, int **unseparated, int *countPositives, int **positivesList, int *countNegatives, int **negativesList) {
	*countPositives = 0;
	*countNegatives = 0;

	for (int i = 0; i < nrElem; i++) {
		if ((*unseparated)[i] >= 0) {
			(*countPositives)++;
		}
		else {
			(*countNegatives)++;
		}
	}

	*positivesList = new int(*countPositives);
	*negativesList = new int(*countNegatives);
	int aux1 = 0, aux2 = 0;

	for (int i = 0; i < nrElem; i++) {
		if ((*unseparated)[i] >= 0) {
			(*positivesList)[aux1++] = (*unseparated)[i];
		}
		else {
			(*negativesList)[aux2++] = (*unseparated)[i];
		}
	}

	delete[] * unseparated;

}

void main() {
	int i, noElems, c_positives, c_negatives, *allElems, *positives, *negatives;

	cout<<"Enter the number of elements:  ";
	cin>>noElems;

	allElems = new int[noElems];

	cout << "Enter elements of the array: " << endl;

	for (i = 0; i < noElems; i++) {
		cout << "unsorted[" << i + 1 << "]=";
		cin >> allElems[i];
	}

	separation(noElems, &allElems, &c_positives, &positives, &c_negatives, &negatives);

	cout << "The list of positive elements: ";
	for (i = 0; i < c_positives; i++) {
		cout << positives[i] << " ";
	}
	cout << endl;

	cout << "The list of negatie ekements:";
	for (i = 0; i < c_negatives; i++) {
		cout << negatives[i] << " ";
	}
	cout << endl;

	delete[]positives;
	delete[]negatives;

	cin.get();
	cin.get();

}