grundy = [0]

for n in range(1, 100):
    plays = set()
    for i in range(n):
        for j in range(3):
            if i + j >= n:
                break
            l = i
            r = n - (i + j) - 1
            plays.add(grundy[l] ^ grundy[r])
    for mex in range(10**18):
        if not mex in plays:
            grundy.append(mex)
            break

y_grundy = [[[-1 for x in range(40)] for y in range(40)] for z in range(40)]

for x in range(1, 40):
    for y in range(1, 40):
        for z in range(1, 40):
            plays = set()

#center
            for tx in range(2):
                for ty in range(2):
                    for tz in range(2):
                        sx = x - tx
                        sy = y - ty
                        sz = z - tz
                        plays.add(grundy[sx] ^ grundy[sy] ^ grundy[sz])

            for i in range(x + 1):
                for j in range(3):
                    if i + j >= x + 1:
                        break
                    l = i
                    r = (x + 1) - (i + j) - 1

                    if r > 1:
                        plays.add(grundy[l] ^ y_grundy[r - 1][y][z])
                    elif r == 1:
                        plays.add(grundy[l] ^ grundy[y + z + 1])
                    else:
                        plays.add(grundy[l] ^ grundy[y] ^ grundy[z])
            for i in range(y + 1):
                for j in range(3):
                    if i + j >= y + 1:
                        break
                    l = i
                    r = (y + 1) - (i + j) - 1

                    if r > 1:
                        plays.add(grundy[l] ^ y_grundy[x][r - 1][z])
                    elif r == 1:
                        plays.add(grundy[l] ^ grundy[x + z + 1])
                    else:
                        plays.add(grundy[l] ^ grundy[x] ^ grundy[z])
            for i in range(z + 1):
                for j in range(3):
                    if i + j >= z + 1:
                        break
                    l = i
                    r = (z + 1) - (i + j) - 1

                    if r > 1:
                        plays.add(grundy[l] ^ y_grundy[x][y][r - 1])
                    elif r == 1:
                        plays.add(grundy[l] ^ grundy[x + y + 1])
                    else:
                        plays.add(grundy[l] ^ grundy[x] ^ grundy[y])

            for mex in range(10**18):
                if not mex in plays:
                    y_grundy[x][y][z] = mex
                    break

for x in range(1, 30):
    for y in range(1, 30):
        for z in range(1, 30):
            if x + y + z + 1 == 31 and y_grundy[x][y][z] == 0:
                print(x, y, z, y_grundy[x][y][z])

#for n in range(31):
#print(n, grundy[n])
