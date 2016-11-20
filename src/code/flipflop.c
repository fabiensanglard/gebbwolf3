void AsmRefresh() {
	for (int =0 ; i < num_columns ; i++) {

        do {
testvertical:
            move_vertically()
            if (hitdoor)
                HitVertDoor();
            if (hitwall)
                HitVertWall();
            if (needed)
            	goto testhorizontal;
        } while (1);

		continue;

		do {
testhorizontal:
            move_horizontaly()
            if (hitdoor)
                HitHorizDoor();
            if (hitwall)
                HitHorizWall();
            if (needed)
            	goto testvertical;            
        } while (1);
	}
}