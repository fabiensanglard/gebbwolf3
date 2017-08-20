word			pcSoundLookup[255];

void SD_Startup(void) {
  [...]
  for (i = 0;i < 255;i++) {
    pcSoundLookup[i] = i * 60;
  }
}