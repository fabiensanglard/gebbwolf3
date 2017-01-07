#define STR_NG	"New Game"
#define	STR_SD	"Sound"
#define	STR_CL	"Control"
#define	STR_LG	"Load Game"
#define	STR_SG	"Save Game"
#define	STR_CV	"Change View"

void CP_NewGame(void);
void CP_Sound(void);
void CP_Control(void);
void CP_LoadGame(void);
void CP_SaveGame(void);
void CP_ChangeView(void);

CP_itemtype far
MainMenu[]=
{
	{1,STR_NG,CP_NewGame},
	{1,STR_SD,CP_Sound},
	{1,STR_CL,CP_Control},
	{1,STR_LG,CP_LoadGame},
	{0,STR_SG,CP_SaveGame},
	{1,STR_CV,CP_ChangeView},
	...
}