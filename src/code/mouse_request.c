#define	MouseInt	0x33
#define	Mouse(x)	_AX = x,geninterrupt(MouseInt)

static void INL_GetMouseDelta(int *x,int *y) {
	Mouse(MDelta);
	*x = _CX;
	*y = _DX;
}