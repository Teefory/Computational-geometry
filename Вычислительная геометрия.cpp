// Геом3lab.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <set>


using namespace std;
struct Point {
    double x, y;
};
struct Edge {
    Point start, end;
};


int orientation(Point A, Point B, Point C)
{
    int val = (B.y - A.y) * (C.x - B.x) - (B.x - A.x) * (C.y - B.y);
    if (val == 0) {
        return 0; // Точки коллинеарны
    }
    return (val > 0) ? 1 : -1; // 1 по часовой, -1 против
}

// Функция, определяющая пересечение отрезков 3 задание
bool doIntersect(Point A, Point B, Point C, Point D) {
    int o1 = orientation(A, B, C);
    int o2 = orientation(A, B, D);
    int o3 = orientation(C, D, A);
    int o4 = orientation(C, D, B);

    if (A.y == B.y or C.y == D.y)
        return true;
    // Условия пересечения отрезков
    if ((o1 == o2) and (o1 == o3) and (o3 == o4)) {
        if (o1 == 0)
            cout << "Точки коллинеарны \n";
        return true;
    }

    return false; // Нет пересечения
}

// Функция для нахождения координат пересечения векторов
Point findIntersection(Point A, Point B, Point C, Point D) {
    Point intersection;

    double delta = (A.x - B.x) * (C.y - D.y) - (A.y - B.y) * (C.x - D.x);

    if (delta == 0) {
        // Векторы параллельны или совпадают, пересечение не существует
        intersection.x = -1;
        intersection.y = -1;
    }
    else {

        double x_intersection = ((A.x * B.y - A.y * B.x) * (C.x - D.x) - (A.x - B.x) * (C.x * D.y - C.y * D.x)) / delta;
        double y_intersection = ((A.x * B.y - A.y * B.x) * (C.y - D.y) - (A.y - B.y) * (C.x * D.y - C.y * D.x)) / delta;

        intersection.x = x_intersection;
        intersection.y = y_intersection;
    }

    return intersection;
}









