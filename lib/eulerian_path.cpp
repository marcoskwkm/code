// Eulerian path/circuit

int mat[MAXN][MAXN]; // matriz de adjacencias
vector<int> adj[MAXN]; // lista de adjacencias
int ptr[MAXN];

vector<int> _path; // guarda o caminho

void find_path(int v) {
    for(int &a=ptr[v];a<adj[v].size();++a) {
        int nxt = adj[v][a];
        if(mat[v][nxt]) {
            mat[v][nxt]--; mat[nxt][v]--;
            find_path(nxt);
            break;
        }
    }
    _path.push_back(v);
}

vector<int> eulerian_path(int s) {
    _path.clear();
    memset(ptr,0,sizeof(ptr));
    find_path(s);
    reverse(_path.begin(),_path.end());
    return _path;
}
