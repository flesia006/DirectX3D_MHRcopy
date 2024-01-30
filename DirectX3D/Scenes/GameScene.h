#pragma once
class GameScene : public Scene
{
public:

    GameScene();
    ~GameScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:

private:
    Naruto* naruto = nullptr;  
    Player* player = nullptr;
    ModelAnimator* boss = nullptr;

    Model* ground = nullptr;
    SkyBox* sky = nullptr;

<<<<<<< HEAD
    Shadow* shadow;
    LightBuffer::Light* light;

    BlendState* blendState[2];
=======
    Quad* clockFrame;
    Quad* durability;
    Quad* durability_gauge;
    Quad* hpBar;
    Quad* idBar;
    Quad* itemSlot;
    Quad* lsCoting;
    Quad* lsCoting2;
    Quad* lsGauge;
    Quad* lsGauge2;
    Quad* quickSlot;
    Quad* slingerBug;
    Quad* staminarBar;
>>>>>>> 3c1ba98ac6e9df4b73434fdac1515fec3796e4db
};

