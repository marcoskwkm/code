// Returns convex hull in counterclockwise order.
template<class T> Poly<T> get_convex_hull(Poly<T> poly) {
    sort(poly.begin(), poly.end(), [](const Point<T> &a, const Point<T> &b) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });
    Poly<T> top, bot;
    size_t top_s = 0, bot_s = 0;
    for (const Point<T> &p: poly) {
        while (top_s > 1 &&
               ((top[top_s - 2] - top[top_s - 1]) ^ (p - top[top_s - 1])) <= 0)
            top_s--, top.pop_back();
        while (bot_s > 1 &&
               ((p - bot[bot_s - 1])^(bot[bot_s - 2] - bot[bot_s - 1])) <= 0)
            bot_s--, bot.pop_back();
        top.push_back(p);
        bot.push_back(p);
        top_s++, bot_s++;
    }
    for (int i = (int)top_s - 2; i > 0; i--)
        bot.push_back(top[i]);
    return bot;
}
