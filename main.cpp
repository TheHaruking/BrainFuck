#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include "ConsoleUtl.cpp"
#include "BrainFuck.cpp"

//////////////////////////////////
void Input(BrainFuck::Mode mode){

}


////////////////////////////////
#define MAX_X 32

void BufHdd(char bufarr[][32], const char* moji){ 
	sprintf(bufarr[0], "%-31.31s", moji); 
}

void BufPrg(char bufarr[][32], const char prgarr[], int max){
	for(int i = 0; i < max; i++)
		sprintf(bufarr[i], "%.16s%.15s", &prgarr[i * 16] , "");
/*	sprintf(bufarr[0], "%.16s%.15s", &prgarr[0] , "");
	sprintf(bufarr[1], "%.16s%.15s", &prgarr[16], "");
	sprintf(bufarr[2], "%.16s%.15s", &prgarr[32], "");
	sprintf(bufarr[3], "%.16s%.15s", &prgarr[48], ""); */
}

void BufHex(char bufarr[][32], const int innarr[], int max){
	for(int i = 0; i < max; i++) {
		sprintf(bufarr[i], "%04X %04X %04X %04X %.11s",
				innarr[i * 4 + 0], innarr[i * 4 + 1], 
				innarr[i * 4 + 2], innarr[i * 4 + 3], "");
	}
/*	sprintf(bufarr[0], "%04X %04X %04X %04X %.11s",
			innarr[0], innarr[1], innarr[2], innarr[3], "");
	sprintf(bufarr[1], "%04X %04X %04X %04X %.11s",
			innarr[4], innarr[5], innarr[6], innarr[7], "");
	sprintf(bufarr[2], "%04X %04X %04X %04X %.11s",
			innarr[8], innarr[9], innarr[10],innarr[11],"");
	sprintf(bufarr[3], "%04X %04X %04X %04X %.11s",
			innarr[12],innarr[13],innarr[14],innarr[15],""); */
}

void BufStr(char bufarr[][32], const int* Outarr, int max){
	for (int j = 0; j < max; j++) {
		for (int i = 0; i < 16; i++) {
			// int -> utf-16
			bufarr[j][i*2    ] = (char) Outarr[j*16 + i];
			bufarr[j][i*2 + 1] = (char)(Outarr[j*16 + i] >> 8);
	/*		bufarr[0][i*2    ] = (char) Outarr[0  + i];
			bufarr[0][i*2 + 1] = (char)(Outarr[0  + i] >> 8);
			bufarr[1][i*2    ] = (char) Outarr[16 + i];
			bufarr[1][i*2 + 1] = (char)(Outarr[16 + i] >> 8);
			bufarr[2][i*2    ] = (char) Outarr[32 + i];
			bufarr[2][i*2 + 1] = (char)(Outarr[32 + i] >> 8);
			bufarr[3][i*2    ] = (char) Outarr[48 + i];
			bufarr[3][i*2 + 1] = (char)(Outarr[48 + i] >> 8);
	*/
		}
	}
}

//-------------------------
void DrawBuf(const char bufarr[][32], int max){
	for(int i = 0; i < max; i++)
		printf("%.31s\n", bufarr[i]);
}

void DrawBufW(const char bufarr[][32], int max){
	for(int i = 0; i < max; i++)
		printf("%.16ls\n", (wchar_t *)bufarr[i]);
}

//-------------------
void DrawChrH(const char* ptrarr, int ptr, int _y){
		int y = ptr / 16 + _y + 1;
		int x = ptr % 16 + 1;
		$(y, x);
		$Y; printf("%c", ptrarr[ptr]); $$;
}

void DrawHexH(const int* ptrarr, int ptr, int _y){
		// MEM
		int y = ptr / 4 + _y + 1;
		int x =(ptr % 4) * 5 + 1;
		$(y, x);
		$Y; printf("%04X", ptrarr[ptr]); $$;
}

int main(){
	BrainFuck bf;
	char prgarr[bf.MAX];
	int  innarr[bf.MAX] = { 0x3042, 0x3043, 67, 68, 0x3042, 0, 0};
	int  outarr[bf.MAX] = { 0 } ;
	int  out = 0;
	
	BrainFuck::Mode mode = BrainFuck::BEGIN;

	char viewBuf[32][MAX_X];

	// Init		//////////////
	setlocale( LC_ALL, "");
	sprintf( prgarr, "%-16.16s%-16.16s%-16.16s%-16.16s", 
		//-- !!CODE!! --//
		"++-- [> ++++ <-]",
		">,. >,. >,. >,. ",
		">,..            ",
		"+               "
		//////////////////
	);
	bf.Input(prgarr, innarr);
	$CLS;
	
	
	while(bf.IsRunning()){
		// Input	//////////////
		if(mode == BrainFuck::BEGIN)
			goto Input_skip;

		switch(char c = getchar()) {
			case '!' : mode = BrainFuck::ALL		; break;
			case '@' : mode = BrainFuck::AUTO_START; break;
			case '*' : mode = BrainFuck::ESC		; break;
			case '\n': mode = BrainFuck::STEP		; break;
			default  : mode = BrainFuck::STEP		; break;
		}
		
		Input_skip:
		// Logic	//////////////
		switch(mode){
			case BrainFuck::STEP		: bf.StepExec(&outarr[out], &out);	break;
			case BrainFuck::ALL 		: bf.AllExec(outarr);				break;
			case BrainFuck::AUTO_START	: bf.StartAuto(200); mode = bf.AUTO;break;
			case BrainFuck::AUTO		: bf.AutoExec(&outarr[out]);		break;
			case BrainFuck::BEGIN		: mode = bf.STEP;					break;
			default             		: break;
		}
	
		// VIEWMODEL
		// PRG
		BufHdd(&viewBuf[0],  "# program View");
		BufPrg(&viewBuf[1],  bf.Cmdarr(), 4);
		// OUT
		BufHdd(&viewBuf[5], "# memory");
		BufHex(&viewBuf[6],  bf.Memarr(), 4);
		// STR
		BufHdd(&viewBuf[10], "# output(string)");
		BufStr(&viewBuf[11], bf.Outarr(), 4);
		// INN
		BufHdd(&viewBuf[15],  "# input   View");
		BufHex(&viewBuf[16], bf.Innarr(), 4);
	
		// VIEW		//////////////
		$(0,0);
		DrawBuf (&viewBuf[0],  5);
		DrawBuf (&viewBuf[5],  5);
		DrawBuf (&viewBuf[10], 1);
		DrawBufW(&viewBuf[11], 4);
		DrawBuf (&viewBuf[15], 5);
		
		// Hilghit
		DrawChrH(bf.Cmdarr(), bf.Cmd(), 1);
		DrawHexH(bf.Memarr(), bf.Mem(), 6);
		DrawHexH(bf.Innarr(), bf.Inn(), 16);
		
		// flush
		fflush(stdout);
		//////////////////////////
	}
	
	$(21, 0);
	printf("press any key to end...\n");
	getchar();
	return 0;
}
