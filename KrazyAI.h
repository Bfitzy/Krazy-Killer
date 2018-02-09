#pragma once
#include "VisibleGameObject.h"


class KrazyAI :
  public VisibleGameObject
{
public:
  KrazyAI();
  virtual ~KrazyAI();
  virtual void Update(float);

private:
  float _velocityX;
  float _velocityY;
  float _angle;
  float _elapsedTimeSinceStart;
  float _speed;
  std::string _path;

  float LinearVelocityX(float angle);
  float LinearVelocityY(float angle);
};
