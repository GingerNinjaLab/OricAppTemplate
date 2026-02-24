#define __DEBUG__

#define PLAYER_SPEED   1
#define BULLET_SPEED   2
#define MAX_ENEMIES     7
#define MAX_TILES     20
#define ENEMY_SPEED   2
#define ENEMY_RADIUS   4
#define APPSTATE_UNCHANGED 1
#define APPSTATE_CHANGED 2
#define APPMODE_INTRO 0
#define APPMODE_MENU 1
#define APPMODE_OPTIONS 2
#define APPMODE_LOAD 3
#define APPMODE_MAIN 4
#define APPMODE_END 5
#define APPMODE_SAVE 6
#define APPMODE_NEW 7
#define VDU_LEFT 2
#define VDU_TOP 2
#define VDU_BOTTOM 18
#define VDU_RIGHT 39
#define BASIC_BUFFER_LEN 100
//#define STATE_BUFFER_START_ADDR 0xB800
//#define STATE_BUFFER_END_ADDR 0xBB7F
#define STATE_BUFFER_START_ADDR 47104
#define STATE_BUFFER_END_ADDR 47999
#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_DEL 8
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52

#define KEY_Y 89
#define KEY_N 78
#define TRUE 1
#define FALSE 0
#define DIALOG_TEXT_MAX_LEN 8

//0x24E

// Enemy structure
typedef struct {
	int x, y;	                // Enemy Position 
	unsigned char active;
	int hp;
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
void Clear();						//Clear all state values
void New();							//Set new state
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
void PrintVolume();
unsigned char ConfirmDialog();
unsigned char TextDialog();

void Test();
char is_bit_set(unsigned char value, unsigned int bit_index);

void Encode2CharsFromUnsignedInt(int value,char *highByte,char *lowByte);
unsigned int UnsignedIntFrom2Chars(unsigned char highByte,unsigned char lowByte);

void Encode2CharsFromSignedInt(int value,char *output);
signed int SignedIntFrom2Chars(unsigned char highByte,unsigned char lowByte);

void ResetBufferPointer();

void StoreCharInBuffer(unsigned char value);
unsigned char GetCharFromBuffer();

void StoreIntInBuffer(int value);
int GetIntFromBuffer();

