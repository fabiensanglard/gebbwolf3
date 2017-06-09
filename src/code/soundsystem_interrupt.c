#define	TickBase	70

static void SDL_SetTimerSpeed(void) {
	word	rate;
	void interrupt	(*isr)(void);

	if (PCM_sound) {               // 7000 Hz
		rate = TickBase * 100;
		isr = SDL_t0ExtremeAsmService;
	}
	else if (FM_sound_effects) {   // 700 Hz
		rate = TickBase * 10;
		isr = SDL_t0FastAsmService;
	}
	else {   // beeper             // 140 Hz
		rate = TickBase * 2;
		isr = SDL_t0SlowAsmService;
	}

	setvect(8,isr);
	SDL_SetIntsPerSec(rate);
}