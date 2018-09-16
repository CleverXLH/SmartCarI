#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif
#include "DFMobile.h"
#include <ros.h>
#include <geometry_msgs/Twist.h>
//x轴方向的速度
DFMobile Robot (4,5,7,6);
double lin_vel = 0.0;
//y轴方向的速度
double ang_vel = 0.0;
int cmd_ctrl = 0;

ros::NodeHandle nh;

void motor_cb(const geometry_msgs::Twist& vel)
{
  lin_vel = vel.linear.x;
  ang_vel = vel.angular.z;
  cmd_ctrl = 1 * lin_vel + 3 * ang_vel;
}

void car_run(){
  Robot.Speed (255,255);  //forward
  digitalWrite (13, HIGH);
}

void car_brake(){
  Robot.Speed (0, 0);
}

void car_left(){
  Robot.Speed (0,255);  //left wheel forward
  digitalWrite (13, HIGH);
}



void car_right(){
  Robot.Speed (255,0);  //left wheel forward
  digitalWrite (13, HIGH);
}

void car_back(){
  Robot.Speed (-255,-255);  //forward
  digitalWrite (13, HIGH);
}

ros::Subscriber<geometry_msgs::Twist> sub("/turtle1/cmd_vel", motor_cb);
void setup()
{
  //初始化电机驱动IO为输出方式
  Robot.Direction (LOW,HIGH); // (left direction,right direction); 
  pinMode (13, OUTPUT);
  //初始化ROS
  nh.initNode();
  //订阅消息
  nh.subscribe(sub);
  
}

void loop()
{
  nh.spinOnce();
  switch (cmd_ctrl)
  {
   case 2: 
  {
    Serial.print("Go Forward!\n");
    //delay(1000);
    car_run();    
    delay(10);
    car_brake();
    break;
  }
  case -2:
  {
    Serial.print("Go Backward!\n");
    //delay(1000);       
    Robot.Speed (-255,-255);  //forward
    digitalWrite (13, HIGH);
    delay(10);
    car_brake();
    break;
  }
  case 6:
  {
    Serial.print("Turn Left!\n");
    //delay(1000);
    Robot.Speed (0,255);  //left wheel forward
    digitalWrite (13, HIGH);  
    delay(10);
    car_brake();   
    break;
  }
  case -6:
  {
    Serial.print("Turn Right!");
    //delay(1000);
    Robot.Speed (255,0);  //left wheel forward
    digitalWrite (13, HIGH);  
    delay(10);
    car_brake();
    break;
  }
  default:
  {
    //delay(1000);
    car_brake();   
    delay(10);    
    break;
  }
}
    car_brake();    
    cmd_ctrl = 0;
}

