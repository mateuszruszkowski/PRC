// PRC - ZADANIE 2
// ---------------
//
// Autor: Michal Rogozinski (s10324)
//
// Tresc Zadania:
// Na podstawie rozdzialu o wskaznikach i tablicach napisac funkcje o prototypie:
//
// double* aver(double* arr, size_t size, double& average);
// 
// która pobiera tablice liczb typu double i jej wymiar oraz zmienna average typu
// double przez referencje. Zadaniem funkcji jest wstawienie do zmiennej average
// sredniej arytmetycznej elementow tablicy oraz zwrocenie wskaznika do tego elementu
// tablicy, ktorego wartosc jest (co do modulu) najblizsza tej sredniej.
//
// Na przyklad nastepujaca funkcja main
//
// int main() {
// 	double arr[] = { 1, 2, 3, 4, 5, 7 };
//	size_t size = sizeof(arr) / sizeof(arr[0]);
//	double average = 0;
//	double* p = aver(arr, size, average);
//	cout << *p << " " << average << endl;
// }
// 
// powinna wypisac:
// 4 3.66667

#include <iostream>
using namespace std;


// funkcja rekurencyjna do wyliczania sredniej arytmetycznej z podanych elementow
double avg(double currAvg, double* elements, size_t index) {

	// Do zliczania sredniej uzywam algorytmu inkrementacyjnego:
	// a(n) = ( a(n-1)*(n-1) + v(n) ) / n
	// Glowna zaleta tego algorytmu jest brak koniecznosci sumowania wszystkich elementow zanim zostana
	// one podzielone przez ich ilosc. 
	// W tradycyjnym algorytmie liczba w liczniku moze szybko urosnac i nie zmiescic sie w zakresie danego typu
	// ktory przechowuje srednia. Zamiast tego przy kazdej inkrementacji wyliczana jest srednia, ktora
	// miesci sie bez problemu w zakresie typu. 

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


// zwraca srednia arytmetyczna z elementow tablicy liczb typu double
double avg(double* elements, size_t size) {
	// wywoluje metode rekrencyjna z podaniem poczatkowej sredniej rownej 0
	return avg(0, elements, size);
}

// Znajduje w tablicy elements najblizsza co do modulu wartosc do average i zwraca wskaznik do tego elelemntu.
double* findClosestValue(double* elements, size_t size, double average) {

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
	average = avg(arr, size);

	// znalezienie najblizszej wartosci
	return findClosestValue(arr, size, average);

}

// Program wlasciwy demonstrujacy uzycie funkcji aver
int main() {
	double arr[] = { 1, 2, 3, 4, 5, 7 };
	size_t size = sizeof(arr) / sizeof(arr[0]);
	double average = 0;
	double* p = aver(arr, size, average);
	cout << *p << " " << average << endl;
}
