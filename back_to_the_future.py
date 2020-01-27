
# из 0 достижима любая вершина, поэтому
# для проверки существования отрицательного цикла можем запустить алгоритм Форда-Беллмана от 0 вершины:
# составим список ребер edges вида (start, finish, weight)
# и список расстояний dist, начальное состояние: [0, infinity, ... infinity]
# n раз(= кол-во вершин) повторим обход списка ребер:
# на первой итерации посчитаем мин расстояния до вершин, смежных с 0,
# т.е для edge(start, finish, weight) т.ч. start = 0, тогда dist(0, finish)= weight
# на второй - до вершин, смежных со смежными с 0,
# т.е.  таких,что dist[start] < infinity, для них dist[finish] мб уже < inf, поэтому
# положим dist[finish] = min(dist[finish], dist[start] + weight)
# и тд до n - 1 (бамбук от 0 до n-й вершины),
# тогда если отрицательный цикл есть, на n-й итерации какое-то расстояние снова уменьшится <-- not_relaxed = False


def find_time_machine(edges, n):
    max_distance = 10000000
    dist = list([max_distance]*n)
    dist[0] = 0
    for i in range(n):
        not_relaxed = True
        for edge in edges:  # edge: (start, end, weight)
            if dist[edge[0]] < max_distance:  # иначе получим dist = max_distance - weight
                if dist[edge[1]] > dist[edge[0]] + edge[2]:
                    dist[edge[1]] = max(-max_distance, dist[edge[0]] + edge[2])  # чтобы не было переполнения
                    not_relaxed = False
    if not_relaxed:
        return False
    return True


if __name__ == "__main__":
    c = int(input())
    for i in range(c):
        n, m = tuple(map(int, input().split()))
        edges = []
        for j in range(m):
            a, b, w = tuple(map(int, input().split()))
            edges.append((a, b, w))
        if find_time_machine(edges, n):
            print("possible", end='\n')
        else:
            print("not possible", end='\n')
