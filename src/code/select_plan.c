#define SC_MAPMASK 0x02

void selectPlane(char plane) {
  outp(SC_INDEX, SC_MAPMASK);
  outp(SC_DATA, 1 << plane);
}