//
// This is a small program that show how to draw graphics with basic commands
//

#include <lib.h>
#include <conio.h>
#include "definitions.h"
#include "unirom.h"
#include "libbasic.h"

#define __DEBUG__

unsigned char mode=GAMEMODE_LOADLEVEL;
unsigned char c,d,e;
unsigned char i,j,k;
int temp;
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

void SetupUDGs() {

}

void main() {
    Init();
    volume=5;
    mode=GAMEMODE_INTRO;

  }

void Init() {
  cls();
  running=1;
  addr = (unsigned char*)0x24E;        //
  *addr = 5;                  // set keyb delay at #24E

  printf("Init game data\n");
  for (i=0;i<MAX_ENEMIES;i++) {
    enemy = &hord[i];
    enemy->active=1;
    enemy->x=i;
    enemy->y=i;
  }

  printf("Write game data to buffer\n");
  //Clear buffer
  ClearBuffer();
  //Write state to buffer
  SetSaveBuffer();

  ShowState();

  printf("Save game\n");
  printf("Enter name:\n");
  gets(buf);
  printf("Saving game:%s\n",buf);
  ClearBasicString();
  sprintf(basicString,"CSAVE\"%s\",A#%s,E#%s",buf,STATE_BUFFER_START_ADDR,STATE_BUFFER_END_ADDR);
  printf("Basic string:%s\n",basicString);

  printf("Saving to tape\n");
  basic(basicString);

  printf("Clear and load\n");
  ClearBuffer();
  for (i=0;i<MAX_ENEMIES;i++) {
    enemy = &hord[i];
    enemy->active=0;
    enemy->x=0;
    enemy->y=0;
  }

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

void ClearBuffer() {
  for (temp=STATE_BUFFER_START_ADDR;temp<STATE_BUFFER_END_ADDR;temp++) {
    poke(temp,0);
  }
}

void SetSaveBuffer() {
  temp=STATE_BUFFER_START_ADDR;
  for (i=0;i<MAX_ENEMIES;i++) {
    enemy = &hord[i];
    poke(temp,enemy->active);
    temp++;
    poke(temp,enemy->x);
    temp++;
    poke(temp,enemy->y);
    temp++;
  }

}

void DoSave() {
  #if defined __DEBUG__
  ClearBasicString();
  sprintf(basicString,"CSAVE\"%s\",A#%s,E#%s",buf,STATE_BUFFER_START_ADDR,STATE_BUFFER_END_ADDR);
  printf("Basic string:%s\n",basicString);

  printf("Saving to tape\n");
  basic(basicString);
}

void GetLoadBuffer() {
  temp=STATE_BUFFER_START_ADDR;
  i=0;
  while (i<MAX_ENEMIES) {
    enemy = &hord[i];
    enemy->active=peek(temp);
    temp++;
    enemy->x=peek(temp);
    temp++;
    enemy->y=peek(temp);
    temp++;
    i++;
  }

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
    printf("NPC:%d - %d - %d/%d\n",i,enemy->active,enemy->x,enemy->y);
  }
}
void ClearBasicString() {
  for (i=0;i<BASIC_BUFFER_LEN;i++) {
    basicString[i]=0;
  }
}