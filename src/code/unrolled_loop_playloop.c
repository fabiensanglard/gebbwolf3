void PlayLoop () {
  PollControls ();         // Get player input

  MoveDoors ();            // Move doors
  MovePWalls ();           // Move secret wall
  for (obj = player; obj; obj = obj->next)
    DoActor (obj);         // Enemies think

  ThreeDRefresh () {       // Render 3D view
    VGAClearScreen ();      // Draw floor/ceiling
    WallRefresh ();         // Draw walls
    DrawScaleds();          // draw scaled stuff
    DrawPlayerWeapon ();    // draw weapon
    [...]  // Flip framebuffer via CRT Controller
  }
  UpdateSoundLoc ();        // Stereo sound loc
}
       