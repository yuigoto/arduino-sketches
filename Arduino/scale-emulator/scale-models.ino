String CHAR_TOLEDO_STX = "";

String padLeft(int value, unsigned size, String character) {
  String padded = (String) value;

  while (padded.length() < size) {
    padded = character + padded;
  }

  return padded;
}

String SCALE_MODEL_DEFAULT (int value) {
  String returnable = padLeft(value, 10, "0");
  return returnable + "kg\r\n";
}

String SCALE_MODEL_TOLEDO_P03 (int value) {
  String returnable = CHAR_TOLEDO_STX + ")p`" + padLeft(value, 6, "0") + padLeft(0, 6, "0");
  return returnable;
}

String SCALE_MODEL_CONFIANTEC (int value) {
  String returnable = padLeft(value, 6, " ");
  return "i" + returnable + "kg\n\r";
}

String SCALE_MODEL_CONFIANTEC_OLD (int value) {
  String returnable = padLeft(value, 9, " ");
  return "*U\b\b" + returnable + "kg \nÿ";
}

String SCALE_MODEL_JUNDIAI_T21 (int value) {
  String returnable = padLeft(value, 7, "0");
  return "ST,GS,+" + returnable + "kg\r\n";
}

String SCALE_MODEL_JUNDIAI_EPM (int value) {
  String returnable = padLeft(value, 6, " ");
  return "    0" + returnable + "0023/01/202303:1001\r\n";
}

String SCALE_MODEL_JUNDIAI_SP6000 (int value) {
  String returnable = padLeft(value, 7, " ");
  return "    " + returnable + "991" + returnable + "0000000" + "XX\r\n";
}

String SCALE_MODEL_GENOVA (int value) {
  String returnable = padLeft(value, 6, " ");
  return "PB:" + returnable + ".0kg PL:" + returnable + ".0kg T:" + returnable + ".0kg\r\n";
}

String SCALE_MODEL_JUNDIAI_TCA (int value) {
  String returnable = padLeft(value, 7, " ");
  return "PB:" + returnable + "kg PL:" + returnable + "kg T:" + returnable + "kg\r\n";
}
