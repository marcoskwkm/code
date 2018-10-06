import sys
lines = []

MOD = 10**9 + 7

for line in sys.stdin.readlines():
    lines.append(line)

checksum = 0
i = 1
for line in sorted(lines):
    for c in line:
        checksum += i * ord(c)
        i += 1

print checksum % MOD
