void scaleTextureTo2(void* src, void* dst) {
	dst[0] = src[0];
	dst[1] = src[32];
}

void scaleTextureTo4(void* src, void* dst) {
	dst[0] = src[0];
	dst[1] = src[16];
	dst[2] = src[32];
	dst[3] = src[48];
}