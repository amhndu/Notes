#include "AudioQueue.h"
#include <stdexcept>
#include <string>

void throwPortAudioError(const PaError err) {
    if(err == paNoError) {
        return;
    }

    auto errorMessage = std::string("error: portaudio: ") + std::to_string(err) + Pa_GetErrorText(err);
    if (err == paUnanticipatedHostError) {
        const PaHostErrorInfo *hostErrorInfo = Pa_GetLastHostErrorInfo();
        errorMessage += std::string("; host api error = ") + hostErrorInfo->errorText +
                "(" + std::to_string(hostErrorInfo->errorCode) + ") apiType = " +
                std::to_string(hostErrorInfo->hostApiType);
    }

    throw std::runtime_error(errorMessage);
}

AudioQueue::AudioQueue(int sample_rate)
    : m_sample_rate(sample_rate)
    , buffer(2048)
{
    PaError err = Pa_Initialize();

    if (err != paNoError) {
        throwPortAudioError(err);
    }

    m_outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (m_outputParameters.device == paNoDevice) {
        throw std::runtime_error("error: No default output device");
    }

    m_outputParameters.channelCount = 1;
    m_outputParameters.sampleFormat = paInt16;
    m_outputParameters.suggestedLatency = Pa_GetDeviceInfo(m_outputParameters.device)->defaultLowOutputLatency;
    m_outputParameters.hostApiSpecificStreamInfo = nullptr;

    auto streamCallback = [](
        const void *input,
        void *output,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo *timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData) {
            return reinterpret_cast<AudioQueue*>(userData)->audioCallback(input, output, frameCount, timeInfo, statusFlags);
    };

    err = Pa_OpenStream(
        &m_stream,
        nullptr,
        &m_outputParameters,
        m_sample_rate,
        paFramesPerBufferUnspecified,
        paClipOff,
        streamCallback,
        this);

    if(err != paNoError) {
        throwPortAudioError(err);
    }
}


AudioQueue::~AudioQueue() {
    Pa_CloseStream(m_stream);
    // if( err != paNoError ) throwPortAudioError(err)
    Pa_Terminate();
}

void AudioQueue::push_sample(std::uint16_t sample) {

}

int AudioQueue::audioCallback(
    const void *inputBUffer,
    void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags) {

}


bool AudioQueue::start()
{
    if (m_stream == 0)
        return false;

    PaError err = Pa_StartStream(m_stream);
    if (err != paNoError) {
        throwPortAudioError(err);
    }
}


bool AudioQueue::stop()
{
    if (m_stream == 0)
        return false;

    PaError err = Pa_StopStream(m_stream);
    if (err != paNoError) {
        throwPortAudioError(err);
    }
}
