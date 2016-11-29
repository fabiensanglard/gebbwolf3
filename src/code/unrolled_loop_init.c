void InitGame () {
    MM_Startup ();       // Memory manager

    SignonScreen ();     // Show system configuration

    VW_Startup ();       // 
    IN_Startup ();
    PM_Startup ();       // Page Manager
    PM_UnlockMainMem (); 
    SD_Startup ();       // Sound manager
    CA_Startup ();       // Cache manager
    US_Startup ();       
    InitDigiMap ();
    ReadConfig ();
    CA_CacheGrChunk(STARTFONT); // Load font
    MM_SetLock (&grsegs[STARTFONT],true);
    LoadLatchMem ();         // Load video asset to VRAM
    BuildTables ();          // trig tables
    SetupWalls ();           // ?
}