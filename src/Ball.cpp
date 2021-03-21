#include "Ball.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <math.h>


#define PI 3.14159f

namespace pong
{
  Ball::Ball(sf::Vector2<unsigned int> resolution, float diameter, sf::Vector2f scale)
    : ballRadius(diameter/2), 
      scale(scale)
  {
    mSource.loadFromFile("assets/pixel.png");
    mSprite = sf::Sprite(mSource);
    mSprite.setScale(diameter * scale.x, diameter * scale.y);
    mSprite.setPosition(resolution.x / 2.f, resolution.y / 2.f);
    mSprite.setOrigin(0.5,0.5);
  }
  void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
  {
    target.draw(mSprite, states);
  }
  void Ball::move(float deltaTime)
  {
    float factor = ballSpeed * deltaTime;
    mSprite.move(sf::Vector2f(std::cos(ballAngle) * factor * scale.x, std::sin(ballAngle) * factor * scale.y));
  }
  const float Ball::getRadius()
  {
    return ballRadius;
  }
  const sf::Vector2f Ball::getPosition()
  {
    return mSprite.getPosition();
  }
  void Ball::setPosition(float x, float y)
  {
    mSprite.setPosition(x, y);
  }
  void Ball::setAngle(float angle)
  {
    ballSpeed += abs(log(pow(ballSpeed, -1) * 5000)) * 100;
    ballAngle = angle * (PI/180);
    printf("%f\n", ballSpeed);
  }
  float Ball::getAngle()
  {
    return ballAngle * (180/PI);
  }
  float Ball::getSpeed()
  {
    return ballSpeed;
  }
  void Ball::setSpeed(float newSpeed)
  {
    ballSpeed = newSpeed;
  }
}
