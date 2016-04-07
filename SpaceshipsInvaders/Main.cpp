#include<stdio.h>
#include<Windows.h>
#include<conio.h>

void gotoxy(int x, int y){
	//Manejador de la consola
	HANDLE consoleHandle;
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Coordenada a la que moveremos el cursor en la consola
	COORD coordinate;
	coordinate.X = x;
	coordinate.Y = y;

	//Instruccion para mover el cursor
	SetConsoleCursorPosition(consoleHandle, coordinate);
}

int main()
{
	bool gameOver = false;
	int x = 10;
	int y = 10;
	char caracter = '*';

	gotoxy(x, y);
	printf("%c", caracter);

	while (!gameOver)
	{
		if (_kbhit())
		{
			gotoxy(x, y);
			printf(" ");
			char tecla = _getch();
			if (tecla == 'a' || tecla == 'A') x--;
			if (tecla == 'd' || tecla == 'D') x++;
			if (tecla == 's' || tecla == 'S') y++;
			if (tecla == 'w' || tecla == 'W') y--;
			if (tecla == 'q' || tecla == 'Q') gameOver = true;
			gotoxy(x, y);
			printf("%c", caracter);
		}
		Sleep(30);
	}
	return 0;
}