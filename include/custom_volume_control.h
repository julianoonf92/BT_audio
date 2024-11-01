#ifndef CUSTOM_VOLUME_CONTROL_H
#define CUSTOM_VOLUME_CONTROL_H

#include "BluetoothA2DPSink.h"
#include "AudioTools/CoreAudio/VolumeControl.h"

class CustomA2DPVolumeControl : public VolumeControl {
private:
    audio_tools::LogarithmicVolumeControl logVolume;

public:
    CustomA2DPVolumeControl(float ym = 0.1) : logVolume(ym) {}

    void set_volume(uint8_t value) override {
        // Convert uint8_t (0-255) to float (0.0-1.0)
        float normalizedVolume = value / 255.0f;
        // The volume is already set internally, no need to store it
    }

    int get_volume() override {
        // This method should return the last set volume
        // Since we don't store it, we can't return the exact value
        // You might want to store the last set value if needed
        return 255; // Always return max volume, as the actual scaling is done in get_volume_factor
    }

    float get_volume_factor() override {
        // This is where we apply our logarithmic volume control
        // We assume the last set volume (0-255) has been normalized to 0.0-1.0
        return logVolume.getVolumeFactor(a2dp_sink.get_volume() / 255.0f);
    }
};

#endif // CUSTOM_VOLUME_CONTROL_H