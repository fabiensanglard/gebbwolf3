WL_MAIN.C  main {
WL_MAIN.C    CheckForEpisodes();
WL_MAIN.C    Patch386 ();
WL_MAIN.C    InitGame () {
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
WL_MAIN.C    DemoLoop() {
               if (tedlevel) {
                 GameLoop(){
                 Quit (NULL);
               }
               StartCPMusic(INTROSONG);
               PG13 ();
               while (1) {
                 CA_CacheScreen (TITLEPIC);
                 CA_CacheScreen (CREDITSPIC);
                 DrawHighScores ();
                 VW_UpdateScreen ();
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
                 }
               }  
             }  
WL_MAIN.C   Quit("Demo loop exited???");
WL_MAIN.C }