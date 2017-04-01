#define	KeyInt		9	// The keyboard ISR number

static void INL_StartKbd(void) {
	INL_KeyHook = NULL;			// no key hook routine

	IN_ClearKeysDown();

	OldKeyVect = getvect(KeyInt);
	setvect(KeyInt,INL_KeyService);
}

static void interrupt INL_KeyService(void) {
  byte	k;
  k = inportb(0x60);	// Get the scan code

  // Tell the XT keyboard controller to clear the key
  outportb(0x61,(temp = inportb(0x61)) | 0x80);
  outportb(0x61,temp);

  [...] // Process scan code.
  Keyboard[k] = XXX;

  outportb(0x20,0x20); // ACK interrupt to interrupt system.
}
