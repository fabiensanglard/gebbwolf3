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