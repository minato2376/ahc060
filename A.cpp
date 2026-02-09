#include "other/template.hpp"

// === ランダムウォーク貪欲法 (BFS先読みあり) ===
// 方針:
// - 最大距離8までBFSして、スコアが上がる店への経路があればその移動をする
// - それ以外で、現在Wの木にいるなら1〜2%の確率で行動2(W→R変換)
// - 上記以外なら、前の頂点以外のアイスの木からランダムに移動
// - 移動できるアイスの木がないなら、しかたなく店へ移動

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

    // BFS: 最大距離8まで探索して、スコアが上がる店への経路を返す
    // 経路途中のコーン変化（木で収穫、店で納品リセット）もシミュレート
    auto bfs_find_shop = [&]() -> vec<int> {
        struct Node {
            int v, prv;
            string cone;
            int parent;  // nodesベクタのインデックス、根なら-1
        };

        vec<Node> nodes;
        queue<int> que;

        // 深さ1: curの隣接頂点を探索
        for (int u : adj[cur]) {
            if (u == prev) continue;
            string new_cone = cone;
            if (u >= K) {
                new_cone += flavor[u];
            } else {
                // 店: 納品でスコアが上がるか？
                if (!inventory[u].count(new_cone)) {
                    return {u};
                }
                new_cone = "";  // 納品してコーンリセット
            }
            int idx = SZ(nodes);
            nodes.push_back({u, cur, new_cone, -1});
            que.push(idx);
        }

        // 深さ2〜8
        int depth = 1;
        while (!que.empty() && depth < 8) {
            int sz = SZ(que);
            rep(_, sz) {
                int ni = que.front();
                que.pop();
                // ノードデータをコピー（nodes拡張で参照無効化を防ぐ）
                int v = nodes[ni].v;
                int prv = nodes[ni].prv;
                string c = nodes[ni].cone;

                for (int u : adj[v]) {
                    if (u == prv) continue;
                    string new_cone = c;
                    if (u >= K) {
                        new_cone += flavor[u];
                    } else {
                        if (!inventory[u].count(new_cone)) {
                            // 経路を復元
                            vec<int> path = {u};
                            int p = ni;
                            while (p != -1) {
                                path.push_back(nodes[p].v);
                                p = nodes[p].parent;
                            }
                            reverse(ALL(path));
                            return path;
                        }
                        new_cone = "";
                    }
                    int idx = SZ(nodes);
                    nodes.push_back({u, v, new_cone, ni});
                    que.push(idx);
                }
            }
            depth++;
        }
        return {};
    };

    while (steps < T) {
        // --- 優先1: BFS距離8以内でスコアが上がる店への経路を探す ---
        vec<int> path = bfs_find_shop();
        if (!path.empty()) {
            for (int v : path) {
                if (steps >= T) break;
                if (v >= K) {
                    cone += flavor[v];
                } else {
                    inventory[v].insert(cone);
                    cone = "";
                }
                print(v);
                prev = cur;
                cur = v;
                steps++;
            }
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

        // --- 優先3: 前の頂点以外のアイスの木からランダムに移動 ---
        vec<int> trees;
        vec<int> shops;
        for (int u : adj[cur]) {
            if (u == prev) continue;
            if (u >= K)
                trees.push_back(u);
            else
                shops.push_back(u);
        }

        int nxt;
        if (!trees.empty()) {
            nxt = trees[rng() % trees.size()];
        } else if (!shops.empty()) {
            // 木がないならしかたなく店へ
            nxt = shops[rng() % shops.size()];
        } else {
            break;  // 2辺連結なので起きないはず
        }
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
