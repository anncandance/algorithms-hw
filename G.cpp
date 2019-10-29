#include "G.h"

using namespace std;

// конструктор через массив
G::G(int num, int**gl) : n(num), list(gl)
{};

// конструктор через initializer_list
G::G(std::initializer_list <std::initializer_list <int> > &l):
n(l.size())
{
    list = new int*[n];
    int i=0;
    for(auto elem : l){
        list[i] = new int[elem.size() + 1];
        list[i][0] = elem.size();             // в начале каждого массива храним размер
        int j=1;
        for(auto item : elem){
            list[i][j] = item;
            ++j;
        }
        ++i;
    }
};

// конструктор через вектор векторов
G::G(std::vector < std::vector <int> > &v):
    n(v.size())
    {
    int**l = new int*[n];
    for(int i = 0; i < n; ++i){
        int* u = new int[v[i].size()+1];
        u[0] = v[i].size();
        for(int j = 1; j <= u[0]; ++j) {
            int t = v[i][j-1];
            u[j] = v[i][j-1];
        }
    l[i] = u;
    }
    list = l;
}

G::~G(){
    for(int i = 0; i < n; ++i){
        delete[] list[i];
    }
}


void G::print(){
    cout<<"G:"<<endl;
    for(int i = 0; i < n; ++i){
        cout<<i<<": ";
        for(int j = 1; j <= list[i][0]; ++j){
            cout<< list[i][j] <<" ";
        }
        cout<< '\n';
    }
}

// рекурсивный DFS, вернет вектор с вершинами, отсортированными по возрастанию времени выхода
// (max Tout в конце)

vector<int> G::DFS(){
vector<int> v;
int* visited = new int[n];
for(int i = 0; i < n; ++i) visited[i]=0;
for(int i = 0; i < n; ++i){
    if(visited[i] == 0) DFS(i, visited, v);
}
delete[] visited;
return v;
}

void G::DFS(int i, int* visited, vector<int> &v){
    if(visited[i] == 1) return;
    visited[i] = 1;
    v.push_back(i);
    for(int j = 1; j <= list[i][0]; ++j){
        if(visited[list[i][j]] == 0) {DFS(list[i][j], visited, v);}
    }
}

// транспонирование
G G::trans(){
    vector < vector <int> > tmp_vector(n);
    for(int i = 0; i < n; ++i){
        for(int j = 1; j <= list[i][0]; ++j){
            tmp_vector[list[i][j]].push_back(i);
        }
    }
    G t_graph(tmp_vector);
    for(int i = 0; i < n; ++i) tmp_vector[i].clear();
    return t_graph;
}

// есть ли вершина в компоненте
bool in_comp(int i, vector<int> &comp){
    for(int j = 0; j < comp.size(); ++j){
        if (comp[j] == i) return true;
    }
    return false;
}

// имея вектор вершин, отсортированных по возрастанию времени выхода и транспонированный граф,
// строим 2 вектора: вектор компоненет и вектор связей между ними(вектор векторов),по последнему строим новый граф

G* G::condensate(vector<int> tout){
    vector< vector <int>  > components;
    vector< vector <int>  > relations;
    int* visited = new int[n];
    for(int i = 0; i < n; ++i) visited[i] = 0;
    for(int i = n - 1; i >= 0; --i){            // идем по вектору tout с конца, находим и обрабатываем компоненты
        vector<int> comp;
        vector<int> rel;
        if(visited[tout[i]] == 0) DFS(tout[i], visited, comp);  // получаем компоненту
        if(!comp.empty()) {
            components.push_back(comp);
            relations.push_back(rel);
            for (auto c : comp) {
                cout << c << " "; // вывод компонент
                for (int j = 1; j <= list[c][0]; ++j) {    // смотрим все вершины, достижимые из компоненты
                    int k = list[c][j];                   // они лежат в компонентах, которые мы уже нашли
                    if (!in_comp(k,comp)) {              // перебираем векторы из components
                        for (int y = 0; y < components.size(); ++y) {           // как сделать просто
                            for (int r = 0; r < components[y].size(); ++r) {    // и без страшного перебора как-то неясно
                                if (components[y][r] == k)
                                    relations[relations.size() - 1].push_back(y);
                            }
                        }
                    }
                }
            }
            cout << '\n'; // вывод компонент
        }
    }
    G* Condensated_graph = new G(relations);                            // тот самый конструктор
    for(int i = 0; i < components.size(); ++i){ components[i].clear();}     // чистим векторы
    for(int i = 0; i < relations.size(); ++i){ relations[i].clear();}
    Condensated_graph -> trans().print();                               // транспонируем
    return Condensated_graph;
}
