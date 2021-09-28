#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

void umiesc_statek(int a, int plansza[7][7], vector <int> statki[3]) {

    bool ok = false;
    int x, y, z, id;

    while (ok == false) {
        ok = true;
        cout << "podaj " << a << " - masztowiec: ";
        cin >> x >> y >> z;
        if (z == 0) { //poziomo
            if (x > 6 - a) {
                cout << "podales zla lokalizacje dla wspolrzednej X";
                ok = false;
            }
            else
                for (int i = x; i < x + a; i++)
                    if (plansza[i][y] != 0) ok = false;
        }
        else if (z == 1) { //pionowo
            if (y > 6 - a) {
                cout << "podales zla lokalizacje dla wspolrzednej Y";
                ok = false;
            }
            else
                for (int i = y; i < y + a; i++)
                    if (plansza[x][i] != 0) ok = false;
        }
    }

    id = statki[2][statki->size() - 1];
    id++;
    if (z == 0) {
        for (int i = x; i < x + a; i++) {
            statki[0].push_back(i);
            statki[1].push_back(y);
            statki[2].push_back(id);
        }
    }
    else {
        for (int i = y; i < y + a; i++) {
            statki[0].push_back(x);
            statki[1].push_back(i);
            statki[2].push_back(id);
        }
    }
    for (int i = 1; i <= a; i++) {
        int xx, yy;
        xx = statki[0][statki->size() - i];
        yy = statki[1][statki->size() - i];
        for (int k = xx - 1; k <= xx + 1; k++)
            for (int l = yy - 1; l <= yy + 1; l++)
                plansza[k][l] = 9;
    }
    for (int i = 1; i <= a; i++)
        plansza[statki[0][statki->size() - i]][statki[1][statki->size() - i]] = a;
}

void umiesc_statek_k(int a, int plansza[7][7], vector <int> statki[3]) {

    bool ok = false;
    int x, y, z, id;

    while (ok == false) {
        ok = true;
        x = rand() % 5 + 1;
        y = rand() % 5 + 1;
        z = rand() % 2;
        /*cout << x << " " << y << " " << z << " " << a << endl;*/
        if (z == 0) { //poziomo
            if (x > 6 - a) ok = false;
            else
                for (int i = x; i < x + a; i++)
                    if (plansza[i][y] != 0) ok = false;
        }
        else if (z == 1) { //pionowo
            if (y > 6 - a) ok = false;
            else
                for (int i = y; i < y + a; i++)
                    if (plansza[x][i] != 0) ok = false;
        }
    }

    id = statki[2][statki->size() - 1];
    id++;
    if (z == 0) {
        for (int i = x; i < x + a; i++) {
            statki[0].push_back(i);
            statki[1].push_back(y);
            statki[2].push_back(id);
        }
    }
    else {
        for (int i = y; i < y + a; i++) {
            statki[0].push_back(x);
            statki[1].push_back(i);
            statki[2].push_back(id);
        }
    }
    for (int i = 1; i <= a; i++) {
        int xx, yy;
        xx = statki[0][statki->size() - i];
        yy = statki[1][statki->size() - i];
        for (int k = xx - 1; k <= xx + 1; k++)
            for (int l = yy - 1; l <= yy + 1; l++)
                plansza[k][l] = 9;
    }
    for (int i = 1; i <= a; i++)
        plansza[statki[0][statki->size() - i]][statki[1][statki->size() - i]] = a;
}

int strzal(int x, int y, int plansza[7][7], vector <int> statki[3]) {
    int zat = 0, id;
    if ((plansza[x][y] <= 3) && (plansza[x][y] >= 1)) {
        if (plansza[x][y] == 1) { // zatopiony
            plansza[x][y] = 0;
            zat = 2;
        }
        else {
            for (int i = 1; i < statki[2].size(); i++)
                if ((statki[0][i] == x) && (statki[1][i] == y)) {
                    id = statki[2][i];
                    statki[0][i] = 0;
                    statki[1][i] = 0;
                    statki[2][i] = 0;
                    plansza[x][y] = 0;
                }
            for (int i = 1; i < statki[2].size(); i++)
                if (statki[2][i] == id)
                    plansza[statki[0][i]][statki[1][i]]--;
            zat = 1;
        }
    }
    return zat;
}

void sortowanie_przez_wstawianie(int tab[][2], int n) {
    int j = 1, k;
    while (j <= n) {
        for (k = j; k > 0; k--)
            if (tab[k][0] > tab[k - 1][0]) {
                swap(tab[k][0], tab[k - 1][0]);
                swap(tab[k][1], tab[k - 1][1]);
            }
            else break;
        j++;
    }
}

