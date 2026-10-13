#pragma once
#include "DspUtils.h"

// Stereo delay with high-pass / low-pass filtered feedback.
// process() returns the wet (echo) signal only.
class DelayEngine
{
public:
    void prepare (double sampleRate)
    {
        sr = sampleRate;
        const int maxS = (int) (2.1 * sr) + 8;
        line[0].prepare (maxS);
        line[1].prepare (maxS);
        clear();
        initialised = false;
        lastHp = lastLp = -1.f;
    }

    void clear()
    {
        line[0].clear(); line[1].clear();
        for (auto& b : hp) b.reset();
        for (auto& b : lp) b.reset();
    }

    void setParams (float timeMs, float feedback01, float hpHz, float lpHz)
    {
        timeT = std::min (std::max (timeMs, 1.0f), 2000.f) * 0.001f * (float) sr;
        if (! initialised) { timeSm = timeT; initialised = true; }
        fb = std::min (std::max (feedback01, 0.f), 0.95f);

        if (hpHz != lastHp) { hp[0].highPass (sr, hpHz); hp[1].highPass (sr, hpHz); lastHp = hpHz; }
        if (lpHz != lastLp) { lp[0].lowPass  (sr, lpHz); lp[1].lowPass  (sr, lpHz); lastLp = lpHz; }
    }

    inline void process (float inL, float inR, float& outL, float& outR)
    {
        timeSm += (timeT - timeSm) * 0.0008f;
        const float d = std::max (1.0f, timeSm);

        const float yl = line[0].read (d);
        const float yr = line[1].read (d);
        line[0].write (inL + hp[0].process (lp[0].process (yl)) * fb);
        line[1].write (inR + hp[1].process (lp[1].process (yr)) * fb);
        outL = yl;
        outR = yr;
    }

private:
    double sr = 44100.0;
    DelayLine line[2];
    Biquad hp[2], lp[2];
    float timeT = 22050.f, timeSm = 22050.f, fb = 0.3f;
    float lastHp = -1.f, lastLp = -1.f;
    bool initialised = false;
};
