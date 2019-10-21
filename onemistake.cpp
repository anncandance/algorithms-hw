#include <iostream>
#include <string>
using namespace std ;


// z-функция, возвращает указатель на массив длины = длине принимаемой строки

int* ZFunction(string &s){
    int l = 0, r = 0;
    int *z = new int[s.size()];
    for(int i = 0; i < s.size(); ++i) z[i] = 0;
    for(int i=1; i < s.size(); ++i){
        if(i <= r){
            z[i] = min(r - i + 1, z[i - l]);
        }
        while ((i + z[i] < s.size()) && (s[z[i]] == s[i + z[i]])){
            ++z[i];
        }
        if (i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}


// возвращает инвертированную строку

string reverse(string &s){
    string s1(s);
    for(int i = 0; i < s.size(); ++i){
        s1[i] = s[s.size() - i - 1];
    }
    return s1;
}


// выводит подстроки первой строки а, отличающиеся от второй строки b не более, чем на 1 символ
// принцип: считаем Z-функцию для строки b#a и инвертированной b'#a'
// суммируем значения z для слов размера b +-1(как бы склеиваем значения z с двух сторон слова)
// если сумма z = b +-1, выводим его

void one_mistake (string &a, string &b){
    string s1 = b + '#' + a;
    string s2 = reverse(b) + '#' + reverse(a);
    int s =  (b + '#' + a).size();
    int *z1 = ZFunction(s1);
    for(int i = 0; i < b.size(); ++i) z1[i]=0;
    int *z2 = ZFunction(s2);
    for(int i = 0; i < b.size(); ++i) z2[i]=0;
    for(int i = b.size() + 1; i <= s - b.size() + 1; ++i){      // идем, пока остается подстрока размера b-1
        int k = z1[i], t = z2[s - i], r = z2[s - i + 1], g = z2[s - i + 2];
        if ((k + t >= b.size())                           // длина подстроки больше на 1 (символ добавлен(возможно, продублирован))
            || (k + r + 1 >= b.size())                    // случай для подстроки длины = длине b(ошибки нет или символ заменен)
            || (k + g + 1 >= b.size()))                   // .. меньше на 1(символ пропущен)
            cout << a.substr(i - b.size() - 1, b.size()) << '\n';
    }
    delete[] z1;
    delete[] z2;
}

// вывод не учитывает прибавление и удаление символа(выходная строка всегда длины b)

int main() {
    string a, b;
    cout << "enter two strings" << endl;
    cin >> a >> b;
    one_mistake(a, b);
    return 0;
}
// test mobbithobbithobithobothobbbithoblit  hobbit
