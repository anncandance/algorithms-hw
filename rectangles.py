# пр-ки храним в виде точек диагонали с высотой и флагом начала/конца пр-ка (-1, +1) в массиве Х
# сортируем точки по о.х, заводим счетчик count открытых пр-в, массив Y высот открытых пр-в
# идем по массиву Х, когда встречаем точку:
#       считаем площадь пр-в в полосе между ней и предыдущей точкой,
#               это (x2-x1)*объединение высот открытых сейчас пр-в(= len_union Y)
#       обновляем счетчик
#       если точка открывает пр-к (левый нижний угол), добавляем высоту в Y
#       иначе удаляем высоту из Y
# если добавляется/удаляется пр-к на той же вертикали, не меняем площадь


# Y: [(int, +-1)]
def len_union(Y):
    if len(Y) == 0:
        return 0
    Y.sort(key=lambda point: point[0])
    a = Y[0][0]
    count = 1
    length = 0
    for i in range(1, len(Y)):
        (b, sign) = Y[i]
        count -= sign
        if count == 0:
            length += (b - a)
            if i + 1 < len(Y):
                a, sign = Y[i + 1]
    return length


# segment: (int, int)
# Y: [(int, +-1)]
def add_y(Y, segment):
    left = min(segment)
    right = max(segment)
    Y.append((left, -1))
    Y.append((right, +1))


# diag: ((int x1, int y1), (int x2, int y2))
# X: [(int x, int y, high,  +-1)]
def add_x(X, diag):
    left = min(diag[0], diag[1])
    right = max(diag[0], diag[1])
    high = abs(right[1] - left[1])
    X.append((*left, high, -1))
    X.append((*right, high, 1))


# X: [(int x, int y, high, +-1)]
def square(X):
    if len(X) == 0:
        return -1
    S = 0
    Y = []
    count = 1
    (x1, y1, high1, sign1) = X[0]
    add_y(Y, (y1, y1 + high1))
    for i in range(1, len(X)):
        (x2, y2, high2, sign2) = X[i]
        # пр-к на той же вертикали - площадь не меняется
        if x2 == x1:
            count -= sign2
        else:
            # high: длина объединения эл-в Y: это высоты "открытых" сейчас прямоугольников
            high = len_union(Y)
            S += (high * (x2 - x1))
            count -= sign2
        # если пр-к открылся, добавляем сторону в Y
        if sign2 == -1:
            add_y(Y, (y2, y2 + high2))
        # если пр-к закрылся, удаляем его сторону из Y
        else:
            Y.remove((y2, 1))
            Y.remove((y2 - high2, -1))
        (x1, y1, high1, sign1) = (x2, y2, high2, sign2)
    return S


# X: [(int x, int y, +-1)]
if __name__ == "__main__":
    print("Введите количество прямоугольников: ", end='\n')
    n = int(input())
    Y = []
    X = []
    print("Введите точки {} диагоналей:".format(n), end='\n')
    for i in range(0, n):
        # прямоугольник задается диагональю: левый нижний, правый верхний
        (x1, y1) = map(int, input().split())
        (x2, y2) = map(int, input().split())
        add_x(X, ((x1, y1), (x2, y2)))
    X.sort(key=lambda x: x[0])
    print(square(X))


# тест 1:
# 2
# 1 2
# 5 6
# 3 1
# 10 4
# ==> 33

# тест 2:
# 3
# 8 9
# 14 10
# 9 6
# 12 10
# 10 7
# 11 8
# ==> 15

# тест 3:
# 5
# 8 9
# 14 10
# 9 6
# 12 10
# 10 7
# 11 8
# 1 2
# 5 6
# 3 1
# 10 4
# ==> 48

# тест 4:
# 3
# 13 7
# 15 11
# 13 4
# 15 6
# 13 0
# 15 2
# ==> 16

# тест 5:
# 3
# 1 2
# 3 6
# 0 1
# 2 2
# 6 5
# 7 9
# ==> 14

