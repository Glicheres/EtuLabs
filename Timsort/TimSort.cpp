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

// нормально merge-ит
int* MergeSort(int* Arr, Helper First, Helper Second)
{
	/*cout << "Merge go";
	system("pause");*/
	int* H_Arr = new int[Second.count];
	// создаём доп массив с 2м "хэлпером" ----------------  изменить !
	for (int i = Second.pointer , j = 0; i < Second.pointer + Second.count; i++, j++)
	{
		H_Arr[j] = Arr[i];
	}
	/*cout << "Доп массив создан";
	system("pause");*/
	// тут была вспомогательная переменная k, и была она bool, получалась bool k (да, да, булка)
	// но я придумал решение без неё... Предлагаю оставить этот коментарий в память о булке!
	int i = First.pointer; // начинаем с F.p, заканчиваем F.p + F.c
	int j = 0; // тут j c 0, до S.c
	int Sumi = 0; // сумма увеличений для галопа (когда > 7, активирует спиды)
	while (i < First.count + First.pointer + Second.count  && j < Second.count )
	{
		if (H_Arr[j] < Arr[i])
		{
			for (int k = (First.pointer + First.count + Second.count-1 ); k >= i; k--)
			{
				Arr[k+1] = Arr[k]; // next item = item
			}
			Arr[i] = H_Arr[j];
			//cout << "j++ :\t";
			j++;
			// когда нашли элемент подходящий, sumi = 0, т.к.... ну куда нам скакать то ?
			Sumi = 0;
		}
		else
		{
			//  ГАЛОП
			if (j == 0) 
			{
				Sumi++;
			}
			if (Sumi < 7)
			{
				i++; // обычное увеличение стало частью галопа )
			}
			else 
			{
				int m = i;
				while (H_Arr[j] > Arr[m])
				{
					m = m + pow(2, (Sumi - 7)); // m + 2^0 = m + 1, m + 2^1 = m + 2, m + 2^2 = m + 4, m + 2^3 = m + 8 и.т.д
					Sumi++;
				}
				while (H_Arr[j] < Arr[m])
				{
					m--;
				}
				i = m;
				Sumi = 0;
			}
		}
		//cout << "i = " << i << " Arr[i] = " << Arr[i] << "\tj = " << j << " H_Arr[j] = " << H_Arr[j] << "\t" << Sumi<<"\n"; // проверка
	}
	if (j < Second.count )
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
			//cout << "i = " << i << " Arr[i] = " << Arr[i] << "\tj = " << j << " H_Arr[j] = " << H_Arr[j] << "\n"; // проверка
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

void Draww_Arr(int* Arr, int start, int end)
{
	for (int j = start; j < end; j++)
	{
		gotoxy((25 + 3 * (j % 20)), 15 + j / 20); cout << "  ";
	}
	for (int j = start; j < end; j++)
	{
		gotoxy((25 + 3 * (j % 20)), 15 + j / 20); cout << Arr[j];
	}
};

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


Stack* StackItem(Stack* beg, unsigned index, bool errMsg = true)
{
	//  Цикл заканчивается, когда 
	while (beg && (index--))
	{
		beg = beg->tail; //доступ к памяти элемента
	}
	if (errMsg && !beg)
	{
		cout << "Элемент отсутствует \n";
	}
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


	// кусочки интерфейса, ьыъ
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
	// останавливает цикл когда остаётся один Run (ему свойственно иметь размер = N)
	bool Stop = 0;

	while (i < N || Stop == 0)
	{
		// чисто для того чтоб ошибок не было с доп заходом в цикл когда  i = N уже
		if (i != N) 
		{
			// пока под i элемент > чем предыдущий или не достигнут minrun
			while ((Arr[i - 1] <= Arr[i] || (R_C < minrun)) && (i < N))
			{
				// чистим, чистим 
				for (int j = L_R_C; j < i + 1; j++)
				{
					gotoxy((25 + 3 * (j % 20)), 15 + j / 20); cout << "  ";
				}
				// если элемент меньше чем предыдущий - используем сортировку
				if (Arr[i - 1] > Arr[i])
				{
					Arr = BynarySort(Arr, L_R_C, i + 1);
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
		}
		/* Тут будет супер странная и неудобная конструкция с "if" :
		* Вы, наверное, в шоке.... Я тоже, это не круто, но так надо)
		* первая строка до || обозначает что последний элемент стека должен быть меньше предыдущего, всё что идйт дальше - 
		* банальная проверка на случай если самый последний элемент стека вдруг оказался меньше чем его предыдущий
		* Например, будут элементы X,Y,Z,W, и W - меньше чем Z. Тогда X и Y совместятся,
		* а для Z и W пришлось бы писать еще один if с абсолютно такими же командами (если удалить всё что идёт после || в 331 строке - программа зависает на случае, где N = 150)
		*/
		if (LengthStack(Run) > 1 && ((StackItem(Run, LengthStack(Run) - 2)->count <= StackItem(Run, LengthStack(Run)-1)->count) ||
			((StackItem(Run, LengthStack(Run) - 2)->count > StackItem(Run, LengthStack(Run) - 1)->count) &&
				(StackItem(Run, LengthStack(Run) - 1)->pointer + StackItem(Run, LengthStack(Run) - 1)->count) == N)))
		{
			Helper Z, Y;
			Z = Pop(Run); // создаём доп переменнные типа HElPER для удобного перемещения в функцию
			cout << "\n";
			Y = Pop(Run);
			Arr = MergeSort(Arr, Y, Z); // совмещаем их
			if (i != N) { Draww_Arr(Arr, 0, i); } // help? i need somebody, help
			else 
			{
				Draww_Arr(Arr, 0, N);
			}
			Push(Run, Y.count + Z.count, Y.pointer);
			//gotoxy(0, 20); DrawStack(Run);
		}
		if (Run->count == N)
		{
			Stop = 1;
		}
	}
	gotoxy(0, 28); system("pause");
	return 0;
}