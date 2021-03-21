#ifndef BOARD_H_
#define BOARD_H_

#include "Ball.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

namespace pong 
{
  class Board: public sf::Drawable
  {
    public:
      Board(sf::Vector2<unsigned int> resolution, sf::Vector2f size, sf::Vector2f scale);
      void moveLeft(float deltaTime);
      void moveRight(float deltaTime);
      virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;
      sf::Vector2f getPosition();
      float getWidth();
      float getLength();
      bool intersects(Ball ball);
      float getSpeed();
      void setSpeed(float newSpeed);
    private:
      sf::Sprite mSprite;
      sf::Texture mSource;
      float speed;
      const sf::Vector2f scale;
  };
}

#endif



