#ifndef GRAPHS1_G_H
#define GRAPHS1_G_H

#include<initializer_list>
#include<vector>

class G {

    int n;       // число вершин
    int** list;  // массив смежности

public:
    // много конструкторов
    G(int n, int** list);
    G(std::initializer_list <std::initializer_list <int> > &list);
    G(std::vector<std::vector<int>> &v);
    ~G();

    // DFS
    std::vector<int>DFS();
    void DFS(int v, int* visited, std::vector<int> &tout);

    // инвертирование
    G trans();

    // конденсация
    G* condensate(std::vector<int>tout);

    // вывод
    void print();

};

#endif //GRAPHS1_G_H
