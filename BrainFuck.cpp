class BrainFuck {
// define
public:
	static const int MAX = 2048;
	enum Mode { END, BEGIN, ALL, STEP, AUTO, AUTO_START, ESC };
private:

// member
public:

private:
	int  memarr[MAX];
	int  mem;
	char cmdarr[MAX];
	int  cmd;
	int  outarr[MAX];
	int  out;
	int  innarr[MAX];
	int  inn;

	int  max;
	bool isAutoRunning;
	int  slp;

// method
private:
	void culc(int num){ memarr[mem]  += num;				}
	void move(int num){ mem			 += num;				}
	void oupt()       { outarr[out++] = memarr[mem];		}
	void inpt()       { memarr[mem]   = innarr[inn++];		}
	void next()       {	if(memarr[mem]) return;
						while (cmdarr[++cmd])
							if(cmdarr[cmd] == ']')
								break;						}
	void back()       { if(!memarr[mem]) return;
						while (--cmd)
							if(cmdarr[cmd] == '[')
								break;
						--cmd;								}
	void skip()		  { do { cmd++; } 
							while(	cmdarr[cmd] == ' ' 
								||	cmdarr[cmd] == '\n' );	}

	void exec() {
		switch(cmdarr[cmd]){
			case '+': culc(+1); break;
			case '-': culc(-1); break;
			case '>': move(+1); break;
			case '<': move(-1); break;
			case '.': oupt()  ; break;
			case ',': inpt()  ; break;
			case '[': next()  ; break;
			case ']': back()  ; break;
			default : break;
		}	skip();
	}

public:
	BrainFuck(){
		mem = cmd = out = inn = max = 0;
		isAutoRunning = false;
	}
	
	int  Cmd()			{ return cmd;							}
	int  Mem()			{ return mem;							}
	int  Out()			{ return out;							}
	int  Inn()			{ return inn;							}
	char Cmdarr(int n)	{ return cmdarr[n];						}
	int  Memarr(int n)	{ return memarr[n];						}
	int  Outarr(int n)	{ return outarr[n];						}
	int  Innarr(int n)	{ return innarr[n];						}
	const char* Cmdarr(){ return (const char *)cmdarr;				}
	const int* Memarr()	{ return (const int  *)memarr;				}
	const int* Outarr()	{ return (const int  *)outarr;				}
	const int* Innarr()	{ return (const int  *)innarr;				}
	bool IsRunning()	{ return (cmdarr[cmd]) && (cmd <= max);	}
	bool IsAutoRunning(){ return isAutoRunning;					}

	void Input(char* str, int* retarr){
		strcpy(cmdarr, str);
		memcpy(innarr, retarr , MAX);
		max = strlen(cmdarr);
	}
	
	void AllExec(int* retarr){
		// command Exec
		while(IsRunning())
			exec();
		
		// output
		memcpy(retarr, outarr, MAX);
	}
	
	void StepExec(int* ret, int* ptr){
		exec();
		*ret = outarr[out];
	}
	
	void AutoExec(int* ret){
		exec();
		*ret = outarr[out];
		//usleep(1);
		
		isAutoRunning = IsRunning();
	}
	
	void StartAuto(int time){
		isAutoRunning = true;
		slp = time;
	}	
};