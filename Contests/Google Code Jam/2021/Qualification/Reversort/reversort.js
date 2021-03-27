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
    const [N] = nextIntArray()
    let arr = nextIntArray()
    let ans = 0

    for (let i = 0; i + 1 < N; i++) {
      const j = arr.slice(i).reduce((acc, val, idx, arr2) => val < arr2[acc] ? idx : acc, 0) + i
      arr = [...arr.slice(0, i), ...arr.slice(i, j + 1).reverse(), ...arr.slice(j + 1)]
      ans += j - i + 1
    }

    console.log(`Case #${t}: ${ans}`)    
  }
})
