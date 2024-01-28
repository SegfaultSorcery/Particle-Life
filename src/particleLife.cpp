#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include "../include/Particle.hpp"
#include "../include/Particles.hpp"
#include "../include/Field.hpp"
#include "../include/config.hpp"
#include "../include/initParticles.hpp"

float fps;
sf::CircleShape dot;
std::vector<sf::CircleShape> visualgrid;

// Particles particles;

sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Life");

void particleLife(){
    dot.setRadius(0.4);
    for(int i = 0; i < window.getSize().x; i+= thresholdRadius){
        for(int j = 0; j < window.getSize().y; j += thresholdRadius){
            dot.setPosition(sf::Vector2f(i,j));
            visualgrid.push_back(dot);
        }
    }
    // Field field(sf::Vector2f(thresholdRadius*3, thresholdRadius*3), sf::Vector2f(thresholdRadius*4,thresholdRadius*4));
    Field field(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x, window.getSize().y));
    Particles particles;
    Particle p1;
    // p1.setColor(sf::Color::Blue);
    // p1.setPosition(sf::Vector2f(thresholdRadius*3, thresholdRadius*3));
    // p1.addVelocity(sf::Vector2f(50,50));
    // std::vector<Particle> testvec;
    // testvec.push_back(p1);
    // p1.setPosition(sf::Vector2f(thresholdRadius*4, thresholdRadius*4));
    // p1.addVelocity(sf::Vector2f(-100,-100));
    // testvec.push_back(p1);
    // particles.addVector(testvec);
    particles.addVector((initParticles(sf::Color::Yellow, 500, field)));
    particles.addVector((initParticles(sf::Color::Green, 1000, field)));
    particles.addVector((initParticles(sf::Color::Blue, 500, field)));

    particles.addRule(Rule(colorToStr(sf::Color::Blue), colorToStr(sf::Color::Blue), 1));
    particles.addRule(Rule(colorToStr(sf::Color::Green), colorToStr(sf::Color::Green), 0.5));
    particles.addRule(Rule(colorToStr(sf::Color::Yellow), colorToStr(sf::Color::Green), -0.5));
    particles.addRule(Rule(colorToStr(sf::Color::Green), colorToStr(sf::Color::Yellow), 0.5));
    particles.addRule(Rule(colorToStr(sf::Color::Green), colorToStr(sf::Color::Blue), 0.5));
    particles.addRule(Rule(colorToStr(sf::Color::Yellow), colorToStr(sf::Color::Blue), 0.2));

    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    while (window.isOpen()){
        start = std::chrono::high_resolution_clock::now();
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        //draw
        particles.update();
        window.clear();
        for(auto& dot: visualgrid){
            window.draw(dot);
        }
        particles.draw();
        window.display();
        particles.applyRules();
        //rule("red", "blue", 10);
        // applyRules();
        end = std::chrono::high_resolution_clock::now();
        fps = (float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
        std::cout << "fps:" << fps << std::endl;
        window.setFramerateLimit(100);
        // std::cin.get();
    }
}