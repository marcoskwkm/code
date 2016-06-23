fun main(args: Array<String>) {
    var n = readLine()!!.toInt()
    var vv = readLine()!!.split(" ").map(String::toInt)
    var v = IntArray(n)
    var cur = 1
    for (x in vv) {
        var cnt = 0
        var j = 0
        while (cnt < x)
            if (v.get(j++) == 0)
                cnt++
        while (v.get(j) > 0) j++
        v.set(j, cur++)
    }
    println(v.joinToString(" "))         
}
