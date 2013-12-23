// PRC - ZADANIE 6
// ---------------
//
// Autor: Michal Rogozinski (s10324)
//
// Tresc Zadania:
//
// Definiujemy struktury opisujace punkt na plaszczyznie
//    struct Point {
//	     int x, y;
//    };
//
// oraz prostokat (reprezentowany przez dwa punkty: dolny-lewy i górny-prawy wierzcholek
//
//    struct Rect {
//	     Point bottom_left, top_right;
//    };
// 
// Prosze napisac i przetestowac funkcje:
// - wypisujaca informacje o punkcie: void printPoint(const Point& p);
// - wypisujaca informacje o prostokacie: void printRect(const Rect* r);
//   (a korzystajaca z printPoint);
// - sprawdzajaca, czy dwa podane prostokaty maja czesc wspolna
//   bool haveIntersection(const Rect* r1, const Rect* r2);
// - znajdujaca prostokat bedacy czescia wspólna (przecieciem) dwoch podanych
//   prostokatow: Rect intersection(const Rect* r1, const Rect* r2);
//   i zglaszajaca wyjatek, jesli podane dwa prostokaty nie maja czesci wspolnej
//   (np. throw "Error in 'intersection'";).

#include <iostream>

using namespace std;

// Struktura do przechowywania wspolrzednych punktu
struct Point {
	int x, y;
};

// Struktura do przechowywania wspolrzednych prostokata
struct Rect {
	Point bottom_left, top_right;
};

// wypisywanie koordynatow punktu
void printPoint(const Point& p) {
	cout << "(" << p.x << "," << p.y << ")";
}

// wypisywanie koordynatow prostokata
void printRect(const Rect* r) {
	cout << "[";
	printPoint(r->bottom_left);
	cout << ",";
	printPoint(r->top_right);
	cout << "]" << endl;
}

// bada czy zadane 2 prostokaty r1 i r2 maja obszar wspolny (przecinaja sie)
bool haveIntersection(const Rect* r1, const Rect* r2) {

	return !(r2->bottom_left.x > r1->top_right.x ||
		r2->top_right.x < r1->bottom_left.x ||
		r2->top_right.y < r1->bottom_left.y ||
		r2->bottom_left.y > r1->top_right.y);	
}

// zwraca przeciecie 2 zadanych prostokatow
Rect intersection(const Rect* r1, const Rect* r2) {

	Rect iRect;

	// zgodnie z warunkami zadania jesli nie ma przeciecia, to wyrzucamy wyjatek
	if (!haveIntersection(r1, r2)) {
		throw "Error in 'intersection'";
	} 

	// jesli jest przeciecie, to wyliczam koordynaty wynikowego prostokata
	iRect.bottom_left.x = (r1->bottom_left.x > r2->bottom_left.x) ? r1->bottom_left.x : r2->bottom_left.x;
	iRect.bottom_left.y = (r1->bottom_left.y > r2->bottom_left.y) ? r1->bottom_left.y : r2->bottom_left.y;
	iRect.top_right.x = (r1->top_right.x < r2->top_right.x) ? r1->top_right.x : r2->top_right.x;
	iRect.top_right.y = (r1->top_right.y < r2->top_right.y) ? r1->top_right.y : r2->top_right.y;

	return iRect;
}

// -------------------------------------------------------------------------------------

// Program wlasciwy 
int main() {

	Rect r1 = { { 1, 1 }, { 4, 3 } };
	Rect r2 = { { 2, 0 }, { 3, 4 } };
	Rect r3 = { { 0, 4 }, { 1, 5 } };

	if (haveIntersection(&r1, &r2)) {

		Rect r = intersection(&r1, &r2);
		printRect(&r);

	} else {
		cout << "No intersection" << endl;
	}

	if (haveIntersection(&r1, &r3)) {

		Rect r = intersection(&r1, &r3);
		printRect(&r);

	} else {

		cout << "No intersection" << endl;

	}

}
