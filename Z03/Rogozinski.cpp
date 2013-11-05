// PRC - ZADANIE 3
// ---------------
//
// Autor: Michal Rogozinski (s10324)
//
// Tresc Zadania:

// Po przeczytaniu rozdzialu na temat C - napisow (tablic znakow) napisz funkcje
//
// bool check(const char* pass);
//
// ktora pobiera haslo(jako C - napis, czyli tablice znakow) i sprawdza jego poprawnosc.
// Przyjmujemy, ze poprawne haslo zawiera
// 1. co najmniej 8 znakow;
// 2. co najmniej 6 znakow roznych;
// 3. co najmniej 1 cyfre;
// 4. co najmniej 1 duza litere;
// 5. co najmniej 1 mala litere;
// 6. co najmniej 1 znak interpunkcyjny.
//
// Funkcja zwraca true jezli haslo jest poprawne, a jezli nie, to zwraca false i wypisuje
// komunikat o przyczynie niepoprawno±ci.Mo»na zalozyc, ze znaki musza byc znakami
// ASCII o kodach w zakresie[32; 126].
// Prosze nie wykonywac wszystkich sprawdzen w jednej funkcji, bo kod staje sie wtedy
// kompletnie nieczytelny funkcja check powinna raczej wywolywac szereg malych
// funkcji pomocniczych.


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <sstream>

using namespace std;

// funkcje pomocnicze - sprawdzajace poszczegolne warunki

// 1. co najmniej 8 znakow
bool chk_min8characters(const char* pass) {

	return	(strlen(pass) >= 8);

}

// 2. co najmniej 6 znakow roznych
bool chk_min6uniq_characters(const char* pass) {

	// zgodnie z trescia zadania mozna przyjac, ze haslo sklada sie ze znakow z zakresu [32,126]
	const int CHAR_SCOPE = 95;

	// w tablicy count przechowuje ilosci wystapien znakow z interesujacego nas zakresu (sumarycznie 95 roznych znakow)
	int count[CHAR_SCOPE];

	// licznik wystapien unikalnych znakow
	int uniqueCount = 0;

	// inicjalizacja, wyzerowanie tablicy count
	for (size_t i = 0; i < CHAR_SCOPE; i++)
		count[i] = 0; 

	// zwiekszam indeks na pozycji znaku (przesuniecie 32 ze wzgledu na zakres [32,126]
	for (size_t i = 0; i < strlen(pass); i++) {
		count[ pass[i] - 32 ]++;
	}

	// zliczam pozycje niezerowe tablicy
	for (int i = 0; i < CHAR_SCOPE; i++) {
		if (count[i] > 0)
			uniqueCount++; 
	}

	// czy jest co najmniej 6 znakow unikalnych w hasle?
	return (uniqueCount >= 6);
}

// 3. co njamniej 1 cyfra
bool chk_min1digit(const char* pass) {

	for (size_t i = 0; i < strlen(pass); i++) {
		if (isdigit(pass[i]))
			return true;
	}

	return false;
}

// 4. co najmniej 1 duza litera
bool chk_min1capitalcase_character(const char* pass) {

	for (size_t i = 0; i < strlen(pass); i++) {
		if (isupper(pass[i]))
			return true;
	}

	return false;
}

// 5. co najmniej 1 mala litera
bool chk_min1lowercase_character(const char* pass) {

	for (size_t i = 0; i < strlen(pass); i++) {
		if (islower(pass[i]))
			return true;
	}

	return false;
}


// 6. co najmniej 1 znak interpunkcyjny
bool chk_min1punctuation_character(const char* pass) {

	for (size_t i = 0; i < strlen(pass); i++) {
		if (ispunct(pass[i]))
			return true;
	}

	return false;
}



// funkcja sprawdzajaca haslo zgodnie z warunkami zadania
bool check(const char* pass) {

	bool pwd_flag = true;

	// WARUNEK: dlugosc hasla minimum 8 znakow
	if (!chk_min8characters(pass)) {
		cout << "Haslo powinno miec minimum 8 znakow" << endl;
		pwd_flag = false;
	}
	
	// WARUNEK: minimum 6 roznych znakow w hasle
	if (!chk_min6uniq_characters(pass)) {
		cout << "Haslo powinno zawierac co najmniej 6 roznych znakow" << endl;
		pwd_flag = false;
	}
	
	// WARUNEK: minimum 1 cyfra w hasle
	if (!chk_min1digit(pass)) {
		cout << "Haslo powinno zawierac co najmniej 1 cyfre" << endl;
		pwd_flag = false;
	}
	
	// WARUNEK: minimum 1 wielka litera w hasle
	if (!chk_min1capitalcase_character(pass)) {
		cout << "Haslo powinno zawierac co najmniej 1 wielka litere" << endl;
		pwd_flag = false;
	}
	
	// WARUNEK: minimum 1 mala litera w hasla
	if (!chk_min1lowercase_character(pass)) {
		cout << "Haslo powinno zawierac co najmniej 1 mala litere" << endl;
		pwd_flag = false;
	}
	
	// WARUNEK: minimum 1 znak interpunkcyjny w hasle
	if (!chk_min1punctuation_character(pass)) {
		cout << "Haslo powinno zawierac co najmniej 1 znak interpunkcyjny" << endl;
		pwd_flag = false;
	}

	return pwd_flag;
}

// Program wlasciwy demonstrujacy uzycie funkcji check
// nalezy wywolac program podajac haslo jako pierwszy argument wywolania
int main(int argc, char *argv[]) {

	if (argc < 2) {
		cout << "Brak argumentu wywolania - poadaj haslo do sprawdzenia jako argument wywolania programu." << endl;
	}
	else {
		if (check(argv[1])) {
			cout << "Haslo jest poprawne" << endl;
		}
		else {
			cout << "Haslo NIE jest poprawne" << endl;
		}
	}
}
