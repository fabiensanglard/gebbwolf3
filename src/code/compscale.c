// Call with
// DS:SI   Source for scale
// ES:DI   Dest for scale
unsigned BuildCompScale (int height, byte far *code)
  [...]
  work = (t_compscale far *)code;
  code = &work->code[0];
  [...]
  for (src=0;src<=64;src++) {

    [...]
    
    // mov al,[si+src]   (Read src into register al)
    *code++ = 0x8a;
    *code++ = 0x44;
    *code++ = src;  

    for (;startpix<endpix;startpix++) {
      // mov [es:di+heightofs],al  (Write al to dest)
      *code++ = 0x26;
      *code++ = 0x88;
      *code++ = 0x85;
      *((unsigned far *)code)++ = startpix*SCREENBWIDE;
    }
  }
  // retf
  *code++ = 0xcb;
}
