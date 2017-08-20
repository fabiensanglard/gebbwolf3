MACRO DOFX
  les di,[pcSound]       ; PC sound effects
  mov ax,es
  or ax,di
  jz @@nopc              ; no PC sound effect going

  mov bl,[es:di]         ; Get the byte
  inc [WORD PTR pcSound] ; Increment pointer
  cmp [pcLastSample],bl  ; Is this sample same as last?
  jz @@pcsame            ; Yep - don't do anything
  mov [pcLastSample],bl  ; No, save it for next time

  or bl,bl
  jz @@pcoff             ; If 0, turn sounds off
  xor bh,bh
  shl bx,1
  mov bx,[pcSoundLookup+bx] ; Use byte as lookup

  mov al,0b6h            ; Select channel 2 (speaker) timer
  out pcTAccess,al
  mov al,bl
  out pcTimer,al         ; Low byte
  mov al,bh
  out pcTimer,al         ; High byte

  in al , pcSpeaker      ; Turn the speaker & gate on
  or al ,3
  out pcSpeaker ,al