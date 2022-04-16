#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

#define st first
#define sc second
#define pb push_back
#define mp make_pair
#define rof(i, a, b) for (int i = a; i < b; i++)

int main()
{


    int n, m, k;
    cin >> n >> m >> k;


    vi poeni(n);
    rof(i, 0, n){
        cin >> poeni[i];

    }

    vector<vector<int> > mx(n, vector<int>(m));
    vector<vector<ll> > dp(n+1, vector<ll>(k+1));

    rof(i, 0, n){
        rof(j, 0, m){
            cin >> mx[i][j];

        }
        sort(mx[i].begin(), mx[i].end());
    }
    ll add;

    for (int i = 0; i < n; i++){
        for (int j = 0; j <= k; j++){
            for (int z = 0; z < m; z++){
                add = mx[i][z] + 1;

                if (j + add > k){
                    break;
                }

                dp[i + 1][j + add] = max(dp[i + 1][j + add], dp[i][j] + (z + 1ll) * poeni[i]);

            }
        }
    }
    cout << dp[n][k];
}
