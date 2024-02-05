#pragma once
class UIManager : public Singleton<UIManager>
{
private:
    friend class Singleton;
    
public:
	UIManager();
	~UIManager();

    void Update();
    void PostRender();

    void SetGreenGauge(float ratio)
    {
        Vector3 Ratio = originGreenBarScale * ratio;
        greenBar->Scale() = Ratio;
    }

private:
    Quad* clockFrame;
    Quad* durability;
    Quad* durability_gauge;

    Quad* hpBar1;

    Quad* idBar;
    Quad* itemSlot;
    Quad* lsCoting;
    Quad* lsCoting2;
    Quad* lsGauge;
    Quad* lsGauge2;
    Quad* quickSlot;
    Quad* slingerBug;
    Quad* staminarBar;

    ColorRect* blackBar;
    ColorRect* redBar;
    ColorRect* greenBar;

    Vector3 originGreenBarScale;
};

