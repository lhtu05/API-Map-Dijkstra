#pragma once
#include <Arduino.h>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include <limits>
#include <map>
#include <LittleFS.h>

using namespace std;

extern std::map<String, vector<pair<String, int>>> graph;

void readGraph(const String& filename);
pair<int, vector<String>> dijkstra(String start, String end);
