#include<stdio.h>
#include<Windows.h>
#include<conio.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESCAPE 27

//Pendiente por ver el video 8
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
	int vidas;
public:
	Nave(int _x, int _y, int _corazones, int _vidas);
	void pintar();
	void borrar();
	void mover(char tecla);
	void pintarCorazones();
	void morir();
};

Nave::Nave(int _x, int _y, int _corazones, int _vidas)
{
	x = _x;
	y = _y;
	corazones = _corazones;
	vidas = _vidas;
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
	printf("       ");
	gotoxy(x, y + 1);
	printf("       ");  
	gotoxy(x, y + 2);
	printf("       ");  
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
	gotoxy(50, 2);
	printf("Vidas: %i", vidas);
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

void Nave::morir() 
{
	if (corazones == 0)
	{
		borrar();
		gotoxy(x, y);     printf("   **   ");
		gotoxy(x, y + 1); printf("  ****  ");
		gotoxy(x, y + 2); printf("   **   ");
		Sleep(200);
		borrar();
		gotoxy(x, y);     printf(" * ** * ");
		gotoxy(x, y + 1); printf("  ****  ");
		gotoxy(x, y + 2); printf(" * ** * ");
		Sleep(200);
		borrar();
		vidas--;
		corazones = 3;
		pintarCorazones();
		pintar();
	}
}

class Asteroide 
{
	int x, y;
public:
	Asteroide(int _x, int _y) : x(_x), y(_y) {}
	void pintar();
	void mover();

};

void Asteroide::pintar()
{
	gotoxy(x, y); printf("%c", 184);
}

void Asteroide::mover()
{
	gotoxy(x, y); printf(" ");
	y++;
	if (y > 32)
	{
		x = rand() % 71 + 4;
		y = 4;
	}
	pintar();
}

int main()
{
	hideCursor();
	paintLimits();
	bool gameOver = false;
	Nave* nave = new Nave(7,7,3,3);
	nave->pintar();
	nave->pintarCorazones();

	Asteroide* asteroide = new Asteroide(10, 4);
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
		asteroide->mover();
		nave->morir();
		Sleep(30);
	}
	return 0;
}