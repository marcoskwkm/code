fun main(args: Array<String>) {
    val (a, x, y) = readLine()!!.split(' ').map(String::toInt)
    if (0 < x && x < a && 0 < y && y < a)
        println(0);
    else if((x == 0 || x == a) && (0 <= y && y <= a))
         println(1);
    else if((y == 0 || y == a) && (0 <= x && x <= a))
         println(1);
    else
        println(2);
}
