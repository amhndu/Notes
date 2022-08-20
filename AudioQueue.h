#pragma once
#include <cstdint>
#include <vector>
#include <array>
#include <portaudio.h>
#include <atomic>

class AudioQueue {

public:
    AudioQueue(int sample_rate);
    ~AudioQueue();
    void push_sample(std::uint16_t sample);

    bool start();
    bool stop();

private:
    void init();

    int AudioQueue::audioCallback(
        const void *inputBUffer,
        void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags);

    PaStreamParameters m_outputParameters;
    PaStream *m_stream;
    int m_sample_rate;

    std::array<std::vector<std::uint16_t>, 2> m_buffers;
    std::size_t active_buffer = 0;
};
