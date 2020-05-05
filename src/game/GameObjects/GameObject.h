//
// Created by Alex on 05/05/2020.
//

#ifndef ANGRYBIRDS_GAMEOBJECT_H
#define ANGRYBIRDS_GAMEOBJECT_H

class ButtonComponent;

class GameObject
{
 public:
  GameObject()  = default;
  ~GameObject() = default;

 public:
  ButtonComponent getButtonComp();
  void setButtonComp(ButtonComponent* buttonComponent);

 private:
};

#endif // ANGRYBIRDS_GAMEOBJECT_H
