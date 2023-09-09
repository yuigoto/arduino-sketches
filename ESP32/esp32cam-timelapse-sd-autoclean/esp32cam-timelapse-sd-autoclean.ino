/**
 * ESP32CAM TIMELAPSE STANDALONE PROGRAM
 * ----------------------------------------------------------------------
 * Records a timelapse using an ESP32-CAM board, saves pictures on a 
 * micro SD card. Automatically handles deletion of the oldest files 
 * after reaching the max file cap.
 * 
 * @author  Fabio Y. Goto <lab@yuiti.dev>
 * @version 0.0.1
 */
#include <SD_MMC.h>
#include "esp_camera.h"
#include "FS.h"
#include "ESP32CAM_PINOUT.h"

#define MINUTES_DELAY   0.25

bool initSdCard() {
  Serial.println("[INFO]: Initializing MicroSD Card");

  // PIN 13 pull up required
  // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/sd_pullup_requirements.html#pull-up-conflicts-on-gpio13
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  if(SD_MMC.begin("/sdcard", true)) {
    Serial.println("[INFO]: Successfully initialized SD Card");
    return true;
  } else {
    Serial.println("[ERROR]: Failed to initialize SD Card");
    return false;
  }
}

bool initCamera() {
  Serial.println("[INFO]: Initializing Camera");

  // Turn off flash light
  pinMode(FLASH_PIN, OUTPUT);
  digitalWrite(FLASH_PIN, LOW);

  // Initialize camera hardware
  camera_config_t CAMERA_CONFIG;
  CAMERA_CONFIG.ledc_channel = LEDC_CHANNEL_0;
  CAMERA_CONFIG.ledc_timer = LEDC_TIMER_0;
  CAMERA_CONFIG.pin_d0 = Y2_GPIO_NUM;
  CAMERA_CONFIG.pin_d1 = Y3_GPIO_NUM;
  CAMERA_CONFIG.pin_d2 = Y4_GPIO_NUM;
  CAMERA_CONFIG.pin_d3 = Y5_GPIO_NUM;
  CAMERA_CONFIG.pin_d4 = Y6_GPIO_NUM;
  CAMERA_CONFIG.pin_d5 = Y7_GPIO_NUM;
  CAMERA_CONFIG.pin_d6 = Y8_GPIO_NUM;
  CAMERA_CONFIG.pin_d7 = Y9_GPIO_NUM;
  CAMERA_CONFIG.pin_xclk = XCLK_GPIO_NUM;
  CAMERA_CONFIG.pin_pclk = PCLK_GPIO_NUM;
  CAMERA_CONFIG.pin_vsync = VSYNC_GPIO_NUM;
  CAMERA_CONFIG.pin_href = HREF_GPIO_NUM;
  CAMERA_CONFIG.pin_sscb_sda = SIOD_GPIO_NUM;
  CAMERA_CONFIG.pin_sscb_scl = SIOC_GPIO_NUM;
  CAMERA_CONFIG.pin_pwdn = PWDN_GPIO_NUM;
  CAMERA_CONFIG.pin_reset = RESET_GPIO_NUM;
  CAMERA_CONFIG.xclk_freq_hz = 20000000;
  CAMERA_CONFIG.pixel_format = PIXFORMAT_JPEG;

  // Set resolution according to extra memory available
  if (psramFound()) {
    Serial.println("[INFO]: PSRAM available. Maximum XGA resolution supported");
    CAMERA_CONFIG.frame_size = FRAMESIZE_XGA;
    CAMERA_CONFIG.jpeg_quality = 10;
    CAMERA_CONFIG.fb_count = 2;
  } else {
    Serial.println("[WARN]: No PSRAM available. Maximum SVGA resolution supported");
    CAMERA_CONFIG.frame_size = FRAMESIZE_SVGA;
    CAMERA_CONFIG.jpeg_quality = 12;
    CAMERA_CONFIG.fb_count = 1;
  }

  // Start camera
  Serial.println("[INFO]: Starting camera...");
  esp_err_t ERROR = esp_camera_init(&CAMERA_CONFIG);

  if (ERROR != ESP_OK) {
    Serial.println("[ERROR]: Could not initialize camera");
    return false;
  } else {
    Serial.println("[INFO]: Successfully initialized");
    return true;
  }
}

void takePhoto(String filename) {
  // Take photo and get data
  camera_fb_t *BUFFER = esp_camera_fb_get();
  if (!BUFFER) {
    Serial.println("[ERROR]: Unable to take photo");
    return;
  }

  // Make sure it is JPEG
  if (BUFFER->format != PIXFORMAT_JPEG) {
     Serial.println("[ERROR]: Capture format is not JPEG");

     // Return buffer photo data
     esp_camera_fb_return(BUFFER);
     return;
  }

  // Save to SD Card
  File file = SD_MMC.open(filename.c_str(), "w");
  if (file) {
    Serial.println("[INFO]: Saving file " + filename);
    file.write(BUFFER->buf, BUFFER->len);
    file.close();

    // [OPTIONAL] Momentarily blink flash light
    // digitalWrite(FLASH_PIN, HIGH);
    // delay(100);
    // digitalWrite(FLASH_PIN, LOW);
    // delay(500);
  } else {
    Serial.println("[ERROR]: Unable to write " + filename);
  }

  // Return picture
  esp_camera_fb_return(BUFFER);
}

void countAndDeleteOldest(int count) {
  if (count < 6000) {
    return;
  }

  File root = SD_MMC.open("/");
  if (!root) {
    Serial.println("[WARN]: Could not open root dir");
    return;
  }

  if (!root.isDirectory()) {
    Serial.println("[WARN]: Root provided is not a directory");
    return;
  }

  // Count files
  File file = root.openNextFile();
  Serial.println(file.path());
  int fileCount = 0;
  while (file) {
    if (!file.isDirectory()) {
      fileCount++;
    }
    
    file = root.openNextFile();
  }
  Serial.println(fileCount);
  root.close();

  if (fileCount > 40) {
    root = SD_MMC.open("/");
    file = root.openNextFile();
    Serial.print("[INFO]: Deleting ");
    Serial.println(file.path());
    SD_MMC.remove(file.path());
  }
}

void setup() {
  static int fileCount = 0;
  static int picsCount = 0;

  // Initialize the peripherals
  Serial.begin(9600);
  while(!Serial) delay(100);

  // Bootstrap everything
  initSdCard();
  initCamera();

  // Delay 5 seconds before first photo
  delay(5000);
}

void loop() {
  // Keep a count of the number of photos we've taken
  static int number = 0;
  number++;

  // Construct a filename like `PHOTO_000001.jpg`
  String filename = "/PHOTO_";
  if(number < 100000) filename += "0";
  if(number < 10000) filename += "0";
  if(number < 1000) filename += "0";
  if(number < 100)  filename += "0";
  if(number < 10)   filename += "0";
  filename += number;
  filename += ".jpg";

  // Take photo and wait until the next
  takePhoto(filename);

  // Count and delete oldest file
  countAndDeleteOldest(number);

  // Delay based on the constant value
  delay(MINUTES_DELAY * 60 * 1000);
}
