if (virtualreality) {
	helmetangle = peek (0x40,0xf0);
	player->angle += helmetangle;
	if (player->angle >= ANGLES)
		player->angle -= ANGLES;
}