word INL_GetJoyButtons(word joy){
  register  word  result;

  result = inportb(0x201); // Get all the joystick buttons
  result >>= joy? 6 : 4;   // Shift into bits 0-1
  result &= 3;             // Mask off the useless bits
  result ^= 3;
  return(result);
}