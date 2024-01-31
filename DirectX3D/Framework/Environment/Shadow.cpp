#include "Framework.h"
#include "Shadow.h"

Shadow::Shadow(UINT width, UINT height)
    : width(width), height(height)
{
    //렌더 타겟, 뎁스 스텐실, 버퍼 생성
    renderTarget = new RenderTarget(width, height);
    depthStencil = new DepthStencil(width, height);
    viewBuffer = new ViewBuffer();
    projectionBuffer = new MatrixBuffer();

    //(테스트용) 쿼드 생성
    quad = new Quad(Vector2(200, 200));
    quad->Pos() = { 100, 100, 0 };
    quad->UpdateWorld();

    //텍스처 생성 (및 테스트용으로 만든 쿼드에도 넣기)
    Texture* texture = Texture::Add(L"Shadow", renderTarget->GetSRV());
    quad->GetMaterial()->SetDiffuseMap(texture);
}

Shadow::~Shadow()
{
    delete renderTarget;
    delete depthStencil;
    delete viewBuffer;
    delete projectionBuffer;
    delete quad;
}

void Shadow::SetRenderTarget()
{
    renderTarget->Set(depthStencil); // 렌더 타겟 설정 (테스트씬에서는 프리렌더에서 했던 것)
    SetViewProjection(); //뷰포트, 행렬공간 투사 과정을 여기서 호출
}

void Shadow::SetRender()
{
    viewBuffer->SetVS(11);
    projectionBuffer->SetVS(12);
    DC->PSSetShaderResources(10, 1, &renderTarget->GetSRV());
    //10번 슬롯부터, 1개 층만큼을, GetSRV에서 가져와 출력 준비

//여기까지 진행되면 텍스처가 준비
}

void Shadow::PostRender()
{
    //위 함수에서 준비된 텍스처....를 입힌 쿼드....를 테스트용으로 출력
    quad->Render();
}

void Shadow::GUIRender()
{
    ImGui::SliderFloat("Scale", &scale, 1, 10); //"크기" 설정
}

void Shadow::SetViewProjection()
{
    // 광원 클래스를 써보기 (DX + 프레임워크 설정)
    LightBuffer::Light* light = Environment::Get()->GetLight(0);
    Matrix view = XMMatrixLookAtLH(Vector3(light->pos), Vector3(), Vector3(0, 1, 0));
    Matrix projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1, 0.1f, 1000);
    viewBuffer->Set(view, XMMatrixInverse(nullptr, view)); // XMMatrixInverse : 역행렬 만들기(행렬 뒤집기)
    // 이 과정을 통해 행렬 데이터를 GPU에서 연산 가능
    // 매개변수는 각각 "추가 옵션이 있는가?
    // 그리고 원본은 무엇인가? (=view)"
    projectionBuffer->Set(projection);

    //버퍼를 셰이더에 넘기기 (=GPU계산 후 출력 대기)
    viewBuffer->SetVS(1);
    projectionBuffer->SetVS(2);
}
