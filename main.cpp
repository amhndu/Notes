#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "Note.h"
#include <SFML/Graphics.hpp>
#define LINE_LOG {std::cout << "Line : " << __LINE__ << " was executed" << std::endl;}

#define MAX_AMPLITUDE (std::numeric_limits<sf::Int16>::max())

#include "spsc.hpp"
#include <thread>
#include <iterator>
#include <cstdlib>

int main()
{
    lockfree::RingBuffer<int> buffer{5};
    buffer.push(1);
    buffer.push(2);
    buffer.push(3);
    buffer.push(4);

    const auto reader_handle = std::thread([&buffer]() {
        std::vector<int> output;
        output.resize(5);

        for (;;)
        {
            auto read = buffer.pop(output.data(), output.size());
            for (; read == 0; read = buffer.pop(output.data(), output.size()))
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            std::cout << "pop " << read << " elements" << std::endl;
            std::copy(output.begin(), output.begin() + read, std::ostream_iterator<int>(std::cout, ", "));
            std::cout << std::endl;
        }

    });

    // for (;;)
    // {
    //     int number = rand();
    //     int sleep_time = rand() % 10000;
    //     std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    //     std::cout << "push: " << number << " " << buffer.push(number) << std::endl;
    // }

    int input;
    while (std::cin >> input)
    {
        const auto ok = buffer.push(input);
        if (!ok)
        {
            std::cout << "not ok" << std::endl;
        }
    }

    std::cout << "exit main" << std::endl;
}

// int main(int argc, char** argv)
// {
//     bool namedinput = false;
//     double sample_rate = 441000;
//     double note_duration = 300;
//     if (argc > 1)
//     {
//         for (auto i = 1; i < argc; ++i)
//         {
//             const auto arg = std::string(argv[i]);
//             if (arg == "--namednotesinput" || arg == "-n")
//             {
//                 namedinput = true;
//                 std::cout << "Using keyboard to input note names instead of positional input" << std::endl;
//             }
//             else if (arg == "--sample-rate" || arg == "-r")
//             {
//                 std::stringstream ss(argv[++i]);
//                 double tmp;
//                 if (ss >> tmp)
//                 {
//                     sample_rate = tmp;
//                 }
//                 else
//                 {
//                     std::cout << "Invalid sample rate input. Defaulting to :" << sample_rate << "per second." << std::endl;
//                 }
//             }
//             else if (arg == "--note-duration" || arg == "-d")
//             {
//                 std::stringstream ss(argv[++i]);
//                 double tmp;
//                 if (ss >> tmp)
//                 {
//                     note_duration = tmp;
//                 }
//                 else
//                 {
//                     std::cout << "Invalid sample rate input. Defaulting to :" << note_duration << "ms." << std::endl;
//                 }
//             }
//             else if (arg == "--help" || arg == "-h")
//             {
//                 std::cout << "Notes is a simple graphical musical notes player.\n"
//                               "Within the window use the keyboard to play. The numeric row and\nalphabetical rows are used."
//                               "Using each row is equivalent, thus 1, Q, A and Z all play the same note.\n"
//                               "The notes get higher from left to right\n\n";
//                 std::cout << "Command line options:\n"
//                            << "Usage ./notes [OPTIONS]\n"
//                            << "--help, -h                        Display this text and exit\n"
//                            << "--note-duration, -d <duration>    Set the note duration in milliseconds\n"
//                            << "                                  (default: 300)\n"
//                            << "--sample-rate, -r <rate>          Set the sample in samples per second, higher\n"
//                            << "                                  means higher quality but also higher load time\n"
//                            << "                                  (default: 441000)\n"
//                            << "--namednotesinput, -n             Input/play notes by their names instead.\n"
//                            << "                                  Available notes: C D E F G A B\n"
//                            << "                                  Don't use this option if you want more notes\n"
//                            << "                                  or the positional input (the default)" << std::endl;
//                 return 0;
//             }
//         }
//     }

//     const std::vector<double> note_frequencies(
//             { 392.00, 440.00, 493.88, 523.25, 587.33, 659.25, 698.46, 783.99, 880.00, 987.77 });
//     const std::string note_mapping = "---CDEFGAB";

