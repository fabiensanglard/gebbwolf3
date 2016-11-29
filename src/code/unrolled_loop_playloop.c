void PlayLoop () {
  PollControls ();
  MoveDoors ();
  MovePWalls ();
   for (obj = player; obj; obj = obj->next)
    DoActor (obj);

  UpdatePaletteShifts ();

  ThreeDRefresh () {
    // clear out the traced array
    CalcViewVariables();    
    VGAClearScreen ();      // Draw floor/ceiling
    WallRefresh ();         // Draw walls
    DrawScaleds();          // draw scaled stuff
    DrawPlayerWeapon ();    // draw weapon
    // Flip framebuffer via CRT Controller
  }
  UpdateSoundLoc ();
}
       