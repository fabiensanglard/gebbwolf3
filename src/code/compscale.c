unsigned BuildCompScale (int height, byte far *code)
  ...
  work = (t_compscale far *)code;
  code = &work->code[0];

  // mov al,[si+src]
  *code++ = 0x8a;
  *code++ = 0x44;
  *code++ = src;  

  for (;startpix<endpix;startpix++) {
    // mov [es:di+heightofs],al
    *code++ = 0x26;
    *code++ = 0x88;
    *code++ = 0x85;
    *((unsigned far *)code)++ = startpix*SCREENBWIDE;
  }
  // retf
  *code++ = 0xcb;
}
