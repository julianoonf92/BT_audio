#ifndef BT_H
#define BT_H


#include "display.h"

void avrc_metadata_callback(uint8_t id, const uint8_t *text) {
  Serial.printf("==> AVRC metadata rsp: attribute id 0x%x, %s\n", id, text);
  switch (id) {
    case ESP_AVRC_MD_ATTR_TITLE:
      title = String((char*)text);
      break;
    case ESP_AVRC_MD_ATTR_ARTIST:
      artist = String((char*)text);
      break;
    case ESP_AVRC_MD_ATTR_ALBUM:
      album = String((char*)text);
      break;
    case ESP_AVRC_MD_ATTR_PLAYING_TIME:
      durTime = String((char*)text).toInt();
      break;
  }
  updateDisplay();
}

void sampleRateCallback(uint16_t rate) {
  sample_rate = rate;
}

void read_data_stream(const uint8_t *data, uint32_t length) {
  i2s.write(data, length);
}

void playPositionCallback(uint32_t play_pos) {
  playtime = play_pos;
}

void playbackStatusCallback(esp_avrc_playback_stat_t Playing) {
  isPlaying = Playing;
}

void setupBT() {
  a2dp_sink.set_avrc_metadata_attribute_mask(ESP_AVRC_MD_ATTR_TITLE | ESP_AVRC_MD_ATTR_ARTIST | ESP_AVRC_MD_ATTR_ALBUM | ESP_AVRC_MD_ATTR_PLAYING_TIME );
  a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
  a2dp_sink.set_avrc_rn_playstatus_callback(playbackStatusCallback);
  a2dp_sink.set_avrc_rn_play_pos_callback(playPositionCallback, 1);
  a2dp_sink.set_sample_rate_callback(sampleRateCallback);
  a2dp_sink.set_stream_reader(read_data_stream, false);
  a2dp_sink.set_volume_control(&vc);

  auto cfg = i2s.defaultConfig();
  cfg.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT;
  cfg.sample_rate = 44100;
  cfg.channels = 2;
  cfg.buffer_count = 8;
  cfg.buffer_size = 512;
  cfg.pin_ws = 15;      //LCK
  cfg.pin_bck = 14;     //BCK
  cfg.pin_data = 25;    //DIN
  cfg.pin_data_rx = 26; //MIC
  cfg.pin_mck = 0;      //SCK

  if (PDM_OUTPUT) {
    cfg.signal_type = PDM;
  } else {
    cfg.signal_type = Digital;
  }

  i2s.begin(cfg);

}

void parseIRCommand(uint32_t irCode) {
  switch (irCode) {
    case IR_CMD_PLAY_PAUSE:
      if (isPlaying) {
        a2dp_sink.pause();
        Serial.println(Playing);
      } else {
        a2dp_sink.play();
        Serial.println(Playing);
      }
      isPlaying = !isPlaying;
      break;
    case IR_CMD_VOLUME_UP:
      newVolume = min(127, a2dp_sink.get_volume() + (127/100)*5);
      a2dp_sink.set_volume(newVolume);
      preferences.putFloat("volume", newVolume);
      Serial.print(a2dp_sink.get_volume());
      break;
    case IR_CMD_VOLUME_DOWN:
      newVolume = (a2dp_sink.get_volume() > 5) ? a2dp_sink.get_volume() - ((127/100)*5) : 0;
      a2dp_sink.set_volume(newVolume);
      preferences.putFloat("volume", newVolume);
      Serial.print(a2dp_sink.get_volume());
      break;
    case IR_CMD_VOLUME_MUTE:
      if (a2dp_sink.get_volume() > 0) {
        volMute = a2dp_sink.get_volume();
        a2dp_sink.set_volume(0);
        Serial.println(a2dp_sink.get_volume());
      }else{
        a2dp_sink.set_volume(volMute);
        Serial.println(a2dp_sink.get_volume());
      }
      break;
    case IR_CMD_FORWARD:
      a2dp_sink.next();
      break;
    case IR_CMD_BACKWARD:
      a2dp_sink.previous();
      break;
    case IR_CMD_POWER:
      digitalWrite(RELAY_PIN, !digitalRead(RELAY_PIN));
      break;
    default:
      break;
  }
}

#endif // BT_H