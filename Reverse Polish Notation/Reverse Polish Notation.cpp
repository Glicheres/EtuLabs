#include <iostream>
#include <string>
using namespace std;

struct Stack
{
	char element; // элемент
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
    stack->element = NULL;
    return stack;
}

void Push(Stack* LI,char sign)
{
    if (LI->element == NULL) 
    {
        LI->element = sign;
    }
    else 
    {
        Stack* stack = new Stack;
        stack->tail = 0;
        stack->element = sign;
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
        cout << "Номер Элемента :" << i << "\t Инфа: " << stack->element << "\tАдрес:" << stack << "\t Адрес следующего:" << stack->tail << "\n";
        stack = stack->tail;
        i++;
    }
}

void Pop(Stack* stack)
{
    Stack* Lstak = stack;
    int k = 0;
    while (stack->tail!=0) 
    {
        k++;
        Lstak = stack;
        stack = stack->tail;
    }
    char token = stack->element;
    Lstak->tail = stack->tail;
    if (k != 0)
    {
        delete stack;
    }
    else { stack->element = NULL; }
    switch (token)
    {
    case('S'): cout << "Sin"; break;
    case('C'): cout << "Cos"; break;
    case('('): case(')'): break;
    default:
        cout << token;
        break;
    }
}

// Выдаёт последний жлемент списка (написано для некоторых проверок)
char Last_el(Stack* stack)
{
    while (stack->tail != 0)
    {
        stack = stack->tail;
    }
    char token = stack->element;
    return token;
}

// ф-ция предающая символам характер (ранг (асоциативность)  )
int OprationCharater(char text) 
{
    int Character = 0;
    switch (text)
    {
    case('+'):case('-'):
        Character = 1;
        break;
    case('*'): case ('/'):
        Character = 2;
    case('^'):
        Character = 3;
    case('S'):case('C'):
        Character = 4;
    default:
        break;
    }
    return Character;
}

int main()
{
    setlocale(0, ""); 
    /*
    была идея записывать текст сразу в динамический массив, однако возникала проблема с
    его раширением что влияло на оптимизацию из за частого обращения к функции расширения массива и отчитки памяти
    (есть вариант изначально задавать длинну массива, но это скучно)
    */
    string symbols;
    getline(cin, symbols);
    int N = symbols.size();
    char* Arr = new char[N];
    Stack* stack = CreateStack();
    for (int i = 0; i < N; i++)
    {
        Arr[i] = symbols[i];
    }
    for (int i = 0; i < N; i++)
    {
        //DrawStack(stack);
        int op1 = OprationCharater(Arr[i]);
        int op2 = OprationCharater(Last_el(stack));

        switch (Arr[i])
        {            
        case ('S'):
            if (Arr[i + 1] == 'i' && Arr[i + 2] == 'n') { Push(stack, Arr[i]); i += 2; }
            break;
        case('C'):
            if (Arr[i + 1] == 'o' && Arr[i + 2] == 's') { Push(stack, Arr[i]); i += 2; }
            break;
        case('^'):
        case('*'): case ('/'):
        case ('+'): case ('-'):
        {
            // тут я столкнулся с вопросом о принципах работы самой польской нотации: 
            // при условии a+b+c получается или abc++, или ab+c+ ?
            // одни сайты пишут одно, дргие - другое: поэтмоу для 1го варианта стоит заменить 156 строку на 
         // while (Last_el(stack) != '(' & (op1 < op2)) и тогда запись изменится  \(._.)/
            while (Last_el(stack) != '(' & (op1 <= op2)) 
            {
                if (Last_el(stack) != NULL)
                {
                    Pop(stack);
                }
                else { break; }
            }
            Push(stack, Arr[i]);
            break;
        }
        case ('('): Push(stack, Arr[i]);
            break;
        case(')'):
            while (Last_el(stack) != '(') 
            {
                Pop(stack);
            }
            Pop(stack);
            break;
        default:
            cout << Arr[i];
            break;
        }
    }
    while (stack->element!=NULL)
    {
        if (Last_el(stack)!='(') 
        {
            Pop(stack);
        }
        else
        {
            break;
        }
    }
	return 0;
}