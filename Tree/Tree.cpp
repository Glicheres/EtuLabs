#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
};


// без деструктора и конструктора копий((((
class node
{
private:
	int Key = NULL;
	short int height;
public:
	node* left = nullptr;
	node* right = nullptr;

	short int h()
	{
		return height;
	}

	node(int k)
	{
		Key = k;
		left = NULL;
		right = NULL;
		height = 1;
	}

	short int height_correct()
	{
		if ((right == NULL) && (left == NULL)) 
		{
			return height = 1;
		}
		if (right == NULL) 
		{
			return height = left->h() + 1;
		}
		if (left == NULL) 
		{
			return height = right->h() + 1;
		}
		if ((left->h()) > (right->h())) 
		{
			height = left->h() + 1;
		}
		else 
		{
			height = right->h() + 1;
		}
		return height;
	}

	short int balance_call()
	{
		if ((right == NULL) && (left == NULL))
			return 1;
		if (right == NULL)
			return -left->h();
		if (left == NULL)
			return right->h();
		return right->h() - left->h();
	}

	int key()
	{
		return Key;
	}

	bool finder(node* Tree, int key, bool& f)
	{
		if (Tree)
		{
			f = finder(Tree->right, key, f);
			if (Tree->key() == key)
				return f = true;
			f = finder(Tree->left, key, f);
		}
		return f;
	}

	bool change(node* Tree, int key, bool& f, int change)
	{
		if (Tree)
		{
			f = Tree->change(Tree->right, key, f,change);
			if (Tree->key() == key) 
			{
				Tree->Key = change;
				return f = 1;
			}
			f = Tree->change(Tree->left, key, f, change);
		}
		return f;
	}
	void ChangeKey(int k)
	{
		Key = k;
	}
};
node* rotateR(node* Tree)
{
	node* Change = Tree->left;
	Tree->left = Change->right;
	Change->right = Tree;
	Change->height_correct();
	Tree->height_correct();
	return Change;
}

node* rotateL(node* l)
{
	node* Tree = l->right;
	l->right = Tree->left;
	Tree->left = l;
	l->height_correct();
	Tree->height_correct();
	return Tree;
}

node* toBalance(node* l)
{
	l->height_correct();
	if (l->balance_call() >= 2) // длинна больше 2 
	{
		if ((l->right)->balance_call() < 0)//rr<rl
			l->right = rotateR(l->right);//правый поворот Tree
		return rotateL(l); //левый поворот
	}
	if (l->balance_call() <= -2)  //l>Tree
	{
		if ((l->left)->balance_call() > 0) //lr>ll
			l->left = rotateL(l->left); //левый поворот l
		return rotateR(l); // правый поворот
	}
	return l;
}

node* insert(node* l, int k)
{
	if (l == nullptr)
		return toBalance(new node(k));
	if (k < l->key())
		l->left = insert(l->left, k);
	if (k > l->key())
		l->right = insert(l->right, k);
	return toBalance(l);
}

node* minNode(node* l)
{
	if (l->left != nullptr)
		return minNode(l->left);
	else
		return l;
}

node* delMin(node* l)
{
	if (l->left == nullptr)
		return l->left;
	l->left = delMin(l->left);
	return toBalance(l);
}


int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void Draww_Tree(node* Tree, int x, int y)
{
	if (Tree != 0)
	{
		gotoxy(x, y); cout << Tree->key();
		if (Tree->left != 0)
		{
			gotoxy(x - Tree->h(), y + 1); cout << "/";
			Draww_Tree(Tree->left, x - 2 - ((Tree->h() - 2) * (Tree->h() - 2)), y + 2);
		}
		if (Tree->right != 0)
		{
			gotoxy(x + Tree->h(), y + 1); cout << char(92);
			Draww_Tree(Tree->right, x + 2 + ((Tree->h() - 2) * (Tree->h() - 2)), y + 2);
		}
	}
	else { return; }
};

int main()
{
	setlocale(0, "");
	cout << "Введите первую вершину:";
	int k; cin >> k;
	node Tree(k);
	node* Link = &Tree;
	bool exit = 0; bool ex2 = 0;
	bool menu=0;
	int l = 1;
	system("cls");
	while (!exit) 
	{
		if (!menu) 
		{
			gotoxy(0, 0); cout << "Меню:";
			gotoxy(0, 1); cout << "1) Добавить элементы";
			gotoxy(0, 2); cout << "2) Проверить наличие";
			gotoxy(0, 3); cout << "3) Изменить";
			gotoxy(0, 4); cout << "esc) Выход";
			Draww_Tree(Link, 80, 1);
			menu = 1;
		}
		if (_kbhit())
		{
			switch (_getch())
			{
			case(49):
				system("cls");
				ex2 = 0;
				cout << "Для выхода из режима ввода введите -1:\n";
				while (!ex2)
				{
					cin >> l;
					if (l!=-1)
					{
						system("cls");
						Link = insert(Link, l);
						Draww_Tree(Link, 60, 1); // рисуем деревце, а начальные координаты в консоли - 60x, y 
						gotoxy(0, 0);
					}
					else { ex2 = 1; }
				}
				menu = 0;
				system("cls");
				break;
			case(50): 
				system("cls");
				cout << "Найти элемент:";
				int m;
				bool z;
				cin >> m;
				cout << m;
				Link->finder(Link, m, z);
				if (z == 1)
				{
					cout << "Элемент существует!";
					Draww_Tree(Link, 60, 1);
				}
				else { cout << "Элемент не найден(";}
				menu = 0;
				system("pause");
				system("cls");
				break;
			case(51): 
			{
				system("cls");
				int zf;
				int zz;
				bool z = 0;
				cout << "Какой элемент меняем? ";
				cin >> zf;
				cout << "\nНа что меняем? ";
				cin >> zz;
				Link->change(Link, zf, z, zz);
				if (!z) 
				{
					cout << "Зменили";
				}
				else 
				{
					cout<<"не нашли(";
				}
				Link = toBalance(Link);
				menu = 0;
				system("cls");
				break; 
			}
			case(27):
				exit = 1;
				break;
			default:
				break;
			}
		}
	}
	system("cls");
	Draww_Tree(Link, 60, 1);
	cout << "\n\n"; system("pause");
	return 0;
}