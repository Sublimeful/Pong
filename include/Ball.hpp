#ifndef BALL_H_
#define BALL_H_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace pong
{
  class Ball: public sf::Drawable
  {
    public:
      Ball(sf::Vector2<unsigned int> resolution, float diameter, sf::Vector2f scale);
      virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;
      void move(float deltaTime);
      const float getRadius();
      void setAngle(float angle);
      float getAngle();
      void setPosition(float x, float y);
      const sf::Vector2f getPosition();
      float getSpeed();
      void setSpeed(float newSpeed);
    private:
      sf::Sprite mSprite;
      sf::Texture mSource;
      float ballAngle;
      const float ballRadius;
      float ballSpeed;
      const sf::Vector2f scale;
  };
}

#endif

