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
  int posX = 0; 

  posX = (analogRead(JOY_X) - JOY_CENTER_X);
  if (posX < JOY_DEADBAND_X && posX > -JOY_DEADBAND_X) posX = 0;
  else {
    if (posX >= JOY_DEADBAND_X) posX -= JOY_DEADBAND_X;
    if (posX <= -JOY_DEADBAND_X) posX += JOY_DEADBAND_X;
    posX += JOY_SHIFT_X;
  }
  return posX;
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

void joystick_move(){
  int ad_x, ad_y, feed;
  
  ad_x = getJoyX();
  ad_y = getJoyY();
  
  if (ad_x != 0 || ad_y != 0){ 
    
    //Slow motion
    if (getJoyBtn() == 1){
      ad_x = ad_x*JOY_SLOW_FACTOR;
      ad_y = ad_y*JOY_SLOW_FACTOR;
      feed = JOY_SLOW_FEEDRATE;
    }
    
    //Fast motion
    else if (getJoyBtn() == 0){
      ad_x = ad_x*JOY_FAST_FACTOR;
      ad_y = ad_y*JOY_FAST_FACTOR;
      feed = JOY_FAST_FEEDRATE;
    }
    
    Serial.println(getJoyGcode((int32_t)ad_x, (int32_t)ad_y, feed));
  }
}

void joystick_print(){
  char buf[100]; 
  snprintf(buf, sizeof buf, "X:%d Y:%d %d", getJoyX(), getJoyY(), getJoyBtn()); 
  Serial.println(buf);
}