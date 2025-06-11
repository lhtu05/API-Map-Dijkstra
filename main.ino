#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>
#include "dijkstra.h"

const char* ssid = "Lucky 2";
const char* password = "thanhthaonguyen";

ESP8266WebServer server(80);

void handleRoot() {
  File file = LittleFS.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "Không tìm thấy index.html");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handleDijkstra() {
  if (!server.hasArg("from") || !server.hasArg("to")) {
    server.send(400, "application/json", "{\"error\":\"Thiếu tham số\"}");
    return;
  }

  String from = server.arg("from");
  String to = server.arg("to");

  auto [cost, path] = dijkstra(from.c_str(), to.c_str());

  String json = "{\"cost\":" + String(cost) + ",\"path\":[";
  for (size_t i = 0; i < path.size(); i++) {
    json += "\"" + String(path[i].c_str()) + "\"";
    if (i < path.size() - 1) json += ",";
  }
  json += "]}";
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Kết nối WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nĐã kết nối, IP: " + WiFi.localIP().toString());

  if (!LittleFS.begin()) {
    Serial.println("Lỗi khởi động LittleFS");
    return;
  }

  readGraph("/graph.csv");

  server.on("/", handleRoot);
  server.on("/dijkstra", handleDijkstra);
  server.begin();
  Serial.println("Web server đã sẵn sàng.");
}

void loop() {
  server.handleClient();
}
