#include <iostream>
#include <limits>
#include <vector>
#include "Note.h"
#include <SFML/Graphics.hpp>
#define LINE_LOG {std::cout << __LINE__ << " was executed" << std::endl;}

#define MAX_AMPLITUDE (std::numeric_limits<sf::Int16>::max())

int main()
{
    const double sample_rate = 44100;
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
                    LINE_LOG
                    break;
                case sf::Event::LostFocus:
                    focus = false;
                    LINE_LOG
                    break;
            }
        }
        window.clear(sf::Color::White);
        if (focus)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                notes[0].play();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                notes[1].play();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                notes[2].play();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                notes[3].play();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
            {
                notes[4].play();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
            {
                notes[5].play();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
            {
                notes[6].play();
            }
        }
        window.display();
    }
    return 0;
}
