#include "Framework.h"
#include "ColorRect.h"

ColorRect::ColorRect(Vector2 size, Float4 color)
    : GameObject(L"Basic/grid.hlsl"), size(size), color(color)
{
    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

ColorRect::~ColorRect()
{
    delete mesh;
}

void ColorRect::Render()
{
    if (!Active()) return;

    SetRender();
    mesh->Draw();
}

void ColorRect::MakeMesh()
{
    float left = 0;
    float right = +size.x;
    float top = +size.y * 0.5f;
    float bottom = -size.y * 0.5f;

    vector<VertexType>& vertices = mesh->GetVertices();

    vertices.emplace_back(left , top,    0, color.x, color.y, color.z, color.w);
    vertices.emplace_back(right, top,    0, color.x, color.y, color.z, color.w);
    vertices.emplace_back(left , bottom, 0, color.x, color.y, color.z, color.w);
    vertices.emplace_back(right, bottom, 0, color.x, color.y, color.z, color.w);

    vector<UINT>& indices = mesh->GetIndices();
    indices = { 0, 1, 2, 2, 1, 3 };
}
