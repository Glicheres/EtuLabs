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
};

// Функция была честно стрельнута с интернета для оперативного вычисления с помощью волшебной математики MinRunов
int GetMinrun(int n)
{
	int r = 0;           /* станет 1 если среди сдвинутых битов будет хотя бы 1 ненулевой */
	while (n >= 64) {
		r |= n & 1;
		n >>= 1;
	}
	return n + r;
};

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
};

union Helper
{
	int pointer; int count;
};

// Структура стека для хранения информации о Run
struct Stack
{
	int pointer; // указатель 
	int count; // длинна 
	Stack* tail;  // адрес следующего
};
//длинна ?
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
// конструктор ?
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
		stack->count = I_count;
		stack->pointer = I_Pointer;
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
	int i = 0;
	while (stack)
	{
		cout << "Номер Элемента :" << i << "\t Инфа: " << stack->count << " " << stack->pointer << "\tАдрес:" << stack << "\t Адрес следующего:" << stack->tail << "\n";
		stack = stack->tail;
		i++;
	}
}
// убираем 
Helper Pop(Stack* stack)
{
	Stack* Lstak = stack;
	int k = 0;
	while (stack->tail != 0)
	{
		k++;
		Lstak = stack;
		stack = stack->tail;
	}
	Helper x;
	x.pointer = stack->pointer;
	x.count = stack->count;
	Lstak->tail = stack->tail;
	if (k != 0)
	{
		delete stack;
	}
	else { stack->count = NULL; stack->pointer = NULL; }
	return x;
	// вывод 
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
		if (i < 100)
		{
			Arr[i] = i;
		}
		else Arr[i] = i % 10;
	}
	// перемешиваю его ( чтобы было что сортировать )
	for (int i = 0; i < N; i++)
	{
		swap(Arr[i], Arr[rand() % (i - N)]); // как бы меняем i элемент на один из рандомного списка 
	}
	// Для проверки правильнх выделений у Run (проверял для массива в 160 элементов)
	// кусочки интерфейса ьыъ
	int minrun = GetMinrun(N); // от 32 до 65  ( какие то волшебные математические манипуляции - разобраться бы в них еще )
	gotoxy(0, 0); cout << "Min_Run = " << minrun;
	gotoxy(0, 1); cout << "I = ";
	gotoxy(0, 2); cout << "Размер тек.run = ";
	gotoxy(0, 3); cout << "L_R_C = ";
	gotoxy(0, 4); cout << "№ Run = ";
	gotoxy(20, 0); cout << "До: ";
	for (int i = 0; i < N; i++)
	{
		gotoxy((25 + 3 * (i % 20)), i / 20); cout << Arr[i];
	}
	gotoxy(15, 15); cout << "После:";

	//Работаем с Run
	/* i - просто счётчик - начинаем с 2 чтобы сразу взять первые 2 элемента и сразу анадизировать 3ий
		по факту 2й(ну с 0 начинаем же )*/
	int i = 2;
	// длинаа Run
	int R_C = 2; // c 0 начинаем же 
	// last Run Counter - фактический указатель на конец предыдущего 
	int L_R_C = 0;
	// номер run
	int NRun = 0;
	while (i < N)
	{
		// пока под i элемент > чем предыдущий или не достигнут minrun
		while ((Arr[i - 1] <= Arr[i] || (R_C < minrun))&&(i<N))
		{
			// чистим, чистим 
			for (int j = L_R_C; j < i+1; j++)
			{
				gotoxy((25 + 3 * (j % 20)), 15 + j / 20); cout << "  ";
			}
			// если элемент меньше чем предыдущий - используем сортировку
			if (Arr[i - 1] > Arr[i])
			{
				Arr = BynarySort(Arr,L_R_C,i + 1);
			}
			// выводим (ля, красиво)
			for (int j = L_R_C; j < i + 1; j++)
			{
				gotoxy((25 + 3 * (j % 20)), 15 + j / 20); cout << Arr[j];
			}
			R_C++;
			i++; // в конце переходит на сл.элемент 
			gotoxy(5, 1); cout << i;
			gotoxy(15, 2); cout << R_C;
		}
		// Вывод:  
		// куда потерялся ?
		cout << "Push";
		Push(Run, R_C, L_R_C);
		L_R_C += R_C;
		gotoxy(8, 3); cout << L_R_C;
		R_C = 0;
		NRun++;
		gotoxy(8, 4); cout << NRun;
		gotoxy(0, 28); system("pause");
	}
	// когда сортировку закончили и записали всё в стек - можно переходить к объединению
	// так же стоит добавить проверка стека на адеватность ( X>Y ; Y>Z; X>Y+Z - иначе слияние Y с наименьшим из них)
	system("cls");
	cout << Run->count <<" "<< Run->pointer;
	system("pause");
	DrawStack(Run);
	Helper Y = Pop(Run);
	gotoxy(0, 5); cout << "Counter = " << Y.count << "Counter =" << Y.pointer;
	return 0;
}