template<class EType> struct Graph {
    int V;
    vector<vector<EType *>> adj;

    Graph(int _V) : V(_V) { adj.resize(V); }
};
