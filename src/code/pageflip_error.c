  asm  mov  cx, startScanOffset 

  asm  mov  dx,0x3d4   ; 3d4h  is the CRTC register

  asm  mov  al,0xc     ; Tell the CRTC we want to update 
  asm  out  dx,al      ;  the start address high register
  asm  inc  dx
  asm  mov  al,ch
  asm  out  dx,al      ; set the high byte

  
  ;*********** CRTC SCAN START HERE  !!!!!!!!! *******
  ;*********** AND SHOW 2 PARTIAL FRAMEBUFFERS *******
  

  asm  mov  al,0xd     ; Tell the CRTC we want to update 
  asm  out  dx,al      ; start address low register
  asm  inc  dx
  asm  mov  al,cl
  asm  out  dx,al      ; set the low byte