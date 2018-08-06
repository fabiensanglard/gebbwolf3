if (virtualreality)
{
	player->angle -= helmetangle;
	if (player->angle < 0)
		player->angle += ANGLES;
}