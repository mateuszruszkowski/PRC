#include <iostream>
#include <string>

using namespace std;

// definicja elementu listy
template <typename T>
struct Node {
	T data;
	Node* next;
};

// Wypisuje zawartosc listy na standardowe wyjscie, ktorej "glowa" zostala podana w argumencie.
template <typename T>
void showList(const Node<T>* head) {
	while (head != NULL) {
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}


// Funkcja pobiera tablice i jej wymiar. Funkcja tworzy liste jednokierunkowa obiektow struktury Node<T>, zawierajaca (jako skladowe data)
// w kolejnych wezlach kolejne elementy z przekazanej tablicy (w takiej samej kolejnosci). Funkcja zwraca wskaznik do "glowy" utworzonej listy.
template <typename T>
Node<T>* arrayToList(const T tab[], size_t size) {

	// tworzona lista (wskaznik do pierwszego elementu listy)
	Node<T> *lista = NULL;

	// wskaznik do ostatniego elementu listy w celu optymalizacji operacji dolaczania elementow listy
	Node<T> *lastElem = NULL;

	for (size_t i = 0; i < size; i++) {

		// podczepienie nowego elementu na koniec listy
		if (lastElem == NULL) {   // przypadek gdy lista nie ma jeszcze zadnych elementow
			lista = new Node<T>() { tab[i], NULL };
			lastElem = lista;
		}
		else {                 // przypadek gdy lista ma juz elementy
			lastElem->next = new Node<T>() { tab[i], NULL };
			lastElem = lastElem->next;
		}

	}

	return lista;
}

// Wydziela do osobnej listy te wezly dla ktorych funkcja (predykat) predicate zastosowana do pola data zwraca true. 
// Jako argumenty przyjmuje wskaznik do "glowy" listy oraz referencje do funckji predykatu.
// Zwraca wskaznik do glowy listy zawierajacej wezly spelniajace predykat, podczas gdy head po powrocie z funkcji zawiera
// wskaznik do "glowy" listy wezlow niespelniajacych predykatu (czyli head moze byc przez funkcje zmodyfikowane - dlatego jest 
// przekazywane przez referencje)
template<typename T>
Node<T>* extract(Node<T>*& head, bool(*predicate)(const T&)) {

	Node<T> *extractedList = NULL;
	Node<T> *extractedListLastElement = NULL;

	Node<T> *leftOverList = NULL;
	Node<T> *leftOverListLastElement = NULL;

	while (head != NULL) {		

		if ( predicate(head->data) ) {      // predykat spelniony
			if (extractedListLastElement == NULL) {
				extractedList = head;
				extractedListLastElement = head;
			}
			else {
				extractedListLastElement->next = head;
				extractedListLastElement = extractedListLastElement->next;
			}

		} else {     // predykat nie spelniony
			if (leftOverListLastElement == NULL) {
				leftOverList = head;
				leftOverListLastElement = head;
			} else {
				leftOverListLastElement->next = head;
				leftOverListLastElement = leftOverListLastElement->next;
			}
		}

		// przesuniecie wskaznika na nastepny elelement listy
		head = head->next;
	}

	// upewniam sie, ze ostatni element nie wskazuje na nic nastepnego
	// istnieje przypadek w tym algorytmie, w ktorym ostatni element ma ustawione pole next i 
	// w tym kroku eliminuje ten przypadek
	extractedListLastElement->next = NULL;
	leftOverListLastElement->next = NULL;

	// podmiana listy glownej
	head = leftOverList;

	// zwrot listy ekstrahowanej
	return extractedList;
}

// Zwalnia (za pomoca delete) wszystkie wezly listy do ktorej wskaznik przekazany zostal jako argument. Przy kazdym usuwaniu wezla funkcja drukuje
// wartosc danej z usuwanego wezla, aby bylo wiadomo 
template <typename T>
void deleteList(Node<T>*& head) {	

	while (head != NULL) {
		// element listy do usuniecia
		Node<T> *elem2del = head;

		// wypisuje usuwany element zgodnie z przykladem
		cout << "DEL " << elem2del->data << ";";

		// przesuwam wskaznik pierwszego elementu do nastepnego elementu listy
		head = head->next;

		// usuwam ten element
		delete elem2del;		
	}
	
	cout << endl;
}

bool isEven(const int& n) { return n % 2 == 0; }

bool isLong(const string& s) { return s.size() >= 5; }

int main() {

	int tabi[] = { 2, 1, 4, 3, 6, 5, 7, 8 };

	size_t sizei = sizeof(tabi) / sizeof(tabi[0]);

	Node<int> *listAi = arrayToList(tabi, sizei);

	showList(listAi);

	Node<int> *listBi = extract(listAi, isEven);

	showList(listAi);

	showList(listBi);
	
	deleteList(listAi);

	deleteList(listBi);

	string tabs[] = { "Kasia", "Ola", "Ala", "Zosia", "Ela", "Basia" };
	
	size_t sizes = sizeof(tabs) / sizeof(tabs[0]);

	Node<string> *listAs = arrayToList(tabs, sizes);

	showList(listAs);

	Node<string> *listBs = extract(listAs, isLong);

	showList(listAs);

	showList(listBs);

	deleteList(listAs);

	deleteList(listBs);
	
}
