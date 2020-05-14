#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"
#include "SD.h"
#include "HTTPClient.h"

#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"

#include "loudp.h"

AudioGeneratorWAV *wav;
AudioFileSourcePROGMEM *pfile;
AudioOutputI2S *out;

void setup() {
  WiFi.mode(WIFI_OFF); 
  Serial.begin(115200);
  
  Serial.println("Start!");
  audioLogger = &Serial;
  
  while (!SPIFFS.begin(true)) {
    Serial.println("waiting ...");
    delay(100);
  }
  
  // with dma buffer size of 2
  // NOTE: you'll hear a BEEP at the end, because the complete song is played
  out = new AudioOutputI2S(0,0, 2);
  out->SetOutputModeMono(true);
  out->SetGain(0.3);

  wav = new AudioGeneratorWAV();
  pfile = new AudioFileSourcePROGMEM(loudp_wav, sizeof(loudp_wav));
  wav->begin(pfile, out);

  while (wav->isRunning()) {
    wav->loop();
  }

  out->stop();
  delete out;
  delete wav;
  delete pfile;

  delay(1000);

  // with dma buffer size of 16
  // NOTE: no BEEP at the end
  out = new AudioOutputI2S(0,0, 16);
  out->SetOutputModeMono(true);
  out->SetGain(0.3);

  wav = new AudioGeneratorWAV();
  pfile = new AudioFileSourcePROGMEM(loudp_wav, sizeof(loudp_wav));
  wav->begin(pfile, out);

  while (wav->isRunning()) {
    wav->loop();
  }

  out->stop();
  delete out;
  delete wav;
  delete pfile;

}

void loop() {
  delay(1000);
}