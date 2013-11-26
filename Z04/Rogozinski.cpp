// PRC - ZADANIE 4
// ---------------
//
// Autor: Michal Rogozinski (s10324)
//
// Tresc Zadania:

// Przeprowadzamy ankiete na pewien temat. Wynik pojedynczej ankiety (uzyskanej
// od jednego respondenta) zawiera nastepujace informacje, ktore nalezy zakodowac
// w jednej zmiennej typu unsigned short (mozna zalozyc, ze ma ona 2 bajty, czyli
// 16 bitów):
//    1. plec 1 bit, bo 2 mozliwosci (kobieta, mezczyzna), kodowane jako 0 lub 1;
//    2. stan cywilny 2 bity, bo 4 mozliwo±ci (panna / kawaler, mezatka / zonaty, rozw
//       odka / rozwodnik, wdowa / wdowiec) kodowane jako 0, 1, 2 lub 3;
//    3. grupa wiekowa 2 bity, bo 4 mozliwosci (np. 18 - 30, 31 - 45, 46 - 60, 60+ ) kodowane
//       jako 0, 1, 2 lub 3;
//    4. wyksztalcenie 2 bity, bo 4 mozliwo±ci (np.podstawowe, srednie, licencjat,
//       magister+) kodowane jako 0, 1, 2 lub 3;
//    5. miejsce zamieszkania 2 bity, bo 4 mozliwosci(np.wies, miasto do 50 tys.,
//       miasto 50-400 tys., miasto ponad 400 tysiecy mieszkancow) kodowane jako 0,
//       1, 2 lub 3;
//    6. region kraju 4 bity, bo (przypuscmy) jest 16 regionów ponumerowanych od
//       0 do 15;
//    7. odpowiedz na pytanie ankietera 3 bity, bo w ankiecie (przypuscmy) bylo 8
//       mozliwych odpowiedzi, ponumerowanych od 0 do 7.
//
// Napisac funkcje
// 
//    unsigned short koduj(int plec, int stan_cyw, int grupa_wiek, int edu, int zam, int region, int odp);
//
// ktora pobiera 7 liczb (jak wyzej), koduje informacje w nich zawarte w jednej zmiennej
// typu unsigned short i zwraca ta jedna liczbe do funkcji wywolujacej.
// 
// Napisac rowniez funkcje
//
//    void info(unsigned short kod);
// 
// ktora pobiera jeden argument typu unsigned short zawierajacy informacje o jednej
// ankiecie i wypisuje te informacje, np.w formie:
//    plec : 0
//	  stan cywilny : 3
//	  grupa wiekowa : 2
//    wyksztalcenie : 3
//    miejsce zam. : 0
//    region : 12
//    odpowiedz : 6


#include <iostream>

// stale z informacja o przesunieciu bitowym / miejscu skladowania informacji o danej odpowiedzi
#define A_PLEC 15
#define A_STAN_CYW 13
#define A_GRUPA_WIEK 11
#define A_EDU 9
#define A_ZAM 7
#define A_REGION 3
#define A_ODP 0

using namespace std;

// Metoda kodujaca odpowiedzi do ankiety do zapisu binarnego na 2 bajtach
unsigned short koduj(int plec, int stan_cyw, int grupa_wiek, int edu, int zam, int region, int odp) {

	return (plec << A_PLEC) 
		| (stan_cyw << A_STAN_CYW) 
		| (grupa_wiek << A_GRUPA_WIEK) 
		| (edu << A_EDU) 
		| (zam << A_ZAM) 
		| (region << A_REGION)
		| (odp << A_ODP);
	
}

// metoda odkodowujaca i wyswietlajaca na ekran wyniki ankiety z zapisu binarnego dwubajtowego
void info(unsigned short kod) {

	cout << "Plec:\t" << ( ( kod & ( 1 << A_PLEC ) ) >> A_PLEC ) << endl
		<< "stan cywilny:\t" << ( ( kod & ( 3 << A_STAN_CYW ) ) >> A_STAN_CYW ) << endl
		<< "grupa wiekowa:\t" << ( ( kod & ( 3 << A_GRUPA_WIEK ) ) >> A_GRUPA_WIEK ) << endl
		<< "wyksztalcenie:\t" << ( ( kod & ( 3 << A_EDU ) ) >> A_EDU ) << endl
		<< "miejsce zam:\t" << ( ( kod & ( 3 << A_ZAM ) ) >> A_ZAM ) << endl
		<< "region:\t" << ( ( kod & ( 15 << A_REGION ) ) >> A_REGION ) << endl
		<< "odpowiedz:\t" << ( ( kod & ( 7 << A_ODP ) ) >> A_ODP ) << endl;

}



// Program wlasciwy demonstrujacy uzycie funkcji check
int main() {	

	// wywolanie testowej metody zakodowania i odkodowania odpowiedzi do antkiety
	info(koduj(0,0,0,0,0,0,0));

}
