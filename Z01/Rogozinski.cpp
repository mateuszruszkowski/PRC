// PRC - ZADANIE 1 
// ---------------
//
// Autor: Michal Rogozinski (s10324)
//
// Tresc zadania: 
// Program, ktory: 
// - prosi uzytkownika o wpisanie 3 liczb naturalnych (calkowitych dodatnich)
// - Rysuje za pomoca symboli '*' lub '=' "histogram" dla tych danych, to znaczy
//   trzy slupki, wyrownane od dolu, o wysokosciach rownych trzem wpisanym liczbom. 
//   Na przyklad dla liczb 7, 2, 4 program powinien wydrukowac:
// 
//   *
//   *
//   *
//   *   *
//   *   *
//   * * *
//   * * *
//
// - Wybor symbolu powinien byc uzalezniony od zdefiniowanego makra preprocesora. 
//   Na przyklad, jesli zdefiniowane jest makro STAR, to symbolem tym powinien byc
//   znak '*', a jesli zdefiniowane jest makro EQU, to znak '='. Jesli zadne z tych
//   makr nie jest zdefiniowane, albo zdefiniowane sa obydwa, to program nie powinien 
//   sie w ogole skompilowac.

// Dla ulatwienia ponizej definicje makr w kodzie, mozna tez przekazac parametr /DSTAR albo /DEQU podczas kompilacji 
//#define STAR
//#define EQU

#include <iostream>

using namespace std;

// zwraca maksymalna wartosc sposrod podanych 2 argumentow calkowitych dodatnich
unsigned int max(unsigned int a, unsigned int b) {
	return (a > b) ? a : b;
}

// zwraca maksymalna wartosc sposrod podanych 3 argumentow calkowitych dodatnich
unsigned int max(unsigned int a, unsigned int b, unsigned int c) {	
	return max(a, max (b, c));
}

// rysuje histogram dla zadanych 3 liczb naturalnych dodatnich
void drawHistogram(unsigned int a, unsigned int b, unsigned int c) {
	
	// zgodnie z wymogami zadania wymagane jest zdefiniowanie makra preprocesora STAR albo EQU.
	// jesli zadne z nich nie jest zdefiniowane lub zdefiniowane sa oba, to powinien wystapic
	// blad kompilacji.
    #if defined STAR 
    const char symbol = '*';
    #endif

    #if defined EQU
    const char symbol = '=';
    #endif


	// rysowanie histogramu
	for (unsigned int i=max(a, b, c); i>0; i--) {
		cout << ((a >= i) ? symbol : ' ') << ' ' << ((b >= i) ? symbol : ' ') << ' ' << ((c >= i) ? symbol : ' ') << endl;
	}

}

// obsluga wejscia - od uzytkownika wymagane jest podanie 3 liczb naturalnych (calkowitych dodatnich)
void getInput(unsigned int &a, unsigned int &b, unsigned int &c) {

	cout << "Wprowadz 3 liczby naturalne dodatnie" << endl;
	cin >> a >> b >> c;

	if (!cin) {	
		cout << "Wprowadzono nieprawidlowa wartosc.";
		exit(1);
	}

}


// program wlasciwy - glowna funkcja programu
int	main() {

	unsigned int liczba1, liczba2, liczba3;

	getInput(liczba1, liczba2, liczba3);
	
	drawHistogram(liczba1, liczba2, liczba3);
	
	return 0;
}

