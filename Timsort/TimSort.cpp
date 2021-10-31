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

// ну она реально помогает работать одной функции.... в перспективе будет помогать всем. А потом всему миру.
struct Helper
{
	int pointer; int count;
};

// ну ради проверки чиста
int* MergeSort(int* Arr, Helper First, Helper Second)
{
	/*cout << "Merge go";
	system("pause");*/
	int* H_Arr = new int[Second.count];
	// создаём доп массив с 2м "хэлпером" ----------------  изменить !
	for (int i = Second.pointer, j = 0; i < Second.pointer + Second.count; i++, j++)
	{
		H_Arr[j] = Arr[i];
	}
	/*cout << "Доп массив создан";
	system("pause");*/
	// тут была вспомогательная переменная k, и была она bool, получалась bool k (да, да, булка)
	// но я придумал решение без неё... Предлагаю оставить этот коментарий в память о булке!
	int i = First.pointer; // начинаем с F.p, заканчиваем F.p + F.c
	int j = 0; // тут j c 0, до S.c
	while (i < First.count + First.pointer + Second.count && j < Second.count)
	{
		if (H_Arr[j] < Arr[i])
		{
			for (int k = First.pointer + First.count + Second.count; k >= i; k--)
			{
				Arr[k + 1] = Arr[k];
			}
			Arr[i] = H_Arr[j];
			//cout << "j++ : ";
			j++;
		}
		else
		{
			//cout << "i++ : ";
			i++;
		}
		//cout << "i = " << i << " Arr[i] = " << Arr[i] << " j = " << j << " H_Arr[j] = " << H_Arr[j] << "\n";
	}
	//system("pause");
	if (j < Second.count)
	{
		int dl = Second.count - j;
		//gotoxy(0, 15); cout << dl;
		i = i - dl;
		while (dl != 0)
		{
			Arr[i] = H_Arr[j];
			i++;
			j++;
			dl--;
			//cout << "i = " << i << " Arr[i] = " << Arr[i] << " j = " << j << " H_Arr[j] = " << H_Arr[j] << "\n";
		}
	}
	return Arr;
};

// Структура стека для хранения информации о Run
struct Stack
{
	int pointer; // указатель 
	int count; // длинна 
	Stack* tail;  // адрес следующего
};
//длинна ?
unsigned LengthStack(Stack* beg)
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
	if (LI->count == NULL)
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
		cout << "Номер Элемента :" << i << "\t Начало с : " << stack->pointer << "\tДлинна:" << stack->count << "  Адрес:" << stack << "   Адрес следующего:" << stack->tail << "\n";
		stack = stack->tail;
		i++;
	}
}

// выводим элемент по правилам стека
Helper Pop(Stack* stack)
{
	Helper X;
	if (LengthStack(stack) > 1)
	{
		Stack* AfterEl = stack; // элемент что был до этого
		while (stack->tail != 0)
		{
			AfterEl = stack;
			stack = stack->tail;
		}
		AfterEl->tail = stack->tail;
		X.count = stack->count;
		X.pointer = stack->pointer;
		delete stack;
	}
	else
	{
		int x, y;
		x = stack->count; y = stack->pointer;;
		X.count = x;
		X.pointer = y;
		stack->count = NULL;
		stack->pointer = NULL;
	}
	// вывод 
	return X;
};

void Draww_Arr(int* Arr,int start,int end) 
{
	for (int j = start; j < end; j++)
	{
		gotoxy((25 + 3 * (j % 20)), 15 + j / 20); cout << "  ";
	}
	for (int j = start; j < end ; j++)
	{
		gotoxy((25 + 3 * (j % 20)), 15 + j / 20); cout << Arr[j];
	}
}

// выводит адрес конкретного элемента стека
Stack* GetStackItem(Stack* beg, unsigned index, bool errMsg = true)
{
	//  Цикл заканчивается, когда 
	while (beg && (index--))
		beg = beg->tail; //доступ к памяти элемента
	if (errMsg && !beg)
		cout << "Элемент списка отсутствует \n";
	return beg;
};


int main()
{
	setlocale(0, "");
	int N; cout << "Введите размер массива: = ";  cin >> N;
	system("cls");
	Stack* Run = CreateStack();
	int* Arr = new int[N]; // массив для сортировки 
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
		Push(Run, R_C, L_R_C);
		L_R_C += R_C;
		gotoxy(8, 3); cout << L_R_C;
		R_C = 0;
		NRun++;
		gotoxy(8, 4); cout << NRun;
		gotoxy(0, 28); system("pause");

		// тут будет супер странная и неудобная конструкция с "if", но помоему, без неё никак
		//когда 2 и больше Run уже в стеке - проверяем их на адекватность ( X>Y ; Y>Z; X>Y+Z - иначе слияние Y с наименьшим из них)
		if (LengthStack(Run) == 2 && Run->count <= Run->tail->count) 
		{
			Helper Z, Y;
			Z = Pop(Run); // создаём доп переменнные типа HElPER для удобного перемещения в функцию
			cout << "\n";
			Y = Pop(Run);
			Arr = MergeSort(Arr, Y, Z); // совмещаем их
			Draww_Arr(Arr, Y.pointer, Y.count + Z.count);
			Push(Run, Y.pointer + Z.pointer, Y.pointer);
		}
		else // иначе или соединяем их, или у нас остался 1 элемент стека( по факту это должен быть элемент обозначающий весь массив Arr)
		{

		}
	}
	Draww_Arr(Arr, 0, N);
	gotoxy(0, 27);
	return 0;
}