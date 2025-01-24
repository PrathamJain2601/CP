#include<bits/stdc++.h>
using namespace std;

#define vin(a) for(int i=0;i<(a).size();i++)cin>>a[i];
#define vout(a) for(int i=0;i<a.size();i++)cout<<a[i]<<' ';cout<<endl;

vector<int> dijkstra(vector<vector<pair<int, int>>> &adjList, int src) {
    vector<int> distance(adjList.size(), INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    distance[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        int dist = pq.top().first;
        int prev = pq.top().second;
        pq.pop();
        for (auto node : adjList[prev]) {
            int next = node.first;
            int weight = node.second;
            if (dist + weight < distance[next]) {
                distance[next] = dist + weight;
                pq.push({distance[next], next});
            }
        }
    }
    return distance;
}

void tarjanDFS(int src, int parent, vector<int> &visited, vector<vector<int>> &adjList, vector<int> &timeIn, vector<int> &low, int &timer, vector<pair<int, int>> &bridges){
    visited[src] = 1;
    low[src] = timer;
    timeIn[src] = timer;
    timer++;
    for(auto node: adjList[src]){
        if(node == parent) continue;
        if(visited[node]){
            low[src] = min(low[src], low[node]);
        }
        else{
            tarjanDFS(node, src, visited, adjList, timeIn, low, timer, bridges);
            if(low[node] > low[src]){
                bridges.push_back({src, node});
            }
            else{
                low[src] = min(low[src], low[node]);
            }
        }
    }
}
vector<pair<int, int>> tarjan(vector<vector<int>> adjList){
    int n = adjList.size();
    vector<int> visited(n, 0);
    vector<int> timeIn(n, 0);
    vector<int> low(n, n);
    vector<pair<int, int>> bridges;
    int timer = 0;
    tarjanDFS(0, -1, visited, adjList, timeIn, low, timer, bridges);
    return bridges;
}

pair<int, vector<pair<int, int>>> prims(vector<vector<pair<int, int>>> adjList){
    int n = adjList.size();
    vector<pair<int, int>> mst;
    int sum = 0;
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<int> visited(n, 0);
    visited[0] = 1;
    pq.push({0, 0, -1});

    while(!pq.empty()){
        int weight = pq.top()[0];
        int src = pq.top()[1];
        int parent = pq.top()[2];
        pq.pop();
        if(visited[src] == 0){
            mst.push_back({parent, src});
            sum += weight;
        }
        visited[src] = 1;
        for(auto node: adjList[src]){
            if(visited[node.first] == 0){
                pq.push({node.second, node.first, src});
            }
        }
    }
    return {sum, mst};
}

vector<int> kahn(vector<vector<int>> adjList){
    int n = adjList.size();
    vector<int> degrees(n, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < adjList[i].size(); j++){
            degrees[adjList[i][j]]++;
        }
    }
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(degrees[i] == 0) q.push(i);
    }
    vector<int> ans;
    while(!q.empty()){
        int src = q.front();
        ans.push_back(src);
        q.pop();
        for(auto node: adjList[src]){
            degrees[node]--;
            if(degrees[node] == 0){
                q.push(node);
            }
        }
    }
    return ans;
}

