void AsmRefresh() {
    
    for (int i=0 ; i < pixx ; i++) {
        short angle=midangle+pixelangle[pixx];
        // Setup xstep and ystep based on angle.
        do {
            if (needed)
                goto testhorizontal;

testvertical:
            move_vertically()
            if (hitdoor)
                HitVertDoor();
            if (hitwall)
                HitVertWall();
        } while (1);

        continue;

        do {
            if (needed)
                goto testvertical;  

testhorizontal:
            move_horizontaly()
            if (hitdoor)
                HitHorizDoor();
            if (hitwall)
                HitHorizWall();
         
        } while (1);
    }
}