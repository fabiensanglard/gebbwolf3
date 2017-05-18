#define    sbOut(n,b)    outportb((n) + sbLocation,b)

#define    sbpMixerAddr    0x204    
#define    sbpMixerData    0x205    

//    SBPro Mixer addresses
#define    sbpmVoiceVol    0x04

static void SDL_PositionSBP(int leftpos,int rightpos) {
    byte    v;

    if (!SBProPresent)
        return;

    leftpos = 15 - leftpos;
    rightpos = 15 - rightpos;
    v = ((leftpos & 0x0f) << 4) | (rightpos & 0x0f);

    asm    pushf
    asm    cli

    sbOut(sbpMixerAddr,sbpmVoiceVol);
    sbOut(sbpMixerData,v);

    asm    popf
}