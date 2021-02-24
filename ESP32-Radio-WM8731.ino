#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"
#include "Wire.h"

// Digital I/O used
#define I2S_DOUT      22
#define I2S_BCLK      23
#define I2S_LRC       21  
#define I2C_SDA       18
#define I2C_SCL       19

#define WM8731_LINVOL 0x00
#define WM8731_RINVOL 0x01
#define WM8731_LOUT1V 0x02
#define WM8731_ROUT1V 0x03
#define WM8731_APANA  0x04
#define WM8731_APDIGI 0x05
#define WM8731_PWR    0x06
#define WM8731_IFACE  0x07
#define WM8731_SRATE  0x08
#define WM8731_ACTIVE 0x09
#define WM8731_RESET  0x0f


void wm8731_i2c_init()
{
  Wire.begin(I2C_SDA, I2C_SCL);
  
  Wire.beginTransmission(0x1a);
  Wire.write(uint8_t(WM8731_PWR << 1) | (0x80 >> 8));
  Wire.write(uint8_t(0x80 & 0xff));
  Wire.endTransmission();
  
  Wire.beginTransmission(0x1a);
  Wire.write(uint8_t(WM8731_RESET << 1) | (0x00 >> 8));
  Wire.write(uint8_t(0x00 & 0xff));
  Wire.endTransmission();
  
  Wire.beginTransmission(0x1a);
  Wire.write(uint8_t(WM8731_APANA << 1) | (0x12 >> 8));
  Wire.write(uint8_t(0x12 & 0xff));
  Wire.endTransmission();
  
  Wire.beginTransmission(0x1a);
  Wire.write(uint8_t(WM8731_APDIGI << 1) | (0x00 >> 8));
  Wire.write(uint8_t(0x00 & 0xff));
  Wire.endTransmission();
  
  Wire.beginTransmission(0x1a);
  Wire.write(uint8_t(WM8731_PWR << 1) | (0x00 >> 8));
  Wire.write(uint8_t(0x00 & 0xff));
  Wire.endTransmission();
  
  Wire.beginTransmission(0x1a);
  Wire.write(uint8_t(WM8731_ACTIVE << 1) | (0x00 >> 8));
  Wire.write(uint8_t(0x00 & 0xff));
  Wire.endTransmission();
  
  Wire.beginTransmission(0x1a);
  Wire.write(uint8_t(WM8731_IFACE << 1) | (0x02 >> 8));
  Wire.write(uint8_t(0x02 & 0xff));
  Wire.endTransmission();
  
  Wire.beginTransmission(0x1a);
  Wire.write(uint8_t(WM8731_LINVOL << 1) | (0x17 >> 8));
  Wire.write(uint8_t(0x17 & 0xff));
  Wire.endTransmission();
  
  Wire.beginTransmission(0x1a);
  Wire.write(uint8_t(WM8731_RINVOL << 1) | (0x17 >> 8));
  Wire.write(uint8_t(0x17 & 0xff));
  Wire.endTransmission();
  
  Wire.beginTransmission(0x1a);
  Wire.write(uint8_t(WM8731_LOUT1V << 1) | (0x7F >> 8));
  Wire.write(uint8_t(0x7F & 0xff));
  Wire.endTransmission();
  
  Wire.beginTransmission(0x1a);
  Wire.write(uint8_t(WM8731_ROUT1V << 1) | (0x7F >> 8));
  Wire.write(uint8_t(0x7F & 0xff));
  Wire.endTransmission();
  
  Wire.beginTransmission(0x1a);
  Wire.write(uint8_t(WM8731_ACTIVE << 1) | (0x01 >> 8));
  Wire.write(uint8_t(0x01 & 0xff));
  Wire.endTransmission();

}

Audio audio;

String ssid = "<wifi ssid>";
String password = "<wifi pass>";

void setup() {
    Serial.begin(115200);

    wm8731_i2c_init();
    
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED) delay(1500);
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(15); // 0...21

//    audio.connecttoFS(SD, "/320k_test.mp3");
//    audio.connecttoFS(SD, "test.wav");
//    audio.connecttohost("http://www.wdr.de/wdrlive/media/einslive.m3u");
//    audio.connecttohost("http://macslons-irish-pub-radio.com/media.asx");
//    audio.connecttohost("http://mp3.ffh.de/radioffh/hqlivestream.aac"); //  128k aac
      audio.connecttohost("http://mp3.ffh.de/radioffh/hqlivestream.mp3"); //  128k mp3
//    audio.connecttospeech("Wenn die Hunde schlafen, kann der Wolf gut Schafe stehlen.", "de");
//    audio.connecttohost("http://media.ndr.de/download/podcasts/podcast4161/AU-20190404-0844-1700.mp3"); // podcast
}

void loop() 
{
    audio.loop();
}

// optional
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}