void topologicalDFS(int src, vector<int> &visited, vector<vector<int>> &adjList, stack<int> &st){
    visited[src] = 1;
    for(int node: adjList[src]){
        if(visited[node] == 0){
            topologicalDFS(node, visited, adjList, st);
        }
    }
    st.push(src);
}
vector<int> topological(vector<vector<int>> adjList){
    int n = adjList.size();
    vector<int> visited(n, 0);
    stack<int> st;
    for(int i = 0; i < n; i++){
        if(visited[i] == 0){
            topologicalDFS(i, visited, adjList, st);
        }
    }
    vector<int> ans;
    while(!st.empty()){
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}

int ultimateParent(vector<int> &parent, int node){
    if(parent[node] == node){
        return node;
    }
    parent[node] = ultimateParent(parent, parent[node]);
}
pair<int, vector<pair<int, int>>> kruskal(vector<vector<pair<int, int>>> adjList){
    int n = adjList.size();
    vector<vector<int>> edges;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < adjList[i].size(); j++){ 
            if(i < adjList[i][j].first){
                edges.push_back({adjList[i][j].second, i, adjList[i][j].first});
            }
        }
    }
    sort(edges.begin(), edges.end());
    vector<int> size(n, 1);
    vector<int> parent(n);
    for(int i = 0; i < n; i++){
        parent[i] = i;
    }
    int sum = 0;
    vector<pair<int, int>> ans;
    for(auto edge: edges){
        int parent1 = ultimateParent(parent, edge[1]);
        int parent2 = ultimateParent(parent, edge[2]);
        if(parent1 != parent2){
            if(size[parent1] > size[parent2]){
                parent[parent2] = parent1;
                size[parent1] += parent2;                
            }
            else{
                parent[parent1] = parent2;
                size[parent2] += parent1;
            }
            sum += edge[0];
            ans.push_back({edge[1], edge[2]});
        }
    }
    return {sum, ans};
}

vector<int> bellmanFord(vector<vector<pair<int, int>>> adjList){
    int n = adjList.size();
    vector<vector<int>> edges;
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < adjList[i].size(); j++){
            edges.push_back({i, adjList[i][j].first, adjList[i][j].second});
        }
    }
    vector<int> distance(n, 1e9);
    distance[0] = 0;
    for(int i = 0; i < n-1; i++){
        for(auto edge: edges){
            if(distance[edge[0]] == 1e9) continue;
            if(distance[edge[0]] + edge[2] < distance[edge[1]]){
                distance[edge[1]] = distance[edge[0]] + edge[2];
            }
        }
    }

    for(auto edge: edges){
        if(distance[edge[0]] == 1e18) continue;
        if(distance[edge[0]] + edge[2] < distance[edge[1]]){
            vector<int> res(n, -1);
            return res;
        }
    }

    return distance;
}

vector<vector<int>> floydWarshal(vector<vector<pair<int, int>>> adjList){
    int n = adjList.size();
    vector<vector<int>> arr(n, vector<int>(n, 1e9));
    for(int i = 0; i < n; i++){
        arr[i][i] = 0;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < adjList[i].size(); j++){
            arr[i][adjList[i][j].first] = adjList[i][j].second; 
        }
    }

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(arr[i][k] == 1e9 || arr[k][j] == 1e9) continue;
                    arr[i][j] = min(arr[i][j], arr[i][k] + arr[k][j]);
            }
        }
    }

    bool negativeCycle = false;
    for(int i = 0; i < n; i++){
        negativeCycle = negativeCycle || (arr[i][i] < 0);
    }

    if(negativeCycle){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                arr[i][j] = -1; 
            }
        }
    }

    return arr;
}

