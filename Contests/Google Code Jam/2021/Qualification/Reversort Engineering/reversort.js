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
    let [N, C] = nextIntArray()

    let arr = [...new Array(N)].map((_, idx) => idx + 1)
    const indices = []
    C -= N - 1
    for (let i = N; i > 1; i--) {
      if (C >= i - 1) {
        C -= i - 1;
        indices.push(N - i);
      }
    }

    if (C !== 0) {
      console.log(`Case #${t}: IMPOSSIBLE`)
    } else {
      indices.reverse().forEach((idx) => {
        arr = [...arr.slice(0, idx), ...arr.slice(idx).reverse()]
      })

      console.log(`Case #${t}: ${arr.join(' ')}`)
    }
  }
})
