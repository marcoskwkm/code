fun main(args: Array<String>) {
    var v1 = readLine()!!.split(" ").map(String::toInt)
    var v2 = readLine()!!.split(" ").map(String::toInt)
    v1 = v1.slice(IntRange(1, v1.get(0)))
    v2 = v2.slice(IntRange(1, v2.get(0)))
    var v3 = IntArray(1000000)
    var len = 0
    for (x in v1) {
        if (!(x in v2)) {
           v3.set(len + 1, x)
           len++
        }
    }
    for (x in v2) {
        if (!(x in v1)) {
            v3.set(len + 1, x)
            len++;
        }
    }
    v3.set(0, len)
    println(v3.slice(IntRange(0, len)).joinToString(" "))
    
}
          
