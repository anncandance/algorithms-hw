#include <iostream>
#include <string>
#include <map>

using namespace std ;

// удалим ребра, которые рвет усатый, построим dsu,
// далее будем добавлять в dsu ребра в порядке, обратном удалению и фиксировать изменение кол-ва компонент,
// которое будет ответом (в обратном порядке)


// просто dsu
void make(int u, int** &parent) {
    parent[u][0] = u;
    parent[u][1] = 1;
    ++parent[0][0];     // количество компонент
}

int find(int u, int** &parent){
    if( parent[u][0] == u ) return u;
    parent[u][0] = find(parent[u][0], parent);
    return parent[u][0];
}

void union_(int u, int v, int** &parent){
    u = find(u, parent);
    v = find(v, parent);
    if(u != v){
        --parent[0][0];
        if(parent[u][1] >= parent[v][1]) {
            parent[v][0] = u;
            parent[u][1] += parent[v][1];
        }
        else {
            parent[u][0] = v;
            parent[v][1] += parent[u][1];
        }
    }
}

int main() {
    int n, m;
    cin>>n>>m;
    int** parent = new int*[n+1];   // нумерация узлов в условии с 1
    for(int i = 0; i <= n; ++i){
        parent[i] = new int[2];
    }
    parent[0][0] = 0;               // в 0 храним кол-во компонент
    for(int i = 1; i <= n; ++i){
        make(i, parent);
    }
    int** graph = new int*[m+1];     // список ребер ==> сохраняем нумерацию
    for(int i = 0; i <= m; ++i){
        graph[i] = new int[3];       // третий эл-т = флаг удаления
    }
    for(int i=1; i <= m; ++i){         // ввод графа
        cin >> graph[i][0] >> graph[i][1];
        graph[i][2] = 0;
    }

    int q, b;
    cin >> q;
    int* rmv = new int[q];              // массив ребер на удаление
    for(int i=0; i < q; ++i){
        cin >> b;
        rmv[i] = b;
        graph[b][2] = 1;                // флаг удаления ребра в графе
    }
    for(int i = 1; i <= m; ++i){            // кладем в DSU вершины кроме тех, которые будут удалены
        if(graph[i][2] == 0) {
            union_(graph[i][0], graph[i][1], parent);
        }
    }

    int* answer = new int[q];
    answer[0] = parent[0][0];
    for(int i = 0; i < q-1; ++i){           // добавляем в dsu ребра в обратном удалению порядке
        union_(graph[rmv[q - i - 1]][0], graph[rmv[q - i - 1]][1], parent);
        answer[i + 1] = parent[0][0];     // фиксируем изменения в кол-ве компонент
    }
    for(int i = q - 1; i >= 0; --i){
        cout<<answer[i]<<' ';
    }

    for(int i=0; i<=n; ++i){
        delete[]parent[i];
    }
    for(int i=0; i<=m; ++i){
        delete[]graph[i];
    }
    delete[]rmv;
    delete[] answer;


    return 0;
}