int main()
{
    srand(time(NULL));
    const int n = 7;
    int komputer[25][2];
    string plansza11[n][n];
    vector <int> statki1[3], statki2[3];
    int zatopiony = 0, licznik = 0;

    //zerowania tablic
    for (int i = 0; i < 3; i++) {
        statki1[i].push_back(0);
        statki2[i].push_back(0);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            plansza11[i][j] = '.'; //Y X

        }
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 5; j++) {
            komputer[licznik][0] = i;
            komputer[licznik][1] = j;
            licznik++;
        }

    int plansza1[n][n] = { 0 }, plansza2[n][n] = { 0 };

    umiesc_statek(3, plansza1, statki1);
    umiesc_statek(2, plansza1, statki1);
    umiesc_statek(1, plansza1, statki1);
    umiesc_statek(1, plansza1, statki1);

    umiesc_statek_k(3, plansza2, statki2);
    umiesc_statek_k(2, plansza2, statki2);
    umiesc_statek_k(1, plansza2, statki2);
    umiesc_statek_k(1, plansza2, statki2);

    bool a = true;
    while (zatopiony < 4) {
        int x, y, z, los;

        if (a) {
        cin >> x >> y;
        z = strzal(x, y, plansza2, statki2);
        if (z == 2) {
            cout << "zatopiony" << endl;
            plansza11[x][y] = 'X';
            zatopiony++;
            a = true;
        }
        else if (z == 1) {
            cout << "trafiony" << endl;
            plansza11[x][y] = 'X';
            a = true;
        }
        else {
            plansza11[x][y] = 'O';
            a = false;
        }

        for (int i = 1; i <= 5; i++) {
            for (int j = 1; j <= 5; j++)
                cout << plansza11[j][i] << " ";
            cout << endl;
        }

        }
        else {
            los = rand() % licznik;
            x = komputer[los][0];
            y = komputer[los][1];
            cout << endl << "K: " << x << " " << y << endl;
            z = strzal(x, y, plansza1, statki1);
            for (int i = 1; i <= 5; i++) {
                for (int j = 1; j <= 5; j++)
                    cout << plansza1[j][i] << " ";
                cout << endl;
            }
        komputer[los][0] = 0;
        komputer[los][1] = 0;
        if (z == 2) {
            cout << " zatopiony" << endl;
            a = false;
        }
        else if (z == 1) {
            cout << " trafiony" << endl;
            a = false;
        }
        else {
            cout << " pudlo" << endl;
            a = true;

        }
        sortowanie_przez_wstawianie(komputer, 25);
        licznik--;
        }


        /*for (int i = 0; i < licznik; i++)
            cout << komputer[i][0] << " " << komputer[i][1] << endl;*/
    }
}

