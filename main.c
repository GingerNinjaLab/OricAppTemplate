//
// This is a small program that show how to draw graphics with basic commands
//

#include <lib.h>
#include <conio.h>
#include "definitions.h"
#include "libbasic.h"

//#define __DEBUG__

unsigned char mode=APPMODE_INTRO;
unsigned char appState=APPSTATE_UNCHANGED;
unsigned char c,d,e;
unsigned char i,j,k;
unsigned int temp;
unsigned int posX, posY;
unsigned int px,py,bx,by;
unsigned int tX,tY;
unsigned char volume;
unsigned int enemyX,enemyY,enemyX2,enemyY2,targetX,targetY;
unsigned char d;
unsigned char bd,bl;
unsigned char iCtrl,iJoy;
extern unsigned char controlIndex[];
Enemy hord[MAX_ENEMIES];
Enemy iEnemy;
Enemy *enemy,*enemy2;
char buf[8];
char basicString[BASIC_BUFFER_LEN];
char intBuf[10];

unsigned char active[MAX_ENEMIES];
unsigned int lastKey;
unsigned char enemies;
unsigned int counter;
unsigned char counter2,counter3,counter4;
unsigned char running;
unsigned int score,lives;
unsigned char debugCounter;
unsigned char level;
unsigned char txtX,txtY;
unsigned char* addr;
char *stuff;

char *dialogMsg;
char dialogText[8];

//===========================================================================================
//Buffer variables
//===========================================================================================
int bufferPointer;
unsigned char bufferChar1,bufferChar2;
unsigned int bufferInt;

void main() {
  Init();
  mode=APPMODE_INTRO;
  
  running=1;
  MainLoop();
//  Test();
}

void MainLoop() {

  while (running) {
    switch (mode) {
      case APPMODE_INTRO:
        Intro();
        break;
      case APPMODE_MENU:
        Menu();
        break;
      case APPMODE_OPTIONS:
        Options();
        break;
      case APPMODE_SAVE:
        if (Save()==TRUE) {
          mode=APPMODE_MAIN;
        } else {
          mode=APPMODE_MENU;
        }
        break;
      case APPMODE_LOAD:
        if (Load()==TRUE) {
          mode=APPMODE_MAIN;
          appState=APPSTATE_UNCHANGED;
        } else {
          mode=APPMODE_MENU;
        }
        break;
      case APPMODE_NEW:
        New();
        mode=APPMODE_MAIN;
        break;
      case APPMODE_MAIN:
        MainApp();
        break;
      default:
        mode=APPMODE_MENU;
    }
  }
  cls();
  printf("Retro Ginger https://retroginger.com\n");
  printf("Thanks for playing!\n");
}

char is_bit_set(unsigned char value, unsigned int bit_index) {
  return (value & (1 << bit_index)) != 0;
}

void Intro() {
  cls();
  printf("App template\n");
  Pause(10000);
  mode=APPMODE_MENU;
}

void MainApp() {
  cls();
  printf("App template - Main app");
  printf("esc to quit\n");
  printf("Press space to 'do stuff'\n");
  j=0;
  ShowState();
  while (j==0) {
    lastKey = get();  
    if (lastKey==KEY_ESC) {mode=APPMODE_MENU;j=1;}
    if (lastKey==KEY_SPC) {appState=APPSTATE_CHANGED;UpdateState();}
    ShowState();
  }  
}

void Menu() {
  cls();
  printf("App template - Main menu %d",mode);
  printf("\n\n");
  if (appState==APPSTATE_NOTLOADED) {
    printf("1. New\n");
    printf("2. Load\n");
  }
  if (appState==APPSTATE_UNCHANGED) {
    printf("1. Continue\n");
    printf("2. Load\n");
    printf("4. Close\n");
  }
  if (appState==APPSTATE_CHANGED) {
    printf("1. Continue\n");
    printf("2. Load\n");
    printf("3. Save\n");
    printf("4. Close\n");
  }
  printf("5. Options\n");
  printf("esc . Quit\n");

  j=0;    
  while (i=0) {
      srandom(j);
      j++;
      if (j==200) {j=0;}
      if(kbhit()>0) {i=1;}
  }
  lastKey = get();  
//  printf("%d",lastKey);
  if (appState==APPSTATE_NOTLOADED) {
    if (lastKey==KEY_1) {mode=APPMODE_NEW;}
    if (lastKey==KEY_2) {mode=APPMODE_LOAD;}
  }
  if (appState==APPSTATE_UNCHANGED) {
    if (lastKey==KEY_1) {mode=APPMODE_NEW;}
    if (lastKey==KEY_2) {mode=APPMODE_LOAD;}
    if (lastKey==KEY_4) {
      dialogMsg=TEXT_CLOSE;
      if (ConfirmDialog()) {
        appState=APPSTATE_NOTLOADED;
      }
    }
  }
  if (appState==APPSTATE_CHANGED) {
    if (lastKey==KEY_1) {mode=APPMODE_MAIN;}
    if (lastKey==KEY_3) {mode=APPMODE_SAVE;}
    if (lastKey==KEY_4) {
      dialogMsg=TEXT_CLOSE;
      if (ConfirmDialog()) {
        appState=APPSTATE_NOTLOADED;
      }
    }
  }
  if (lastKey==KEY_5) {mode=APPMODE_OPTIONS;}
  if (lastKey==KEY_ESC) {
    dialogMsg="Are you sure you want to quit?";
    if (ConfirmDialog()) {
      mode=APPMODE_END;
      running=0;
    } else {
      mode=APPMODE_MENU;
    }
  }
    Pause(10000);
}

