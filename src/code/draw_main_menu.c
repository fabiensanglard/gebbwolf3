void DrawMainMenu(void)
{
	ClearMScreen();                  // Turn screen to red
	VWB_DrawPic(112,184,C_MOUSELBACKPIC);  // Bottom image
	DrawStripes(10);                   // Draw black strip
	VWB_DrawPic(84,0,C_OPTIONSPIC);        // OPTION image
	DrawWindow(MENU_X-8,MENU_Y-3,MENU_W,MENU_H,BKGDCOLOR);
    [...]
	DrawMenu(&MainItems,&MainMenu[0]);
	VW_UpdateScreen();
}
