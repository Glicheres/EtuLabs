#include <windows.h>
#include <conio.h>
#include <string>

#include <iostream>

using namespace std;



/*
* � ����� ���������� ��� ������� � ���������
* ������ �� ��������������, ��������������� �� ��������������, ����� �� ��������������, �� ��� ��������)
* �������� ���� - ���� �������� �������, � � ��������� �� ��� �������� ������ � �������������.... �������� ����((((((
* ��� ����....
* � ���� ���������� ���� ����� ����� �� ����, � ����� ������� � ����, ��� �� ���� ������ � �� �������.
* � �����, �� ��� �� �������, ��� �������, ��� � ������, �����.
*/


// �������� �������� ��������
struct graf
{
    string First;
    string Second;
    int unsigned number;
};

// ����������� ������ ��� �������� ������
struct Linked_list
{
    graf data; //������ 
    Linked_list* tail; //����� ���������� ��������
};

//������
unsigned LengthList(Linked_list* beg)
{
    unsigned length = 0;   //  ������� ��������� ������
    // �������� � ������ ������
    while (beg)
    {
        // ����������� ������� ��������� ������ �� �������
        ++length;
        // ������������ �� ��������� ������� ������
        beg = beg->tail;
    }
    return length;
}

//������ 
Linked_list* CreateList()
{
    Linked_list* Curr = 0; //����� �������� ������
    
    return Curr;
}
Linked_list* CreateList(unsigned Lenght)
{
    Linked_list* Curr = 0; //����� �������� ������
    Linked_list* Next = 0; //����� ���������� ��������
    for (unsigned i = 1; i <= Lenght; ++i) //������ �������� � ���������� ��������
    {
        Curr = new Linked_list; // ������� ������� ������  
        Curr->tail = Next; // � ������ ����� ���������� ����� ���������� ��������
        Next = Curr; // �.� ��� ����� ������ - ��� ��������
    }
    // �� � ������ curr - ��� ����� ������� ��������))
    Linked_list* List = Curr;
    while (Curr) //������ ������
    {
        cin >> Curr->data.First >> Curr->data.Second >> Curr->data.number;
        Curr = Curr->tail; //��������� � ����������
    }
    Curr = List;
    return Curr;
}
Linked_list* CreateList(unsigned Lenght, graf graph)
{
    Linked_list* Curr = 0; //����� �������� ������
    Linked_list* Next = 0; //����� ���������� ��������
    for (unsigned i = 1; i <= Lenght; ++i) //������ ������ � ���������� ��������
    {
        Curr = new Linked_list; // ������� ������� ������  
        Curr->tail = Next; // � ������ ����� ���������� ����� ���������� ��������
        Next = Curr; // �.� ��� ����� ������ - ��� ��������
    }
    // �� � ������ curr - ��� ����� ������� ��������))
    Linked_list* List = Curr;
    while (Curr) //������ ������
    {
        Curr->data = graph;
        Curr = Curr->tail; //��������� � ����������
    }
    Curr = List;
    return Curr;
}

//������� ��� ���������
void DeleteList(Linked_list*& Beg)
{
    Linked_list* Next;  // ��������� �� ��������� ������� ������
    // �������� � ������ ������
    while (Beg)
    {
        Next = Beg->tail;
        delete Beg;
        Beg = Next;
    }
}

//������  �� ��� �����
void DrawList(Linked_list* Curr)
{
    int i = 1;
    while (Curr)
    {
        cout << "����� �������� :" << i << "\t ����: " << Curr->data.First << " " << Curr->data.Second << " " << Curr->data.number<<"\n";
        Curr = Curr->tail;
        i++;
    }
}

// ����� ���������� - ������ � ������������ �������� � ������(������, � �� ��� �������)
Linked_list* ListItem(Linked_list* beg, unsigned index, bool errMsg = true)
{
    //  ���� �������������, ����� 
    while (beg && (index--))
        beg = beg->tail; //������ � ������ ��������
    if (errMsg && !beg)
        cout << "������� ������ ����������� \n";
    return beg;
}

//������� �������
void t_New(Linked_list* beg, unsigned k, graf graph)
{
    if (k > LengthList(beg) + 1 || k < 1) { return; }
    Linked_list* Item = new Linked_list;
    Item->data = graph;
    if (k == 1)
    {
        Linked_list* LItem = ListItem(beg, k - 1, 1); // ����� ��������������, �� ��� ����
        Item->tail = LItem->tail;
        LItem->tail = Item;
        Item->data = LItem->data;
        LItem->data = graph;
    }
    if (k > 1)
    {
        Linked_list* LItem = ListItem(beg, k - 2, 0);
        Item->tail = LItem->tail;
        LItem->tail = Item;
    }

}

//������� �������
void DelItem(Linked_list*& Beg, unsigned Index)
{
    if (Index >= LengthList(Beg))
        return;
    Linked_list* Item;
    if (!Index)
    {
        Item = Beg->tail;
        delete Beg;
        Beg = Item;
        return;
    }
    Item = ListItem(Beg, Index - 1, 0);
    Linked_list* DItem = Item->tail;
    Item->tail = DItem->tail;
    delete DItem;
}

// ������ �������
void ChangeItem(Linked_list* Beg, int change_number, graf graph)
{
    while (change_number < 1 || change_number> LengthList(Beg))
    {
        cout << "�������� ����� - ������� �����: ";
        cin >> change_number;

        if (change_number > LengthList(Beg) || change_number < 1)
            return;
        Linked_list* LItem = ListItem(Beg, change_number - 1, 0);
        LItem->data = graph;
    }

}