void Options() {
  cls();
  printf("App template - Options %d",mode);
  PrintVolume();
  gotoxy(3,4);
  printf("esc . Quit\n");
  j=0;
  while (j==0) {
    lastKey = get();  
    if (lastKey==50) {mode=APPMODE_OPTIONS;j=1;}
    if (lastKey==27) {mode=APPMODE_MENU;j=1;}
    if (lastKey==44 && volume>0) {volume--; PrintVolume();}
    if (lastKey==46 && volume<10) {volume++; PrintVolume();}
  }
}

void PrintVolume() {
  gotoxy(3,3);
  printf("Sound volume < %d > \n",volume);
}

void Init() {
  cls();
  setflags(8+2); // Disable blinking cusor and keyboard click
  volume=5;
  mode=APPMODE_INTRO;
  appState=APPSTATE_NOTLOADED;
}

void Clear() {
  #ifdef __DEBUG__
    printf("Clear()()\n");
  #endif 
  for (i=0;i<MAX_ENEMIES;i++) {
    enemy = &hord[i];
    enemy->active=0;
    enemy->x=0;
    enemy->y=0;
    enemy->hp=0;
  }
}

//Start a new name, with default values
void New() {
  #ifdef __DEBUG__
    printf("New()\n");
  #endif 
  for (i=0;i<MAX_ENEMIES;i++) {
    enemy = &hord[i];
    enemy->active=1;
    enemy->x=i;
    enemy->y=i;
    enemy->hp=1000+(int)+i;
  }
  appState=APPSTATE_UNCHANGED;
}


//===========================================================================================
// Save/load functions
//===========================================================================================
unsigned char Save() {
  #ifdef __DEBUG__
    printf("Save()\n");
  #endif 
  dialogMsg=TEXT_SAVE;
  if (TextDialog()==TRUE) {
    printf("Press Record/Play on your tape drive\n");
    printf("The press any key (or esc to abort)\n");
    lastKey = get();  
    if (lastKey==KEY_ESC) {
      printf("Cancelled\n");
      return FALSE;
    }
    SetSaveBuffer(); 
    SaveBufferToTape();
    printf("Saved to tape\n");
    return TRUE;
  } else {
    printf("Cancelled\n");
    return FALSE;
  }
}

unsigned char Load() {
  #ifdef __DEBUG__
    printf("Load()\n");
  #endif 
  Clear();
  dialogMsg=TEXT_SAVE;
  if (TextDialog()==TRUE) {
    printf("Press Play on your tape drive\n");
    LoadBufferFromTape();
    GetLoadBuffer();
    printf("Loaded from tape\n");
    return TRUE;
  } else {
    printf("Cancelled\n");
    return FALSE;
  }
}


//===========================================================================================
//Utilities
//===========================================================================================
void Pause(unsigned char time) {
  for (i=0;i<time;i++) {
    for (j=0;j<time;j++) {
      k=1;
    }
  }
}

int RandomNumber(int low,int high) {
    return low + rand() % (high - low + 1);
}

//===========================================================================================
//Debugging
//===========================================================================================
void ShowState() {
  if (appState==APPSTATE_UNCHANGED) {
    gotoxy(3,4);
    printf("App state has not changed");
  } else {
    gotoxy(3,4);
    printf("App state changed        ");
  }
  for (i=0;i<MAX_ENEMIES;i++) {
    enemy = &hord[i];
    gotoxy(3,5+i);
    printf("%d.%d,%d/%d,%d      ",i,enemy->active,enemy->x,enemy->y,enemy->hp);
  }
}

