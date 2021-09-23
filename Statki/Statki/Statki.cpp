#include <iostream>
#include <string>
#include <vector>

using namespace std;

char statki_znaki(int i) {
	switch (i)
	{
	case 0:
		return '0';
		break;
	case 1:
		return '1';
		break;
	default:
		break;
	}
}

void show(int p[][5]) {
	cout << "   1 2 3 4 5\n  -----------\n";
	for (int i = 0; i < 5; i++)
	{
		cout << i << "| ";
		for (int j = 0; j < 5; j++)
		{
			cout << statki_znaki(p[i][j]) << " ";
		}
		cout << endl;
	}
}

int main()
{
	int pole[5][5] = { 0 };
	vector<int> statki[3];

	int x, y, z;
	while (true) {
		cout << "Gdzie 3-masztowiec: ";
		cin >> x >> y >> z;

		if (z == 0) {
			if (x > 3)
				cout << "Zla lokalizacja dla x\n";
			else {
				int p = 0;
				for (int i = x - 1; i <= x + 2; i++) p += (pole[i][y - 1] != 0);
				if (p == 0) break;
			}
		}
		else if (z == 1) {
			if (y > 3)
				cout << "Zla lokazliacja dla y\n";
			else {
				int p = 0;
				for (int i = y - 1; i <= y + 2; i++) p += (pole[x - 1][i] != 0);
				if (p == 0) break;
			}
		}
		else
			break;
	}
	if (z == 0)
		int id = statki[2][statki->size() - 1];
		for (int i = x - 1; i <= x + 2; i++) {
			statki[0].push_back(i);
			statki[1].push_back(y);
			//statki[2].push_back(id);
		}

	show(pole);
}
