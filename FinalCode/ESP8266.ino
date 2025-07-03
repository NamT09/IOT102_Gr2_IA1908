#define BLYNK_TEMPLATE_ID "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "Security System"
#define BLYNK_AUTH_TOKEN "YourAuthTokenHere"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char ssid[] = "PG09";         // Tên WiFi
char pass[] = "soiden022509";      // Mật khẩu WiFi


String inputData = "";


void setup() {
  Serial.begin(9600);              // Nhận dữ liệu từ Arduino
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  delay(1000);
  Serial.println("ESP8266 đã sẵn sàng nhận tín hiệu từ Arduino...");
}


void loop() {
  Blynk.run();


  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      inputData.trim();


      if (inputData.startsWith("ALARM:")) {
        String payload = inputData.substring(6);
        Serial.println("Nhận tín hiệu: " + payload);


        if (payload == "OFF") {
          Blynk.virtualWrite(V0, "Tắt cảnh báo");
        } else {
          String msg = "Phát hiện xâm nhập từ người dùng " + payload;
          Blynk.logEvent("intrusion_detected", msg);  // Gửi cảnh báo
        }
      }


      inputData = "";
    } else {
      inputData += c;
    }
  }
}
