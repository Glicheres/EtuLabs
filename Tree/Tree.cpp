#include <iostream>
#include <windows.h>

using namespace std;

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
};

struct node // узел
{
	int key;
	int height;
	node* left = 0;
	node* right = 0;
};

node* Create_Tree(int k)
{
	node* Tree = new node;
	Tree->key = k;
	return Tree;
};

void Add(node*& Tree, int key) 
{
	if (!Tree)  // если элемента нет, создадим новый 
	{
		Tree = new node;
		Tree->key = key;
		return;
	}
	else 
	{
		if (key > Tree->key)
		{
			Add(Tree->right,key);
		}
		else 
		{
			Add(Tree->left,key);
		}
	}
};

void Draww_Tree(node* Tree, int x, int y)
{
	if (Tree != 0)
	{
		gotoxy(x, y); cout << Tree->key;
		if (Tree->left != 0)
		{
			gotoxy(x - 1, y + 1); cout << "/";
			Draww_Tree(Tree->left, x - 2, y + 2);
		}
		if (Tree->right != 0)
		{
			gotoxy(x + 1, y + 1); cout << char(92);
			Draww_Tree(Tree->right, x + 2, y + 2);
		}
	}
	else { return; }
};

int main()
{
	setlocale(0, "");
	cout << "Введите циферки. Для выхода из режима ввода введите любой символ:\n";
	int k; cin >> k;
	node* Tree = Create_Tree(k);
	int i;
	while (cin >> i)
	{
		Add(Tree, i);
		Draww_Tree(Tree, 20, 2);
		gotoxy(0, 1);
	}
	Draww_Tree(Tree, 20, 2);
	system("pause");
	return 0;
}