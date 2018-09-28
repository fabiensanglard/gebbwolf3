#define	TickBase	70

typedef	enum {
  sds_Off,
  sds_PC,
  sds_SoundSource,
  sds_SoundBlaster
} SDSMode;

extern	SDSMode	 DigiMode;

static void SDL_SetTimerSpeed(void) {
	word	rate;
	void interrupt	(*isr)(void);

	if ((DigiMode == sds_PC) && DigiPlaying) { 
		rate = TickBase * 100;     // 7000 Hz
		isr = SDL_t0ExtremeAsmService;
	}
	else if (music || ((DigiMode == sds_SoundSource)) 
		&& DigiPlaying) {   
		rate = TickBase * 10;     //  700 Hz
		isr = SDL_t0FastAsmService;
	}
	else {         
		rate = TickBase * 2;      //  140 Hz
		isr = SDL_t0SlowAsmService;
	}
	setvect(8,isr);
	SDL_SetIntsPerSec(rate);
}