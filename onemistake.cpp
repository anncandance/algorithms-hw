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


// выводит подстроки первой строки а, отличающиеся от второй строки b не более, чем на 1 символ
// принцип: считаем Z-функцию для строки b#a и инвертированной b'#a'
// суммируем значения z для слов размера b +-1(как бы склеиваем значения z с двух сторон слова)
// если сумма z = b +-1, выводим его

void one_mistake (string a, string b){
    string s1 = b+'#'+a;
    string s2 = reverse(b)+'#'+reverse(a);
    int s =  (b+'#'+a).size();
    int *z1 = ZFunction(s1);
    int *z2 = ZFunction(s2);
    for(int i=b.size()+1; i<s; ++i){
        if (((z1[i]+z2[s-i] <= b.size())&&(b.size()-1 <= z1[i]+z2[s-i]))
        ||((z1[i]+z2[s-i+1] <= b.size())&&(b.size()-1 <= z1[i]+z2[s-i+1]))
        || ((z1[i]+z2[s-i-1] <= b.size()+1)&&(b.size() <= z1[i]+z2[s-i-1])))
        {cout<<a.substr(i-b.size()-1, b.size())<<'\n';
        }
    }
}


int main() {
    string a, b;
    cout<<"введите строки";
    cin >>a>>b;
    one_mistake(a, b);
    return 0;
}
