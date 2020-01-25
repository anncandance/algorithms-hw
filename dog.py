# python 2.7
from itertools import imap


# векторное произведение ab*bc
# если порядок обхода: a,..., b, c то ab*bc  0 ==> c слева от ab
# если порядок a,...,c, b то  ab*bc  0 ==> c справа от ab
# != 0, тк нет самопересечений
def cross_product(a, b, c):
    ux, uy = b[0] - a[0], b[1] - a[1]
    vx, vy = c[0] - b[0], c[1] - b[1]
    cp = ux*vy - uy*vx
    return cp

# найдем самую нижнюю и верхнюю точки (а и b), тк нет самопересечеий,
# то если из верхней точки спортсмен бежит направо относительно ab( в точку с),
# то обход по часовой,
# иначе - против часовой,
# направление определим через векторное произведение ab*bc
if __name__ == u"__main__":
    n = int(raw_input())
    points = []
    min = 100000
    max = -100000
    imin = 0
    imax = 0
    for i in xrange(n):
        x, y = tuple(imap(int, raw_input().split()))
        if y < min:
            min = y
            imin = i
        if y > max:
            max = y
            imax = i
        points.append((x, y))
    a = points[imin]
    b = points[imax]
    # наибольший эл-т не последний в списке и после него не идет наименьший:
    if imax + 1 != n and imin != imax + 1:
        c = points[imax + 1]
        cp = cross_product(a, b, c)
        if cp > 0:
            print u"ccw"
        else:
            print u"cw"
    # номер максимального последний, после него не мин
    if imax + 1 == n and imin != 0:
        c = points[0]
        cp = cross_product(a, b, c)
        if cp > 0:
            print u"ccw"
        else:
            print u"cw"
    # после наибольшего идет наименьший
    if (imax + 1 != n and imax + 1 == imin) or (imax + 1 == n and imin == 0):
        c = points[imax - 1]
        cp = cross_product(a, b, c)
        if cp > 0:
            print u"cw"
        else:
            print u"ccw"
