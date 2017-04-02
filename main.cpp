#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ConsoleUtl.cpp"
#include "BrainFuck.cpp"
#define PrintTitle(s) $B;printf(s);$$;

//////////////////////////////////

	void PrgOut(char* prgarr, int prg){
		// Title
		$(0,0);
		PrintTitle("# prg output\n");

		// 本体 (文字5行)
		printf("%s\n", prgarr);

		// 移動部
		int y = prg / 16 + 1;
		int x = prg % 16 + 1;

		$(2, x);
		$Y; printf("%c", prgarr[prg]); $$;
	}

	void ValOut(int* innarr, int _x){
		// Title
		$(5,0);
		PrintTitle("# num output\n");

		// 本体 (数値)
		int x;
		for(int j = 0; j < 2; j++){
			x = _x;
			for(int i = 0; i < 8; i++){
				printf("%d\t", innarr[i + j*8]);
			}	printf("\n");
			while(x--) printf("\t");
			printf("^\n");
		}	puts("");
	}

	void StrOut(int* innarr, int max){
		$(10,0);
		PrintTitle("# str output\n");
		for(int i = 0; i < max; i++){
			printf("%c", (char)innarr[i]);
		}
		puts("");
	}

#define MAX_X 32

int main(){
	BrainFuck bf;
	char prgarr[bf.MAX];

	sprintf(
		prgarr, "%-16.16s%-16.16s%-16.16s%-16.16s", 
		//-- !!CODE!! --//
		"+++ [> ++++ <-] ",
		">,. >,. >,. >,.",
		"...............",
		"+"
		//////////////////
	);
	int  innarr[bf.MAX] = { 65, 66, 67, 68, 0, 0, 0};
	int  outarr[bf.MAX] = { 0 } ;
	int  out = 0;
	
	char c;
	BrainFuck::Mode  mode = BrainFuck::STEP;

	char viewBuf[32][MAX_X];

	// Init		//////////////
	bf.Input(prgarr, innarr);
	$CLS;/*
	PrgOut(prgarr, bf.Cmd());
	ValOut(bf.Memarr(), bf.Mem());
	StrOut(outarr, 16);*/

	while(bf.IsRunning()){
	// Input	//////////////
	Input:
		if(mode == bf.AUTO) goto Logic;

		c = getchar();
		switch(c) {
			case '!': mode = BrainFuck::ALL			; break;
			case '@': mode = BrainFuck::AUTO_START	; break;
			case '*': mode = BrainFuck::ESC			; break;
			default : mode = BrainFuck::STEP		; break;
		}	
	// Logic	//////////////
	Logic:
		switch(mode){
			case BrainFuck::STEP		: bf.StepExec(&outarr[out], &out);	break;
			case BrainFuck::ALL 		: bf.AllExec(outarr);			break;
			case BrainFuck::AUTO_START	: bf.StartAuto(200); mode = bf.AUTO; break;
			case BrainFuck::AUTO		: bf.AutoExec(&outarr[out]);	break;
			default             		: break;
		}
	
	// VIEWMODEL
	// PRG
	sprintf(viewBuf[0], "%-31.31s", "# prg output");
	sprintf(viewBuf[1], "%.16s%.15s", &prgarr[0] , "");
	sprintf(viewBuf[2], "%.16s%.15s", &prgarr[16], "");
	sprintf(viewBuf[3], "%.16s%.15s", &prgarr[32], "");
	sprintf(viewBuf[4], "%.16s%.15s", &prgarr[48], "");

	// INN
	sprintf(viewBuf[5], "%-31.31s", "# inn output");
	sprintf(viewBuf[6], "%04X %04X %04X %04X %.11s",
			innarr[0], innarr[1], innarr[2], innarr[3], "");
	sprintf(viewBuf[7], "%04X %04X %04X %04X %.11s",
			innarr[4], innarr[5], innarr[6], innarr[7], "");
	sprintf(viewBuf[8], "%04X %04X %04X %04X %.11s",
			innarr[8], innarr[9], innarr[10],innarr[11],"");
	sprintf(viewBuf[9], "%04X %04X %04X %04X %.11s",
			innarr[12],innarr[13],innarr[14],innarr[15],"");

	// OUT
	sprintf(viewBuf[10],"%-31.31s", "# out output");
	sprintf(viewBuf[11], "%04X %04X %04X %04X %.11s",
			bf.Memarr(0), bf.Memarr(1), bf.Memarr(2), bf.Memarr(3), "");
	sprintf(viewBuf[12], "%04X %04X %04X %04X %.11s",
			bf.Memarr(4), bf.Memarr(5), bf.Memarr(6), bf.Memarr(7), "");
	sprintf(viewBuf[13], "%04X %04X %04X %04X %.11s",
			bf.Memarr(8), bf.Memarr(9), bf.Memarr(10),bf.Memarr(11),"");
	sprintf(viewBuf[14], "%04X %04X %04X %04X %.11s",
			bf.Memarr(12),bf.Memarr(13),bf.Memarr(14),bf.Memarr(15),"");
	
	// STR
	sprintf(viewBuf[15],"%-31.31s", "# str output");
	for (int i = 0; i < 16; i++) {
		viewBuf[16][i] = (char)bf.Outarr(i     );
		viewBuf[17][i] = (char)bf.Outarr(i + 16);
	}
	
//	sprintf(&viewBuf[2], &prgarr[0]);
			

	// VIEW		//////////////
	View:
		int x, y;
		$(0,0);
		for(int i = 0; i < 18; i++)
			printf("%.31s\n", viewBuf[i]);
		// STRONG
		// PRG
		y = bf.Cmd() / 16 + 2;
		x = bf.Cmd() % 16 + 1;
		$(y, x);
		$Y; printf("%c", prgarr[bf.Cmd()]); $$;
		// MEM
		y = bf.Mem() / 4 + 12;
		x =(bf.Mem() % 4) * 5 + 1;
		$(y, x);
		$Y; printf("%04X", bf.Memarr(bf.Mem())); $$;
		// INN
		y = bf.Inn() / 4 + 7;
		x =(bf.Inn() % 4) * 5 + 1;
		$(y, x);
		$Y; printf("%04X", bf.Innarr(bf.Inn())); $$;
		
		fflush(stdout);
		//printf(viewBuf[1]);		
		/*PrgOut(prgarr,		bf.Cmd());
		 *ValOut(bf.Memarr(),	bf.Mem());
		 *StrOut(outarr,		16);
		 */
	//////////////////////////
	}
	
	$(20, 0);
	scanf(NULL, "please any key.");
	return 0;
}
