#include <Servo.h>

#include <PS2X_lib.h>
// chân kết nối 
#define PS2_DAT        13  //14    
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        12  //17

#define pressures   false
#define rumble      false
// khởi động ps2
PS2X ps2x;
// tên servo
Servo servo0,servo1,servo2,servo3;
// khởi tạo biến 
const int SL = 4;

int value[SL],MIN[SL],MAX[SL],posBD[SL],poswrite[SL];

void setup() {
// setup tính hiệu cho ps2
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  Serial.begin(9600);
// servo0
  MIN[0]= 0;
  MAX[0]=180;
  posBD[0]=60;
// servo1
  MIN[1]= 0;
  MAX[1]= 130;
  posBD[1]=90;
// servo2
  MIN[2]= 0;
  MAX[2]= 155;
  posBD[2]=90;
// servo3
  MIN[3]= 110;
  MAX[3]= 160;
  posBD[3]=110;
// khởi động servo
  servo0.attach(3);
  servo1.attach(5);
  servo2.attach(6);
  servo3.attach(9);

  pinMode(2,OUTPUT); // IN 1
  pinMode(4,OUTPUT); // IN 2
  pinMode(7,OUTPUT); // IN 3
  pinMode(8,OUTPUT); // IN 4
  
  servo0.write(posBD[0]);
  servo1.write(posBD[1]);
  servo2.write(posBD[2]);
  servo3.write(posBD[3]);

  poswrite[0]=posBD[0];
  poswrite[1]=posBD[1];
  poswrite[2]=posBD[2];
  poswrite[3]=posBD[3];
}

void loop() {
  
  ps2x.read_gamepad();
  
  value[0] = ps2x.Analog(PSS_LX);
  value[1] = ps2x.Analog(PSS_LY);
  value[2] = ps2x.Analog(PSS_RY);
  value[3] = ps2x.Analog(PSS_RX);

  // điều khien servo 0
  if (value[0] == 0 && poswrite[0] <= MAX[0]){
      poswrite[0] = poswrite[0] +1;
      servo0.write(poswrite[0]); 
    }
  else if (value[0] == 255 && poswrite[0] >= MIN[0]){
      poswrite[0] = poswrite[0] -1;
      servo0.write(poswrite[0]);
    }
  // điều khiển servo 1 
  else if (value[1] == 255 && poswrite[1] <= MAX[1]){
      poswrite[1] = poswrite[1] +1;
      servo1.write(poswrite[1]);
    }
  else if (value[1] == 0 && poswrite[1] >= MIN[1]){
      poswrite[1] = poswrite[1] -1;
      servo1.write(poswrite[1]);
    }
  // điều khiển servo 2
  else if (value[2] == 0 && poswrite[2] <= MAX[2]){
      poswrite[2] = poswrite[2] +1;
      servo2.write(poswrite[2]);
    }
  else if (value[2] == 255 && poswrite[2] >= MIN[2]){
      poswrite[2] = poswrite[2] -1;
      servo2.write(poswrite[2]); 
    }
    // dieu khien servo gap vat (waring)
  else if (value[3] == 0 && poswrite[3] <= MAX[3]){
      poswrite[3] = poswrite[3] +1;
      servo3.write(poswrite[3]);
    }
  else if (value[3] == 255 && poswrite[3] >= MIN[3]){
      poswrite[3] = poswrite[3] -1;
      servo3.write(poswrite[3]); 
  } 

  // nut nhan dong co gap
   if(ps2x.ButtonPressed(PSB_CIRCLE)){
      servo3.write(110);
   }
   
   if(ps2x.ButtonPressed(PSB_SQUARE)){
       servo3.write(160);
  }  
 
  // điều khiển động cơ 
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
    }else if(ps2x.ButtonReleased(PSB_PAD_DOWN)){ dunglai(); 
  }

  delay(10);
}

void tien(){
    digitalWrite(2,LOW);
    digitalWrite(7,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(8,LOW);
  }
  void lui(){
    digitalWrite(2,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(4,LOW);
    digitalWrite(8,HIGH);
  }
  void phai(){
    digitalWrite(2,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(8,LOW);
  }
  void trai(){
    digitalWrite(2,LOW);
    digitalWrite(7,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(8,HIGH);
  }
  void dunglai(){
    digitalWrite(2,LOW);
    digitalWrite(7,LOW);
    digitalWrite(4,LOW);
    digitalWrite(8,LOW);
  }
