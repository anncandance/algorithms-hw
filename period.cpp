#include"period.h"

// префикс-функция, возвращает указатель на массив длины = длине принимаемой строки
int* prefix(string s) {
    int n = s.size(), i = 1, j;
    int *p;
    p = new int[n];
    p[0] = 0;
    for (; i < n; ++i) {
        j = p[i - 1];
        int t=i;
        while ((j > 0) && (s[t] != s[j])) {
            j = p[t - 1]; --t;}
        if (s[i] == s[j]) ++j;
        p[i] = j;
    }
    return p;
}


// возвращает значение минимального периода принимаемой строки
// принцип: если строка периодична( min период = mink),
// то значение префикс-функции от последнего символа строки=длина строки-мин период (p[s.size()-1] = s.size()-mink)
// тогда это же верно для подстроки s[0:s.size()-mink*i], где i целое
// увеличивая i, либо придем к подстроке длины mink ==> mink действительно min период
// либо к подстроке длины < mink ==> длина строки не кратна mink и строка не периодична,
// либо перестанет выполняться равенство p[s.size()-1] = s.size()-mink ==> снова нет периода

int min_period(string s) {
    int *p = prefix(s);
    int mink = s.size() - p[s.size() - 1];
    for (int i = 1; i <= s.size() / mink; ++i) {
        int cut = (s.size() - mink * i);
        if(cut==mink) return mink;
        if ((cut<mink)||(cut - p[cut - 1]) != mink) return s.size();
    };
    return mink;
}