#include <iostream>
#include <string>
//#include <vector>

//NOTE Okazuje się że 5x5 tablica jest troche mała

/*

1 2 (koordynaty statki)
1 - pionowo
0 - poziomo

5x5

2 - przyległe pola (ale w rzeczywistości ma być 9 potem)
8 - strzał

*/

struct statekTyp{ // struktura statku
	int x,y;
	int orient; // orientacja, poziomo lub pionowo
	int len; // Na przykład, jeżeli długość 0 to 
	int trafienia = 0; // Może jakiś inny sposób
};

using namespace std;

char statki_symbole[] = {
	'0', // Puste pole
	'#', // Statek
	'*'  // Pole przyległe (nie można tu wstawiać)
};

void show(int p[][5]){ // p od Pole
	cout << "\n   1 2 3 4 5\n  -----------\n";
	for(int i=0; i<5; i++){
		cout << i+1 << "| ";
		for(int j=0; j<5; j++){
			cout << statki_symbole[p[i][j]] << " "; // wziąć znak który odpowiada liczbie (na przykład 1 to statek więc wypisz # za niego) i wypisz
		}
		cout << endl;
	}
}

void wstaw_statek(statekTyp s, int p[][5]){
	if(s.orient == 0){ // poziomo
		if(s.x-2 >= 0) 		 p[s.y-1][s.x - 2] 		   = 2; 	// przyległe pole na lewo od statku
		if(s.x + s.len <= 5) p[s.y-1][s.x + s.len - 1] = 2; 	// przyległe pole na prawo od statku

		for(int i = 0; i < s.len ; i++){ 				  // Wstawienie pól przyległych nad i pod statkiem
			if(s.y-2 >= 0) p[s.y-2][s.x-1 + i] = 2; 
			if(s.y < 5)	   p[s.y][s.x-1 + i]   = 2;
		}

		for(int i = 0; i < s.len ; i++)	p[s.y - 1][i + s.x - 1] = 1; // wstaw tam gdzie jest statek
	}
	else{ 			   // pionowo
		if(s.y-2 >= 0) p[s.y-2][s.x - 1] = 2; 				  // przyległe pole na górze od statku
		if(s.y + s.len <= 5) p[s.y + s.len -1][s.x - 1] = 2; // przyległe pole na dole od statku

		for(int i = 0; i < s.len ; i++){ 				    // Wstawienie pól przyległych po bokach statku
			if(s.x-2 < 5 && s.x != 1)  p[s.y-1 + i][s.x-2] = 2; //! != 1 jest po to żeby przyległe pola się nie pojawiły po drugiej stronie
			if(s.x >= 0  && s.x != 5)  p[s.y-1 + i][s.x]   = 2; //! != 5 Tutaj to samo, przyległe pola pojawiają się po drugiej stronie, a != 5 powoduje że nie wstawiają się gdy statek jest na końcu pola
		}

		for(int i = 0; i < s.len ; i++)	p[i + s.y - 1][s.x - 1] = 1; // wstaw tam gdzie jest statek
	}
}

int main(){

	int ile_statkow = 3; // ile statków dla gracza
	int statki_lista[ile_statkow] = {3,2,1}; // Trzyma ile i jakie statki chcemy w grze (czyli ich długość)
	

	statekTyp* statki_gracz1 = new statekTyp[ile_statkow];
	statekTyp* statki_gracz2 = new statekTyp[ile_statkow];
	
	int pole[5][5] = {0}; // powinno być pole1 i pole2, żeby mieć strzały gracza1 i gracza2

	for(int i=0;i< ile_statkow;i++){ // Pętla wstawiania danych o statku
		//? Czy pokazywać pole z każdym wstawieniem statku
		show(pole);
		
		int x,y,z = 0;
		int len = statki_lista[i];

		while(true){ // Powtarzaj aż dane podane przez gracza się zgadzają
			cout << "Wpisz gdzie znajdzie się statek o długości " << len <<"\nx: ";
			cin >> x;
			cout << "y: ";
			cin >> y;
			cout <<"z: ";
			cin >> z;

			if(x > 5 || x < 1 || y > 5 || y < 1){ // Czy wybrano miejsce poza polem
				cout << "Miejsce poza polem!\n\n";
			}
			else{
				if(z != 0 && z != 1){ // Czy gracz podał złą orientacje statku
					cout << "Nie ma takiej orientacji statku, wybierz albo 1 albo 0!\n\n";
				}
				else{
					if((x+len-1 > 5 && z == 0) || (y+len-1 > 5 && z == 1)){cout << "Statek wychodzi poza pole!\n\n"; continue;} // Statek by wyszedł poza indexy tablicy
					
					int puste = 0;
					if(z == 0){
						for(int j=0; j < len; j++)	puste += (pole[y-1][x + j - 1] == 0); // Sprawdz czy pola gdzie chcemy postawić statek są puste
						if(puste < len) cout << "Miejsce jest już zajęte!\n\n";
						else break; // Kończymy pętle
					}
					else{
						for(int j=0; j < len; j++)	puste += (pole[y + j - 1][x-1] == 0); // Sprawdz czy pola gdzie chcemy postawić statek są puste
						if(puste < len) cout << "Miejsce jest już zajęte!\n\n";	
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

		// Tu ustawić te pola w okół statku na pola przyległe (nie można stawiać statku obok drugiego statku)
		// I wstawić statek na pole
		wstaw_statek(statki_gracz1[i],pole);
	}

	show(pole);
	return 0;
}
