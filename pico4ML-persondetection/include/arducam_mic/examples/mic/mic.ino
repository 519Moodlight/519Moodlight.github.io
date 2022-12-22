
#include "arducam_mic.h"

int16_t g_audio_capture_buffer[512];

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  config.data_buf = g_audio_capture_buffer;
  config.data_buf_size = 512;
  mic_i2s_init(&config);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (isAvailable) {
    isAvailable = 0;
    for (int16_t i : g_audio_capture_buffer) {
      Serial.println(i);
    }
  }
}
