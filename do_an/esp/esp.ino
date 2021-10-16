#include <WebSocketsClient.h>
#include <SerialCommand.h> // Thêm vào sketch thư viện Serial Command
#include <ESP8266WiFi.h>

SerialCommand sCmd; // Khai báo biến sử dụng thư viện Serial Command
WebSocketsClient webSocket;
//WiFiClient client;

const char* ssid = "OPPO A37f"; //Đổi thành wifi của bạn
const char* password = "Dat1392@"; //Đổi pass luôn
const char ip_host[] = "iot-app-nhom11.herokuapp.com"; //Đổi luôn IP host của PC nha
const int port = 80; //Port thích đổi thì phải đổi ở server nữa
char path[] = "/";

int DEVICE1 = D1;
int DEVICE2 = D2;
int DEVICE3 = D3;
int DEVICE4 = D4;
int activeSenser = -1;

//xu li su kien socket
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("Disconnected!");
      break;
    case WStype_CONNECTED:
      {
        Serial.println(" Da ket noi toi server");
      }
      break;
    case WStype_TEXT:
      Serial.printf("Get text: %s :\n", payload);
      strcmp((char*)payload, "LED_ON");
      if (strcmp((char*)payload, "LED_ON") == 0) {
        digitalWrite(DEVICE1, 1); 
        // Khi client phát sự kiện "LED_ON" ==> DEVICE1 MO
        webSocket.sendTXT("DEVICE1_ON");
      } else if (strcmp((char*)payload, "LED_OFF") == 0) {
        digitalWrite(DEVICE1, 0); 
        // Khi client phát sự kiện "LED_OFF" ==> DEVICE1 TAT
        webSocket.sendTXT("DEVICE1_OFF");
      } else if (strcmp((char*)payload, "SENSER_DEVICE1_DISABLE") == 0) {
        activeSenser = 0;
        webSocket.sendTXT("SENSER_DEVICE1_DISABLE");
      } else if (strcmp((char*)payload, "SENSER_DEVICE1_ACTIVE") == 0) {
        activeSenser = 1;
        webSocket.sendTXT("SENSER_DEVICE1_ACTIVE");
      }

      if (strcmp((char*)payload, "LED_ON2") == 0) {
        digitalWrite(DEVICE2, 1); // Khi client phát sự kiện "LED_ON2" ==> DEVICE2 MO
        webSocket.sendTXT("DEVICE2_ON");
      } else if (strcmp((char*)payload, "LED_OFF2") == 0) {
        digitalWrite(DEVICE2, 0); // Khi client phát sự kiện "LED_OFF2" ==> DEVICE2 TAT
        webSocket.sendTXT("DEVICE2_OFF");
      }
      if (strcmp((char*)payload, "LED_ON3") == 0) {
        digitalWrite(DEVICE3, 1); // Khi client phát sự kiện "LED_ON3" ==> DEVICE3 MO
        webSocket.sendTXT("DEVICE3_ON");
      } else if (strcmp((char*)payload, "LED_OFF3") == 0) {
        digitalWrite(DEVICE3, 0); // Khi client phát sự kiện "LED_OFF3" ==> DEVICE3 TAT
        webSocket.sendTXT("DEVICE3_OFF");
      }
      if (strcmp((char*)payload, "LED_ON4") == 0) {
        digitalWrite(DEVICE4, 1); // Khi client phát sự kiện "LED_ON4" ==> DEVICE4 MO
        webSocket.sendTXT("DEVICE4_ON");
      } else if (strcmp((char*)payload, "LED_OFF4") == 0) {
        digitalWrite(DEVICE4, 0); // Khi client phát sự kiện "LED_OFF4" ==> DEVICE4 TAT
        webSocket.sendTXT("DEVICE4_OFF");
      }


      break;

  }
}

void setup() {
  //Khởi tạo Serial ở baudrate 9600 (trùng với HOST)
  Serial.begin(9600);

  //  ket noi wifi
  Serial.println("ESP8266 Websocket Client");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //  khoi tao socket
  webSocket.begin(ip_host, port, path);
  webSocket.onEvent(webSocketEvent);

  pinMode(DEVICE1, OUTPUT);
  pinMode(DEVICE2, OUTPUT);
  pinMode(DEVICE3, OUTPUT);
  pinMode(DEVICE4, OUTPUT);

  sCmd.addCommand("DEVICE", DEVICE_CONTROL);

}


void loop() {
  sCmd.readSerial();
  webSocket.loop();
}

void DEVICE_CONTROL() {
  char *arg;
  arg = sCmd.next();
  int value = atoi(arg);
  if (activeSenser != 0) {
    digitalWrite(DEVICE1, value);
    if (value == 0) {
      webSocket.sendTXT("DEVICE1_OFF");
    }
    else {
      webSocket.sendTXT("DEVICE1_ON");
    }
  }


  Serial.println("da nhan lenh!");
}
