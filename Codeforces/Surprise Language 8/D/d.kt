fun main(args: Array<String>) {
    var q = readLine()!!.toInt()
    while (q-- > 0) {
          var (n, m ,p) = readLine()!!.split(" ").map(String::toInt)
          if (n > m) {
             var tmp = n
             n = m
             m = tmp
          }
          var ok = 0
          var d = 1
          while (d <= p) {
                if (p % d > 0) {
                   d++
                   continue
                }
                var a = p / d
                var b = d
                if (a > b) {
                   var tmp = a
                   a = b
                   b = tmp
                }
                if (a <= n && b <= m) ok = 1
                d++
          }
          if (ok == 1) println("Yes")
          else println("No")
   }
          
}
          
