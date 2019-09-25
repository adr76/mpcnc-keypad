#define JOY_X  A0
#define JOY_Y  A1
#define JOY_BTN  8

#define JOY_SHIFT_X 13
#define JOY_SHIFT_Y 25
#define JOY_MAX_XY 650 
#define JOY_CENTER_X 525 
#define JOY_CENTER_Y 537
#define JOY_DEADBAND_X 5
#define JOY_DEADBAND_Y 5
#define JOY_SLOW_FACTOR 0.1
#define JOY_FAST_FACTOR 1
#define JOY_SLOW_FEEDRATE 10
#define JOY_FAST_FEEDRATE 100

int getJoyX(){
  int step = 0;
  int posX = analogRead(JOY_X);
  
  //return posX;
 
  if (posX >= 0 && posX < 30 ) step = -100;
  else if (posX > 30 && posX < 400) step = -10;  
  else if (posX > 400 && posX < 520) step = -1;
  
  else if (posX > 520 && posX < 530 ) step = 0;
  
  else if (posX > 530 && posX < 700) step = 1;
  else if (posX > 700 && posX < 1000) step = 10;
  else if (posX > 1000) step = 100;
 
  return step;
}

int getJoyY(){
  int posY = 0;

  posY = (analogRead(JOY_Y) - JOY_CENTER_Y)*-1;
  if (posY < JOY_DEADBAND_Y && posY > -JOY_DEADBAND_Y) posY = 0;
  else {
    if (posY >= JOY_DEADBAND_Y) posY -= JOY_DEADBAND_Y;
    if (posY <= -JOY_DEADBAND_Y) posY += JOY_DEADBAND_Y;
    posY -= JOY_SHIFT_Y;
  }
  return posY;
}

int getJoyBtn(){
  int Joy_BtnState = 0;
  Joy_BtnState = digitalRead(JOY_BTN);
  return Joy_BtnState;
}

char* getJoyGcode(int x, int y, int f = JOY_FAST_FEEDRATE){
  char buf[20];
  
  //snprintf(buf, sizeof buf, "G91\n G0 X%d Y%d %s \nG90", x, y, f);
  snprintf(buf, sizeof buf, "G0 X%d Y%d F%d", x, y, f); 
  return buf;
}


int getJoyStep(int val){
  int step;

  bool back = val < 0;
  val = abs(val);
   
  if ((val > 0) && (val < 200)) step = 1;
  else if ((val > 200) && (val < 450)) step = 10;
  else if ((val > 450) && (val < 510)) step = 100;
  
  if (back) step = int(step * -1);
  
  return step;
}

void joystick_move(){
  int ad_x, ad_y, feed;
  
  ad_x = getJoyX();
  ad_y = getJoyY();
  
  if (ad_x != 0 || ad_y != 0){     
    ad_x = getJoyStep(ad_x);
    ad_y = getJoyStep(ad_y);
    
    //Serial.print("G91\n");
    Serial.print(getJoyGcode(ad_x, ad_y, feed));
    //Serial.print("G90\n");
    Serial.println();
  }
}

void joystick_print(){
  char buf[100]; 
  snprintf(buf, sizeof buf, "X:%d Y:%d %d", getJoyX(), getJoyY(), getJoyBtn()); 
  Serial.println(buf);
}