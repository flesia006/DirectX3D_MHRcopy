#pragma once
class ColorRect : public GameObject
{
private:
    typedef VertexColor VertexType;

public:
    ColorRect(Vector2 size, Float4 color);
    ~ColorRect();

    void Render();

private:
    void MakeMesh();

private:
    Vector2 size;

    Mesh<VertexType>* mesh;
    Float4 color;
};

