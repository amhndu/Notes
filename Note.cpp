#include "Note.h"
#include <cmath>
#include <iostream>

Note::Note(const double rate, const double freq, const double amp, const double note_dur) :
    m_sampleRate(rate),
    m_frequency(freq),
    m_amplitude(amp),
    m_duration(note_dur)
{
}

void Note::setFrequency(const double frequency)
{
    m_frequency = frequency;
}


void Note::generate()
{
    std::vector<sf::Int16> samples(m_sampleRate * m_duration / 1000);
    AddNote(m_frequency, m_amplitude, samples);
    //Add in some harmonics
    AddNote(m_frequency * 2, m_amplitude * 0.2, samples);
    AddNote(m_frequency * 4, m_amplitude * 0.01, samples);
    AddNote(m_frequency * 8, m_amplitude * 0.001, samples);
    m_buffer.loadFromSamples(&samples[0], samples.size(), 1, m_sampleRate);
    m_noteSound.setBuffer(m_buffer);
}

void Note::play()
{
    if (m_noteSound.getStatus() != sf::Sound::Playing)
        m_noteSound.play();
}

void Note::stop()
{
    m_noteSound.stop();
}

sf::Int16 Note::getPlayingSample()
{
    if (m_noteSound.getStatus() == sf::Sound::Playing)
    {
        auto offset = m_noteSound.getPlayingOffset();
        return m_buffer.getSamples()[static_cast<int>(offset.asSeconds() *  m_sampleRate)];
    }
    else
        return 0;
}

void Note::AddNote(const double frequency, const double amplitude, std::vector<sf::Int16>& samples, const std::size_t position)
{
    if (position + m_sampleRate * m_duration / 1000 >= samples.size())
        samples.resize(position + m_sampleRate * m_duration / 1000);

    for (size_t i = position; i < position + m_sampleRate * m_duration / 1000; ++i)
    {
        //Fade in/out sinusoidally
        double amp = amplitude * std::sin(M_PI * ((i - position) / (m_sampleRate * m_duration / 1000)));
        //Waveform = sin ( 2 * PI * wavelengths)
        samples[i] +=  amp * std::sin((2 * M_PI * i * frequency) /
                                        m_sampleRate);
    }
}
