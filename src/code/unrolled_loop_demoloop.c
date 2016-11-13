DemoLoop() {
    StartCPMusic(INTROSONG);
    PG13 ();
    while (1) {
        CA_CacheScreen (TITLEPIC);
        CA_CacheScreen (CREDITSPIC);
        DrawHighScores ();
        PlayDemo (0); 
        GameLoop ();  // 2D phase
        SetupGameLevel ();
        StartMusic ();
        PM_CheckMainMem ();
        PreloadGraphics ();
        DrawLevel (); 
        PlayLoop () ; // 3D phase 
        StopMusic ();
    }
  }    
  Quit("Demo loop exited???");
}