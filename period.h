#ifndef ALGOSY_PERIOD_H
#define ALGOSY_PERIOD_H

#include <string>
using namespace std ;

// префикс-функция, возвращает указатель на массив длины = длине принимаемой строки
int* prefix(string s);

// возвращает значение минимального периода принимаемой строки
int min_period(string s);


#endif //ALGOSY_PERIOD_H