int main()
{
    setlocale(LC_ALL, "Russian");
    int z;
    cout << "Введите номер задания ";
    cin >> z;
    switch (z)
    {
    case(1):
    {
        // Заданные точки
        vector<Point> points = { {3, 1}, {2, 3}, {3, 5}, {8, 3}, {10, 1}, {6, 6}, {10, 7} };
        //Заданные прямоугольники
        vector<int> pram = { 1,5,1,6,7,10,1,4,7,10,5,7 };
        int x, y;
        int count = 0;
        for (int i = 0; i < pram.size() - 3; i = i + 4) {
            for (int j = 0; j < points.size(); j++)
            {
                if (pram[i] <= points[j].x and points[j].x <= pram[i + 1] and pram[i + 2] <= points[j].y and points[j].y <= pram[i + 3])
                {
                    count++;
                }

            }
            cout << "Кол-во точек в " << i / 4 + 1 << " прямоугольнике: " << count << endl;
            count = 0;
        }

        break;
    }
    case(2):
    {
        //Point A = { 6,4 };//раб
        //Point A = { 7,2.5 };//раб
        //Point A = { 4,2.5 };
        Point A = { 8,5.5 };
        vector<Point> verh = { {3, 1}, {2, 3}, {3, 5}, {8, 3}, {10, 1},{6, 2}, {9, 7} };
        vector<Edge> subdivision = { {{3, 1}, {2, 3}}, {{2, 3}, {3, 5}}, {{3, 5}, {6, 2}}, {{6, 2}, {3, 1}}, {{6, 2}, {10, 1}}, {{ 10, 1 }, {3, 1}},  {{10, 1}, {8, 3}},  {{8, 3}, {9, 7}},  {{9, 7}, {3, 5}} };
        vector<int> sorte(subdivision.size());
        for (int i = 0; i < subdivision.size(); i++)
        {
            sorte[i] = subdivision[i].start.y;
        }
        sort(sorte.begin(), sorte.end());
        sorte.erase(unique(sorte.begin(), sorte.end()), sorte.end());

        bool b = 1;
        Point Yy1 = { 0,0 };
        Point Yy2 = { 10,0 };
        Point Yy3 = { 0,0 };
        Point Yy4 = { 10,0 };
        cout << endl;
        if (A.y < sorte[0] or A.y > sorte[sorte.size() - 1])
        {
            cout << "Не принадлежит точка А графу \n";
        }
        else
        {
            for (int i = 0; i < sorte.size() - 1; i++)
            {
                // А.у совпадает с у ошибка мб убрать знак равно в усл
                if (sorte[i] <= A.y and A.y <= sorte[i + 1] and b == 1)
                {
                    cout << "Между " << sorte[i] << " и " << sorte[i + 1] << endl;
                    Yy1.y = sorte[i]; Yy3.y = sorte[i + 1];
                    b = 0;
                }

            }
        }
        Yy2.y = Yy1.y;
        Yy4.y = Yy3.y;

        vector<Point>rebra;

        //Нашли все ребра между прямыми
        for (int i = 0; i < subdivision.size(); i++)
        {
            if (doIntersect(subdivision[i].start, Yy3, subdivision[i].end, Yy4))
            {
                Point intersection = findIntersection(subdivision[i].start, subdivision[i].end, Yy3, Yy4);
                if (intersection.x == -1 && intersection.y == -1) {
                    cout << "Векторы параллельны или совпадают, пересечение не существует" << endl;
                }
                else {

                    if (doIntersect(subdivision[i].start, Yy1, subdivision[i].end, Yy2))
                    {
                        Point intersection1 = findIntersection(subdivision[i].start, subdivision[i].end, Yy1, Yy2);
                        if (intersection1.x == -1 && intersection1.y == -1) {
                            cout << "Векторы параллельны или совпадают, пересечение не существует" << endl;
                        }
                        else {
                            rebra.push_back(intersection); // Сперва идет верх
                            rebra.push_back(intersection1);// Затем идет низ
                            cout << "Координаты пересечения:A (" << intersection.x << ", " << intersection.y << ")" << endl;
                            cout << "Координаты пересечения:B (" << intersection1.x << ", " << intersection1.y << ")" << endl;
                        }
                    }
                }
            }
        }
        vector<double> verh11/*(rebra.size()/2)*/;
        vector<double> niz/*(rebra.size() / 2)*/;

        for (int i = 0; i < rebra.size(); i++)
        {
            if (i % 2 == 0)
                verh11.push_back(rebra[i].x);
            else
            {
                niz.push_back(rebra[i].x);
                /*cout << rebra[i].x << "n ";*/
            }
        }

        sort(niz.begin(), niz.end());
        sort(verh11.begin(), verh11.end());
        verh11.erase(unique(verh11.begin(), verh11.end()), verh11.end());

        double crav = 0;
        int crav2 = 0;
        for (int i = 0; i < verh11.size(); i++)// нашли правую грань
        {
            cout << verh11[i] << " ";
            if (A.x <= verh11[i])
            {
                crav2 = verh11[i - 1];// левая точка
                crav = verh11[i];// правая точка
                break;
            }
        }
        cout << crav2 << " ";
        double ASA = 0; double ASO = 0;  double x1 = 0;
        for (int i = 0; i < rebra.size(); i++)
        {
            if (rebra[i].x == crav)
            {
                cout << "Правое ребро с координатами " << rebra[i].x << "," << rebra[i].y << " и " << rebra[i + 1].x << "," << rebra[i + 1].y << endl;

            }
            if (rebra[i].x == crav2)
            {
                //cout << "Левое ребро с координатами " << rebra[i].x << ", " << rebra[i].y << " и " << rebra[i + 1].x << ", " << rebra[i + 1].y << endl;
                if (rebra[i + 1].x > ASA)
                {
                    ASA = rebra[i + 1].x;
                    ASO = rebra[i + 1].y;
                    x1 = i;
                }

            }


        }
        cout << "Левое ребро с координатами " << rebra[x1].x << "," << rebra[x1].y << " и " << ASA << "," << ASO << endl;
        x1 = 0;


        break;
    }

    }

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
