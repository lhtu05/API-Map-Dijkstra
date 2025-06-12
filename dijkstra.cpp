#include "dijkstra.h"

std::map<String, vector<pair<String, int>>> graph;

void readGraph(const String& filename) {
  File file = LittleFS.open(filename, "r");
  if (!file) return;

  String line = file.readStringUntil('\n'); // bỏ dòng tiêu đề
  while (file.available()) {
    line = file.readStringUntil('\n');
    line.trim();
    if (line == "") continue;

    int idx1 = line.indexOf(',');
    int idx2 = line.indexOf(',', idx1 + 1);
    String u = line.substring(0, idx1);
    String v = line.substring(idx1 + 1, idx2);
    int w = line.substring(idx2 + 1).toInt();

    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
  }
  file.close();
}

pair<int, vector<String>> dijkstra(String start, String end) {
  std::map<String, int> dist;
  std::map<String, String> prev;
  for (auto& node : graph) dist[node.first] = 999999;
  dist[start] = 0;

  using P = pair<int, String>;
  priority_queue<P, vector<P>, greater<P>> pq;
  pq.push({0, start});

  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (u == end) break;
    for (auto& [v, w] : graph[u]) {
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        prev[v] = u;
        pq.push({dist[v], v});
      }
    }
  }

  vector<String> path;
  String cur = end;
  while (cur != start && prev.count(cur)) {
    path.push_back(cur);
    cur = prev[cur];
  }
  if (cur == start) {
    path.push_back(start);
    reverse(path.begin(), path.end());
  } else {
    path.clear();
  }
  return {dist[end], path};
}
