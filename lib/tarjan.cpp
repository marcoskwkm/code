// Algoritmo de Tarjan
// Encontra componentes fortemente conexas em O(V+E)

int cmp[MAXN];                     // Guarda em qual componente estah o vertice i
int ind[MAXN], low[MAXN], pre, cnt;  // Zerar vetor ind com -1 !!!  <-----------------
bool inStack[MAXN];
stack<int> st;

void tarjan(int v) {
    ind[v] = low[v] = pre++;
    st.push(v);
    inStack[v] = 1;
    for (int nxt: adj[v]) {
        if (ind[nxt] == -1) {
            tarjan(nxt);
            low[v] = min(low[v], low[nxt]);
        }
        else if (inStack[nxt]) low[v] = min(low[v], ind[nxt]);
    }
    if (ind[v] == low[v]) {
        int vv;
        do {
            vv = st.top();
            st.pop();
            inStack[vv] = 0;
            cmp[vv] = cnt;
        } while (vv != v);
        ++cnt;
    }
}
