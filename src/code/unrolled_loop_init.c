void InitGame () {
    MM_Startup ();       // Memory manager

    SignonScreen ();     // Show system configuration

    VW_Startup ();       // Video Manager
    IN_Startup ();       // Input Manager
    PM_Startup ();       // Page Manager
    PM_UnlockMainMem (); 
    SD_Startup ();       // Sound manager
    CA_Startup ();       // Cache manager
    US_Startup ();       // Font manager
    InitDigiMap ();
    ReadConfig ();
    CA_CacheGrChunk(STARTFONT); // Load font
    MM_SetLock (&grsegs[STARTFONT],true);
    LoadLatchMem ();         // Load picture asset to VRAM
    BuildTables ();          // sin/cos/view loopu tables
    SetupWalls ();           // Lookup table wall textures
}