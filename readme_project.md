# API-Map-Dijkstra-Project

## Tổng quan

- Dự án sử dụng module ESP8266 NodeMCU 1.0(ESP-12E) như một phần cứng để chạy server thông qua địa chỉ IP bằng cách kết nối chung Wi-fi với thiết bị truy cập. Mã nguồn được nạp vào chip bao gồm tệp main.ino, dijkstra.cpp, dijkstra.h. Các file dữ liệu như index.html, graph.csv được nạp vào bộ nhớ flash qua plugin LittleFS. Tất cả được thực hiện trên phần mềm Arduino IDE.

## Đầu vào

- Dữ liệu về các nút, bao gồm tên và tọa độ, nằm sẵn trong file index
- Dữ liệu về các cạnh nằm trong file graph

## Tính năng

- Hiển thị bản đồ Bách Khoa dạng địa hình, vệ tinh, xem đường phố và có thể tương tác được (phóng to, thu nhỏ, di chuyển)
- Tìm ra đường đi ngắn nhất giữa các địa điểm ở Bách Khoa thông qua thuật toán Dijkstra
- Hiển thị đường đi ngắn nhất qua những điểm nào trên bản đồ, đường đi hiển thị được mô phỏng sát thực tế, tính toán tổng khoảng cách 

## Cách vận hành

- Khi file main chạy, địa chỉ IP của web được hiển thị qua Serial Monitor, mã nguồn về cấu trúc và cách chạy web server sẽ được gọi qua file index. Chi tiết bao gồm: bố cục văn bản, phông chữ, cỡ chữ, hình dạng nút nhấn và bản đồ.
  + Hai trường để lựa chọn điểm bắt đầu và điểm kết thúc. Có thể lựa chọn địa điểm bằng cách nhấn trực tiếp trên bản đồ
  + Nút tìm đường đi
  + Bản đồ Javascript động tạo bởi khóa API đăng ký từ Google Console. Các đường biên và độ thu phóng của bản đồ được giới hạn. Trên bản đồ có hiển thị các điểm được đánh dấu sẵn và đặt tên tương ứng với các địa điểm trong khuôn viên trường (do dữ liệu về các địa điểm được cung cấp sẵn trong file index)
- File graph được gọi để đọc và lưu trữ về các cạnh cũng như trọng số của nó
- Khi nhấn nút tìm đường, web rẽ sang nhánh con của nó. Ở đó, file dijkstra.cpp được gọi để thực hiện thuật toán Dijkstra. Thuật toán sử dụng dữ liệu về đồ thị đã được đọc để xử lý, tìm đường đi ngắn nhất giữa hai nút. Đường đi và tổng trọng số sau đó được đưa lên web

## Sử dụng
- Thư viện chuẩn Arduino
- Thư viện kết nối Wi-fi và tạo web của ESP8266
- Thư viện LittleFS (plugin nạp dữ liệu vào bộ nhớ flash)
- Thư viện chuẩn C++
- Lập trình mã nguồn nạp vào module
- Lập trình thuật toán Dijkstra bằng C++
- Lập trình hướng đối tượng gọi các thư viện và các file
- Lập trình web sử dụng HTML(cấu trúc web), JavaScript(vận hành web), CSS(chỉnh sửa giao diện)
- Khóa API của Google
- Module ESP8266
- Dây nạp
- Wifi cục bộ
