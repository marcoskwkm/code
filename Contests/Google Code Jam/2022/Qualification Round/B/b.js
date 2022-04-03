let __data = ''
let __lines = []
let __curLine = 0

const parseInput = () => __lines = __data.split('\n').map((line) => line.trim())
const nextLine = () => __lines[__curLine++]
const nextIntArray = () => __lines[__curLine++].split(' ').map((x) => parseInt(x))

process.stdin.on('data', (x) => __data += x)

process.stdin.on('end', () => {
  parseInput()

  const [T] = nextIntArray()
  for (let t = 1; t <= T; t++) {
    const ink = [0, 1, 2].map((_) => nextIntArray())
    let left = 1000000
    const ans = [0, 1, 2, 3].map(
      (idx) => {
        const take = Math.min(left, ...[0, 1, 2].map((c) => ink[c][idx]))
        left -= take
        return take
      }
    )

    console.log(`Case #${t}: ${left > 0 ? 'IMPOSSIBLE' : ans.join(' ')}`)
  }
})
