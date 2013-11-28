// PRC - ZADANIE 5
// ---------------
//
// Autor: Michal Rogozinski (s10324)
//
// Tresc Zadania:
//
// Prosze napisac i przetestowac funkcje pobierajaca
//    1. tablice wskaznikow do funkcji typu double -> double,
//    2. jej wymiar,
//    3. granice przedzialu a i b (typu double),
//    4. adres zmiennej typu double,
// a zwracajaca wskaznik do funkcji typu double -> double, czyli np.:
//    typedef double(*D2D)(double);
//    // deklaracja
//    D2D wfun(D2D[], int, double, double, double*);
//    int main() {
//	     // ...
//    }
//    // definicja
//    D2D wfun(D2D* tab, int size,
//	  double a, double b, double* pxmax) {
//	     // ...
//    }
//
// Funkcja oblicza dla kazdej z funkcji wskazywanych przez elementy tablicy jej maksymalna
// wartosc na odcinku[a; b] i zwraca wskaznik do tej z funkcji, dla której to
// maksimum wypadnie najwieksze.
// Aby znalezc maksimum funkcji na odcinku, mozna "przejechac" przez ten odcinek
// z malym krokiem(np. e = 10^-4) i znajdowac w kazdym punkcie wartosc funkcji.
// Do zmiennej wskazywanej przez ostatni argument(pxmax) nalezy wpisac wartosc
// argumentu(czyli "iksa"), dla ktorego znaleziona funkcja miala najwieksza wartosc.
// W programie testowym mozna uzyc wskaznikow do funkcji bibliotecznych z naglowka
// cmath(jak sin, cos, exp) oraz przynajmniej jednej funkcji napisanej samemu.


#include <iostream>
#include <cmath>

using namespace std;

typedef double(*D2D)(double);

// deklaracje funkcji 
D2D wfun(D2D[], int, double, double, double*);
double fun_max(D2D, double, double, double*);


// ---------------------------------------------------------------------------------------
// definicje funkcji do analizy maksimum

// prosta funkcja liniowa
double funkcja1(double x) {
	return x;
}

// parabola
double funkcja2(double x) {
	return -2 * pow(x, 2) - 4 * x + 8;
}

// sinusoida z amplituda 15
double funkcja3(double x) {
	return 15 * sin(x);
}


// -------------------------------------------------------------------------------------

// Program wlasciwy demonstrujacy uzycie funkcji wfun
int main() {

	// przygotowanie tablicy wskaznikow funkcji
	// zeby bylo ich wiecej celowo niektore funkcje umieszczam podwojnie, 
	// oraz dodaje wskazniki do funkcji z biblioteki cmath
	D2D funkcje[] = { funkcja1, funkcja2, funkcja3, funkcja1, funkcja2, sin, cos };

	// rozmiar tablicy wskaznikow funkcji wyliczany automatycznie
	const int funkcje_size = sizeof(funkcje) / sizeof(*funkcje);

	// wartosc argumentu dla maksimum
	double xmax;
	

	// znajdz funkcje o najwiekszym maksimum
	D2D maxfun = wfun(funkcje, funkcje_size, -10, 10, &xmax);


	// wypisanie wszystkich funkcji
	cout << "LISTA "<< funkcje_size << " ANALIZOWANYCH FUNKCJI (REFERENCJE):" << endl;
	for (int a = 0; a < funkcje_size; a++) {
		cout << "\t" << (a+1) << ". " << funkcje[a] << endl;
	}

	// wypisanie danych o poszukiwanej funkcji
	cout << endl << endl << "Adres funkcji z najwiekszym maksimum: " << maxfun << ". Maksimum dla argumentu x=" << xmax << " osiaga wartosc f(x)="<<maxfun(xmax) << "." << endl;
	

}

// definicja wfun 
D2D wfun(D2D* tab, int size,
	double a, double b, double* pxmax) {
	
	D2D curr_max = tab[0];
	double curr_xmax;
	fun_max(tab[0], a, b, &curr_xmax);


	// przelot po wszystkich funkcjach z tablicy i wyszukanie maksimum z maksimów
	for (int f = 1; f < size; f++) {

		double tmp_xmax;

		if (fun_max(curr_max, a, b, pxmax) < fun_max(tab[f], a, b, &tmp_xmax)) {
			curr_max = tab[f];
			curr_xmax = tmp_xmax;
		}

	}

	*pxmax = curr_xmax;
	return curr_max;
}

// znajduje maksimum zadanej funkcji na przedziale <a, b>
double fun_max(D2D f, double a, double b, double* pxmax) {

	// krok do poszukiwania maksimum funkcji
	double const epsilon = 0.0001;

	// biezace maksimum
	// ustawiam domyslna wartosc na kraniec przedzialu i pomijam sprawdzanie tej wartosci w petli - oszczednosc jednej iteracji
	double curr_max = f(b);
	*pxmax = b;

	// proszty przelot przez cala funkcje i porownanie do biezacej wartosci curr_max
	for (double i = a; i < b; i += epsilon) {

		if (curr_max < f(i)) {
			curr_max = f(i);
			*pxmax = i;
		}

	}
	
	return curr_max;
}