/*
#include <iostream>
//#include <string>
//#include <vector>
//NOTE Okazuje się że 5x5 tablica jest troche mała


1 2 (koordynaty statki)
1 - pionowo
0 - poziomo

5x5

2 - przyległe pola (ale w rzeczywistości ma być 9 potem)
8 - strzał



struct statekTyp { // struktura statku
	int x, y;
	int orient; // orientacja, poziomo lub pionowo
	int len; // Na przykład, jeżeli długość 0 to 
	int trafienia = 0; // Może jakiś inny sposób
};

using namespace std;

char statki_symbole[] = {
	'.', // Puste pole
	'#', // Statek
	'*', // Pole przyległe (nie można tu wstawiać)
	'O', // Pudło
	'X', // Strzał trafiony
};

void show(int p[][5]) { // p od Pole
	cout << "\n   1 2 3 4 5\n  -----------\n";
	for (int i = 0; i < 5; i++) {
		cout << i + 1 << "| ";
		for (int j = 0; j < 5; j++) {
			cout << statki_symbole[p[i][j]] << " "; // wziąć znak który odpowiada liczbie (na przykład 1 to statek więc wypisz # za niego) i wypisz
		}
		cout << endl;
	}
}

int ile_niezatopionych(statekTyp statki[], int n = 3) {
	int res = 0;
	for (int i = 0; i < n; i++)
		res += !(statki[i].trafienia == statki[i].len);
	return res;
}

void wstaw_statek(statekTyp s, int p[][5]) {
	if (s.orient == 0) { // poziomo

		for (int i = s.x - 2; i < s.x + s.len; i++)
			for (int j = s.y - 2; j < s.y + 1; j++)
				if (i >= 0 && i < 5 && j >= 0 && j < 5)	p[j][i] = 2;

		for (int i = 0; i < s.len; i++)	p[s.y - 1][i + s.x - 1] = 1; // wstaw tam gdzie jest statek
	}
	else { 			   // pionowo

		for (int i = s.x - 2; i < s.x + 1; i++)
			for (int j = s.y - 2; j < s.y + s.len; j++)
				if (i >= 0 && i < 5 && j >= 0 && j < 5)	p[j][i] = 2;

		for (int i = 0; i < s.len; i++)	p[i + s.y - 1][s.x - 1] = 1; // wstaw tam gdzie jest statek
	}
}

int znajdz_statek(statekTyp statki[], int x, int y, int n = 3) {
	for (int i = 0; i < n; i++) {
		if (statki[i].orient == 0) { // statek poziomy

			if (statki[i].y == y)
				for (int j = 0; j < statki[i].len; j++) if (statki[i].x + j == x) return i;
		}
		else { // statek pionowy

			if (statki[i].x == x)
				for (int j = 0; j < statki[i].len; j++) if (statki[i].y + j == y) return i;
		}
	}
	return -1;
}

void strzel(int x, int y, statekTyp statki[], int p[][5]) {
	int index = znajdz_statek(statki, x, y);
	if (index == -1) {
		cout << "\nPUDŁO\n";
		p[y - 1][x - 1] = 3;
	}
	else {
		if (statki[index].len == statki[index].trafienia || p[y - 1][x - 1] >= 3) cout << "\nPUDŁO\n"; // Jeżeli statek już wcześniej trafiony
		else {
			statki[index].trafienia++;
			if (statki[index].len == statki[index].trafienia)
				cout << "\n!!ZATOPIONY!!\n"; // Zatopiony jeżeli wszystkie pola już zostały trafione
			else
				cout << "\nTRAFIONY\n";
			p[y - 1][x - 1] = 4;
		}
	}
}

int main() {

	int ile_statkow = 3; // ile statków dla gracza
	int* statki_lista = new int[ile_statkow] {3, 2, 1}; // Trzyma ile i jakie statki chcemy w grze (czyli ich długość)


	statekTyp* statki_gracz1 = new statekTyp[ile_statkow];
	statekTyp* statki_gracz2 = new statekTyp[ile_statkow];

	int pole[5][5] = { 0 }; // powinno być pole1 i pole2, żeby mieć strzały gracza1 i gracza2

	for (int i = 0; i < ile_statkow; i++) { // Pętla wstawiania danych o statku
		show(pole);

		int x, y, z = 0;
		int len = statki_lista[i];

		while (true) { // Powtarzaj aż dane podane przez gracza się zgadzają
			cout << "Wpisz gdzie znajdzie się statek o długości " << len << "\nx: ";
			cin >> x;
			cout << "y: ";
			cin >> y;
			cout << "z: ";
			cin >> z;

			if (x > 5 || x < 1 || y > 5 || y < 1) { // Czy wybrano miejsce poza polem
				cout << "Miejsce poza polem!\n\n";
			}
			else {
				if (z != 0 && z != 1) { // Czy gracz podał złą orientacje statku
					cout << "Nie ma takiej orientacji statku, wybierz albo 1 albo 0!\n\n";
				}
				else {
					if ((x + len - 1 > 5 && z == 0) || (y + len - 1 > 5 && z == 1)) { cout << "Statek wychodzi poza pole!\n\n"; continue; } // Statek by wyszedł poza indexy tablicy

					int puste = 0;
					if (z == 0) {
						for (int j = 0; j < len; j++)	puste += (pole[y - 1][x + j - 1] == 0); // Sprawdz czy pola gdzie chcemy postawić statek są puste
						if (puste < len) cout << "Miejsce jest już zajęte!\n\n";
						else break; // Kończymy pętle
					}
					else {
						for (int j = 0; j < len; j++)	puste += (pole[y + j - 1][x - 1] == 0); // Sprawdz czy pola gdzie chcemy postawić statek są puste
						if (puste < len) cout << "Miejsce jest już zajęte!\n\n";
						else break; // Kończymy pętle
					}

				}
			}
		}
		// Dodaj statki tutaj
		statki_gracz1[i].x = x;
		statki_gracz1[i].y = y;
		statki_gracz1[i].orient = z;
		statki_gracz1[i].len = len;


		// I wstawić statek na pole
		wstaw_statek(statki_gracz1[i], pole);
	}

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (pole[i][j] == 2) pole[i][j] = 0; // Wyczyść przyległe pola

	while (ile_niezatopionych(statki_gracz1) > 0) {
		show(pole);
		int x, y;
		cout << "\nGdzie strzelic?\nx: ";
		cin >> x;
		cout << "y: ";
		cin >> y;

		if ((x <= 5 && x >= 1) && (y >= 1 && y <= 5)) {
			strzel(x, y, statki_gracz1, pole);
		}
		else {
			cout << "Miejsce poza polem, spróbuj jeszcze raz\n";
		}
	}
	cout << "\n\n PRZEGRAŁEŚ \n\n";
	return 0;
}
*/