#include <AdafruitIO_WiFi.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PAS "your_wifi_password"
#define IO_USERNAME "your_adafruitio_username"
#define IO_KEY "your_adafruitio_key"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PAS);
AdafruitIO_Feed *gas = io.feed("gas sensor");

void setup() {
  Serial.begin(115200);
  io.connect();
  pinMode(A0, INPUT);
  while(io.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
}

void loop() {
  Serial.println(WiFi.localIP());
  io.run();
  float g = analogRead(A0) * (10000.0/1024.0);
  gas->save(g);
  delay(10000);

}
