#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

const int maxn = 501;
const int INF = 0x3fffffff;
int G[maxn][maxn], unin[maxn], d[maxn];
bool vis[maxn];
int c, n, s, m, minout = INF, minin = INF;
vector<int> lines, linebest;
vector<int> store[maxn];
void Dijkstra() {
  fill(vis, vis + maxn, false);
  fill(d, d + maxn, INF);
  d[0] = 0;
  for (int i = 0; i <= n; ++i) {
    int u = -1, MIN = INF;
    for (int j = 0; j <= n; ++j) {
      if (vis[j] == false && d[j] < MIN) {
        u = j;
        MIN = d[j];
      }
    }
    if (u == -1) return;
    vis[u] = true;
    for (int v = 0; v <= n; ++v) {
      if (vis[v] == false && G[u][v] != INF && d[u] + G[u][v] <= d[v]) {
        if (d[u] + G[u][v] < d[v]) store[v].clear();
        store[v].push_back(u);
        d[v] = d[u] + G[u][v];
      }
    }
  }
}
void DFS(int st) {
  lines.push_back(st);
  if (st == 0) {
    int out = 0, in = 0;
    //		for(int i=0;i<lines.size();++i){
    //			cout<<lines[i]<<" ";
    //		}
    //		cout<<endl;
    for (int i = lines.size() - 2; i >= 0; --i) {
      int temp = lines[i], mid = c / 2;
      if (unin[temp] > mid) {
        in += (unin[temp] - mid);
        //				cout<<in<<" "<<out<<" 99"<<endl;
      } else {
        if (in + unin[temp] > mid) {
          in += (unin[temp] - mid);
          //					cout<<in<<" "<<out<<" 98"<<endl;
        } else {
          out += (mid - (unin[temp] + in));
          in = 0;
          //					cout<<in<<" "<<out<<" 97"<<endl;
        }
      }
    }
    if (out < minout) {
      minout = out;
      minin = in;
      linebest = lines;
    } else {
      if (out == minout && in < minin) {
        minin = in;
        linebest = lines;
      }
      lines.pop_back();
      return;
    }
  }
  for (int i = 0; i < store[st].size(); ++i) {
    DFS(store[st][i]);
  }
  lines.pop_back();
}
// void DFS(int st){
//	if(st==0){
//		int cost=spend-len*c/2;
//		if(abs(cost)<abs(spendmin)){
//			spendmin=cost;
//			linebest=lines;
//		}
//		return ;
//	}
//	vector<int> temp=store[st];
//
//	for(int i=0;i<temp.size();++i){
//		spend+=unin[temp[i]];
//		++len;
//		lines.push_back(temp[i]);
//		DFS(temp[i]);
//		spend-=unin[temp[i]];
//		--len;
//		lines.pop_back();
//	}
//
//}
int main() {
  cin >> c >> n >> s >> m;
  fill(G[0], G[0] + maxn * maxn, INF);
  for (int i = 1; i <= n; ++i) {
    cin >> unin[i];
  }
  int line, row;
  for (int i = 0; i < m; ++i) {
    cin >> line >> row;
    scanf("%d", &G[line][row]);
    G[row][line] = G[line][row];
  }
  Dijkstra();
  //	for(int i=0;i<=n;++i){
  //		for(int j=0;j<store[i].size();++j){
  //			cout<<store[i][j]<<" ";
  //		}
  //		cout<<endl;
  //	}

  DFS(s);

  cout << minout << " ";
  for (int i = linebest.size() - 1; i > 0; --i) {
    cout << linebest[i] << "->";
  }
  cout << s << " " << minin << endl;
  return 0;
}
