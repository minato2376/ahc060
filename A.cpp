#include "other/template.hpp"

// === ランダムウォーク貪欲法 ===
// 方針:
// - 隣接する店があり、納品するとスコアが上がるなら店に移動して納品
// - それ以外で、現在Wの木にいるなら1〜2%の確率で行動2(W→R変換)
// - 上記以外なら、前の頂点以外からランダムに隣接頂点を選んで移動

void solve() {
    INT(N, M, K, T);
    vvec<int> adj(N);
    rep(i, M) {
        INT(a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vec<int> X(N), Y(N);
    rep(i, N) cin >> X[i] >> Y[i];

    // 各木の味: 初期はすべてW
    vec<char> flavor(N, 'W');

    // 各ショップの在庫集合
    vec<set<string>> inventory(K);

    int cur = 0;       // 現在位置（頂点0=ショップ）
    int prev = -1;     // 前回の行動1での移動元
    string cone = "";  // 手元のコーン
    int steps = 0;     // 使用ステップ数

    mt19937 rng(42);

    while (steps < T) {
        // --- 優先1: 隣接するショップで、納品するとスコアが上がるものがあるか ---
        int best_shop = -1;
        for (int u : adj[cur]) {
            if (u == prev) continue;  // 前の頂点には戻れない
            if (u < K) {
                // ショップu: 現在のconeがまだ在庫にないならスコアUP
                if (inventory[u].find(cone) == inventory[u].end()) {
                    best_shop = u;
                    break;
                }
            }
        }

        if (best_shop != -1) {
            // ショップに移動して納品
            inventory[best_shop].insert(cone);
            cone = "";
            print(best_shop);
            prev = cur;
            cur = best_shop;
            steps++;
            continue;
        }

        // --- 優先2: 現在Wの木にいるなら、1〜2%の確率で行動2 ---
        if (cur >= K && flavor[cur] == 'W') {
            if ((int)(rng() % 100) < 2) {
                print(-1);
                flavor[cur] = 'R';
                steps++;
                continue;
            }
        }

        // --- 優先3: 前の頂点以外からランダムに隣接頂点を選んで移動 ---
        vec<int> cands;
        for (int u : adj[cur]) {
            if (u != prev) cands.push_back(u);
        }
        if (cands.empty()) break;  // 2辺連結なので起きないはず

        int nxt = cands[rng() % cands.size()];
        if (nxt >= K) {
            // 木 → アイスを収穫
            cone += flavor[nxt];
        } else {
            // ショップ → 納品
            inventory[nxt].insert(cone);
            cone = "";
        }
        print(nxt);
        prev = cur;
        cur = nxt;
        steps++;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);
    cerr << fixed << setprecision(7);

    int T = 1;
    for (int test_case = 1; test_case <= T; test_case++) {
        solve();
    }
}
