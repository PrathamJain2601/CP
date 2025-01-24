#include<bits/stdc++.h>
using namespace std;

#define int long long int
#define double long double
#define MAX LLONG_MAX
#define MIN LLONG_MIN
#define endl '\n'
#define vin(a) for(int i=0;i<(a).size();i++)cin>>a[i];
#define vout(a) for(int i=0;i<a.size();i++)cout<<a[i]<<' ';cout<<endl;
#define cout(x) cout<<setprecision(20)<<x<<endl;
#define yes cout<<"YES"<<endl; return;
#define no cout<<"NO"<<endl; return;
const int M = 1e9+7;
const int N = 1e5+10;
vector<bool> prime(N,true);

// __builtin_clzll(n) gives the number of leading zeros in n

int lcm(int a,int b){return (a*b)/__gcd(a,b);}

int ceil(int n,int k){return (n+k-1)/k;}

int power(int a,int b){
	if(b==0) return 1;
	int ans = power(a,b/2);
	ans = (ans*ans)%M;
	if(b&1) ans = (a*ans)%M;
	return ans;
}

void precalc(){}

bool cmp(pair<int, int> a, pair<int, int> b){
  
}

void solve() {
  int n, m;
  cin>>n>>m;
  vector<vector<char>> arr(n, vector<char>(m, 0));
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      cin>>arr[i][j];
    }
  }
  if(arr[1][0] == '#' || arr[0][1] == '#'){
    cout<<-1<<endl;
    return;
  }
  vector<vector<char>> visited(n, vector<char>(m, -1));
  visited[i][j] = 0;
  queue<pair<int, int>> q;
  q.push({0, 0});
  while(!q.empty()){
    int top = q.front();
    q.pop();
    vector<int> l = {0, 1, 0 , -1, 0};
    for(int i = 0; i < 4; i++){
      int row = l[i];
      int col = l[i+1];
      if(top.first + row >= 0 && top.first + row < n && top.second + col >= 0 && top.second + col < m){
      if(visited[top.first + row][top.second + col] == -1 && arr[top.first + row][top.second + col] == '.'){
        visited[top.first + row][top.second + col] = visited[top.first][top.second] + 1;
        q.push({top.first + row, top.second + col});
      }
      }
    }
  }
  if(visited[n-1][m-1] == -1){
    cout<<-1<<endl;
    return;
  }
  int ans = visited[n-1][m-1];

  
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	precalc();
	int t = 1;	
  cin >> t;
	while(t--){
		solve();
	}
	return 0;
}