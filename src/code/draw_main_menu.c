void DrawMainMenu(void)
{
	ClearMScreen();   // Turn screen to red

	VWB_DrawPic(112,184,C_MOUSELBACKPIC);  // Bottom image
	DrawStripes(10);                       // Draw black strip
	VWB_DrawPic(84,0,C_OPTIONSPIC);        // OPTION image
    ...
	DrawMenu(&MainItems,&MainMenu[0]);
	VW_UpdateScreen();
}
