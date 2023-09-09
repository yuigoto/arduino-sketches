int clamp(int value, int min, int max) {
  return max(min(max, value), min);
}