int main(){


    //dijkastra
    // int n, m;
    // cin>>n>>m;
	// vector<vector<pair<int, int>>> adjList(n);
    // for(int i = 0; i < m; i++){
    //     int a, b, c;
    //     cin>>a>>b>>c;
    //     adjList[a].push_back({b, c});
    //     adjList[b].push_back({a, c});
    // }
    // vector<int> ans = dijkstra(adjList, 0);
    // vout(ans);
    // 6 8
    // 0 1 4
    // 0 2 4
    // 1 2 2
    // 2 3 3 
    // 2 4 1
    // 2 5 6
    // 3 5 2
    // 4 5 3


    //detecting bridge in graph - tarjan
    // int n, m;
    // cin>>n>>m;
    // vector<vector<int>> adjList(n);
    // for(int i = 0; i < m; i++){
    //     int a, b;
    //     cin>>a>>b;
    //     adjList[a].push_back(b);
    //     adjList[b].push_back(a);
    // }
    // vector<pair<int, int>> ans = tarjan(adjList);
    // for(int i = 0; i < ans.size(); i++){
    //     cout<<ans[i].first<<" "<<ans[i].second<<endl;
    // }
    // 12 14
    // 0 1
    // 0 3
    // 1 2
    // 2 3
    // 3 4
    // 4 5
    // 5 6
    // 5 8
    // 6 7
    // 7 8
    // 7 9
    // 9 10
    // 9 11
    // 10 11


    // minimum spanning tree - prims
    // int n, m;
    // cin>>n>>m;
	// vector<vector<pair<int, int>>> adjList(n);
    // for(int i = 0; i < m; i++){
    //     int a, b, c;
    //     cin>>a>>b>>c;
    //     adjList[a].push_back({b, c});
    //     adjList[b].push_back({a, c});
    // }
    // pair<int, vector<pair<int, int>>> res = prims(adjList);
    // vector<pair<int, int>> ans = res.second;
    // int sum = res.first;
    // cout<<sum<<endl;
    // for (int i = 0; i < ans.size(); i++) {
    //     cout<<ans[i].first<<" "<<ans[i].second<<endl;
    // }
    // 5 6
    // 0 1 2
    // 0 2 1
    // 1 2 1
    // 2 4 2
    // 2 3 2
    // 3 4 1


    // topological sort - kahn's algorithm (directed acyclic graph)
    // int n, m;
    // cin>>n>>m;
    // vector<vector<int>> adjList(n);
    // for(int i = 0; i < m; i++){
    //     int a, b;
    //     cin>>a>>b;
    //     adjList[a].push_back(b);
    // }
    // vector<int> ans = kahn(adjList);
    // vout(ans);
    // 6 6
    // 2 3
    // 3 1
    // 4 0
    // 4 1
    // 5 0 
    // 5 2


    // topological sort - dfs algorithm (directed acyclic graph)
    // int n, m;
    // cin>>n>>m;
    // vector<vector<int>> adjList(n);
    // for(int i = 0; i < m; i++){
    //     int a, b;
    //     cin>>a>>b;
    //     adjList[a].push_back(b);
    // }
    // vector<int> ans = topological(adjList);
    // vout(ans);
    // 6 6
    // 2 3
    // 3 1
    // 4 0
    // 4 1
    // 5 0 
    // 5 2


    // minimum spanning tree - kruskal
    // int n, m;
    // cin>>n>>m;
	// vector<vector<pair<int, int>>> adjList(n);
    // for(int i = 0; i < m; i++){
    //     int a, b, c;
    //     cin>>a>>b>>c;
    //     adjList[a].push_back({b, c});
    //     adjList[b].push_back({a, c});
    // }
    // pair<int, vector<pair<int, int>>> ans = kruskal(adjList);
    // cout<<ans.first<<endl;
    // for(auto node: ans.second){
    //     cout<<node.first<<" "<<node.second<<endl;
    // }
    // 6 9
    // 4 3 9
    // 4 0 4
    // 0 3 1
    // 0 1 2
    // 3 2 5
    // 3 1 3
    // 1 2 3
    // 2 5 8
    // 1 5 7

    
    // bellman ford - shortest path (helps detect negative cycle in directed graphs)
    // int n, m;
    // cin>>n>>m;
	// vector<vector<pair<int, int>>> adjList(n);
    // for(int i = 0; i < m; i++){
    //     int a, b, c;
    //     cin>>a>>b>>c;
    //     adjList[a].push_back({b, c});
    // }
    // vector<int> ans = bellmanFord(adjList);
    // vout(ans);


    // floyd warshal - multi source shortest path
    // int n, m;
    // cin>>n>>m;
	// vector<vector<pair<int, int>>> adjList(n);
    // for(int i = 0; i < m; i++){
    //     int a, b, c;
    //     cin>>a>>b>>c;
    //     adjList[a].push_back({b, c});
    // }
    // vector<vector<int>> ans = floydWarshal(adjList);
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         cout<<ans[i][j]<<" "; 
    //     }cout<<endl;
    // }
    // 4 6
    // 0 1 2
    // 1 0 1
    // 3 0 3
    // 3 1 5
    // 1 2 3
    // 3 2 4

}