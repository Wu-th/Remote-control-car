/*
 * arduino蓝牙遥控部分程序
 * arduino+单摇杆通过蓝牙实现对蓝牙小车的控制
 * 摇杆控制原理：两个电位器+一个开关
 * 注释日期：2022.03.03
 * by:wu@@@
 */
int a = 0;              //用来接收摇杆电位器的值
int b = 0;
int c = 0;

int d = 0;
int e = 0;
int f = 0;

char buffer [2]; //Feld zum Speichern der Eingabe

#define VRX A0    //x轴
#define VRY A1    //y轴
#define SW 7      //开关
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SW,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 
  a=analogRead(VRX);
  b=analogRead(VRY);
  c=digitalRead(SW);
  d = map(a, 0,1023, -100,101);         //将电位器的值映射到（-100~100）范围内
  e = map(b, 0,1023, -100,101);
  //Serial.println(d);
  buffer[0]=d;
  buffer[1]=e;
  Serial.write(buffer,2);
  delay(100);  
}
