# направляющий вектор прямой
def get_line(x1, y1, x2, y2):
    a = y1 - y2
    b = x2 - x1
    c = x1 * y2 - x2 * y1
    return a, b, c


# перпендикулярность <== > ск произведение = 0
def is_perp(d1, d2):
    if d1[0] * d2[0] + d1[1] * d2[1] == 0:
        return True
    return False

# проверка того, что d1 пересекает d2 в середине отрезка a, b
# d: (a, b, c);
# a: (x1, y1)
def is_middle(d1, d2, a, b):
    delta = d1[0] * d2[1] - d2[0] * d1[1]
    if delta == 0:
        return False
    x = (d2[2] * d1[1] - d1[2] * d2[1]) / delta
    y = (d2[0] * d1[2] - d1[0] * d2[2]) / delta
    m1, m2 = get_middle(a, b)
    if x == m1 and y == m2:
        return True


# середина отрезка
def get_middle(a, b):
    m1 = (b[0] + a[0]) / 2
    m2 = (b[1] + a[1]) / 2
    return m1, m2


# a: (x1, y1)
# вернет кортеж из двух напр векторов прямых(ср. линии)
def get_axis(a, b, c, d):
    m1, m2 = get_middle(a, b)
    m3, m4 = get_middle(c, d)
    ax1 = get_line(m1, m2, m3, m4)
    l1, l2 = get_middle(b, c)
    l3, l4 = get_middle(a, d)
    ax2 = get_line(l1, l2, l3, l4)
    return ax1, ax2


# нужно проверить симметрию относительно диагоналей d1 d2 и средних линий ax1 ax2
# 4-угольник симм отн-но d1, если d1 перпендикулярна d2 и точкой пересечения делит d2 пополам
# 4-к симм отн-но средней линии, если она перпендикулярна основаниям, которые делит
if __name__ == "__main__":
    x1, y1 = map(int, input().split())
    x2, y2 = map(int, input().split())
    x3, y3 = map(int, input().split())
    x4, y4 = map(int, input().split())
    count = 0
    # прямые диагоналей:
    d1 = get_line(x1, y1, x3, y3)
    d2 = get_line(x2, y2, x4, y4)
    # прямые сторон:
    a = get_line(x1, y1, x2, y2)
    b = get_line(x2, y2, x3, y3)
    c = get_line(x3, y3, x4, y4)
    d = get_line(x4, y4, x1, y1)
    # проверка симметрии относительно диагоналей
    if is_perp(d1, d2):
        if is_middle(d1, d2, (x2, y2), (x4, y4)):
            count += 2
        if is_middle(d1, d2, (x1, y1), (x3, y3)):
            count += 2
    # проверка симметрии от-но ср линий
    ax1, ax2 = get_axis((x1, y1), (x2, y2), (x3, y3), (x4, y4))
    if is_perp(ax1, a) and is_perp(ax1, c):
        count += 2
    if is_perp(ax2, b) and is_perp(ax2, d):
        count += 2
    print(count)
