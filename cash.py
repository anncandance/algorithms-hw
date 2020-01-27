
# так как вася не перемещается по дорогам L+, выбросим их из графа
# и найдем путь ab, например, Дейкстрой(если найдем)
import heapq


# очередь с приоритетами на основе двоичной кучи
class PriorityQueue:
    def __init__(self):
        self.elements = []

    def empty(self):
        return len(self.elements) == 0

    def put(self, item, priority):
        heapq.heappush(self.elements, (priority, item))

    def get(self):
        return heapq.heappop(self.elements)  # priority, item


def dijkstra(vertices, a, b):
    queue = PriorityQueue()
    queue.put(a, 0)
    trace = [-1] * (n + 1)  # откуда пришли в текущую
    distance = [-1] * (n + 1)  # стоимость проезда от а до текущей вершины
    distance[a] = 0
    trace[a] = a
    v = a
    while v != b and not queue.empty():
        qw, v = queue.get()
        # вместо замены приоритета в очереди, тк приоритет = мин расстояние на момент добавления в очередь
        if qw > distance[v]:  # т.е это случай, когда мы достали старую версию элемента (v, w)
            continue
        for (u, w) in vertices[v]:
            if distance[u] == -1 or distance[u] > distance[v] + w:
                distance[u] = distance[v] + w
                queue.put(u, distance[v] + w)
                trace[u] = v
    if v == b:
        return trace
    else:
        return False


# рекурсивная печать пути от a до b
def get_trace(trace, v):
    if trace[v] == v:  # тк trace[a] = a
        return
    else:
        get_trace(trace, trace[v])
        print(trace[v], end=' ')
        return


if __name__ == "__main__":
    L = int(input())
    n, m = tuple(map(int, input().split()))
    a, b = tuple(map(int, input().split()))
    vertices = [[] for i in range(n + 1)]
    m0 = m
    for i in range(m0):
        u, v, w = tuple(map(int, input().split()))
        if w <= L:  # тк мы все равно не можем перемещаться по L+, можно их и не рассматривать
            vertices[u].append((v, w))
            vertices[v].append((u, w))
        else:
            m -= 1  # уменьшаем кол-во за счет L+
    trace = dijkstra(vertices, a, b)
    if trace:
        print("found", end='\n')
        get_trace(trace, b)
        print(b, end='\n')
    else:
        print("not found", end='\n')
