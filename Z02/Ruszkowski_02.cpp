// PJC - ZADANIE 2
// ---------------
//
// Napisz funkcj¦ o prototypie
// double* aver(double* arr, size_t size, double& average);
// która pobiera tablic¦ liczb typu double i jej wymiar oraz zmienn¡ average typu do-
// uble przez referencj¦. Zadaniem funkcji jest wstawienie do zmiennej average ±redniej
// arytmetycznej elementów tablicy oraz zwrócenie wska¹nika do tego elementu tablicy,
// którego warto±¢ jest (co do moduªu) najbli»sza tej ±redniej.
// Na przykªad nast¦puj¡ca funkcja main
//
// 
//
// int main() {
// double arr[] = {1,2,3,4,5,7};
// size_t size = sizeof(arr)/sizeof(arr[0]);
// double average = 0;
// double* p = aver(arr,size,average);
// cout << *p << " " << average << endl;
// }
//
// powinna wypisa¢
// 4 3.66667

#include <iostream>
using namespace std;


// funkcja rekurencyjna do wyliczania sredniej arytmetycznej z podanych elementow
double avg(double currAvg, double* elements, size_t index) {

	if (index == 1) {
		// definicja base case
		return elements[index-1];
	} else {
		// poprzednia wartosc sredniej
		double prevAvg = avg(currAvg, elements, index - 1);
		// biezaca wartosc sredniej
		return ( prevAvg * (index-1) + elements[index-1] ) / index;
	}

}

// Znajduje w tablicy elements najblizsza co do modulu wartosc do average i zwraca wskaznik do tego elelemntu.
double* findClsValue(double* elements, size_t size, double average) {

	// najblizszy element
	double* elem = NULL;

	// przejscie przez kolejne elementy tablicy i wykonanie sprawdzenia
	for (size_t i = 0; i < size; i++) {
		if ( 
			(elem == NULL)  // przypadek pierwszej iteracji
			||	(abs(average - elements[i]) < abs(average - *elem)) ) {   // kazda nastepna iteracja

				// znaleziono element blizszy do average
				elem = &elements[i];
		}
	}

	return elem;
}


// Wylicza wartosc sredniej i wstawia ja do argumentu average przekazanego przez referencje
// oraz zwraca wskaznik do elementu, ktorego wartosc jest, co do modulu, najblizsza tej sredniej
double* aver(double* arr, size_t size, double& average) {

	// wyliczenie sredniej arytmetycznej
	average = return avg(0, elements, size);

	// znalezienie najblizszej wartosci
	return findClsValue(arr, size, average);

}

// main z zadania
int main() {
	double arr[] = { 1, 2, 3, 4, 5, 7 };
	size_t size = sizeof(arr) / sizeof(arr[0]);
	double average = 0;
	double* p = aver(arr, size, average);
	cout << *p << " " << average << endl;
}
