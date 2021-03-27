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
  }
})
