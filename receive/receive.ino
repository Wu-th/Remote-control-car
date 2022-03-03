/*
 * arduino蓝牙遥控小车
 * 蓝牙接收摇杆数据控制小车方向
 * 注释日期：2022.03.03
 * by:wu@@@
 */
char buffer [2];        //数据缓冲
int c=0;                //传递
int a[2];               //比例因子
void setup()
{
  Serial.begin(9600);
  pinMode(5,OUTPUT);        //电机输出引脚
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
}
void uart()                 //通信函数
{
  while(Serial.available()>0)
   {
     Serial.readBytes(buffer,2);
     delay(90);
     zoom();
    Serial.print(a[0],DEC);
    Serial.println(a[1],DEC);     
     determ();
   }
}
void turnleft()
{
  c=200-abs(a[1]);
  analogWrite(5,c);
  analogWrite(6,0);
  analogWrite(9,200);
  analogWrite(10,0);
  delay(10);
} 
void turnright()
{
  c=203-a[1];
  analogWrite(5,200);
  analogWrite(6,0);
  analogWrite(9,c);
  analogWrite(10,0);
  delay(10);
} 
void turnleft1()
{
  c=200-abs(a[1]);
  analogWrite(6,c);
  digitalWrite(5,LOW);
  analogWrite(10,200);
  digitalWrite(9,LOW);
  delay(10);
} 
void turnright1()
{
  c=203-a[1];
  analogWrite(6,200);
  digitalWrite(5,LOW);
  analogWrite(10,c);
  digitalWrite(9,LOW);
  delay(10);
}
void forword()
{
  c=abs(a[0]);
  analogWrite(5,c);
  analogWrite(6,0);
  analogWrite(9,c);
  analogWrite(10,0);
  delay(10);
}
void backword()
{
  c=abs(a[0]);
  analogWrite(6,c);
  analogWrite(5,0);
  analogWrite(10,c);
  analogWrite(9,0);
  delay(10);
}
void stopp()
{
  analogWrite(5,0);
  analogWrite(6,0);
  analogWrite(9,0);
  analogWrite(10,0);
  delay(10);
}
void determ()                  //判断摇杆位置函数
{
  if(abs(buffer[0])<10)
    stopp();
  if(abs(buffer[1])<10)
  {
    if(buffer[0]>10)
      forword();
    if(buffer[0]<-10)
      backword();
  }
  if(buffer[0]>10 && buffer[1]>10)
    turnright();
  if(buffer[0]>10 && buffer[1]<-10)
    turnleft();
  if(buffer[0]<-10 && buffer[1]>10)
    turnright1();  
  if(buffer[0]<-10 && buffer[1]<-10)
    turnleft1();           
}
void zoom()
{
 a[0]=map(buffer[0],-100,100,-240,240);
 a[1]=map(buffer[1],-100,100,-200,200);
} 
void loop()
{
  uart();
  //Serial.print(buffer[0],DEC);
  //Serial.println(buffer[1],DEC);
}
