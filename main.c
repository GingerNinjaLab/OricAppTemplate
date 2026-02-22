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
  //  GameLoop();
}

void Init() {
  running=1;
  addr = (unsigned char*)0x24E;        //
  *addr = 5;                  // set keyb delay at #24E
// 	bang("CSAVE\"CHARSET.CHR\",A#B400,E#B7FF"); 
//  bang("HIRES");
  j=0;
  for (temp=47104;temp<47999;temp++) {
    poke(temp,j);
    j++;
    if (j==255) {
      printf("block\n");
      j=0;
    }
  }
//  basic("CSAVE\"GAME1\",A#B800,E#BB7F");

      printf("loading\n");

  basic("CLOAD\"GAME1\"");

        printf("displaying\n");

  gotoxy(2,2);
  for (temp=47104;temp<47120;temp++) {
    i=peek(temp);
    printf("%d",i);
  }
  
        printf("done\n");

  Pause(100000);

//47104
//47999
    //B800
    //BB7F
}

void Intro() {
  u_cls();
  printf("Retro Ginger... %d",mode);
  printf("\n\n");
  Pause(50000);
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
  if (lastKey==49) {mode=GAMEMODE_LOADLEVEL;}
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

void StartGame() {

    u_cls();
    #ifdef __DEBUG__
        printf("Starting game\n");
    #endif

    //Set player strart position
    px=VDU_RIGHT/2-VDU_LEFT-2;
    py=VDU_BOTTOM/2-VDU_TOP-2;

    printf("Player position x:%d/y:%d\n",px,py);

    //Randomly place enemies
    enemies=5;

    #ifdef __DEBUG__
        printf("Generate level\n");
    #endif
    i=0;
    while (i<MAX_TILES) {
        posX=RandomNumber(VDU_LEFT,VDU_RIGHT);
        posY=RandomNumber(VDU_TOP,VDU_BOTTOM);
        if (posX!=(px) && posY!=(py)) {
            tile = &tiles[i];
            tile->x=RandomNumber(VDU_LEFT,VDU_RIGHT);
            tile->y=RandomNumber(VDU_TOP,VDU_BOTTOM);
            tile->canDestroy=RandomNumber(0,1);
            tile->isSolid=RandomNumber(0,1);

            #ifdef __DEBUG__
                printf("Tile %d x:%d/y:%d D:%d S:%d\n",i,tile->x,tile->y,tile->canDestroy,tile->isSolid);
            #endif
            i++;
        } else {
            #ifdef __DEBUG__
                printf("Tile hits player, skipping\n");
            #endif
        }
    }

    #ifdef __DEBUG__
        printf("Placing enemies\n");
    #endif

    i=0;
    while (i<MAX_ENEMIES) {
        enemy = &hord[i];
        enemy->active=0;
        posX=RandomNumber(VDU_LEFT,VDU_RIGHT);
        posY=RandomNumber(VDU_TOP,VDU_BOTTOM);
        if ((fabs(posX-px)>ENEMY_RADIUS) && (fabs(posY-py)>ENEMY_RADIUS)) {
            i++;
            enemy->x=posX;
            enemy->y=posY;
            enemy->active=1;
            #ifdef __DEBUG__
                printf("Enemy %d x:%d/y:%d\n",c,enemy->x,enemy->y);
            #endif
        } else {
            #ifdef __DEBUG__
                printf("Out of bounds %d x:%d/y:%d\n",c,posX,posY);
            #endif
        }
    }

    running=1;
    debugCounter=0;
    level=1;
    enemies=0;
    iCtrl = 0;

    score=0;
    lives=5;
  //TODO:Add level layout

  //  PrintScore();
  //  PrintLives();

    lastKey = get();  
}


void GameLoop() {
    while (running==1) {			

        switch (mode) {
          case GAMEMODE_INTRO:
            Intro();
            break;

          case GAMEMODE_MENU:
            Menu();
            break;

            case GAMEMODE_OPTIONS:
            Options();
            break;

            case GAMEMODE_LOADLEVEL:
            cls();
            printf("Entering Level: %d",level);	
            mode=GAMEMODE_PLAYLEVEL;
            lastKey = get();
            cls();
            DrawLevel();
            break;

        case GAMEMODE_PLAYLEVEL:
            lastKey = get();
            d=0;
            tX=posX;
            tY=posY;
            if (lastKey=='A' || lastKey=='a') {
              d=1;
              tX=posX-1;
            }
            if (lastKey=='D' || lastKey=='d') {
              d=2;
              tX=posX+1;
            }
            if (lastKey=='W' || lastKey=='w') {
              d=3;
              tY=posY-1;
            }
            if (lastKey=='S' || lastKey=='s') {
              d=4;
              tY=posY+1;
            }
            
            //Check sceneray
            c=0;
            for (i=0;i<MAX_TILES;i++) {
              tile = &tiles[i];
              if (tile->x==tX && tile->y==tX) {
                //Collision
                c=1;
              }
            }
            
            //Check enemies
            e=0;
            for (i=0;i<MAX_ENEMIES;i++) {
              enemy = &hord[i];
              if (enemy->active==1) {
                if (enemy->x==tX && enemy->y==tX) {
                  //Collision
                  e=1;
                }
              }
            }


            if (c==0 && e==0) {posX=tX;posY=tY;}

            #ifdef __DEBUG__
              gotoxy(1,2);
              printf("x:%d y:%d c:%d e:%d d:%d\n",posX,posY,c,d,e);
            #endif
    
            DrawLevel();
        
          //  counter=0;
//            ShowDebug();
        
//            ShowEnemies(active[0],active[1],active[2],active[3],active[4]);
            break;

            case GAMEMODE_ENEMYCOLLISION:
              u_cls();
              printf("Hit an enemy!");
            break;
        }
    }
}

void DrawLevel() {
    for (i=0;i<MAX_TILES;i++) {
        tile = &tiles[i];
        gotoxy(tile->x,tile->y);
        putchar('#');
    }
    for (i=0;i<MAX_ENEMIES;i++) {
        enemy = &hord[i];
        if (enemy->active==1) {
          gotoxy(enemy->x,enemy->y);
          putchar('*');
        }
          #ifdef __DEBUG__
      //      printf("Enemy x:%d y:%d i:%d\n",enemy->x,enemy->y,i);
          #endif
    }    
    gotoxy(posX,posY);
    putchar('&');
}

void MoveEnemies() {
    for (i=0;i<MAX_ENEMIES;i++) {
        enemy = &hord[i];
        if (enemy->active==1) {
        d=0;
        targetX=0;
        targetY=0;
        if (enemy->x>px) { targetX = (enemy->x-=ENEMY_SPEED); }
        if (enemy->x<px) { targetX = (enemy->x+=ENEMY_SPEED); }
        if (enemy->y>py) { targetY = (enemy->y-=ENEMY_SPEED); }
        if (enemy->y<py) { targetY = (enemy->y+=ENEMY_SPEED); }

        enemy->x=targetX;
        enemy->y=targetY;

        if (enemy->x>(px-ENEMY_RADIUS) &&
            enemy->x<(px+ENEMY_RADIUS) &&
            enemy->y>(py-ENEMY_RADIUS) &&
            enemy->y>(py+ENEMY_RADIUS)) {
            lives--;
            enemy->active=0;
            PrintLives();
            if (lives==0) {
                //TODO: End game
                GameOver();
            }
        }

        }
        enemies=0;
        if (enemy->active==1) {
//            EnableSprite(i+3);
//            LocateSprite(enemy->x, enemy->y);
//            SetSprite(i+3, 1);
            enemies++;
        }
    }
    counter2=0;
    PrintDebug2(enemies);
}

void PrintScore() {
  txtX = 0; txtY = 0; 
  printf("Score:");	
  txtX = 7;
  printf("%d",score);
}

void PrintLives() {
  txtX = 11;
  txtY = 0; 
  printf("Lives:");	
  txtX = 17;
  printf("%d",lives);
}

void GameOver() {
  txtX = 0;
  txtY = 0; 
  printf("Game Over!!!!!                   ");	
}

void ShowDebug() {
  txtX = 20;
  txtY = 0; 
  printf("%d",enemies);

}

void PrintDebug(unsigned int v1,unsigned int v2,unsigned int v3) {
  txtX = 1;
  txtY = 10; 
  printf("                         ");	
  txtX = 1;
  txtY = 10; 
  printf("%d",v1);
  txtX = 5;
  txtY = 10; 
  printf("%d",v2);
  txtX = 10;
  txtY = 10; 
  printf("%d",v3);

}

void PrintDebug1(unsigned int val) {
  txtX = 1;
  txtY = 10; 
  printf("  ");	
  txtX = 1;
  txtY = 10; 
  printf("%d",val);
}

void PrintDebug2(unsigned int val) {
  txtX = 4;
  txtY = 10; 
  printf("  ");	
  txtX = 4;
  txtY = 10; 
  printf("%d",val);
}

void PrintDebug3(unsigned int val) {
  txtX = 8;
  txtY = 10; 
  printf("  ");	
  txtX = 8;
  txtY = 10; 
  printf("%d",val);
}

void PrintDebug4(unsigned int val) {
  txtX = 12;
  txtY = 10; 
  printf("  ");	
  txtX = 12;
  txtY = 10; 
  printf("%d",val);
}

void PrintDebug5(unsigned int val) {
  txtX = 16;
  txtY = 10; 
  printf("  ");	
  txtX = 16;
  txtY = 10; 
  printf("%d",val);
}

void ShowEnemies(unsigned char e1,unsigned char e2,unsigned char e3,unsigned char e4,unsigned char e5) {
  txtY = 5; 
  txtX = 1;
  printf("%d",e1);
  txtX = 2;
  printf("%d",e2);
  txtX = 3;
  printf("%d",e3);
  txtX = 4;
  printf("%d",e4);
  txtX = 5;
  printf("%d",e5);

}



void Load() {

}