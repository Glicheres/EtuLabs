#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;


// структура соединения 
struct graf
{
    string Fist;
    string Second;
    int unsigned number;
};
//список соединений
typedef vector<graf> Vg;

// это ввод
Vg input()
{
    graf input;
    Vg points;
    while (cin)
    {
        cin >> input.Fist >> input.Second >> input.number;
        points.push_back(input);
    }
    points.pop_back();
    return points;
}
// выводит содержимое списка
void print_all(Vg x) 
{
    for (int i = 0; i < x.size(); i++) 
    {
        cout << x[i].Fist<<" " << x[i].Second <<" " << x[i].number<<"\n";
    }
}

void quickSort(Vg& array, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = array[(i + j) / 2].number;
    graf temp;

    while (i <= j)
    {
        while (array[i].number < pivot)
            i++;
        while (array[j].number > pivot)
            j--;
        if (i <= j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(array, low, j);
    if (i < high)
        quickSort(array, i, high);
}

// благодаря этой функции мы можем создать вектор с перечислением всех рёбер (показывает нахождение точки в списке) 
bool chech_vertex(vector<string> vertex, string point)
{
    for (int i = 0; i < vertex.size(); i++) 
    {
        if (vertex[i] == point) { return 0; }
    }
    return 1;
}

// мапа используется для системы непересекающихся множеств и определения вершины множества
map <string, string> dsu;
// найдём элемент в множестве
string find (string v) 
{
    if (dsu[v] != v) 
    {
        dsu[v] = find(dsu[v]);
    }
    return dsu[v];
}
//объединяем множества
void un(string a, string b)
{
    a = find(a);
    b = find(b);
    if (a != b) { dsu[b] = a; }
}

// выписать из файла
bool Get_in_file(Vg& points, string dyrectory)
{
    std::ifstream file(dyrectory, ios_base::in); // Менять адрес тут!

    if (!file.is_open())
    {
        std::cout << "Failed to open file\n";
        return false;
    }
    graf input;
    while (file)
    {
        file >>  input.Fist >> input.Second >> input.number;
        points.push_back(input);
    }
    points.pop_back();

    file.close();
    return true;
}



int main()
{
    setlocale(0, "");

    bool foc = 0;
    cout << "Запись из файла ? 0 - нет; 1 - да";
    cin >> foc;
    system("cls");
    Vg data;
    if (foc == 1) 
    {
        string dyrectory;
        cout << "Введите директорию и имя файла:";
        cin >> dyrectory;
        Get_in_file(data, dyrectory);
    }
    else 
    {
        cout << "для перкращения ввода вместо веса ребра напишите что - нибудь\n";
        data = input();
    }

    vector<string> points; // список точек 
    vector<pair<string, string>> mst; // система непересекающихся мнжеств 
    unsigned int cost = 0; // счётчик для mst 

    system("cls");

    for (int i = 0; i < data.size(); i++) 
    {
        if (chech_vertex(points, data[i].Fist) == 1) 
        {
            points.push_back(data[i].Fist);
        }
        if (chech_vertex(points, data[i].Second) == 1)
        {
            points.push_back(data[i].Second);
        }
    }

    for (int i = 0; i < points.size(); i++) 
    {
        dsu[points[i]] = points[i];
    }

    quickSort(data,0, data.size()-1);

    //MST
    for (int i = 0; i < data.size(); i++) 
    {
        string a = data[i].Fist;
        string b = data[i].Second;
        int c = data[i].number;

        if (find(a) != find(b)) 
        {
            mst.push_back(pair<string, string>(a, b));
            un(a, b);
            cost += c;
        }
    }

    for (int i = 0; i < mst.size(); i++) 
    {
        cout << mst[i].first << " " << mst[i].second << "\n";
    }
    cout << cost;
    return 0;
};