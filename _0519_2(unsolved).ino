//音樂部分(巨集)
#define NOTE_C3 131
#define NOTE_D3 147
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_C4 262

//圖形部分(巨集)
#define ROW1 13
#define ROW2 12
#define ROW3 11
#define ROW4 10
#define ROW5 9
#define ROW6 8
#define ROW7 7
#define ROW8 6

#define COL1 5
#define COL2 4                                                                                                                                                          
#define COL3 3
#define COL4 A4
#define COL5 A3
#define COL6 A2
#define COL7 A1
#define COL8 A0

#define BUTTON A5

//音樂部分(陣列)
int melody[] = {
  NOTE_C3, NOTE_C3, NOTE_C3, NOTE_G3, NOTE_G3, NOTE_F3, NOTE_E3, 0, NOTE_D3, NOTE_E3, NOTE_F3, 0, NOTE_E3,
  NOTE_D3, NOTE_C3, NOTE_C3, NOTE_E3, NOTE_D3, NOTE_G3, NOTE_C3, NOTE_C3, NOTE_C3, NOTE_D3 
};

int melody2[] = {
  NOTE_C3, NOTE_E3, NOTE_C3, NOTE_E3, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_D3, NOTE_G3, NOTE_A3, NOTE_E3,
  NOTE_B3, NOTE_C4, NOTE_B3, NOTE_C4, NOTE_B3, NOTE_A3, NOTE_G3, NOTE_E3, NOTE_G3, NOTE_D3, NOTE_E3, NOTE_C3   
};

int noteDurations[] = {
  8, 8, 8, 4, 4, 8, 8, 8, 4, 8, 8, 8, 4, 
  8, 8, 4, 4, 8, 4, 4, 8, 4, 4
};

int noteDurations2[] = {
  4, 4, 4, 4, 4, 8, 8, 4, 4, 8, 8, 
  8, 8, 8, 16, 16, 16, 8, 8, 8, 8, 8, 4
};

//圖形部分(矩陣)
const int row[] = { ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8 };
const int col[] = { COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8 };

byte scan[8][8] = {
  {1,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,1}
};

byte circle[8][8] = { //笑臉
  {1,1,0,0,0,0,1,1},
  {1,0,1,1,1,1,0,1},
  {0,1,0,1,1,0,1,0},
  {0,1,1,1,1,1,1,0},
  {0,1,0,1,1,0,1,0},
  {0,1,1,0,0,1,1,0},
  {1,0,1,1,1,1,0,1},
  {1,1,0,0,0,0,1,1}
};

byte H[8][8] = {
  {1,0,1,1,1,1,0,1},
  {1,0,1,1,1,1,0,1},
  {1,0,1,1,1,1,0,1},
  {1,0,1,1,1,1,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,1,1,1,1,0,1},
  {1,0,1,1,1,1,0,1},
  {1,0,1,1,1,1,0,1}
};

byte A[8][8] = {
  {1,0,0,0,0,0,0,1},
  {1,0,1,1,1,1,0,1},
  {1,0,1,1,1,1,0,1},
  {1,0,1,1,1,1,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,1,1,1,1,0,1},
  {1,0,1,1,1,1,0,1},
  {1,0,1,1,1,1,0,1}
};

byte previousState=1, presentState=1;
byte patternNumber=0, melodyNumber=0;

void setup()
{
  for (byte i = 0; i <= sizeof(row); i++) {
    pinMode(row[i], OUTPUT);
  }
  for (byte i = 0; i <= sizeof(col); i++) {
    pinMode(col[i], OUTPUT);
  }  

  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{ 
  if(melodyNumber == 0) {
    for (int thisNote = 0; thisNote < 23; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(8, melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(8); // stop the tone playing:
      
      presentState = digitalRead(BUTTON);//讀取按鈕
   
      if(presentState == 0 && previousState == 1){
        patternNumber++;
        if(patternNumber > 2) patternNumber = 0;
        melodyNumber = melodyNumber + 1;
        thisNote = 23;
      }
      if(patternNumber == 0) showPattern(circle);
      else if(patternNumber == 1) showPattern(H);
      else if(patternNumber == 2)showPattern(A);
      delay(2);  
      
      previousState = presentState;
    }
  }
  if(melodyNumber == 1) {
    for (int thisNote = 0; thisNote < 23; thisNote++) {
      int noteDuration = 1000 / noteDurations2[thisNote];
      tone(8, melody2[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(8); // stop the tone playing:
      presentState = digitalRead(BUTTON);//讀取按鈕
      //圖形部分
      if(presentState == 0 && previousState == 1){
        patternNumber++;
        if(patternNumber > 2) patternNumber = 0;
        melodyNumber = melodyNumber + 1;
        thisNote = 23;
      }
      if(patternNumber == 0) showPattern(circle);
      else if(patternNumber == 1) showPattern(H);
      else if(patternNumber == 2)showPattern(A);
      delay(2);  
      previousState = presentState;
    }
  }
  
}

void showPattern(byte matrix[8][8]){
  for(byte i = 0; i < 8; i++){
    for(byte j = 0; j < 8; j++){
      digitalWrite(row[j], scan[i][j]);
      digitalWrite(col[j], matrix[i][j]);	
    }
    for(byte j = 0; j < 8; j++){
      digitalWrite(row[j], LOW);
      digitalWrite(col[j], HIGH);	
    }
  }
  delay(2);
}
