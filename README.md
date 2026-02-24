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


