
#include <Keyboard.h>
#include <Bounce2.h>
#include <EEPROM.h>

#define LED_PIN LED_BUILTIN
#define KEY_PIN 28

int ledState = HIGH;
int pressed_key = 0;
//char incomingByte;    // for incoming serial data

#define PARSE_AMOUNT 7         // число значений в массиве, который хотим получить
String strData[PARSE_AMOUNT];     // массив численных значений после парсинга
int intData = 0;;
boolean recievedFlag;
boolean getStarted;
int aindex = 0;
String string_convert = "";

int address = 100;

String dataArray[] = {"10", "20", "30", "40"};
String read_data[PARSE_AMOUNT];
int keys_arr[] = {92, 49, 50, 51, 52, 53, 54, 55, 56, 57, 113, 119, 101, 114, 116, 121, 117, 105, 111, 112};
//                 \   1   2   3   4   5   6   7   8   9   q    w    e    r    t    y    u    i    o    p  20pcs
int active_layer = 1;



// Instantiate a Bounce object with a 5 millisecond debounce time
Bounce bouncer0 = Bounce(0, 5);   // 1
Bounce bouncer1 = Bounce(1, 5);   // 2
Bounce bouncer2 = Bounce(2, 5);   // 3
Bounce bouncer3 = Bounce(3, 5);   // 4
Bounce bouncer4 = Bounce(4, 5);   // 5
Bounce bouncer5 = Bounce(5, 5);   // 6
Bounce bouncer6 = Bounce(6, 5);   // 7
Bounce bouncer7 = Bounce(7, 5);   // 8
Bounce bouncer8 = Bounce(8, 5);   // 9
Bounce bouncer9 = Bounce(9, 5);   // 0
Bounce bouncer10 = Bounce(10, 5);   // CTRL
Bounce bouncer11 = Bounce(11, 5);   // ALT
Bounce bouncer12 = Bounce(12, 5);   // SHIFT
Bounce bouncer13 = Bounce(13, 5);   // Q
Bounce bouncer14 = Bounce(14, 5);   // W
Bounce bouncer15 = Bounce(15, 5);   // E
Bounce bouncer16 = Bounce(16, 5);   // R
Bounce bouncer17 = Bounce(17, 5);   // T
Bounce bouncer18 = Bounce(18, 5);   // Y
Bounce bouncer19 = Bounce(19, 5);   // U
Bounce bouncer20 = Bounce(20, 5);   // I
Bounce bouncer21 = Bounce(21, 5);   // O
Bounce bouncer22 = Bounce(22, 5);   // P
Bounce bouncer26 = Bounce(26, 5);   // DEL
Bounce bouncer27 = Bounce(27, 5);   // ESC


void setup() {
  EEPROM.begin(2048);
  //Initialize serial and wait for port to open:
  Serial.begin (9600);
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for native USB port only
  //  }
  delay(3000);

  Serial.println("<Ready>");

  Keyboard.begin();

  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);

  // LED SETUP
  pinMode(LED_PIN, OUTPUT);
  pinMode(KEY_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  digitalWrite(LED_PIN, LOW);
}

void default_settings() {
  // $DEFAULT;
  //  keys_arr[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 113, 119, 101, 114, 116, 121, 117, 105, 111, 112};
  //                 0   1   2   3   4   5   6   7   8   9   q    w    e    r    t    y    u    i    o    p  20pcs
  //  0123456789  q  w  e  r  t  y  u  i  o  p   20
  //  0123456789  10 11 12 13 14 15 16 17 18 19  20
  //  1-100:190 2-200:290 3-300:390 4-400:490 5-500:590 6-600:690 7-700:790 8-800:890 9-900:990 0-0:90
  //  q = KeyLay Ctr Alt Shf Old New
  //  1 =   100   1   2   3   4   5
  //  1 =   190   91  92  93  94  95
  //  q = 1000  1001  1002  1003  1004  1005
  //  q = 1090  1091  1092  1093  1094  1095
  //  w-1100:1190 e-1200:1290 r-1300:1390 t-1400:1490 y-1500:1590 u-1600:1690 i-1700:1790 o-1800:1890
  //  p = 1900  19901  1902  1903  1904  1905
  //  p = 1990  19991  1992  1993  1994  1995
  Serial.println("RESET SETTINGS TO DEFAUL");
  int original_key = -1;
  int ascii_key = 0;
  for (int layer = 0; layer < 1996; layer = layer + 10) {
    if ( ! ( layer % 100 ) ) { // Change key every 10 times
      original_key++;
      ascii_key = keys_arr[original_key];
    }
    EEPROM.put(layer + 1, 0);
    EEPROM.put(layer + 2, 0);
    EEPROM.put(layer + 3, 0);
    EEPROM.put(layer + 4, original_key);
    EEPROM.put(layer + 5, ascii_key);
  }
  EEPROM.commit();
}

