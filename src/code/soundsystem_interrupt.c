#define	TickBase	70

static void SDL_SetTimerSpeed(void) {
	word	rate;
	void interrupt	(*isr)(void);

	if (DigiMode == PCSpeaker) && DigiPlaying) { 
		rate = TickBase * 100;     // 7000 Hz
		isr = SDL_t0ExtremeAsmService;
	}
	else if (music || ((DigiMode == Dss) && DigiPlaying) {   
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