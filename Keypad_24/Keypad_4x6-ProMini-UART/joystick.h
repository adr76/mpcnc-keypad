#define JOY_X  A0
#define JOY_Y  A1
#define JOY_BTN  8

#define JOY_SHIFT_X 13
#define JOY_SHIFT_Y 25
#define JOY_MAX_XY 650 
#define JOY_CENTER_X 525 
#define JOY_CENTER_Y 537
#define JOY_DEADBAND_X 10
#define JOY_DEADBAND_Y 10
#define JOY_SLOW_FEEDRATE 10
#define JOY_FAST_FEEDRATE 50

int moveStep = 1;

int getJoyX(){
  int step = 0;
  int posX = analogRead(JOY_X);
 
  if (posX >= 0 && posX < (JOY_CENTER_X-JOY_DEADBAND_X)) step = -1;  
  else if (posX > (JOY_CENTER_X-JOY_DEADBAND_X) && posX < (JOY_CENTER_X+JOY_DEADBAND_X) ) step = 0; 
  else if (posX > (JOY_CENTER_X+JOY_DEADBAND_X)) step = 1;
 
  return step;
}

int getJoyY(){
  int step = 0;
  int posY = analogRead(JOY_Y);
 
  if (posY >= 0 && posY < (JOY_CENTER_Y-JOY_DEADBAND_Y)) step = 1;  
  else if (posY > (JOY_CENTER_Y-JOY_DEADBAND_Y) && posY < (JOY_CENTER_Y+JOY_DEADBAND_Y) ) step = 0; 
  else if (posY > (JOY_CENTER_Y+JOY_DEADBAND_Y)) step = -1;
 
  return step;
}

int getJoyBtn(){
  int Joy_BtnState = 0;
  Joy_BtnState = digitalRead(JOY_BTN);
  return Joy_BtnState;
}

char* getJoyGcode(int x, int y, int f = JOY_FAST_FEEDRATE){
  char buf[20];
  
  //snprintf(buf, sizeof buf, "G91\n G0 X%d Y%d F%d \nG90", x, y, f);
  snprintf(buf, sizeof buf, "G0 X%d Y%d F%d", x, y, f); 
  return buf;
}

void switchStepRate(){
  if (moveStep == 1) moveStep = 10;
  else moveStep = 1;
  
  Serial.println(moveStep);
}

void joystick_move(){
  int ad_x, ad_y, feed;
  
  // Slow/Fast Move
  if (getJoyBtn() == 1) switchStepRate();
    
  ad_x = getJoyX();
  ad_y = getJoyY();
  
  if (ad_x != 0 || ad_y != 0){       
    ad_x = ad_x * moveStep;
    ad_y = ad_y * moveStep;
    
    //Serial.print("G91\n");
    Serial.print(getJoyGcode(ad_x, ad_y));
    //Serial.print("G90\n");
    Serial.println();
  }
}

void joystick_print(){
  char buf[100]; 
  snprintf(buf, sizeof buf, "X:%d Y:%d %d", getJoyX(), getJoyY(), getJoyBtn()); 
  Serial.println(buf);
}