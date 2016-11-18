DrawWall( int wallNum ) {
    char name[128];
    texture_t *tex;
    sprintf( name, "walls/%d.tga", wallNum );
    tex = FindTexture( name );
    ...
}
texture_t FindTexture( const char *name ) {     
    int   i;
    for ( i = 0 ; i < numTextures ; i++ ) {
        if ( !strcmp( name, texture[name]->name ) ) {
            return texture[name];
        }
    }
    ...
}