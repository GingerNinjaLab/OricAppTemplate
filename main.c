//
// This is a small program that show how to draw graphics with basic commands
//

#include <lib.h>
#include <conio.h>
#include "definitions.h"
#include "unirom.h"
#include "libbasic.h"

#define __DEBUG__

unsigned char mode=GAMEMODE_INTRO;
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

void main() {

 //   printf("%d\n", (void*)&hord[i]);

//    return;

  Init();

//  Test();
  temp=1438;
  stuff=itoa(temp);
//  intBuf[0]=200;
//  intBuf[1]=135;

  /*
  0000101 10011110
  98

  00000101  5
  10011110  158

  */
  //Encode2CharsFromUnsignedInt(1438,&intBuf[0],&intBuf[1]);
  printf("%s\n",stuff);

  printf("Int = %d\n",temp);

  i  = temp & 0xFF;        // Mask lower 8 bits
  j = (temp >> 8) & 0xFF; // Shift right 8 bits, then mask

  printf("Bytes, Low: %d High:%d\n",i,j);

  temp = (j << 8) | i;

  printf("Int = %d\n",temp);

  return;

  temp=0;
  for (j=0;j<8;j++) {
    printf("%d - %d\n",j,is_bit_set(intBuf[0],j));    
  }
  if (is_bit_set(intBuf[0],0)!=0) {temp+=256;}
  if (is_bit_set(intBuf[0],1)!=0) {temp+=512;}
  if (is_bit_set(intBuf[0],2)!=0) {temp+=1024;}
  if (is_bit_set(intBuf[0],3)!=0) {temp+=2048;}
  if (is_bit_set(intBuf[0],4)!=0) {temp+=4906;}
  if (is_bit_set(intBuf[0],5)!=0) {temp+=8192;}
  if (is_bit_set(intBuf[0],6)!=0) {temp+=16384;}
  if (is_bit_set(intBuf[0],7)!=0) {temp+=32768;}
  temp+=intBuf[1];
  printf("%d",temp);

}

void Encode2CharsFromUnsignedInt(int value,char *highByte,char *lowByte) {
  *highByte=0;
  *lowByte=(char)(value & 256);
  if (value & (1 << 8)==1) { *highByte+=1; }
  if (value & (1 << 9)==1) { *highByte+=2; }
  if (value & (1 << 10)==1) { *highByte+=4; }
  if (value & (1 << 11)==1) { *highByte+=8; }
  if (value & (1 << 12)==1) { *highByte+=16; }
  if (value & (1 << 13)==1) { *highByte+=32; }
  if (value & (1 << 14)==1) { *highByte+=64; }
  if (value & (1 << 15)==1) { *highByte+=128; }
}

char is_bit_set(unsigned char value, unsigned int bit_index) {
  return (value & (1 << bit_index)) != 0;
}

void Intro() {
  cls();
  printf("App/Game template\n");
  Pause(10000);
  mode=GAMEMODE_MENU;
}


void Menu() {
  u_cls();
  printf("Battle Drome - Main menu %d",mode);
  printf("\n\n");
  printf("1 . New game\n");
  printf("2 . Options\n");
  printf("esc . Quit\n");

  Load();
  
  i=0;
  j=0;    
  while (i=0) {
      srandom(j);
      j++;
      if (j==200) {
          j=0;
      }
      if(kbhit()>0) {
          i=1;
      }
  }
  lastKey = get();  
  printf("%d",lastKey);
  if (lastKey==49) {mode=GAMEMODE_INTRO;}
  if (lastKey==50) {mode=GAMEMODE_OPTIONS;}
  if (lastKey==27) {mode=GAMEMODE_MENU;}
}

void SaveGame() {

}

void Options() {
  u_cls();
  printf("Battle Drome - Options %d",mode);
//  printf("\n\n");
  PrintVolume();
  gotoxy(3,4);
  printf("esc . Quit\n");
  j=0;
  while (j==0) {
    lastKey = get();  
   // printf("%d",lastKey);
    if (lastKey==50) {mode=GAMEMODE_OPTIONS;j=1;}
    if (lastKey==27) {mode=GAMEMODE_MENU;j=1;}
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
  mode=GAMEMODE_INTRO;

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
  temp=STATE_BUFFER_START_ADDR;
  for (i=0;i<MAX_ENEMIES;i++) {
    enemy = &hord[i];
    poke(temp,enemy->active);
    temp++;
    poke(temp,enemy->x);
    temp++;
    poke(temp,enemy->y);
    temp++;


    sprintf(intBuf,"%d", enemy->hp);
    poke(temp,intBuf[0]);
    temp++;
    poke(temp,intBuf[1]);
    temp++;
    poke(temp,intBuf[2]);
    temp++;
    poke(temp,intBuf[3]);
    temp++;

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

    intBuf[0]=peek(temp);
    temp++;
    intBuf[1]=peek(temp);
    temp++;
    intBuf[2]=peek(temp);
    temp++;
    intBuf[3]=peek(temp);
    intBuf[4]=0;
    temp++;
    printf("intBuf:%s\n",intBuf);
    enemy->hp = sscanf(intBuf, "%d");


    i++;
  }

}

void Load() {

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