#include "robomodule_due_CAN.h"
//#include <LobotServoController.h>
CRobomodule_due_CAN can;
//LobotServoController myse;
int start = -2;
int left = -1;
int right = -1;
int sum = 0;
int n = 0;
int sum1 = 0;
int sum2 = 0;
int lightswitchleft = 9;
int lightswitchright = 10;
int lightswitchHL = 7;
int lightswitchHR = 8;
int lightswitchHouL = A0;
int lightswitchHouR = A1;
int valueleft = 0;
int valueright = 0;
int headL = 1;
int headR = 1;
int rearL = 0;
int rearR = 0;
//int robotarmoutput = A0;
#include <Servo.h>
Servo myservo;
#define TrigPin1 2
#define EchoPin1 3
#define TrigPin2 11
#define EchoPin2 12
#define TrigPin3 4
#define EchoPin3 5
float cm1, cm2, cm3;
char ss;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(TrigPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);
  pinMode(TrigPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);
  pinMode(TrigPin3, OUTPUT);
  pinMode(EchoPin3, INPUT);
  myservo.attach(30);
  pinMode(lightswitchleft, INPUT);
  pinMode(lightswitchright, INPUT);
  pinMode(lightswitchHL, INPUT);
  pinMode(lightswitchHR, INPUT);
  pinMode(lightswitchHouR,INPUT);
  pinMode(lightswitchHouL,INPUT);
 // digitalWrite(robotarmoutput, LOW);
}
//========================loop====================////========================loop====================////========================loop====================//
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("===================================================================");
  if (start == -2)
  {
    //myse.runActionGroup(0, 0);
    //delay(2000);
    chaosheng();
    shuchu();
    int Cm1,i;
    int Cm2,j;
    i = 0;
    j = 0;
    i = cm1;
    j = cm2;
    sum1 = sum1 + i;
    sum2 = sum2 + j;
    n++;
    if (n == 10)
    {
      Cm1 = sum1 / 10;
      Cm2 = sum2 / 10;
      Serial.print("平均：");
      Serial.print(Cm1);
      Serial.print("               ");
      Serial.print(Cm2);
      Serial.println("               ");
      start++;
      if( Cm1 < Cm2)
      {
        left++;
      }
      if( Cm1 > Cm2)
      {
        right++;
      }
    }
  }
  if (start == -1)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 0)//出家
  {
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    qianjin();
     if (headL == 0 && headR == 1)
    {
      can.speedwheel(2000,  0, 1);
      can.speedwheel(0,  0, 2);
      can.speedwheel(2000,  0, 3);
      can.speedwheel(0,  0, 4);
    }
    if (headL == 1 && headR == 0)
    {
      can.speedwheel(0,  0, 1);
      can.speedwheel(2000,  0, 2);
      can.speedwheel(0,  0, 3);
      can.speedwheel(2000,  0, 4);
    }
    if (headL == 0 && headR == 0)
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
  if (start == 1 || start == 2)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    start++;
  }
  if (start == 3 && left == 0)
  {
    can.positionwheel(3000, -140000, 0, 1);//桥
    can.positionwheel(3000, -140000, 0, 2);
    can.positionwheel(3000, -140000, 0, 3);
    can.positionwheel(3000, -140000, 0, 4);
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    zuo();
    //delay(3000);
    start++;
  }
  if(start == 3 && right == 0)
  {
    can.positionwheel(3000, -150000, 0, 1);//继续后退 到门口
    can.positionwheel(3000, -150000, 0, 2);
    can.positionwheel(3000, -150000, 0, 3);
    can.positionwheel(3000, -150000, 0, 4);
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    you();
    //delay(3000);
    start++;
  }
  if (start == 4)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 5)
  {
    valueleft = digitalRead(lightswitchleft);
    valueright = digitalRead(lightswitchright);
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    if ((valueright == 0 && valueleft == 0) || (valueright == 1 && valueleft == 1))
    {
      qianjin();
    }
    if (valueright == 1 && valueleft == 0)
    {
      can.speedwheel(3500,  0, 1);
      can.speedwheel(3000,  0, 2);
      can.speedwheel(3500,  0, 3);
      can.speedwheel(3000,  0, 4);
    }
    if (valueright == 0 && valueleft == 1)
    {
      can.speedwheel(3000,  0, 1);
      can.speedwheel(3500,  0, 2);
      can.speedwheel(3000,  0, 3);
      can.speedwheel(3500,  0, 4);
    }
    if (start == 5)
    {
      //========================head====================//
      //========================head====================//
      if (headL == 0 && headR == 0)
      {
        can.initdriver(CAN_BPS_1000K, 0, 0, 4);
        start++;
      }
    }
  }
  if (start == 6)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    start++;
  }
  if (start == 7 && left == 0)
  {
    buchang();
    zuo();
    start++;
  }
  if (start == 7 && right == 0)
  {
    buchang();
    you();
    start++;
  }
  if (start == 8)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 9)//走向放置台
  {
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    qianjin();
     if (headL == 0 && headR == 1)
    {
      can.speedwheel(2000,  0, 1);
      can.speedwheel(0,  0, 2);
      can.speedwheel(2000,  0, 3);
      can.speedwheel(0,  0, 4);
    }
    if (headL == 1 && headR == 0)
    {
      can.speedwheel(0,  0, 1);
      can.speedwheel(2000,  0, 2);
      can.speedwheel(0,  0, 3);
      can.speedwheel(2000,  0, 4);
    }
    if (headL == 0 && headR == 0)
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
  if (start == 10)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    Serial1.print('A');
    digitalWrite(13, HIGH);
    delay(300);
    digitalWrite(13, LOW);
    delay(22000);//让13脚的LED闪烁
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);//========================================================================================================拿球
    start++;
  }
  if (start == 11 && left == 0)//-------------------------------------- left == 2
  {
    buchang();
    zuo();
    //delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(4000, 850000, 0, 1);//-200000   走向门
    can.positionwheel(4000, 850000, 0, 2);
    can.positionwheel(4000, 850000, 0, 3);//-200000
    can.positionwheel(4000, 850000, 0, 4);
    delay(7000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);//-200000    转
    you();
    //delay(3000);
    start++;
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
  }
  if (start == 11 && right == 0)//---------------------------------------right == 2
  {
    buchang();
    you();
    //delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(4000, 850000, 0, 1);//-200000   走向门
    can.positionwheel(4000, 850000, 0, 2);
    can.positionwheel(4000, 850000, 0, 3);//-200000
    can.positionwheel(4000, 850000, 0, 4);
    delay(7000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);//-200000    转
    zuo();
    //delay(3000);
    start++;
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
  }
  if (start == 12) //走向墙
  {
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    chaosheng();
    shuchu();
    can.speedwheel(1000,  0, 0);
    if (headL == 0 && headR == 1)
    {
      can.speedwheel(1000,  0, 1);
      can.speedwheel(0,  0, 2);
      can.speedwheel(1000,  0, 3);
      can.speedwheel(0,  0, 4);
    }
    if (headL == 1 && headR == 0)
    {
      can.speedwheel(0,  0, 1);
      can.speedwheel(1000,  0, 2);
      can.speedwheel(0,  0, 3);
      can.speedwheel(1000,  0, 4);
    }
    if ((headL == 0 && headR == 0 )&& (cm3 < 5 && cm3 > 0))
    {
      start++;
    }
  }
  if (start == 13 && left == 0)
  {
    /*chaosheng();
    shuchu();
    can.speedwheel(-800,  0, 0);
    if ( cm1 > 55 && cm1 < 150 ) //找门
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }*/
    can.speedwheel(-800,  0, 0);
    rearR = digitalRead(lightswitchHouR);
    if(rearR == 1)
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
    if (start == 13 && right == 0)
  {
    /*chaosheng();
    shuchu();
    can.speedwheel(-800,  0, 0);
    if ( cm2 > 55 && cm2 < 150) //找门
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }*/
    can.speedwheel(-800,  0, 0);
    rearL = digitalRead(lightswitchHouL);
    if(rearL == 1)
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
  if (start == 14)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    start++;
  }
  if (start == 15 && left == 0)
  {
    can.positionwheel(3000, -200000, 0, 1);//继续后退 到门口
    can.positionwheel(3000, -200000, 0, 2);
    can.positionwheel(3000, -200000, 0, 3);
    can.positionwheel(3000, -200000, 0, 4);
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    zuo();//-200000左  转向门
    //delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, 750000, 0, 1);//+200000  过门
    can.positionwheel(3000, 750000, 0, 2);
    can.positionwheel(3000, 750000, 0, 3);
    can.positionwheel(3000, 750000, 0, 4);
    delay(7000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    you();//-200000 转向桥 换墙
    //delay(3000);
    start++;
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
  }
  if (start == 15 && right == 0)
  {
    can.positionwheel(3000, -200000, 0, 1);//继续后退 到门口
    can.positionwheel(3000, -200000, 0, 2);
    can.positionwheel(3000, -200000, 0, 3);
    can.positionwheel(3000, -200000, 0, 4);
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    you();//-200000左  转向门
    //delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(4000, 750000, 0, 1);//+200000  过门
    can.positionwheel(4000, 750000, 0, 2);
    can.positionwheel(4000, 750000, 0, 3);
    can.positionwheel(4000, 750000, 0, 4);
    delay(7000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    zuo();//-200000左 转向桥 换墙
    //delay(3000);
    start++;
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
  }
  if (start == 16)
  {
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    qianjin();
    //========================head====================//
    if (headL == 0 && headR == 1)
    {
      can.speedwheel(2000,  0, 1);
      can.speedwheel(0,  0, 2);
      can.speedwheel(2000,  0, 3);
      can.speedwheel(0,  0, 4);
    }
    if (headL == 1 && headR == 0)
    {
      can.speedwheel(0,  0, 1);
      can.speedwheel(2000,  0, 2);
      can.speedwheel(0,  0, 3);
      can.speedwheel(2000,  0, 4);
    }
    //========================head====================//
    if ( (headL == 0 && headR == 0 )) //到放置台边
    {
      start++;
    }
  }
  if (start == 17 && left == 0)
  {
    rearR = digitalRead(lightswitchHouR);
    chaosheng();
    shuchu();
    can.speedwheel(-800,  0, 0);
    if (cm1 > 50 && rearR == 1)
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
  if (start == 17 && right == 0)
  {
    rearL = digitalRead(lightswitchHouL);
    chaosheng();
    shuchu();
    can.speedwheel(-800,  0, 0);
    if (cm2 > 50 && rearL == 1 )
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
  if (start == 18 && left == 0)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, -300000, 0, 1);//继续后退 退到台子前  和回家相关联
    can.positionwheel(3000, -300000, 0, 2);
    can.positionwheel(3000, -300000, 0, 3);
    can.positionwheel(3000, -300000, 0, 4);
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    zuo();
    //delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 18 && right == 0)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, -300000, 0, 1);//继续后退 退到台子前  和回家相关联
    can.positionwheel(3000, -300000, 0, 2);
    can.positionwheel(3000, -300000, 0, 3);
    can.positionwheel(3000, -300000, 0, 4);
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    you();
    //delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 19) //找边  在台前停
  {
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    qianjin();
    if (headL == 0 && headR == 1)
    {
      can.speedwheel(2000,  0, 1);
      can.speedwheel(0,  0, 2);
      can.speedwheel(2000,  0, 3);
      can.speedwheel(0,  0, 4);
    }
    if (headL == 1 && headR == 0)
    {
      can.speedwheel(0,  0, 1);
      can.speedwheel(2000,  0, 2);
      can.speedwheel(0,  0, 3);
      can.speedwheel(2000,  0, 4);
    }
    if ( ( headL == 0 && headR == 0 ) )
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
  if (start == 20 && left == 0)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, -350000, 0, 1);//继续后退 退到放球处
    can.positionwheel(3000, -350000, 0, 2);
    can.positionwheel(3000, -350000, 0, 3);
    can.positionwheel(3000, -350000, 0, 4);
    delay(3500);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    you();
    //delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 20 && right == 0)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, -350000, 0, 1);//继续后退 退到放球处
    can.positionwheel(3000, -350000, 0, 2);
    can.positionwheel(3000, -350000, 0, 3);
    can.positionwheel(3000, -350000, 0, 4);
    delay(3500);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    zuo();
    //delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 21)
  {
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    can.speedwheel(1000, 0, 0);
    if (headL == 0 && headR == 1)
    {
      can.speedwheel(1000,  0, 1);
      can.speedwheel(0,  0, 2);
      can.speedwheel(1000,  0, 3);
      can.speedwheel(0,  0, 4);
    }
    if (headL == 1 && headR == 0)
    {
      can.speedwheel(0,  0, 1);
      can.speedwheel(1000,  0, 2);
      can.speedwheel(0,  0, 3);
      can.speedwheel(1000,  0, 4);
    }
    if ( ( headL == 0 && headR == 0 ) )// 到放球台前
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      //buchang();
      start++;
      Serial1.print('B');//先向从机发一个‘a’，
      Serial.print('B');
      digitalWrite(13, HIGH);
      delay(300);
      digitalWrite(13, LOW);
      delay(300);//让13脚的LED闪烁
      delay(19000);
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    }
  }
  if (start == 22 && left == 0)
  {
    
    //delay(6000);//放球
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, -100000, 0, 1);//继续后退 退到台子前   和回家对应
    can.positionwheel(3000, -100000, 0, 2);
    can.positionwheel(3000, -100000, 0, 3);
    can.positionwheel(3000, -100000, 0, 4);
    delay(1500);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    zuo();
    //delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 22 && right == 0)
  {
    //delay(6000);//拿球
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, -100000, 0, 1);//继续后退 退到台子前   和回家对应
    can.positionwheel(3000, -100000, 0, 2);
    can.positionwheel(3000, -100000, 0, 3);
    can.positionwheel(3000, -100000, 0, 4);
    delay(1500);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    you();
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 23)
  {
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    qianjin();
    if (headL == 0 && headR == 1)
    {
      can.speedwheel(3000,  0, 1);
      can.speedwheel(0,  0, 2);
      can.speedwheel(3000,  0, 3);
      can.speedwheel(0,  0, 4);
    }
    if (headL == 1 && headR == 0)
    {
      can.speedwheel(0, 0, 1);
      can.speedwheel(3000,  0, 2);
      can.speedwheel(0, 0, 3);
      can.speedwheel(3000,  0, 4);
    }
    if (headL == 0 && headR == 0)
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
  if (start == 24  && left == 0)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    you();
    //delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, 350000, 0, 1);
    can.positionwheel(3000, 350000, 0, 2);
    can.positionwheel(3000, 350000, 0, 3);
    can.positionwheel(3000, 350000, 0, 4);
    delay(30000);
  }
  if (start == 24 && right == 0)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    zuo();
    //delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, 350000, 0, 1);
    can.positionwheel(3000, 350000, 0, 2);
    can.positionwheel(3000, 350000, 0, 3);
    can.positionwheel(3000, 350000, 0, 4);
    delay(30000);
  }
}
//========================han==shu====================////========================han==shu====================////========================han==shu====================//
void ting()
{
  can.speedwheel(0,  0, 1);
  can.speedwheel(0,  0, 2);
  can.speedwheel(0,  0, 3);
  can.speedwheel(0,  0, 4);
}
void qianjin()
{
  can.speedwheel(3000,  0, 1);
  can.speedwheel(3000,  0, 2);
  can.speedwheel(3000,  0, 3);
  can.speedwheel(3000,  0, 4);
}
void houtui()
{
  can.speedwheel(-3000,  0, 1);
  can.speedwheel(-3000,  0, 2);
  can.speedwheel(-3000,  0, 3);
  can.speedwheel(-3000,  0, 4);
}
void buchang()
{
  can.initdriver(CAN_BPS_1000K, 0, 0, 4);
  can.positionwheel(3000, -40000, 0, 1);
  can.positionwheel(3000, -40000, 0, 2);
  can.positionwheel(3000, -40000, 0, 3);
  can.positionwheel(3000, -40000, 0, 4);
  delay(1000);
  can.initdriver(CAN_BPS_1000K, 0, 0, 4);
}
void zuo()
{
  can.positionwheel(3000, -190000, 0, 1);
  can.positionwheel(3000, 190000, 0, 2);
  can.positionwheel(3000, -190000, 0, 3);
  can.positionwheel(3000, 190000, 0, 4);
  delay(3000);
}
void zuoj()
{
  can.positionwheel(3000, -180000, 0, 1);
  can.positionwheel(3000, 210000, 0, 2);
  can.positionwheel(3000, -210000, 0, 3);
  can.positionwheel(3000, 210000, 0, 4);
  delay(3000);
}
void you()
{
  can.positionwheel(3000, 190000, 0, 1);
  can.positionwheel(3000, -190000, 0, 2);
  can.positionwheel(3000, 190000, 0, 3);
  can.positionwheel(3000, -190000, 0, 4);
  delay(3000);
}
void youj()
{
  can.positionwheel(3000, 210000, 0, 1);
  can.positionwheel(3000, -210000, 0, 2);
  can.positionwheel(3000, 210000, 0, 3);
  can.positionwheel(3000, -210000, 0, 4);
  delay(3000);
}
void yuan()
{
  can.positionwheel(3000, 0, 0, 1);
  can.positionwheel(3000, 0, 0, 2);
  can.positionwheel(3000, 0, 0, 3);
  can.positionwheel(3000, 0, 0, 4);
}
//========================han==shu====================////========================han==shu====================////========================han==shu====================//
void chaosheng()
{
  digitalWrite(TrigPin1, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin1, LOW);
  cm1 = pulseIn(EchoPin1, HIGH) / 58.0; //将回波时间换算成cm
  cm1 = (int(cm1 * 100.0)) / 100.0; //保留两位小数
  digitalWrite(TrigPin2, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin2, LOW);
  cm2 = pulseIn(EchoPin2, HIGH) / 58.0; //将回波时间换算成cm
  cm2 = (int(cm2 * 100.0)) / 100.0; //保留两位小数
  digitalWrite(TrigPin3, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin3, LOW);
  cm3 = pulseIn(EchoPin3, HIGH) / 58.0; //将回波时间换算成cm
  cm3 = (int(cm3 * 100.0)) / 100.0; //保留两位小数
  delay(50);
}
void shuchu()
{
  Serial.print(cm1);
  Serial.print("cm1");
  Serial.print("     ");
  Serial.print(cm2);
  Serial.print("cm2");
  Serial.print("     ");
  Serial.print(cm3);
  Serial.print("cm3");
  Serial.println("     ");
}
//========================han==shu====================////========================han==shu====================////========================han==shu====================//
