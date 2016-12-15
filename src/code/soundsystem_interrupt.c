#define	TickBase	70

static void SDL_SetTimerSpeed(void) {
	word	rate;
	void interrupt	(*isr)(void);

	if (A) {
		rate = TickBase * 100;
		isr = SDL_t0ExtremeAsmService;
	}
	else if (B) {
		rate = TickBase * 10;
		isr = SDL_t0FastAsmService;
	}
	else {
		rate = TickBase * 2;
		isr = SDL_t0SlowAsmService;
	}

	setvect(8,isr);
	SDL_SetIntsPerSec(rate);
}