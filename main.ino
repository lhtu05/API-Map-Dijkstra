#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>                                                   //Thư viện kết nối Wi-fi và tạo web của ESP8266   
#include <LittleFS.h>                                                           //Thư viện plugin nạp file vào bộ nhớ flash
#include "dijkstra.h"

const char* ssid = "zef";
const char* password = "ryhdbssa";                                       //Tên và mật khẩu Wi-fi

ESP8266WebServer server(80);                                                    //Tạo web server chạy trên cổng 80(mặc định)

void handleRoot() {
  File file = LittleFS.open("/index.html", "r");                                //Mở và đọc file index
  if (!file) {
    server.send(500, "text/plain", "Không tìm thấy index.html");                //Trả về mã lỗi 500(không tìm thấy file) với định dạng văn bản thường
    return;
  }                                                                             //Nếu không tìm thấy file thì báo lỗi 500
  server.streamFile(file, "text/html");                                         //Trả về toàn bộ nội dung trong file với định dạng html
  file.close();
}

void handleDijkstra() {
  if (!server.hasArg("from") || !server.hasArg("to")) {                         //Nếu trên URL không chứa 
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
  server.on("/parking.json", HTTP_GET, []() {
    File file = LittleFS.open("/parking.json", "r");
    if (!file || file.isDirectory()) {
      server.send(404, "application/json", "{\"error\":\"File not found\"}");
      return;
    }
    server.streamFile(file, "application/json");
    file.close();
  });

  server.begin();
  Serial.println("Web server đã sẵn sàng.");
}

void loop() {
  server.handleClient();
}
