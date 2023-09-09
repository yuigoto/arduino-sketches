const long BAUD_RATE[] = {
  300L,
  600L,
  750L,
  1200L,
  2400L,
  4800L,
  9600L,
  19200L,
  31250L,
  38400L,
  57600L,
  74880L,
  115200L,
  230400L,
  250000L,
  460800L,
  500000L
};

const int BAUD_RATE_MIN = 0;

const int BAUD_RATE_MAX = sizeof(BAUD_RATE) / sizeof(BAUD_RATE[0]);
