
#define PLAYER_SPEED   1
#define BULLET_SPEED   2
#define MAX_ENEMIES     5
#define MAX_TILES     20
#define ENEMY_SPEED   2
#define ENEMY_RADIUS   4
#define GAMEMODE_INTRO 0
#define GAMEMODE_MENU 1
#define GAMEMODE_OPTIONS 2
#define GAMEMODE_LOADLEVEL 3
#define GAMEMODE_PLAYLEVEL 4
#define GAMEMODE_ENDLEVEL 5
#define GAMEMODE_ENEMYCOLLISION 6
#define GAMEMODE_ENDGAME 7
#define VDU_LEFT 2
#define VDU_TOP 2
#define VDU_BOTTOM 18
#define VDU_RIGHT 39

// Enemy structure
typedef struct {
	int x, y;	                // Enemy Position 
	unsigned char active;
} Enemy;

typedef struct {
	int x, y;	                // Tile Position 
	unsigned char canDestroy;   // Can destroy
    unsigned char isSolid;      // Enemy cannot walk over
} Tile;

void Init();
void Intro();
void SetupUDGs();
void Menu();
void Options();
void LoadGame();
void SaveGame();


void SetupSprites();
void StartGame();
void GameLoop();
void PrintScore();
void PrintLives();
void GameOver();
void MoveEnemies();
int RandomNumber(int low,int high);
void DrawLevel();
void Pause(unsigned char time);
void ShowDebug();
void ShowEnemies(unsigned char e1,unsigned char e2,unsigned char e3,unsigned char e4,unsigned char e5);
void PrintDebug1(unsigned int val);
void PrintDebug2(unsigned int val);
void PrintDebug3(unsigned int val);
void PrintDebug4(unsigned int val);
void PrintDebug5(unsigned int val);

void PrintVolume();


void Load();
