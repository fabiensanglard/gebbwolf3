void scaleTextureToHeight (int height , void * src , void * dst ){
  fixed_t src_cursor = 0;  // 24:8 format
  int dest_cursor = 0;
  fixed_t step = FixedDiv(64, height);
  while (height > 0) {
    if (dst_not_clipped(dest_cursor)) {
      dst[dest_cursor] = src [ src_cursor >> 8];
    }
    src_cursor += step;
    height--;
    dest_cursor++;
  }
}