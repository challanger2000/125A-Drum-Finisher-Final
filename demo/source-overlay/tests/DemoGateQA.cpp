#include "DemoGate.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    using a125::drum::DemoGate;

    constexpr int sampleRate = 2000;
    constexpr int count = 126100;

    std::vector<float> left(count, 1.0f);
    std::vector<float> right(count, 1.0f);
    float* outputs[2] {left.data(), right.data()};

    DemoGate demo;
    demo.configure(sampleRate, false);
    demo.process(outputs, 2, count);

    // Before the 10 ms fade-out, the demo is bit-transparent.
    if (left[119978] != 1.0f || right[119978] != 1.0f)
        return 1;

    // Fade-out is active immediately before 60 s.
    if (!(left[119990] > 0.0f && left[119990] < 1.0f))
        return 2;

    // Middle of the 3 s interruption is silent.
    if (left[122000] != 0.0f || right[122000] != 0.0f)
        return 3;

    // Final 10 ms of the interruption fades back in.
    if (!(left[125990] > 0.0f && left[125990] < 1.0f))
        return 4;

    // New cycle is fully open again.
    if (left[126000] != 1.0f || right[126000] != 1.0f)
        return 5;

    std::fill(left.begin(), left.end(), 1.0f);
    std::fill(right.begin(), right.end(), 1.0f);

    DemoGate full;
    full.configure(sampleRate, true);
    full.process(outputs, 2, count);

    for (int i = 0; i < count; ++i) {
        if (left[i] != 1.0f || right[i] != 1.0f)
            return 6;
    }

    std::cout << "Drum DemoGate PASS\n";
    return 0;
}
