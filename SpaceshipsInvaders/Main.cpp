#include<stdio.h>
#include<Windows.h>
#include<conio.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESCAPE 27

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

void hideCursor() 
{
	//Manejador de la consola
	HANDLE consoleHandle;
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//Archivo de info de cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;

	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void paintLimits()
{
	for (int i = 2; i < 78; i++)
	{
		gotoxy(i, 3);
		printf("%c", 205);
		gotoxy(i, 33);
		printf("%c", 205);
	}

	for (int i = 4; i < 33; i++)
	{
		gotoxy(2, i);
		printf("%c", 186);
		gotoxy(77, i);
		printf("%c", 186);
	}

	gotoxy(2, 3);
	printf("%c", 201);
	gotoxy(2, 33);
	printf("%c", 200);
	gotoxy(77, 3);
	printf("%c", 187);
	gotoxy(77, 33);
	printf("%c", 188);
}

class Nave {
private:
	int x;
	int y;
	int corazones;
public:
	Nave(int _x, int _y, int _corazones);
	void pintar();
	void borrar();
	void mover(char tecla);
	void pintarCorazones();
};

Nave::Nave(int _x, int _y, int _corazones)
{
	x = _x;
	y = _y;
	corazones = _corazones;
}

void Nave::pintar()
{
	gotoxy(x, y);
	printf("  %c", 30); //?
	gotoxy(x, y + 1);
	printf(" %c%c%c", 40, 207, 41);  //(¤)
	gotoxy(x, y + 2);
	printf("%c%c %c%c", 30, 190, 190, 30);  //?¥ ¥?
}

void Nave::borrar()
{
	gotoxy(x, y);
	printf("     ");
	gotoxy(x, y + 1);
	printf("     ");  
	gotoxy(x, y + 2);
	printf("     ");  
}

void Nave::mover(char tecla)
{
		borrar();
		if (tecla == LEFT && x > 3) x--;
		if (tecla == RIGHT && x < 72) x++;
		if (tecla == DOWN && y < 30) y++;
		if (tecla == UP && y > 4) y--;
		if (tecla == 'e') corazones--;
		pintar();
		pintarCorazones();
}

void Nave::pintarCorazones()
{
	gotoxy(64, 2);
	printf("Salud");
	gotoxy(70, 2);
	printf("           ");
	for (int i = 0; i < corazones; i++)
	{
		gotoxy(70 + i, 2);
		printf("%c", 3);
	}
}

int main()
{
	hideCursor();
	paintLimits();
	bool gameOver = false;
	Nave* nave = new Nave(7,7,3);
	nave->pintar();
	nave->pintarCorazones();
	while (!gameOver)
	{
		if (_kbhit())
		{
			char tecla = _getch();
			switch (tecla)
			{
			case UP:
			case DOWN:
			case LEFT:
			case RIGHT:
			case 'e':
				nave->mover(tecla);
				break;
			case ESCAPE:
				gameOver = true;
				break;
			}
		}
		Sleep(30);
	}
	return 0;
}