#define MOTOR_A_a 3 //모터A의 +출력핀은 3번핀입니다
#define MOTOR_A_b 11 //모터A의 -출력핀은 11번핀입니다
#define MOTOR_B_a 9 //모터B의 +출력핀은 5번핀입니다
#define MOTOR_B_b 10 //모터B의 -출력핀은 6번핀입니다

unsigned char m_a_spd = 0, m_b_spd = 0; //모터의 속력을 저장하는 전역변수
boolean m_a_dir = 0, m_b_dir = 0; //모터의 방향을 결정하는 전역변수

String Speed;
char  LorR;
int  i;
byte DataToRead[2];

void setup() {
  TCCR1B = TCCR1B & 0b11111000 | 0x05;  //저속주행이 가능하도록 모터A PWM 주파수 변경
  TCCR2B = TCCR2B & 0b11111000 | 0x07;

  // put your setup code here, to run once:
  pinMode(MOTOR_A_a, OUTPUT);
  pinMode(MOTOR_A_b, OUTPUT);
  pinMode(MOTOR_B_a, OUTPUT);
  pinMode(MOTOR_B_b, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(50);
  while(!Serial);
}

void loop(){
  DataToRead[2] = '\n';
  if(Serial.available() > 0) {
    Serial.readBytesUntil(char(13), DataToRead, 2);

    /*for(i = 0; i < 6; i++) {
      Serial.write(DataToRead[i]);
      if(DataToRead[i] == '\n') break;
    }
    */
    
    LorR = DataToRead[0];
    
    switch(LorR) {
      case 'R' :
        right();
        break;
      case 'L' :
        left();
        break;
      case 'B' :
        back();
        break;
      case 'G' :
        go();
        break;
    }
  }

}

void motor_drive()  //모터를 구동하는 함수
{
  if(m_a_dir == 0)
  {
    digitalWrite(MOTOR_A_a, LOW);     //모터A+ LOW
    analogWrite(MOTOR_A_b, m_a_spd);  //모터A-의 속력을 PWM 출력
  }
  else
  {
    analogWrite(MOTOR_A_a, m_a_spd);  //모터A+의 속력을 PWM 출력
    digitalWrite(MOTOR_A_b, LOW);     //모터A- LOW
  }
  if(m_b_dir == 1)
  {
    digitalWrite(MOTOR_B_a, LOW);     //모터B+ LOW
    analogWrite(MOTOR_B_b, m_b_spd);  //모터B-의 속력을 PWM 출력
  }
  else
  {
    analogWrite(MOTOR_B_a, m_b_spd);  //모터B+의 속력을 PWM 출력
    digitalWrite(MOTOR_B_b, LOW);     //모터B- LOW
  }
}

void motor_stop() {
  m_a_dir = 0;
  m_b_dir = 0;
  m_a_spd = 0; //모터A의 속력값 조정
  m_b_spd = 0; //모터B의 속력값 조정
  motor_drive();
}

void right() {
  m_a_dir = 0;
  m_b_dir = 1;
  
  m_a_spd = 200; //모터A의 속력값 조정
  m_b_spd = 200; //모터B의 속력값 조정
  motor_drive();
  delay(200);
  motor_stop();
}

void left() {
  m_a_dir = 1;
  m_b_dir = 0;
  
  m_a_spd = 200; //모터A의 속력값 조정
  m_b_spd = 200; //모터B의 속력값 조정
  motor_drive();
  delay(200);
  motor_stop();
}

void go() {
  m_a_dir = 0;
  m_b_dir = 0;
  
  m_a_spd = 200; //모터A의 속력값 조정
  m_b_spd = 200; //모터B의 속력값 조정
  motor_drive();
  delay(300);
  motor_stop();
}

void back() {
  m_a_dir = 1;
  m_b_dir = 1;
  
  m_a_spd = 200; //모터A의 속력값 조정
  m_b_spd = 200; //모터B의 속력값 조정
  motor_drive();
  delay(150);
  motor_stop();
}

void super_go() {
  m_a_dir = 0;
  m_b_dir = 0;
  
  m_a_spd = 255; //모터A의 속력값 조정
  m_b_spd = 255; //모터B의 속력값 조정
  motor_drive();
  delay(400);
  motor_stop();
}
