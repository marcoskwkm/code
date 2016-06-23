fun main(args: Array<String>) {
    var (a, b, c) = readLine()!!.split(".","(",")")
    var aa = a.toInt()
    var bb = b.toInt()
    var zeroes = b.length
    var period = c.length    
    var cc = c.toInt()
    var nines = 1
    var j = 0
    while (j++ < period) nines *= 10
    nines--

    var den = nines
    j = 0
    while (j++ < zeroes) den *= 10
    var num = cc + bb * nines + aa*den
    var d = gcd(num, den)
    num /= d
    den /= d
    print(num)
    print("/")
    println(den)
}

fun gcd(a: Int, b: Int): Int {
    if (b == 0) return a
    return gcd(b, a % b)
}
