#include <Servo.h>
#include <PS2X_lib.h>  
#define PS2_DAT        12  //khai báo biến chan cho ps2
#define PS2_CMD        19  //khai báo biến chan cho ps2
#define PS2_SEL        18  //khai báo biến chan cho ps2
#define PS2_CLK        13  //khai báo biến chan cho ps2
PS2X ps2x; 
Servo servo1,servo2,servo3,servo4; // tên servo
int posa = 90;
int posb = 90; // dặt biến 
int posc = 90;
int posd = 0;
void setup(){
 pinMode(11,OUTPUT); // IN 1 
 pinMode(10,OUTPUT); // IN 3 
 pinMode(8,OUTPUT); // IN 2
 pinMode(7,OUTPUT); // IN 4
 servo1.attach(3);// xoay trái và phải 
 servo2.attach(5);// nâng lên hạ xuống
 servo3.attach(6); // nâng cao hạ thấp khai báo servo
 servo4.attach(9); // tay gắp
 ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);
 Serial.begin(57600);
}

void loop() {
/********************************************************* 
 * phiên bản điều khiển robot tích hợp cánh tay cho robot 
 * phiên bản nâng cấp cho ROBOT ARM + TANK V 20T1
 * thiết kế Nguyễn Thanh Tuấn 
 *********************************************************/
    ps2x.read_gamepad();
     
    int valuea = ps2x.Analog(PSS_LX); // trục ngang 1
    int valueb = ps2x.Analog(PSS_RY); // 3
    int valuec = ps2x.Analog(PSS_LY); // 2
    int valued = ps2x.Analog(PSS_RX); // trục dọc 4
    
    if(ps2x.Button(PSB_PAD_UP)) {     // robot chạy tới 
      tien(); 
    } else if(ps2x.ButtonReleased(PSB_PAD_UP)){ dunglai(); }
    if(ps2x.Button(PSB_PAD_RIGHT)){ // robot sang trái
      trai();
    }else if(ps2x.ButtonReleased(PSB_PAD_RIGHT)){ dunglai(); }
    if(ps2x.Button(PSB_PAD_LEFT)){ // robot sang phải 
      phai();
    }else if(ps2x.ButtonReleased(PSB_PAD_LEFT)){ dunglai(); }
    if(ps2x.Button(PSB_PAD_DOWN)){ // robot lùi về 
     lui();
    }else if(ps2x.ButtonReleased(PSB_PAD_DOWN)){ dunglai(); }
 
    if(ps2x.ButtonReleased(PSB_CIRCLE)){
      servo4.write(90);                  // tay ghắp cho SERVO (khoảng cách == 90)
      Serial.println("Circle just pressed");     
    }
    if(ps2x.ButtonReleased(PSB_SQUARE)) {      
      servo4.write(0);                  // tay ghắp cho SERVO (khỏang cách == 0)           
      Serial.println("Square just released");    
    } 
    
    if(ps2x.Button(PSB_R1)){
    if (valuec == 0 && posc <= 180){
      posc = posc +2;
      servo2.write(posc); // servo nâng lên hạ xuống 
    }
    else if (valuec == 255 && posc >= 40){
      posc = posc -2;
      servo2.write(posc);
    }
    if (valueb == 0 && posb <= 180){
      posb = posb +2;
      servo3.write(posb); // servo nâng cao và hạ thấp xuống 
    }
    else if (valueb == 255 && posb >= 90){
      posb = posb -2;
      servo3.write(posb);
    }
  }
  
  if(ps2x.Button(PSB_L1)){
  if(valuec > 200){
    luiR();
  }
  if(valuec < 100){
    tienR();
  }
  if(valueb > 200){
    luiL();
  }
  if(valueb < 100){
    tienL();
  }
  if(valuec == 127){
    stopR();
  }
  if(valueb == 127){
    stopL();
  }
} else if(ps2x.ButtonReleased(PSB_L1)){ dunglai();}  

  if(ps2x.Button(PSB_L2)){ // chuyển hướng robot 1 động cơ sang phải 
    digitalWrite(11,HIGH);
    digitalWrite(8,LOW);
  } else if(ps2x.ButtonReleased(PSB_L2)){
    digitalWrite(11,LOW);
    digitalWrite(8,LOW);
  }
  if(ps2x.Button(PSB_R2)){ // chuyển hướng robot 1 động cơ sang trái 
    digitalWrite(10,HIGH);
    digitalWrite(7,LOW);
  } else if(ps2x.ButtonReleased(PSB_R2)){
    digitalWrite(10,LOW);
    digitalWrite(8,LOW);
  }
  delay(20);  
}
  void stopL(){
    digitalWrite(11,LOW);
    digitalWrite(8,LOW);
  }
  void stopR(){
    digitalWrite(10,LOW);
    digitalWrite(7,LOW);
  }
  void tienR(){
    digitalWrite(10,HIGH);
    digitalWrite(7,LOW);
  }
  void luiR(){
    digitalWrite(10,LOW);
    digitalWrite(7,HIGH);
  }
  void tienL(){
    digitalWrite(11,HIGH);
    digitalWrite(8,LOW);
  }
  void luiL(){
    digitalWrite(11,LOW);
    digitalWrite(8,HIGH);
  }
  void tien(){
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(8,LOW);
    digitalWrite(7,LOW);
  }
  void lui(){
    digitalWrite(11,LOW);
    digitalWrite(8,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(7,HIGH);
  }
  void phai(){
    digitalWrite(11,HIGH);
    digitalWrite(8,LOW);
    digitalWrite(10,LOW);
    digitalWrite(7,HIGH);
  }
  void trai(){
    digitalWrite(10,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(11,LOW);
    digitalWrite(8,HIGH);
  }
  void dunglai(){
    digitalWrite(11,LOW);
    digitalWrite(8,LOW);
    digitalWrite(10,LOW);
    digitalWrite(7,LOW);
  }
 
