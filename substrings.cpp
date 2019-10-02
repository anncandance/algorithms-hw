#include <iostream>
#include <string>
using namespace std ;

// z-функция, возвращает указатель на массив длины = длине принимаемой строки

int* ZFunction(string s){
    int *z;
    int l=0, r=0, i=1, j;
    z = new int[s.size()];
    for(j=0;j<s.size();++j) z[j]=0;
    for(;i<s.size(); ++i){
        if(i<=r){
            z[i] =min(r-i+1, z[i-l]);}
        while ((i+z[i]<s.size())&&(s[z[i]]==s[i+z[i]])){
            ++z[i];}
        if (i+z[i]-1>r){
            l=i;
            r = i+z[i]-1;}
    }
return z;
}

// возвращает инвертированную строку

string reverse(string s){
    string s1(s);
    for(int i=0; i<s.size(); ++i){
        s1[i] = s[s.size()-i-1];}
    return s1;
}

// возвращает количество различных подстрок введенной строки s
// принцип: добавляя новую букву к подстроке длины а, получим а+1-х новых подстрок(длины 1, 2,...а+1)
// х = кол-во подстрок, оканчивающихся на новый символ внутри старой подстроки(и совпадающих с новыми подстроками)
// ==> ивертируем строку и смотрим на z функцию, х= наибольшему значению z
// теперь заметим, что вместо прибавления а+1-х каждый раз, можем просуммировать zmax по всем подстрокам s[0:i]
// и вычесть из суммы длин всех подстрок = s.size()*(s.size()+1)/2

int substrings(string s){
    int zmax=0, Szmax=0;
    int *z;
    unsigned int i=1, j=0;
    string s1;
    for(; i<=s.size(); ++i){
        zmax=0;
        s1 =reverse(s.substr(0, i));
        z = ZFunction(s1);
        for(j=0; j<i; ++j){
            if (z[j]>zmax) zmax=z[j];}
        Szmax+=zmax;

    }
    return s.size()*(s.size()+1)/2 - Szmax;
}




int main() {
    string s;
    cout<<"введите строку";
    cin>>s;
    cout<<substrings(s);
    return 0;
}
