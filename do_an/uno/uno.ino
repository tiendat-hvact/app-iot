int CBAS = 9;
int DEVICE_STATE = -1; // trang thai truoc cua cam bien
void setup() {
  Serial.begin(9600);
  pinMode(CBAS, INPUT);
}

void loop() {
  if (digitalRead(CBAS) != DEVICE_STATE) {
    
    if (digitalRead(CBAS) == 1) {
          DEVICE_STATE = 1;
      Serial.println("DEVICE 1"); // Đèn đỏ sáng. 1 == HIGH
    } else {
          DEVICE_STATE = 0;
      Serial.println("DEVICE 0"); // Đèn đỏ tắt . 0 == LOW
    }
    
    delay(1000);// Dừng một giây giữa các lần gửi
  }

}
