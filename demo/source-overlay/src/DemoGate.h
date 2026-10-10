#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace a125::drum {

class DemoGate final {
public:
    void configure(double sampleRate, bool licensed) noexcept {
        licensed_ = licensed;
        sampleRate_ = std::isfinite(sampleRate) && sampleRate > 1000.0
            ? sampleRate : 44100.0;
        normalSamples_ = static_cast<std::uint64_t>(std::llround(sampleRate_ * 60.0));
        muteSamples_ = static_cast<std::uint64_t>(std::llround(sampleRate_ * 3.0));
        fadeSamples_ = std::max<std::uint64_t>(
            1u, static_cast<std::uint64_t>(std::llround(sampleRate_ * 0.010)));
        counter_ = 0;
    }

    template <class Sample>
    void process(Sample** outputs, int channels, int samples) noexcept {
        if (licensed_ || !outputs || channels <= 0 || samples <= 0)
            return;

        const std::uint64_t cycle = normalSamples_ + muteSamples_;
        if (cycle == 0)
            return;

        for (int i = 0; i < samples; ++i) {
            const std::uint64_t pos = counter_ % cycle;
            double gain = 1.0;

            if (pos < normalSamples_) {
                const std::uint64_t remaining = normalSamples_ - pos;
                if (remaining <= fadeSamples_)
                    gain = static_cast<double>(remaining - 1u) /
                           static_cast<double>(fadeSamples_);
            } else {
                const std::uint64_t mutePos = pos - normalSamples_;
                if (mutePos + fadeSamples_ >= muteSamples_) {
                    const std::uint64_t intoFade =
                        mutePos + fadeSamples_ - muteSamples_;
                    gain = std::clamp(
                        static_cast<double>(intoFade + 1u) /
                        static_cast<double>(fadeSamples_),
                        0.0, 1.0);
                } else {
                    gain = 0.0;
                }
            }

            for (int ch = 0; ch < channels; ++ch) {
                if (outputs[ch])
                    outputs[ch][i] =
                        static_cast<Sample>(
                            static_cast<double>(outputs[ch][i]) * gain);
            }
            ++counter_;
        }
    }

private:
    bool licensed_ {false};
    double sampleRate_ {44100.0};
    std::uint64_t normalSamples_ {2646000u};
    std::uint64_t muteSamples_ {132300u};
    std::uint64_t fadeSamples_ {441u};
    std::uint64_t counter_ {0u};
};

} // namespace a125::drum
