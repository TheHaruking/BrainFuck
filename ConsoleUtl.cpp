
#ifdef __GNUC__
#define $CLS		system("clear")
#define $A			printf("\e[37m\e[40m")
#define $B			printf("\e[36m\e[40m")
#define $X			printf("\e[30m\e[47m")
#define $Y			printf("\e[30m\e[46m")
#define $$			printf("\e[39m\e[49m")	// default
#define $(_y,_x)	printf("\e[%d;%dH",_y,_x)
#endif

#ifdef _MSC_VER
#define $CLS	system("cls")
#define $A		SetConsoleTextAttribute(hCons, 0x0f)	//color : cyan
#define $B		SetConsoleTextAttribute(hCons, 0x0e)	// default
#define $X		SetConsoleTextAttribute(hCons, 0xf0)	// default
#define $Y		SetConsoleTextAttribute(hCons, 0xe0)	// default
#define $$		SetConsoleTextAttribute(hCons, 0x0f)	// default
#define $(_y,_x)	printf("\e[%d;%dH",_y,_x)
#endif