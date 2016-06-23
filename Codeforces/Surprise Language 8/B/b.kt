fun main(args: Array<String>) {
    val n = readLine()!!.toInt()
    val idx = IntArray(n)
    val h =  IntArray(n)
    val names = Array(n, {i -> ""})
    var i = 0
    while (i < n) {
          val(name, height) = readLine()!!.split(" ")
          names.set(i, name)
          h.set(i, height.toInt())
          idx.set(i, i)
          i++
    }
    var a = 0
    while (a < n) {
          var b = a + 1
          while (b < n) {
                if (h.get(idx.get(a)) > h.get(idx.get(b))) {
                   var tmp = idx.get(a)
                   idx.set(a, idx.get(b))
                   idx.set(b, tmp)
                }
                b++
          }
          a++;
    }
    for (x in idx) {
        println(names.get(x))
    }
          
    
}
