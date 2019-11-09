#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

// будем хранить информацию об отрезках в массиве segments
// массив сортируем по возрастанию начал (по ходу заполнения)
// при считывании нового отрезка:
//      если нет другого с таким же началом:
//          находим подходящую позицию для вхождения, сортируем (while(...) swap)
//      иначе 3 случая:
//          новый отрезок лежит в старом: меняем местами
//          новый совпадает со старым: проверяем четность, уменьшаем счетчик, чтобы не хранить лишний отрезок
//          новый больше: вычитаем из него старый, четность получившегося = xor предыдущих


struct Segment{
    int start, end;
    bool parity;

    // конструкторы
    Segment(int s, int e,  bool p): start(s), end(e), parity(p){}
    Segment(){start=0; end=0; parity = false;}

};

// перегрузка ввода
istream & operator>>(istream &st, Segment &s){
    string c;
    st>>s.start>>s.end>>c;
    s.parity = c == "odd";
    return st;
}


void swap(int i, int j, Segment* &segments){
    Segment s = segments[i];
    segments[i] = segments[j];
    segments[j] = s;
}

int main(){
    int n=0, n_q=0, i=1, j=0; // длина п-ти, кол-в вопросов, счетчик  вопросов и массива segments
    bool lie = false;
    cin>>n;
    while(n != -1){
        cin>>n_q;
        i=1; j=0; lie = false;
        Segment* segments = new Segment[n_q + 1]; // отрезки храним по возрастанию старта, одинаковые обрабатываем
        for(; i <= n_q; ++i){
            ++j;
            cin>>segments[j];       // считываем новый отрезок
            int k = j-1;            // находим место для отрезка в массиве
            while( (k > 0) && (segments[k].start >= segments[j].start) ){
                --k;
            }
            ++k;                    // если у отрезков одинаковое начало, возможны 3 случая:
            while((k != j) && (segments[k].start == segments[j].start) && (!lie)){
                // если новый отрезок меньше, меняем их местами, продолжаем
                if(segments[k].end > segments[j].end) swap(k, j, segments);

                // если отрезки совпали, проверяем четность, место последнего добавленного "освобождаем"
                if(segments[k].end == segments[j].end){
                    lie = segments[k].parity != segments[j].parity;
                    if(lie) {cout<<i - 1<<'\n';}
                    --j; k = j;
                }

                // если новый отрезок больше, откусываем от него меньший, перезаписываем
                else{
                    segments[j] = Segment(segments[k].end + 1, segments[j].end, segments[j].parity^segments[k].parity);
                }
                while((k < j) && (segments[k].start < segments[j].start)) ++k;
            }
            while(k < j){
                swap(k, j, segments);
                ++k;
            }
        }
        if(!lie) cout<<i-1<<'\n';
        cin>>n;
        delete[] segments;
    }
return 0;
}

