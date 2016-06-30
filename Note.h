#ifndef NOTE_H
#define NOTE_H
#include <SFML/Audio.hpp>
#include <vector>

class Note
{
    public:
        Note(const double rate, const double freq, const double amp, const double note_dur);
        void setFrequency(const double frequency);
        void generate();
        void play();
        void stop();
        sf::Int16 getPlayingSample();
    private:
        void AddNote(const double frequency, const double amplitude, std::vector<sf::Int16>& samples, const std::size_t position = 0);

        double m_sampleRate;
        double m_frequency;
        double m_amplitude;
        double m_duration;
        sf::SoundBuffer m_buffer;
        sf::Sound m_noteSound;
};

#endif // NOTE_H
