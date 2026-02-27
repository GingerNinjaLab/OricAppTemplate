# Oric App Template





B800	ALTERNATE CHAR SET	Mozaic char set in a 2x3 matrix for semi-graphics drawing. Can be redefined	BB7F	896




CSAVE

Atmos: #E909

Get Tape param  #E91E





Tape storage

Var                 max     bytes
unsigned char       255     1
unsigned int        65k     2


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

  ResetBufferPointer();
  StoreCharInBuffer(123);
  StoreIntInBuffer(1438);

  ResetBufferPointer();
  bufferChar1 = GetCharFromBuffer();
  printf("Retrieved char = %d\n",bufferChar1);

  temp = GetIntFromBuffer();
  printf("Retrieved int = %d\n",temp);
  
  //return;

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




Start           In game (unchanged)       In game (changed)
=====           ===================       =================
1 New             Continue                1Continue
2 Load            Load                    2Load
                                          3Save
                  Close                   4Close
Options           Options                 5Options
Quit                                      6Quit

N
L
S
O
Q
C

                