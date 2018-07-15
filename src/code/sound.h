[...]

boolean	SD_PlaySound(soundnames sound);
        SD_PositionSound(int leftvol,int rightvol);
void    SD_SetPosition(int leftvol,int rightvol);
        SD_StopSound(void);
        SD_WaitSoundDone(void);
word    SD_SoundPlaying(void);
        SD_SetSoundMode(SDMode mode);
				
void    SD_StartMusic(MusicGroup far *music);
        SD_MusicOn(void);
        SD_MusicOff(void);
        SD_FadeOutMusic(void);
boolean SD_MusicPlaying(void);
        SD_SetMusicMode(SMMode mode);
