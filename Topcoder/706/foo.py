import math, string, itertools, fractions, heapq, collections, re, array, bisect

class MovingCandies:
    def minMoved(self, A):
        R, C = len(A), len(A[0])
        candycount = sum(row.count('#') for row in A)

        pq = [( (0,0), +(A[0][0] == '.'), +(A[0][0] == '.'), 1 )]
        def neighbors(r, c):
            for cr, cc in [(r+1, c), (r-1, c), (r, c-1), (r, c+1)]:
                if 0<=cr<R and 0<=cc<C:
                    yield cr, cc
        M = R+C+1
        seen = {}
        answers = []
        while pq:
            (r, c),_, m, p = heapq.heappop(pq)
            if ((r, c), m) in seen: continue
            if m > M: continue
            if r == R-1 and c == C-1:
                if p <= candycount:
                    answers.append(m)
            seen[(r, c), m] = p
            for cr, cc in neighbors(r, c):
                if A[cr][cc] == '#':
                    heapq.heappush(pq, ((cr, cc), m + p + 1, m, p+1))
                else:
                    heapq.heappush(pq, ((cr, cc), m + p + 2, m + 1, p + 1))
        return min(answers) if answers else -1

t = [
              "#.##.##",
              "#.#...#",
              "###...#",
              "......#",
              "......#"
]
mc = MovingCandies()
print mc.minMoved(t)