//������� � ������������ ��������
void DeleteAfter(Linked_list* Beg, unsigned k)
{
    Linked_list* Next = 0;
    while (k < 1 || k> LengthList(Beg))
    {
        cout << "�������� ����� - ������� �����: ";
        cin >> k;
    }
    Linked_list* List = ListItem(Beg, k - 1, 0);
    Linked_list* MList = ListItem(Beg, k, 0); // ��������������(������������ ����������)
    DeleteList(MList);
    List->tail = 0;// �������� ������ � ������������� (����� ����� �� ��������)
}

//������� � ����� �� �����
void DeleteBefore(Linked_list* Beg, int k, int m)
{
    Linked_list* Next = 0; // �� �������� � �������� �������� ���������
    while (k < 1 || k> LengthList(Beg))
    {
        cout << "�������� ����� - ������� �����: ";
        cin >> k;
    }
    while (m < 1 || m> LengthList(Beg))
    {
        cout << "�������� ����� - ������� �����: ";
        cin >> m;
    }
    if (k < m)
    {
        Linked_list* List = ListItem(Beg, k - 1, 0);
        Linked_list* HaList = ListItem(Beg, k, 0);
        Linked_list* MList = ListItem(Beg, m - 1, 0);
        while (k != (m - 1))
        {
            Next = HaList->tail;
            delete HaList;
            HaList = Next;
            k++;
        }
        List->tail = MList; // �������� ������ ����� �� �������
    }
    else { return; }
}

// ����������� ������ �� 3� ����� � ��������� graf 
graf convert(string text[3]) 
{

    graf one;
    // Use std::stoi() to convert string to integer
    try
    {
        // Wrap up code in try-catch block if string is not validated
        one.number = stoi(text[2]);
        one.First = text[0]; one.Second = text[1];
    }
    catch (std::invalid_argument e)
    {
        cout << "Caught Invalid Argument Exception\n";
        one.First = text[0]; one.Second = text[1]; //  ����� ���������� ������� ������ 
    }
    return one;
}

// ���� �� �������
Linked_list* get_input_data() 
{
    Linked_list* input_dat = CreateList();
    bool exit = 0;
    string text[3];
    int i = 0; // �������� �� ���� ����
    bool j = 0; // �������� ����������, ������ �� ��� ��� "����"
    while (!exit)
    {
        switch (_kbhit())
        {
        case 1:
        {
            char ch = _getche();
            int  code = static_cast<int>(ch);
            switch (code)
            {
            case(27):
                exit = 1; // esc - �����.
                break;
            case (13):
                // enter
                if (j == 0)
                {
                    graf one = convert(text);
                    input_dat = CreateList(1, one);
                    j = 1;
                }
                else
                {
                    graf one = convert(text);
                    t_New(input_dat, LengthList(input_dat) + 1, one);
                }
                i = 0;
                text[0] = ""; text[1] = ""; text[2] = "";
                cout << "\n";
                break;
            case (32):
                // ������ ������� ������� � ������ �� 3� ����.
                i++;
                break;
            default:
                text[i] += ch;
                break;
            }
        }
        }
    }
    DrawList(input_dat);
    return input_dat;

}

//���� �� �����
Linked_list* Get_in_file(string dyrectory)
{
    std::ifstream file(dyrectory, ios_base::in); // ������ ����� ���!

    if (!file.is_open())
    {
        std::cout << "Failed to open file\n";
    }
    graf input;
    Linked_list* points = CreateList();
    bool j = 0;
    while (file)
    {
        file >> input.First >> input.Second >> input.number;
        if (j == 0)
        {
            points = CreateList(1, input);
            j = 1;
        }
        else
        {
            t_New(points, LengthList(points) + 1, input);
        }
    }
    file.close();
    DelItem(points, LengthList(points) - 1); // ���� ��� �������(
    return points;
}

// ������� ����������
void quickSort(Linked_list* array, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = ListItem(array, (i + j) / 2)->data.number;
    graf temp;

    while (i <= j)
    {
        while (ListItem(array, i)->data.number < pivot)
            i++;
        while (ListItem(array, j)->data.number > pivot)
            j--;
        if (i <= j)
        {
            temp = ListItem(array, i)->data;
            ListItem(array, i)->data = ListItem(array, j)->data;
            ListItem(array, j)->data = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(array, low, j);
    if (i < high)
        quickSort(array, i, high);
}


struct Universal_points
{
    string points; //������ 
    Universal_points* tail; //����� ���������� ��������
};
Universal_points* U_P_Create(string point)
{
    Universal_points* N_U_P = new Universal_points;
    N_U_P->points = point;
    N_U_P->tail = 0;
    return N_U_P;
}
void U_P_Push(Universal_points* U_P, string point)
{
    while (U_P->tail)
    {
        U_P = U_P->tail;
    }
    Universal_points* NP = new Universal_points;
    U_P->tail = NP;
    NP->points = point;
    NP->tail = 0;
}
bool U_P_check(Universal_points* U_P, string point)
{
    if (U_P->points == point) { return 0; }
    while (U_P->tail)
    {
        if (U_P->points == point) { return 0; }
        if (U_P->tail->points == point) { return 0; }
        U_P = U_P->tail;
    }
    return 1;
}
void U_P_Draw(Universal_points* U_P)
{
    while (U_P)
    {
        cout << U_P->points << "\n";
        U_P = U_P->tail;
    }
}
unsigned U_P_size(Universal_points* beg)
{
    unsigned length = 0;   //  ������� ��������� ������
    // �������� � ������ ������
    while (beg)
    {
        // ����������� ������� ��������� ������ �� �������
        ++length;
        // ������������ �� ��������� ������� ������
        beg = beg->tail;
    }
    return length;
}
string U_P_get(Universal_points* U_P,unsigned k)
{
    while (U_P->tail!=0 & k>0)
    {
        U_P = U_P->tail;
        k--;
    }
    return U_P->points;
    
}
