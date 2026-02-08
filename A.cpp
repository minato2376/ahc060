#include "other/template.hpp"

// === 貪欲法 ===
// 戦略:
// 1. BFSで各頂点間の最短経路を事前計算
// 2. 現在位置から木を何個か巡ってコーンに文字列を構築
// 3. 近くのショップに行って納品
// 4. W→R変換を活用して同じ経路でも異なる文字列を生成
//
// 制約:
// - 前回の移動元には戻れない
// - 最大T=10000ステップ
// - N=100頂点, K=10ショップ

void solve() {
    INT(N, M, K, T);
    vvec<int> adj(N);
    rep(i, M) {
        INT(a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // 座標（使わないかもしれないが読み込む）
    vec<int> X(N), Y(N);
    rep(i, N) cin >> X[i] >> Y[i];

    // BFS: 各頂点からの最短距離と最短経路の次の頂点を計算
    // bfs_next[s][t] = s→tの最短経路で最初に移動する頂点
    vvec<int> dist(N, vec<int>(N, -1));
    vvec<int> bfs_next(N, vec<int>(N, -1));
    rep(s, N) {
        queue<int> que;
        dist[s][s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int u : adj[v]) {
                if (dist[s][u] == -1) {
                    dist[s][u] = dist[s][v] + 1;
                    bfs_next[s][u] = (v == s) ? u : bfs_next[s][v];
                    que.push(u);
                }
            }
        }
    }

    // 各木の味: 初期はすべてW
    vec<char> flavor(N, 'W');

    // 各ショップの在庫集合
    vec<set<string>> inventory(K);

    int cur = 0;       // 現在位置
    int prev = -1;     // 前回の移動元（最初はなし）
    string cone = "";  // 手元のコーン
    int steps = 0;     // 使用ステップ数

    // ショップに移動して納品する関数
    // 戻り値: 使ったステップ数。移動不能なら-1。
    // 注意: prev制約を守りながらBFS経路をたどる
    auto move_to = [&](int target) -> bool {
        while (cur != target) {
            if (steps >= T) return false;
            int nxt = bfs_next[cur][target];
            // prev制約チェック: nxtがprevなら迂回が必要
            if (nxt == prev) {
                // 別の隣接頂点を経由する
                bool found = false;
                for (int u : adj[cur]) {
                    if (u == prev) continue;
                    // uを経由してtargetへ向かう
                    nxt = u;
                    found = true;
                    break;
                }
                if (!found) return false;  // 2辺連結なのでここには来ないはず
            }
            // 移動実行
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
        return true;
    };

    // --- メインロジック ---
    // 戦略: 各ショップの近くの木を巡回して、異なる文字列を生成して納品
    //
    // Phase 1: まずWのみで各ショップ周辺を巡回
    // Phase 2: 一部の木をRに変換して再巡回

    // 各ショップに隣接する木のリストを取得
    vvec<int> shop_trees(K);
    rep(shop, K) {
        // BFS距離が近い木を集める（距離3以内くらい）
        vec<pair<int, int>> tree_dist;  // (dist, node)
        rep(v, N) {
            if (v >= K) {  // 木
                tree_dist.push_back({dist[shop][v], v});
            }
        }
        sort(ALL(tree_dist));
        for (auto [d, v] : tree_dist) {
            shop_trees[shop].push_back(v);
        }
    }

    // ショップ0, 1, ..., K-1 を順に巡回し、各ショップ周辺で文字列を生成
    // まずは単純に: 各ショップへ行き、周辺の木を1〜数個訪問して戻る

    // 残りステップ内でできるだけ多くの文字列を各ショップに納品する
    mt19937 rng(42);

    // 訪問するショップの順序を距離ベースで決める
    vec<int> shop_order(K);
    iota(ALL(shop_order), 0);

    // 何ラウンドか繰り返す
    int max_rounds = 50;
    rep(round, max_rounds) {
        if (steps >= T - 20) break;

        // ショップ順をシャッフル（ただし最初のラウンドは0から順番に）
        if (round > 0) {
            shuffle(ALL(shop_order), rng);
        }

        for (int shop : shop_order) {
            if (steps >= T - 20) break;

            // ショップへ移動
            if (!move_to(shop)) break;

            // ショップ周辺の木を巡回
            // 長さ1〜5程度の文字列を生成してみる
            int max_depth = min(5, (int)shop_trees[shop].size());
            // 木を1〜max_depth個訪問する組み合わせを試す
            rep(num_trees, 1, max_depth + 1) {
                if (steps >= T - 20) break;

                // shop_trees[shop] のうち最初のnum_trees個の木を訪問する
                // ただし単純にmove_toすると遠い木に行ってしまうので、
                // 近い木をnum_trees個訪問してショップに戻る

                // 近い木をランダムに選んで訪問
                vec<int> candidates;
                int search_range = min(20, SZ(shop_trees[shop]));
                rep(j, search_range) {
                    candidates.push_back(shop_trees[shop][j]);
                }
                shuffle(ALL(candidates), rng);

                // num_trees個の木を訪問
                bool ok = true;
                rep(j, num_trees) {
                    if (j >= SZ(candidates)) {
                        ok = false;
                        break;
                    }
                    if (!move_to(candidates[j])) {
                        ok = false;
                        break;
                    }
                }
                if (!ok) break;

                // ショップに戻って納品
                if (!move_to(shop)) break;
            }
        }

        // 一部の木をRに変えるフェーズ
        // 各ラウンドの終わりに、まだWの木を少しずつRに変換
        if (round == 2 || round == 5 || round == 10 || round == 20) {
            // 各ショップの近くの木を半分くらいRに変換
            rep(shop, K) {
                int count = 0;
                for (int tree : shop_trees[shop]) {
                    if (flavor[tree] == 'W' && count < SZ(shop_trees[shop]) / 3) {
                        // 木に移動
                        if (steps >= T - 20) break;
                        if (!move_to(tree)) break;
                        // 行動2: W→R変換
                        if (steps < T) {
                            print(-1);
                            flavor[tree] = 'R';
                            steps++;
                        }
                        count++;
                    }
                }
            }
        }
    }

    // 残りステップを使い切る: ランダムウォークしてショップに着いたら納品
    while (steps < T) {
        // 最寄りのショップを見つけてそこへ向かう
        int nearest_shop = 0;
        int min_dist = INT_MAX;
        rep(shop, K) {
            if (chmin(min_dist, dist[cur][shop])) {
                nearest_shop = shop;
            }
        }

        // ランダムに木を1〜3個巡ってからショップへ
        int walk_len = rng() % 3 + 1;
        rep(w, walk_len) {
            if (steps >= T) break;
            // ランダムに隣接頂点を選ぶ（prev以外）
            vec<int> cands;
            for (int u : adj[cur]) {
                if (u != prev) cands.push_back(u);
            }
            if (cands.empty()) break;
            int nxt = cands[rng() % cands.size()];
            if (nxt >= K) {
                cone += flavor[nxt];
            } else {
                inventory[nxt].insert(cone);
                cone = "";
            }
            print(nxt);
            prev = cur;
            cur = nxt;
            steps++;
        }

        // 最寄りショップへ
        if (steps < T) {
            if (!move_to(nearest_shop)) break;
        }
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
