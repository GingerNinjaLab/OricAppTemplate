#define __DEBUG__

#define PLAYER_SPEED   1
#define BULLET_SPEED   2
#define MAX_ENEMIES     7
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
#define BASIC_BUFFER_LEN 100
#define STATE_BUFFER_START_ADDR 0xB800
#define STATE_BUFFER_END_ADDR 0xBB7F

//0x24E

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
void Intro();						//Show Intro
void Menu();						//Show main menu
void Options();						//Show options
void ClearBuffer();					//Clear out the buffer for LOAD/SAVE operations
void Load();						//Prompt for loading
void DoLoad();						//Load data from tape
void GetLoadBuffer();				//Setup app/game state from the buffer after a load
void SetSaveBuffer();				//Write app/game state to buffer for saving
void Save();						//Prompt for saving
void DoSave();						//Save data to tape
void MainLoop();					//Main app/game loop
int RandomNumber(int low,int high);	//Generate a random number between low and high
void Pause(unsigned char time);		//Pause execution for a short time (crude)
void ResetState();					//Reset all app/game state
void ShowState();					//Show the state of the app/game
void ClearBasicString();			//Clear the basic string buffer for each new command
