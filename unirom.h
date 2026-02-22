

#ifdef ASSEMBLER
// Included from an assembler module
#else
// Included from a C module

// Initialization of ISR
extern void u_test();
extern void u_cls();
extern void u_text();
extern void u_lores();
extern void u_hires();
extern void u_ping();
extern void u_zap();
extern void u_explode();
extern void u_shoot();
extern void u_ink(unsigned char colour);
extern void u_curset(unsigned char x,unsigned char y,unsigned char fb);
extern void u_circle(unsigned char radius,unsigned char fb);
extern unsigned char u_curmov(unsigned char x,unsigned char y);

extern void _LoadOneParam();
extern void _LoadTwoParams();
extern void _LoadThreeParams();
extern void _LoadFourParams();
extern void _SetResultParam();
#endif

#define VERSIONCODEADDR $EDAD

/* ROM Verison 1.0 routine addresses */
#define ROM1_0_ROUTINE_____CLS $CC0A
#define ROM1_0_ROUTINE____TEXT $E9A9
#define ROM1_0_ROUTINE___LORES $D937
#define ROM1_0_ROUTINE___HIRES $E9BB
#define ROM1_0_ROUTINE____PING $F412
#define ROM1_0_ROUTINE_____ZAP $F41B
#define ROM1_0_ROUTINE_EXPLODE $F418
#define ROM1_0_ROUTINE___SHOOT $F415
#define ROM1_0_ROUTINE_____INK $F18B
#define ROM1_0_ROUTINE__CURSET $F02D
#define ROM1_0_ROUTINE__CIRCLE $F2E5
#define ROM1_0_ROUTINE__CURMOV $F064

//TODO: PING and ZAP routine addr wrong?

/* ROM Verison 1.1 routine addresses */
#define ROM1_1_ROUTINE_____CLS $CCCE
#define ROM1_1_ROUTINE____TEXT $EC21
#define ROM1_1_ROUTINE___LORES $D9DE
#define ROM1_1_ROUTINE___HIRES $EC33
#define ROM1_1_ROUTINE____PING $FA9F
#define ROM1_1_ROUTINE_____ZAP $FAE1
#define ROM1_1_ROUTINE_EXPLODE $FACB
#define ROM1_1_ROUTINE___SHOOT $FAB5
#define ROM1_1_ROUTINE_____INK $F210
#define ROM1_1_ROUTINE__CURSET $F0C8
#define ROM1_1_ROUTINE__CIRCLE $F37F
#define ROM1_1_ROUTINE__CURMOV $F064


