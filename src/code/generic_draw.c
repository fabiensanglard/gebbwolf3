void scaleTextureToHeight(int height, void* src, void* dst)
{
  // Variables here ...
  for (int cursor=0 ; cursor<height ; cursor++) {
  	// Calculations
  	if (shouldWritePixel()) {
  	  fixed_t texture_offset = ... * curor;
  	  fixed_t dst_offset = ...;
  	  dst[dst_offset>>3] = src[texture_offset>>3];
  	}
  }
}