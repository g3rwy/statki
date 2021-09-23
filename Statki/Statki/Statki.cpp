#include <iostream>
#include <string>

using namespace std;

void show(int p[][5]) {
	cout << "   1 2 3 4 5\n  -----------\n";
	for (int i = 0; i < 5; i++)
	{
		cout << i << "| ";
		for (int j = 0; j < 5; j++)
		{
			cout << p[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
    int pole[5][5] = { 0 };
	int statki[7][3];
	int x, y, z;
	cout << "Gdzie 3-masztowiec: ";
	cin >> x >> y >> z;
	if (z == 0) {
		if (x > 3)
			cout << "Zła lokalizacja dla x";

	}
	show(pole);
}
