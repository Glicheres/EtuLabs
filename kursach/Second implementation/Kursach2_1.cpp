#include <iostream>
#include <fstream>
#include <string>

#include "Helper.h"

using namespace std;


struct not_a_map
{
    string data;
    string father;
};

not_a_map* dsu_create(string X) 
{
    not_a_map* dsu = new not_a_map;
    dsu->father = X;
    dsu->data = X;
    return dsu;
}

string find(string v,not_a_map* dsu,int size ) 
{
    for (int i = 0; i < size; i++) 
    {
        if (v == dsu[i].data) 
        {
            return dsu[i].father;
        }
    }
}

void un(string a, string b,not_a_map* dsu, int size) 
{
    string Fa = find(a, dsu,size);
    for (int i = 0; i < size; i++)
    {
        if (b == dsu[i].data)
        {
            dsu[i].father = Fa;
        }
    }
}


int main()
{
    setlocale(0, "");

    bool foc = 0;
    cout << "Запись из файла ? 0 - нет; 1 - да";
    cin >> foc;
    system("cls");
    Linked_list* data = CreateList();
    if (foc == 1)
    {
        string dyrectory;
        cout << "Введите директорию и имя файла:";
        cin >> dyrectory;
        data = Get_in_file(dyrectory);
    }
    else
    {
        cout << "Esc - выход \n";
        data = get_input_data();
    }

    Universal_points* points = 0;
    bool f_o_n = 1;//first or not ?
    //vector<pair<string, string>> mst; // система непересекающихся множеств 
    unsigned int cost = 0; // счётчик для mst 

    system("cls");
    for (int i = 0; i < LengthList(data); i++) 
    {
        if (f_o_n == 1) 
        {
            points = U_P_Create(data->data.First);
            f_o_n = 0;
        }
        else
        {
            if (U_P_check(points, ListItem(data, i)->data.First)) 
            {
                U_P_Push(points, ListItem(data, i)->data.First);
            }
        }
    }
    for (int i = 0; i < LengthList(data); i++)
    {
        if (U_P_check(points, ListItem(data, i)->data.Second))
        {
            U_P_Push(points, ListItem(data, i)->data.Second);
        }
    }
    U_P_Draw(points);

    not_a_map* dsu = new not_a_map[U_P_size(points)];
    for (int i = 0; i < U_P_size(points); i++) 
    {
        dsu[i] = *dsu_create(U_P_get(points, i));
    }
    quickSort(data, 0, LengthList(data) - 1);
    DrawList(data);
    //MST
    for (int i = 0; i < LengthList(data) - 1; i++)
    {
        string a = ListItem(data,i)->data.First;
        string b = ListItem(data, i)->data.Second;
        int c = ListItem(data, i)->data.number;

        if (find(a,dsu, U_P_size(points)) != find(b,dsu, U_P_size(points)))
        {
            cout << a << " " << b<<"\t"<< find(a, dsu, U_P_size(points)) <<" " << find(b, dsu, U_P_size(points))<<"\t";
            un(a, b,dsu, U_P_size(points));
            cout<< find(a, dsu, U_P_size(points)) << " " << find(b, dsu, U_P_size(points)) << "\n";
            cost += c;
        }
    }
    cout << cost;
    return 0;
};