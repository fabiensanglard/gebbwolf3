void scaleTextureToHeight(int height, void* src, void* dst){
  fixed_t steps = ...;
  for (int cursor=0;i<steps;steps++) {
  	int texture_offset = ...;
  	int dst_offset = ...;
  	dst[dst_offset] = src[texture_offset];
  }
}