#include <iostream>
#include <windows.h>
using namespace std;


// НУ мы же все тут любим крассивый интерфейс ?
void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

// Функция была честно стрельнута с интернета для оперативного вычисления с помощью волшебной математики MinRunов
int GetMinrun(int n)
{
	int r = 0;           /* станет 1 если среди сдвинутых битов будет хотя бы 1 ненулевой */
	while (n >= 64) {
		r |= n & 1;
		n >>= 1;
	}
	return n + r;
}

// Сортировка вставками (ну или сортировка бинарным поиском ) - быстрая по коротким дистанциям 
// n - длинна, who(кто?) - окуда начинается сортировка
int* BynarySort(int* arr, int who, int n)
{
	for (int i = who; i < n; i++)
	{
		for (int j = i; j > who && arr[j - 1] > arr[j]; j--)
		{
			swap(arr[j - 1], arr[j]); // если вы состоите в коалиции против swap можно заменить на :
			/*
			int k = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = k;
			*/
		}
	}
	return arr;
}


// Структура стека для хранения информации о Run - ах 
struct Stack
{
	int pointer; // указатель 
	int count; // длинна 
	Stack* tail;  // адрес следующего
};

unsigned LengthList(Stack* beg)
{
	unsigned length = 0;   //  Счетчик элементов списка
	while (beg)
	{
		++length; // Увеличиваем счетчик элементов списка на единицу
		beg = beg->tail; // Перемещаемся на следующий элемент списка
	}
	return length;
}

Stack* CreateStack()
{
	Stack* stack = new Stack; //Адрес элемента списка
	stack->tail = 0;
	stack->count = NULL;
	stack->pointer = NULL;
	return stack;
}
// добавляем  - Run, длинна, место в массиве
void Push(Stack* LI, int I_count, int I_Pointer)
{
	if (LI->count == NULL || LI->pointer == NULL)
	{
		LI->count = I_count;
		LI->pointer = I_Pointer;
	}
	else
	{
		Stack* stack = new Stack;
		stack->tail = 0;
		LI->count = I_count;
		LI->pointer = I_Pointer;
		while (LI->tail != 0)
		{
			LI = LI->tail;
		}
		LI->tail = stack;
	}
}

// Использовал для проверки содержимого Стека
void DrawStack(Stack* stack)
{
	int i = 1;
	while (stack)
	{
		cout << "Номер Элемента :" << i << "\t Инфа: " << stack->count << " " << stack->pointer << "\tАдрес:" << stack << "\t Адрес следующего:" << stack->tail << "\n";
		stack = stack->tail;
		i++;
	}
}
// убираем 
void Pop(Stack* stack, int* I_count, int* I_Pointer)
{
	Stack* Lstak = stack;
	int k = 0;
	while (stack->tail != 0)
	{
		k++;
		Lstak = stack;
		stack = stack->tail;
	}
	I_count = &stack->count;
	I_Pointer = &stack->pointer;
	Lstak->tail = stack->tail;
	if (k != 0)
	{
		delete stack;
	}
	else { stack->count = NULL; stack->pointer = NULL; }
}


int main()
{
	setlocale(0, "");
	int N; cout << "Введите размер массива: = ";  cin >> N;
	system("cls");
	Stack* Run = CreateStack();
	int* Arr = new int[N];
	// создаю массив с элементами от 0 до 100 ( ну можно и без них, но мы же всётаки хотим красивую сортировку.... да? )
	for (int i = 0; i < N; i++)
	{
		Arr[i] = i;
	}
	// перемешиваю его ( чтобы было что сортировать )
	for (int i = 0; i < N; i++)
	{
		swap(Arr[i], Arr[rand() % (i - N)]); // как бы меняем i элемент на один из рандомного списка 
	}

	// кусочки интерфейса ьыъ
	int minrun = GetMinrun(N); // от 32 до 65  ( какие то волшебные математические манипуляции - разобраться бы в них еще )
	gotoxy(0, 0); cout << "Min_Run = " << minrun;
	gotoxy(0, 1); cout << "I = ";
	gotoxy(0, 2); cout << "Размер тек.run = ";
	gotoxy(25, 0); cout << "МАссив до Run:";
	for (int i = 0; i < N; i++)
	{
		gotoxy((45 + 3 * (i % 10)), i / 10); cout << Arr[i]; // как бы меняем i элемент на один из рандомного списка 
	}
	gotoxy(25, 15); cout << "МАссив после Run:";

	// i - просто счётчик - начинаем с 2 чтобы сразу взять первые 2 элемента и сразу анадизировать 3ий
	// по факту 2й(ну с 0 начинаем же )
	int i = 2;

	// длинаа Run
	int R_C = 2; // c 0 начинаем же 
	// last Run Counter - фактический указатель на конец предыдущего 
	int L_R_C = 0;

	while (i < N)
	{
		// пока под i элемент > чем предыдущий или не достигнут minrun
		while (Arr[i - 1] <= Arr[i] || (R_C < minrun))
		{
			// чистим, чистим, чистим, чистим 
			for (int j = 0; j < N; j++)
			{
				gotoxy((45 + 3 * (j % 10)), 15 + j / 10); cout << "  ";
			}
			// если элемент меньше чем предыдущий - используем сортировку
			if (Arr[i - 1] > Arr[i])
			{
				Arr = BynarySort(Arr,L_R_C,i + 1);
			}
			R_C++;
			i++; // в конце переходит на сл.элемент 
			gotoxy(14, 1); cout << i;
			gotoxy(15, 2); cout << R_C;
			// Вывод: 
			for (int j = 0; j < N; j++)
			{
				gotoxy((45 + 3 * (j % 10)), 15 + j / 10); cout << Arr[j];
			}
			Sleep(300);
		}
		L_R_C += R_C;
		R_C = 0;
		gotoxy(0, 28); system("pause");
	}
	return 0;
}