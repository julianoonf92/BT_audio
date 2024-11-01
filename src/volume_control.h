#ifndef VOLUME_CONTROL_H
#define VOLUME_CONTROL_H

#include "dependencies.h"

class A2DPLogarithmicVolumeControl : public A2DPVolumeControl {
public:
    A2DPLogarithmicVolumeControl(float ym = 0.1) : ym(ym) {
        volumeFactorMax = 1.0f;
        currentVolume = 1.0f;
    }

    void update_audio_data(Frame* data, uint16_t frameCount) override {
        if (data != nullptr && frameCount > 0 && is_volume_used) {
            float logVolume = getLogVolumeFactor();
            for (int i = 0; i < frameCount; i++) {
                data[i].channel1 = static_cast<int32_t>(data[i].channel1 * logVolume);
                data[i].channel2 = static_cast<int32_t>(data[i].channel2 * logVolume);
            }
        }
    }

    void set_volume(uint8_t volume) override {
        currentVolume = static_cast<float>(volume) / 127.0f;
    }

    float getVolumeFactor() {
        return getLogVolumeFactor();
    }

private:
    float getLogVolumeFactor() {
        float b = pow(((1/ym)-1), 2);
        float a = 1.0f / (b - 1.0f);
        float volumeFactor = pow(b, currentVolume) * a - a;
        return limit(volumeFactor);
    }

    float limit(float in) {
        if (in < 0.0f) return 0.0f;
        if (in > 1.0f) return 1.0f;
        return in;
    }

    float ym;
    float currentVolume;
};

#endif // VOLUME_CONTROL_H