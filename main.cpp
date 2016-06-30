#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include "Note.h"
#include <SFML/Graphics.hpp>
#define LINE_LOG {std::cout << "Line : " << __LINE__ << " was executed" << std::endl;}

#define MAX_AMPLITUDE (std::numeric_limits<sf::Int16>::max())

int main()
{
    const double sample_rate = 441000;
    const double note_frequencies[] = { 440.00, 493.88, 523.25, 587.33, 659.25, 698.46, 783.99 };
    std::vector<Note> notes(7, {sample_rate, note_frequencies[0], MAX_AMPLITUDE / 5, 300});
    for (std::size_t i = 0; i < notes.size(); ++i)
    {
        notes[i].setFrequency(note_frequencies[i]);
        notes[i].generate();
    }

    sf::RenderWindow window(sf::VideoMode(500, 100), "Note player");
    sf::RectangleShape rect({50, 50});
    rect.setFillColor(sf::Color::Cyan);

    bool focus = true;
    const std::string keys_layout[] = {"1234567",
                                        "QWERTYU",
                                         "ASDFGHJ",
                                          "ZXCVBNM"};
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
                case sf::Event::GainedFocus:
                    focus = true;
                    break;
                case sf::Event::LostFocus:
                    focus = false;
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
                                break;
                            }
                        }
                    }
                    else if (winEvent.key.code >= sf::Keyboard::Num1 && winEvent.key.code <= sf::Keyboard::Num9)
                    {
                        auto pos = keys_layout[0].find(winEvent.key.code - sf::Keyboard::Num0 + '0');
                        if (pos != std::string::npos)
                        {
                            notes[pos].play();
                            break;
                        }
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        window.display();
    }
    return 0;
}