void UpdateState() {
  for (i=0;i<MAX_ENEMIES;i++) {
    enemy = &hord[i];
    enemy->x+=1;
    enemy->y+=1;
    enemy->hp+=1;
  }
}


void Test() {

}

//===========================================================================================
//Dialog functions
//===========================================================================================
unsigned char ConfirmDialog() {
  gotoxy(3,20);
  printf("%s\n",dialogMsg);
  j=0;
  while (j==0) {
    lastKey = get();  
    if (lastKey==KEY_Y) {return TRUE;}
    if (lastKey==KEY_N) {return FALSE;}
    if (lastKey==KEY_ESC) {return FALSE;}
  }
}

unsigned char TextDialog() {
  gotoxy(3,20);
  printf("%s\n",dialogMsg);
  for (i=0;i<DIALOG_TEXT_MAX_LEN;i++) {
    dialogText[i]=0;
  }
  j=0;
  i=0;
  while (j==0) {
    lastKey = get();  
    if (lastKey>32 && lastKey<=126 && i<DIALOG_TEXT_MAX_LEN-1) {
      dialogText[i]=lastKey;
      i++;
    }
    if (lastKey==KEY_ESC) {return FALSE;}
    if (lastKey==KEY_ENTER) {return TRUE;}
    if (lastKey==KEY_DEL) {
      if (i>0) {
        i--;
        dialogText[i]=0;
      }
    } 
    gotoxy(3,21);
    printf("%s",dialogText);
    gotoxy(3+i,21);
    printf("* ");
    gotoxy(3,22);
  }
  return TRUE;
}


//===========================================================================================
//Buffer handling functions - App specific
//===========================================================================================
void GetLoadBuffer() {
  ResetBufferPointer();
  for (i=0;i<MAX_ENEMIES;i++) {
    enemy = &hord[i];
    enemy->active=GetCharFromBuffer();
    enemy->x=GetCharFromBuffer();
    enemy->y=GetCharFromBuffer();
    enemy->hp=GetIntFromBuffer();
  }
}

void SetSaveBuffer() {
  ResetBufferPointer();
  for (i=0;i<MAX_ENEMIES;i++) {
    enemy = &hord[i];
    StoreCharInBuffer(enemy->active);
    StoreCharInBuffer(enemy->x);  
    StoreCharInBuffer(enemy->y);
    StoreIntInBuffer(enemy->hp);
  }
}

//=============================================================================
//Buffer handling functions - Generic functions to read/write data to/from tape
//=============================================================================
void ResetBufferPointer() {
  bufferPointer=STATE_BUFFER_START_ADDR;
}

void StoreCharInBuffer(unsigned char value) {
  poke(bufferPointer,value);
  bufferPointer++;
}

unsigned char GetCharFromBuffer() {
  bufferChar1 = peek(bufferPointer);
  bufferPointer++;
  return bufferChar1;
}

void StoreIntInBuffer(int value) {
  bufferChar1  = value & 0xFF;        // Mask lower 8 bits
  bufferChar2 = (value >> 8) & 0xFF; // Shift right 8 bits, then mask
  poke(bufferPointer,bufferChar1);
  bufferPointer++;
  poke(bufferPointer,bufferChar2);
  bufferPointer++;
}

int GetIntFromBuffer() {
  bufferChar1 = peek(bufferPointer);
  bufferPointer++;
  bufferChar2 = peek(bufferPointer);
  bufferPointer++;
  bufferInt = (bufferChar2 << 8) | bufferChar1;
  return bufferInt;
}

void ClearBasicString() {
  for (i=0;i<BASIC_BUFFER_LEN;i++) {
    basicString[i]=0;
  }
}

void SaveBufferToTape() {
    ClearBasicString();
    sprintf(basicString,"CSAVE\"%s\",A47104,E47999",dialogText,STATE_BUFFER_START_ADDR,STATE_BUFFER_END_ADDR);
    #ifdef __DEBUG__
      printf("Basic string:%s\n",basicString);
    #endif 
    basic(basicString);
}

void LoadBufferFromTape() {
    ClearBasicString();
    sprintf(basicString,"CLOAD\"%s\"",dialogText);
    #ifdef __DEBUG__
      printf("Basic string:%s\n",basicString);
    #endif 
    basic(basicString);
}

void ClearBuffer() {
  #ifdef __DEBUG__
    printf("ClearBuffer()\n");
  #endif 
  for (temp=STATE_BUFFER_START_ADDR;temp<STATE_BUFFER_END_ADDR;temp++) {
    poke(temp,0);
  }
}


