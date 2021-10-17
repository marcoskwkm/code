const alph = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
const s = [...new Array(300000)].map(() => alph[Math.floor(26 * Math.random())]).join('')
console.log(s)
