#pragma once



class Player :
    public ObjectBase
{
public:
  Player();
  ~Player();

  void Init()override;
  void Update(InputManager&)override;
  void Render()override;
private:

};

