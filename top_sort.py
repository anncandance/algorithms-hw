class OrGraph:

    def __init__(self, l):    # список смежности
        self.list = l
        self.top_list = self.top_sort()   # в топологическом порядке

    def print(self):
        print(*self.list)

# DFS(top - для сортировки)
    def DFS(self, n, visited, top):
        if visited[n] == 1:
            return
        visited[n] = 1
        for m in self.list[n]:
            self.DFS(m, visited, top)
        top.append(n)

# топологичсекая сортировка через DFS
    def top_sort(self):
        k = len(self.list)
        visited = [0] * k
        L = []
        for i in range(0, k):
            if visited[i] == 0:
                self.DFS(i, visited, L)
        L.reverse()
        return L

# есть ли ребро из i в j
    def is_edge(self, i, j):
        for n in self.list[i]:
            if n == j:
                return True
        return False

# проверка единственности сортировки
    def is_only(self):
        for i in range(0, len(self.top_list) - 1):
            if not (self.is_edge(self.top_list[i], self.top_list[i + 1])):
                return False
        return True


# заметим, что если в сортировке между любыми двумя соседними вершинами есть ребро, то она единственна
# обратно: если между какими-то соседними вершинами нет ребра, поменяем их местами и получим другой вариант сортировки
# т.о для проверки достаточно построить какую-то сортировку и проверить наличие ребер между соседями


if __name__ == "__main__":
    # ввод графа через корректировку списка
    g = OrGraph([[1], [2], [3], []])
    print(g.is_only())

# test [3, 4], [3], [4, 7], [5, 6, 7], [6], [], [], []] ==> false
# test [[1], [2], [3], []] ==> true
