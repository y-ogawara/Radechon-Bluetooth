#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11);

void setup(){
    BT.begin(9600);
    Serial.begin(38400);
  //右タイヤ
  pinMode(6,OUTPUT); //信号用ピン 5番ピン
  pinMode(7,OUTPUT); //信号用ピン 6番ピン
  //左タイヤ
  pinMode(8,OUTPUT); //信号用ピン 7番ピン
  pinMode(9,OUTPUT); //信号用ピン 8番ピン

}

String btString;
int MAX_BLUETOOTH_SIZE = 7;


void loop(){
  int n = BT.available();
  if ( n == MAX_BLUETOOTH_SIZE ) {
    char ch[MAX_BLUETOOTH_SIZE];
    int i;
    // MAX_BLUETOOTH_SIZEバイトずつ読み込む
    for ( i=0; i<MAX_BLUETOOTH_SIZE; i++) {
      ch[i] = BT.read();
      Serial.print(ch[i]);
    }

  moterControl(ch);
  }
}


void moterControl(String select){
  //Serial.print(select);
    /* 7桁の配列から　
     * なにをさせたいかが先頭4つ 次の3つが左側の速度 最後の3つが右側の速度
   * 例: 1100100
     * 前進 モーターパワー 左100 右100
     */
    String action = select.substring(0,1);
    String leftPowerChar = select.substring(1,4);
    String rightPowerChar = select.substring(4,7);
    // String配列をint型に変換
    int leftPower = leftPowerChar.toInt();
    int rightPower = rightPowerChar.toInt();

Serial.print(action);
  // 左タイヤ: ピン6,7
  // 右タイヤ: ピン8,9
  
  // 前進
  if (action.equals("1")){
    
    //左タイヤ
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    //右タイヤ
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    analogWrite(3,leftPower);
    analogWrite(5,rightPower);
  }
  
  else if (action.equals("2")){
    //後退
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);  
    analogWrite(3,leftPower);
    analogWrite(5,rightPower);

  }

  else if (action.equals("3")){

    //その場で左回転
    //左タイヤ
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
    //右タイヤ
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);

    analogWrite(3,leftPower);
    analogWrite(5,rightPower);
  }

  else if(action.equals("4")){

    //その場で右回転
    //左回転
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    //右回転
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);

    analogWrite(3,leftPower);
    analogWrite(5,rightPower);
  }

  else if (action.equals("5")){

    //後退
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);  
    analogWrite(3,100);
    analogWrite(5,100);
    delay(100);
      //ストップ
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    analogWrite(3,leftPower);
    analogWrite(5,rightPower);
  }
}
