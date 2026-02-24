//
// This is a small program that show how to draw graphics with basic commands
//

#include <lib.h>
#include <conio.h>
#include "definitions.h"
#include "unirom.h"
#include "libbasic.h"

#define __DEBUG__

unsigned char mode=APPMODE_INTRO;
unsigned char appState=APPSTATE_UNINITIALIZED;
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

Tile tiles[MAX_TILES];
Tile *tile;

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
      case APPMODE_NEW:
        MainLoop();
        break;
      case APPMODE_MAIN:
        MainLoop();
        break;
      default:
        mode=APPMODE_MENU;
    }
  }
}


char is_bit_set(unsigned char value, unsigned int bit_index) {
  return (value & (1 << bit_index)) != 0;
}

void Intro() {
  cls();
  printf("App/Game template\n");
  Pause(10000);
  mode=APPMODE_MENU;
}


void Menu() {
  u_cls();
  printf("Game/App template - Main menu %d",mode);
  printf("\n\n");
  if (appState==APPSTATE_UNCHANGED) {
    printf("1. New\n");
    printf("2. Load\n");
  } else {
    printf("1. Continue\n");
    printf("2. Save\n");
  }
  printf("3. Options\n");
  printf("esc . Quit\n");

  j=0;    
  while (i=0) {
      srandom(j);
      j++;
      if (j==200) {j=0;}
      if(kbhit()>0) {i=1;}
  }
  lastKey = get();  
  printf("%d",lastKey);
  if (appState==APPSTATE_UNCHANGED) {
    if (lastKey==KEY_1) {mode=APPMODE_NEW;}
    if (lastKey==KEY_2) {mode=APPMODE_LOAD;}
  } else {

  }
  if (lastKey==KEY_3) {mode=APPMODE_OPTIONS;}

  if (lastKey==49) {
      New();
      mode=APPMODE_INTRO;
    } else {
      dialogMsg="Start a new app? Current progress will be lost.";
      if (ConfirmDialog()) {
        Clear();
        New();
        appState=APPSTATE_CHANGED;
      }
    }
  }

  if (lastKey==27) {
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

void SaveGame() {

}

void Options() {
  u_cls();
  printf("Game/App template - Options %d",mode);
//  printf("\n\n");
  PrintVolume();
  gotoxy(3,4);
  printf("esc . Quit\n");
  j=0;
  while (j==0) {
    lastKey = get();  
   // printf("%d",lastKey);
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
  addr = (unsigned char*)0x24E;   //
  *addr = 5;                      // set keyb delay at #24E
  volume=5;
  mode=APPMODE_INTRO;

}

void Clear() {
  #ifdef __DEBUG__
    printf("Clear()()\n");
  #endif // __DEBUG__
  for (i=0;i<MAX_ENEMIES;i++) {
    enemy = &hord[i];
    enemy->active=0;
    enemy->x=0;
    enemy->y=0;
    enemy->hp=0;
  }
}

void New() {
  #ifdef __DEBUG__
    printf("New()()\n");
  #endif // __DEBUG__
  for (i=0;i<MAX_ENEMIES;i++) {
    enemy = &hord[i];
    enemy->active=1;
    enemy->x=i;
    enemy->y=i;
    enemy->hp=1000+(int)+i;
  }
  mode=APPMODE_MAIN;
}

void ClearBuffer() {
  #ifdef __DEBUG__
    printf("ClearBuffer()\n");
  #endif // __DEBUG__
  for (temp=STATE_BUFFER_START_ADDR;temp<STATE_BUFFER_END_ADDR;temp++) {
    poke(temp,0);
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

void DoSave() {
  #ifdef __DEBUG__
    printf("DoSave()\n");
  #endif // __DEBUG__
  ClearBasicString();
  sprintf(basicString,"CSAVE\"%s\",A#%s,E#%s",buf,STATE_BUFFER_START_ADDR,STATE_BUFFER_END_ADDR);
  #ifdef __DEBUG__
    printf("Basic string:%s\n",basicString);
    printf("Saving to tape\n");
  #endif // __DEBUG__
  basic(basicString);
}

void GetLoadBuffer() {
  ResetBufferPointer();
  i=0;
  while (i<MAX_ENEMIES) {
    enemy = &hord[i];
    enemy->active=GetCharFromBuffer();
    enemy->x=GetCharFromBuffer();
    enemy->y=GetCharFromBuffer();
    enemy->hp=GetIntFromBuffer();
    i++;
  }
}

void Load() {

  printf("Enter name:\n");
  gets(buf);
  printf("Loading game:%s\n",buf);
  ClearBasicString();
  sprintf(basicString,"CLOAD\"%s\"",buf);
  printf("Basic string:%s\n",basicString);
  basic(basicString);

  //Load data
  GetLoadBuffer();

}

void DoLoad() {
  #ifdef __DEBUG__
    printf("DoLoad()\n");
  #endif // __DEBUG__
  ClearBasicString();

  sprintf(basicString,"CLOAD\"%s\"",buf);
  basic(basicString);
}

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

void ShowState() {
  for (i=0;i<MAX_ENEMIES;i++) {
    enemy = &hord[i];
    printf("%d.%d,%d/%d,%d\n",i,enemy->active,enemy->x,enemy->y,enemy->hp);
  }
}

void ClearBasicString() {
  for (i=0;i<BASIC_BUFFER_LEN;i++) {
    basicString[i]=0;
  }
}

void Test() {

  printf("Write game data to buffer\n");
  //Clear buffer
  ClearBuffer();

  //New state
  New();
  
  //Write state to buffer
  SetSaveBuffer();

  ShowState();

  printf("Save game\n");
  printf("Enter name:\n");
  gets(buf);
  printf("Saving game:%s\n",buf);
  ClearBasicString();
  //TODO: Make addres confirable
  sprintf(basicString,"CSAVE\"%s\",A47104,E47999",buf,STATE_BUFFER_START_ADDR,STATE_BUFFER_END_ADDR);
  printf("Basic string:%s\n",basicString);

  printf("Saving to tape\n");
  basic(basicString);

  printf("Clear and load\n");
  ClearBuffer();
  Clear();

  printf("Enter name:\n");
  gets(buf);
  printf("Loading game:%s\n",buf);
  ClearBasicString();
  sprintf(basicString,"CLOAD\"%s\"",buf);
  printf("Basic string:%s\n",basicString);
  basic(basicString);

  //Load data
  GetLoadBuffer();

  printf("State after load\n");
  ShowState();

  gets(buf);

  Pause(100000);

//47104
//47999
    //B800
    //BB7F

}


unsigned char ConfirmDialog() {
  printf("%s\n",dialogMsg);
  j=0;
  while (j==0) {
    lastKey = get();  
    if (lastKey==KEY_Y) {return TRUE}
    if (lastKey==KEY_N) {return FALSE;}
    if (lastKey==KEY_ESC) {return FALSE;}
  }
}

unsigned char TextDialog() {
  printf("%s\n",dialogMsg);
  for (i=0;i<DIALOG_TEXT_MAX_LEN;i++) {
    dialogText[i]=0;
  }
  j=0;
  i=0;
  while (j==0) {
    lastKey = get();  
    if (lastKey==KEY_DEL) {
      if (i>0) {
        i--;
        dialogText[i]=0;
        printf("\b \b");
      }
    } 
    if (lastKey==KEY_ENTER) {
      j=1;
    }
    if (lastKey>32 && lastKey<=126 && i<DIALOG_TEXT_MAX_LEN-1) {
      dialogText[i]=lastKey;
      i++;
    }

    if (lastKey==KEY_ESC) {return FALSE;}
    gotoxy(1,3);
    printf("%s",dialogText);
  }

}

//===========================================================================================
//Buffer handling functions
//===========================================================================================
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


