T = int(input())

for t in range(1, T + 1):
    input()
    v = list(map(int, input().split(' ')))
    v.sort()

    remove = max(0, 1 - min([val - idx for idx, val in enumerate(v)]))
    print(f'Case #{t}: {len(v) - remove}')