void switch_layer(int x) {
  Serial.print("ACTIVATED LAYER: "); Serial.println(x);
  active_layer = x;
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(KEY_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(KEY_PIN, LOW);
}

void loop() {

  if (bouncer0.update()) {
    if (bouncer0.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(1);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer1.update()) {
    if (bouncer1.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(2);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer2.update()) {
    if (bouncer2.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(3);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer3.update()) {
    if (bouncer3.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(4);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer4.update()) {
    if (bouncer4.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(5);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer5.update()) {
    if (bouncer5.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(6);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer6.update()) {
    if (bouncer6.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(7);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer7.update()) {
    if (bouncer7.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(8);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer8.update()) {
    if (bouncer8.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(9);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer9.update()) {
    if (bouncer9.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(0);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer10.update()) {
    if (bouncer10.read() == LOW) {
      Serial.println("CTRL");
      Keyboard.press(KEY_LEFT_CTRL);
      delay(5);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer11.update()) {
    if (bouncer11.read() == LOW) {
      Serial.println("ALT");
      Keyboard.press(KEY_LEFT_ALT);
      delay(5);
      pressed_key = 1;
    }
    else {
      Keyboard.releaseAll();
      pressed_key = 0;
    }
  }

  if (bouncer12.update()) {
    if (bouncer12.read() == LOW) {
      Serial.println("SHIFT");
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(5);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer13.update()) {
    if (bouncer13.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(10);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer14.update()) {
    if (bouncer14.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(11);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer15.update()) {
    if (bouncer15.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(12);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer16.update()) {
    if (bouncer16.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(13);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer17.update()) {
    if (bouncer17.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(14);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer18.update()) {
    if (bouncer18.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(15);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer19.update()) {
    if (bouncer19.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(16);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer20.update()) {
    if (bouncer20.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(17);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer21.update()) {
    if (bouncer21.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(18);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer22.update()) {
    if (bouncer22.read() == LOW) {
      Serial.print("L"); Serial.println(active_layer);
      pressing_key(19);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer26.update()) {
    if (bouncer26.read() == LOW) {
      Serial.println("DELETE");
      Keyboard.press(KEY_DELETE);
    }
    else {
      Keyboard.releaseAll();
    }
  }

  if (bouncer27.update()) {
    if (bouncer27.read() == LOW) {
      Serial.println("ESC");
      Keyboard.press(KEY_ESC);
    }
    else {
      Keyboard.releaseAll();
    }
  }


  // CHANGE PRESETS IF ALT KEY PRESSED
  if (pressed_key != 0) {
    delay(5);
    if (bouncer0.update()) {
      if (bouncer0.read() == LOW) {
        pressed_key = 0;
        switch_layer(1);
      }
    }
    if (bouncer1.update()) {
      if (bouncer1.read() == LOW) {
        pressed_key = 0;
        switch_layer(2);
      }
    }
    if (bouncer2.update()) {
      if (bouncer2.read() == LOW) {
        pressed_key = 0;
        switch_layer(3);
      }
    }
    if (bouncer3.update()) {
      if (bouncer3.read() == LOW) {
        pressed_key = 0;
        switch_layer(4);
      }
    }
    if (bouncer4.update()) {
      if (bouncer4.read() == LOW) {
        pressed_key = 0;
        switch_layer(5);
      }
    }
    if (bouncer5.update()) {
      if (bouncer5.read() == LOW) {
        pressed_key = 0;
        switch_layer(6);
      }
    }
    if (bouncer6.update()) {
      if (bouncer6.read() == LOW) {
        pressed_key = 0;
        switch_layer(7);
      }
    }
    if (bouncer7.update()) {
      if (bouncer7.read() == LOW) {
        pressed_key = 0;
        switch_layer(8);
      }
    }
    if (bouncer8.update()) {
      if (bouncer8.read() == LOW) {
        pressed_key = 0;
        switch_layer(9);
      }
    }
  }


  // send data only when you receive data:
  parsing();       // функция парсинга
  if (recievedFlag) {                           // если получены данные
    recievedFlag = false;
    if (strData[0] == "WRITE") {
      write_proc();
    } else if (strData[0] == "READ") {
      read_proc(strData[1]);
    } else if (strData[0] == "DEFAULT") {
      default_settings();
    }
  }
}

void pressing_key(int x) {
  int func_key = 0;
  int adr_key = 100 * x + active_layer * 10;
  int ctrl_key = EEPROM.read((adr_key + 1));
  int alt_key = EEPROM.read((adr_key + 2));
  int shift_key = EEPROM.read((adr_key + 3));
  func_key = EEPROM.read((adr_key + 5));
  Serial.print(adr_key + 5); Serial.print(":"); Serial.println(func_key);
  Keyboard.press(ctrl_key);
  delay(10);
  Keyboard.press(alt_key);
  delay(10);
  Keyboard.press(shift_key);
  delay(10);
  Keyboard.press(func_key);
  delay(10);
}

void parsing() {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();        // обязательно ЧИТАЕМ входящий символ
    if (getStarted) {                         // если приняли начальный символ (парсинг разрешён)
      if (incomingByte != ' ' && incomingByte != ';') {   // если это не пробел И не конец
        string_convert += incomingByte;       // складываем в строку
      } else {
        //        Serial.print("string_convert: "); Serial.println(string_convert);// если это пробел или ; конец пакета
        strData[aindex] = string_convert;
        string_convert = "";                  // очищаем строку
        aindex++;                              // переходим к парсингу следующего элемента массива
      }
    }
    if (incomingByte == '$') {                // если это $
      getStarted = true;                      // поднимаем флаг, что можно парсить
      aindex = 0;                              // сбрасываем индекс
      string_convert = "";                    // очищаем строку
    }
    if (incomingByte == ';') {                // если таки приняли ; - конец парсинга
      getStarted = false;                     // сброс
      recievedFlag = true;                    // флаг на принятие
    }
  }
}

void write_proc() {
  // $DEFAULT;
  // $WRITE 1 128 130 129 1 49;
  // $WRITE 2 0 0 0 1 49;
  // $WRITE 1   2   3   4   5   6;
  //       Lay Ctr Alt Shf Ori New
  //           128 130 129
  // 0-0:99 1-100:190 2-200:290 3-300:390
  // Layers: 0-0:100 1-1:101 2-2:102 ...
  int key_name = 100 * 1 * strData[5].toInt();
  int int_layer = 10 * strData[1].toInt() + key_name;

  Serial.println("RUN WRITE PROCCES START");
  Serial.print("WRITE: "); Serial.print(int_layer); Serial.print(" L"); Serial.print(strData[1].toInt());
  for (int i = 2; i < 7; i++) {
    intData = strData[i].toInt();
    EEPROM.put((int_layer + i - 1), intData);
    Serial.print(" "); Serial.print(intData);
    intData = 0;
  }
  EEPROM.commit();
  Serial.println("");
  Serial.print("CHECK: "); Serial.print(int_layer); Serial.print("   ");
  for (int d = (int_layer + 1); d < (int_layer + 6); d++) {
    int asd = EEPROM.read(d);
    Serial.print(" "); Serial.print(asd);
    if ((strData[(d - int_layer + 1)].toInt()) != asd) { // Compare array and EEPROM
      Serial.print("WRITING ERROR!!!");
    }
    asd = 0;
  }
  Serial.println(" DONE");
}

void read_proc(String laeyr_x) {
  //  Data from0 to 1995
  int intit_laeyr = 0;
  int increment = 10;
  if (laeyr_x.toInt() < 11) {
    intit_laeyr = laeyr_x.toInt() * 10;
    increment = 100;
  }
  //  Serial.print("RUN READ LAYER: "); Serial.println(laeyr_x);
  for (int a = intit_laeyr; a < 1996; a = a + increment) {
    //  1234567890 123456789 10 10
    //  qwertyuiop 11 12 13 14 15 16 17 18 19 20 10
    Serial.print("LAYER "); Serial.print(a);
    for (int i = 1; i < 6; i++) {
      int get_ad = a + i;
      int asd = EEPROM.read(get_ad);
      Serial.print(" "); Serial.print(asd);
      asd = 0;
    }
    Serial.println("");
  }
}
