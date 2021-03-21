#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include "Board.hpp"
#include "Ball.hpp"
using namespace pong;

int main()
{
  sf::Vector2<unsigned int> resolution(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
  sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "2k Pong");
  sf::Vector2f scale(resolution.x/1920.f, resolution.y/1080.f);

  Board board(resolution, sf::Vector2f(256,64), scale);
  Ball ball(resolution, 48.f, scale);
  ball.setAngle(std::rand() % 360);
  ball.setSpeed(400.f);
  board.setSpeed(400.f);

  bool left_pressed = false;
  bool right_pressed = false;
  bool game_start = false;

  sf::Clock clock;

  while(window.isOpen())
  {
    sf::Event event;
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
        window.close();
      if(event.type == sf::Event::Resized)
      {
        window.setSize(resolution);
        window.setView(sf::View(sf::FloatRect(0.f, 0.f, resolution.x, resolution.y)));
      }
      if(event.type == sf::Event::KeyPressed)
      {
        if(event.key.code == sf::Keyboard::A)
        {
          left_pressed = true;
        }
        if(event.key.code == sf::Keyboard::D)
        {
          right_pressed = true;
        }
      }
      if(event.type == sf::Event::KeyReleased)
      {
        if(event.key.code == sf::Keyboard::A)
          left_pressed = false;
        if(event.key.code == sf::Keyboard::D)
          right_pressed = false;
        if(event.key.code == sf::Keyboard::Space && !game_start)
          game_start = true;
      }
    }

    float deltaTime = clock.restart().asSeconds();

    if(game_start)
    {
      if(left_pressed && !right_pressed)
        board.moveLeft(deltaTime);
      else if(!left_pressed && right_pressed)
        board.moveRight(deltaTime);

      ball.move(deltaTime);

      // Detect touching edges
      if(ball.getPosition().x + ball.getRadius() > resolution.x) // right
      {
        ball.setAngle(180 - ball.getAngle());
        ball.move(deltaTime);
      }
      if(ball.getPosition().y + ball.getRadius() > resolution.y) // bottom
      {
        return 0;
        // ball.setAngle(-ball.getAngle());
        // ball.setPosition(ball.getPosition().x, ball.getPosition().y - ball.getRadius());
      }
      if(ball.getPosition().x - ball.getRadius() < 0) //left
      {
        ball.setAngle(180 - ball.getAngle());
        ball.move(deltaTime);
      }
      if(ball.getPosition().y - ball.getRadius() < 0) //top
      {
        ball.setAngle(-ball.getAngle());
        ball.move(deltaTime);
      }
      //detect intersection with paddle
      if(board.intersects(ball))
      {
        ball.setAngle(std::rand() * - 30 - 45);
        ball.setPosition(ball.getPosition().x, board.getPosition().y - board.getWidth()/2 - ball.getRadius());
        ball.move(deltaTime);
        board.setSpeed(ball.getSpeed());
      }
    }
    window.clear(sf::Color::Black);
    ball.draw(window);
    board.draw(window);
    window.display();
  }
  return 0;
}
