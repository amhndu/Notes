#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include "Note.h"
#include <SFML/Graphics.hpp>
#define LINE_LOG {std::cout << "Line : " << __LINE__ << " was executed" << std::endl;}

#define MAX_AMPLITUDE (std::numeric_limits<sf::Int16>::max())

int main()
{
    const double sample_rate = 441000;
    const std::vector<double> note_frequencies(
            { 392.00, 440.00, 493.88, 523.25, 587.33, 659.25, 698.46, 783.99, 880.00, 987.77 });
//             { 440.00, 466.16, 493.88, 523.25, 554.37, 587.33, 622.25, 659.26, 698.46, 739.99, 783.99 });
    std::vector<Note> notes(note_frequencies.size(), {sample_rate, note_frequencies[0], MAX_AMPLITUDE / 4, 300});
    std::cout << "Generating notes...\n";
    for (std::size_t i = 0; i < notes.size(); ++i)
    {
        notes[i].setFrequency(note_frequencies[i]);
        notes[i].generate();
        std::cout << "\b\b\b" << i * 100 / (notes.size() - 1) << '%' << std::flush;
    }
    std::cout << "\nGenerated." << std::endl;

    sf::RenderWindow window(sf::VideoMode(500, 100), "Note player");
    std::vector<sf::Vertex> waveform(window.getSize().x);
    for (std::size_t i = 0; i < waveform.size(); ++i)
    {
        waveform[i].color = sf::Color(50, 50, 50);
        waveform[i].position = {static_cast<float>(i), static_cast<float>(window.getSize().y / 2)};
    }

    sf::Clock timer;

    const std::string keys_layout[] = {"1234567890",
                                        "QWERTYUIOP",
                                         "ASDFGHJKL;",
                                          "ZXCVBNM,./"};
    while(window.isOpen())
    {
        sf::Event winEvent;
        while (window.pollEvent(winEvent))
        {
            switch (winEvent.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                {
                    if (winEvent.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }
                    else if (winEvent.key.code >= sf::Keyboard::A && winEvent.key.code <= sf::Keyboard::Z)
                    {
                        for (auto keys : keys_layout)
                        {
                            auto pos = keys.find(winEvent.key.code - sf::Keyboard::A + 'A');
                            if (pos != std::string::npos)
                            {
                                notes[pos].play();
                            }
                        }
                    }
                    else if (winEvent.key.code == sf::Keyboard::SemiColon)
                    {
                        notes[9].play();
                    }
                    else if (winEvent.key.code == sf::Keyboard::Comma)
                    {
                        notes[7].play();
                    }
                    else if (winEvent.key.code == sf::Keyboard::Period)
                    {
                        notes[8].play();
                    }
                    else if (winEvent.key.code == sf::Keyboard::Slash)
                    {
                        notes[9].play();
                    }
                    else if (winEvent.key.code >= sf::Keyboard::Num1 && winEvent.key.code <= sf::Keyboard::Num9)
                    {
                        auto pos = keys_layout[0].find(winEvent.key.code - sf::Keyboard::Num0 + '0');
                        if (pos != std::string::npos)
                        {
                            notes[pos].play();
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
        if (timer.getElapsedTime() > sf::milliseconds(1))
        {
            for (std::size_t i = 0; i < waveform.size() - 1; ++i)
            {
                waveform[i].position.y = waveform[i+1].position.y;
            }
            float value = 0;
            for (auto& note: notes)
            {
                value += note.getPlayingSample();
            }
            value = (value > MAX_AMPLITUDE ? MAX_AMPLITUDE : value);
            value = window.getSize().y / 2 * (1 + value / MAX_AMPLITUDE);
//             for (std::size_t i = 0; i < waveform.size() - 1; ++i)
//             {
//                 waveform[i].position.y = value;
//             }

            waveform[waveform.size() - 1].position.y = value;
            timer.restart();
        }

        window.clear(sf::Color::White);
        window.draw(&waveform[0], waveform.size(), sf::Lines);
        window.display();
    }
    return 0;
}