//     std::vector<Note> notes(note_frequencies.size(), {sample_rate, note_frequencies[0], MAX_AMPLITUDE / 4, note_duration});
//     std::cout << "Generating notes...\n";
//     for (std::size_t i = 0; i < notes.size(); ++i)
//     {
//         notes[i].setFrequency(note_frequencies[i]);
//         notes[i].generate();
//         std::cout << "\b\b\b" << i * 100 / (notes.size() - 1) << '%' << std::flush;
//     }
//     std::cout << "\nGenerated." << std::endl;

//     sf::RenderWindow window(sf::VideoMode(500, 100), "Note player");
//     std::vector<sf::Vertex> waveform(window.getSize().x);
//     for (std::size_t i = 0; i < waveform.size(); ++i)
//     {
//         waveform[i].color = sf::Color(50, 50, 50);
//         waveform[i].position = {static_cast<float>(i), static_cast<float>(window.getSize().y / 2)};
//     }

//     sf::Clock timer;

//     const std::string keys_layout[] = {"1234567890",
//                                         "QWERTYUIOP",
//                                          "ASDFGHJKL;",
//                                           "ZXCVBNM,./"};
//     while(window.isOpen())
//     {
//         sf::Event winEvent;
//         while (window.pollEvent(winEvent))
//         {
//             switch (winEvent.type)
//             {
//                 case sf::Event::Closed:
//                     window.close();
//                     break;
//                 case sf::Event::KeyPressed:
//                 {
//                     if (winEvent.key.code == sf::Keyboard::Escape)
//                     {
//                         window.close();
//                     }
//                     else if (!namedinput && winEvent.key.code >= sf::Keyboard::A && winEvent.key.code <= sf::Keyboard::Z)
//                     {
//                         for (auto keys : keys_layout)
//                         {
//                             auto pos = keys.find(winEvent.key.code - sf::Keyboard::A + 'A');
//                             if (pos != std::string::npos)
//                             {
//                                 notes[pos].play();
//                             }
//                         }
//                     }
//                     else if (!namedinput && winEvent.key.code == sf::Keyboard::SemiColon)
//                     {
//                         notes[9].play();
//                     }
//                     else if (!namedinput && winEvent.key.code == sf::Keyboard::Comma)
//                     {
//                         notes[7].play();
//                     }
//                     else if (!namedinput && winEvent.key.code == sf::Keyboard::Period)
//                     {
//                         notes[8].play();
//                     }
//                     else if (!namedinput && winEvent.key.code == sf::Keyboard::Slash)
//                     {
//                         notes[9].play();
//                     }
//                     else if (!namedinput && winEvent.key.code >= sf::Keyboard::Num1 && winEvent.key.code <= sf::Keyboard::Num9)
//                     {
//                         auto pos = keys_layout[0].find(winEvent.key.code - sf::Keyboard::Num0 + '0');
//                         if (pos != std::string::npos)
//                         {
//                             notes[pos].play();
//                         }
//                     }
//                     else if (namedinput && winEvent.key.code >= sf::Keyboard::A && winEvent.key.code <= sf::Keyboard::Z)
//                     {
//                         auto pos = note_mapping.find(winEvent.key.code - sf::Keyboard::A + 'A');
//                         if (pos != std::string::npos)
//                             notes[pos].play();
//                     }
//                     break;
//                 }
//                 default:
//                     break;
//             }
//         }
//         if (timer.getElapsedTime() > sf::milliseconds(1))
//         {
//             for (std::size_t i = 0; i < waveform.size() - 1; ++i)
//             {
//                 waveform[i].position.y = waveform[i+1].position.y;
//             }
//             float value = 0;
//             for (auto& note: notes)
//             {
//                 value += note.getPlayingSample();
//             }
//             value = (value > MAX_AMPLITUDE ? MAX_AMPLITUDE : value);
//             value = window.getSize().y / 2 * (1 + value / MAX_AMPLITUDE);

//             waveform[waveform.size() - 1].position.y = value;
//             timer.restart();
//         }

//         window.clear(sf::Color::White);
//         window.draw(&waveform[0], waveform.size(), sf::Lines);
//         window.display();
//     }
//     return 0;
// }
