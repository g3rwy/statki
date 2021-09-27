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
	'.', // Puste pole
	'#', // Statek
	'*', // Pole przyległe (nie można tu wstawiać)
	'O', // Pudło
	'X', // Strzał trafiony
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

int ile_niezatopionych(statekTyp statki[], int n = 3){
	int res = 0;
	for(int i=0; i < n; i++)
		res += !(statki[i].trafienia == statki[i].len);
	return res;
}

void wstaw_statek(statekTyp s, int p[][5]){
	if(s.orient == 0){ // poziomo

		for(int i=s.x-2; i< s.x+s.len;i++)
			for(int j=s.y-2; j < s.y+1;j++)
				if(i >= 0 && i < 5 && j >= 0 && j < 5)	p[j][i] = 2;

		for(int i = 0; i < s.len ; i++)	p[s.y - 1][i + s.x - 1] = 1; // wstaw tam gdzie jest statek
	}
	else { 			   // pionowo

		for(int i=s.x-2; i< s.x + 1;i++)
			for(int j=s.y-2; j < s.y+s.len;j++)
				if(i >= 0 && i < 5 && j >= 0 && j < 5)	p[j][i] = 2;
		
		for(int i = 0; i < s.len ; i++)	p[i + s.y - 1][s.x - 1] = 1; // wstaw tam gdzie jest statek
	}
}

int znajdz_statek(statekTyp statki[],int x, int y,int n = 3){
	for(int i=0; i < n; i++){
		if(statki[i].orient == 0){ // statek poziomy

			if(statki[i].y == y)
				for(int j=0; j < statki[i].len; j++) if(statki[i].x + j == x) return i;
		}
		else{ // statek pionowy

			if(statki[i].x == x)
				for(int j=0; j < statki[i].len; j++) if(statki[i].y + j == y) return i;
		}
	}
	return -1;
}

void strzel(int x,int y, statekTyp statki[],int p[][5]) {
	int index = znajdz_statek(statki,x,y);
	if(index == -1){
		cout << "\nPUDŁO\n";
		p[y-1][x-1] = 3;
	}
	else{
		if(statki[index].len == statki[index].trafienia) cout << "\nPUDŁO\n"; // Jeżeli statek już wcześniej trafiony
		else{
			statki[index].trafienia++;
			if(statki[index].len == statki[index].trafienia)
				cout << "\n!!ZATOPIONY!!\n"; // Zatopiony jeżeli wszystkie pola już zostały trafione
			else
				cout << "\nTRAFIONY\n";
			p[y-1][x-1] = 4; 
		}
	}
}

int main(){

	int ile_statkow = 3; // ile statków dla gracza
	int* statki_lista = new int[ile_statkow] {3,2,1}; // Trzyma ile i jakie statki chcemy w grze (czyli ich długość)
	

	statekTyp* statki_gracz1 = new statekTyp[ile_statkow];
	statekTyp* statki_gracz2 = new statekTyp[ile_statkow];
	
	int pole[5][5] = {0}; // powinno być pole1 i pole2, żeby mieć strzały gracza1 i gracza2

	for(int i=0;i< ile_statkow;i++){ // Pętla wstawiania danych o statku
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

		
		// I wstawić statek na pole
		wstaw_statek(statki_gracz1[i],pole);
	}

	for(int i=0; i < 5; i++)
		for(int j=0; j < 5; j++)
			if(pole[i][j] == 2) pole[i][j] = 0; // Wyczyść przyległe pola

	while(ile_niezatopionych(statki_gracz1) > 0){
		show(pole);
		int x,y;
		cout << "\nGdzie strzelic?\nx: ";
		cin >> x;
		cout << "y: ";
		cin >> y;
		
		if((x <= 5 && x >= 1) && (y >= 1 && y <= 5)){
			strzel(x,y,statki_gracz1,pole);
		}
		else{
			cout << "Miejsce poza polem, spróbuj jeszcze raz\n";
		}
	}
	cout << "\n\n PRZEGRAŁEŚ \n\n";
	return 0;
}
