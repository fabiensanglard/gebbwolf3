int main (int argc, char *argv[]) {}
CheckForEpisodes();
Patch386 ();
InitGame () {
    MM_Startup ();

    SignonScreen ();

    VW_Startup ();
    IN_Startup ();
    PM_Startup ();
    PM_UnlockMainMem ();
    SD_Startup ();
    CA_Startup ();
    US_Startup ();
    InitDigiMap ();
    ReadConfig ();
    CA_CacheGrChunk(STARTFONT);
    MM_SetLock (&grsegs[STARTFONT],true);
    LoadLatchMem ();
    BuildTables ();          // trig tables
    SetupWalls ();
}
DemoLoop() {
    StartCPMusic(INTROSONG);
    PG13 ();
    while (1) {
        CA_CacheScreen (TITLEPIC);
        CA_CacheScreen (CREDITSPIC);
        DrawHighScores ();
        PlayDemo (0);
        GameLoop () {
            DrawPlayScreen {
            DrawPlayBorder * 3
            DrawFace ();
	          DrawHealth ();
					  DrawLives ();
						DrawLevel ();
						DrawAmmo ();
						DrawKeys ();
						DrawWeapon ();
						DrawScore ();
        }
        SetupGameLevel ();
        StartMusic ();
        PM_CheckMainMem ();
        PreloadGraphics ();
        DrawLevel ();
        PlayLoop () {
          PollControls ();
          MoveDoors ();
          MovePWalls ();
           for (obj = player; obj; obj = obj->next)
            DoActor (obj);

          UpdatePaletteShifts ();

          ThreeDRefresh () {
            // clear out the traced array
            CalcViewVariables();
            VGAClearScreen ();
            WallRefresh ();  
            DrawScaleds();                  // draw scaled stuff
            DrawPlayerWeapon ();    // draw player's hands
          }
          UpdateSoundLoc ();
        }
        StopMusic ();
    }
  }    
  Quit("Demo loop exited???");
}