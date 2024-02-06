#include "Framework.h"
#include "ShadowScene.h"
#include "Objects/Character/Valphalk.h"

ShadowScene::ShadowScene()
{
    forest = new Model("Forest");
    forest->Scale() *= 10;
    forest->UpdateWorld();

    valphalk = new Valphalk();
    valphalk->Pos().z -= 1500.0f;
    valphalk->Rot().y += XM_PI;
    valphalk->UpdateWorld();

    player = new Player();
    shadow = new Shadow();
    UIManager::Get();

    // ���� �˾ƺ��� Ȱ��� : �� ȣ�� Ȥ�� ����� (<-�� ��� ���)

    light = Environment::Get()->GetLight(0);

    light->type = 0;          
    light->pos = { 0, 2000, -500 }; 
    light->range = 3000;           

    light->direction = { 0, -1, 1 }; 
    light->color = { 1, 1, 1, 1 };  

    light->length; 
    light->inner;   //���� ���� ���� (���� ���ߵǾ� ���̴� ����...�� ����)
    light->outer;   //���� �ܰ� ���� (���� ������� ��ġ�� ����...�� ����)

    skyBox = new SkyBox(L"Textures/Landscape/BlueSky.dds");
    Sounds::Get()->AddSound("Valphalk_Thema", SoundPath + L"Valphalk_Thema.mp3");
    Sounds::Get()->Play("Valphalk_Thema", 0.1f);    

}

ShadowScene::~ShadowScene()
{
    delete forest;
    delete player;
    delete shadow;
    delete skyBox;

}

void ShadowScene::Update()
{
    if (KEY_DOWN('1')) light->type = 0; 
    if (KEY_DOWN('2')) light->type = 1; 
    if (KEY_DOWN('3')) light->type = 2;
    if (KEY_DOWN('4')) light->type = 3; 

    forest->UpdateWorld();
    player->Update();
    valphalk->Update();
    UIManager::Get()->Update();

}

void ShadowScene::PreRender()
{
    //�׸����� ���� Ÿ�� ����(�� �غ�)
    shadow->SetRenderTarget();

    //�ΰ����� ���� ���̴��� ���� (���ǿ� ���� ���̴� ��ȭ...���� ���� ���� �Լ�)
    player->SetShader(L"Light/DepthMap.hlsl");
    valphalk->SetShader(L"Light/DepthMap.hlsl");
    //���ǿ� ���� �ȼ��� �ٲ� �ΰ��� ����...�ؼ� �ؽ�ó�� �غ�
    player->Render();
    valphalk->Render();
}

void ShadowScene::Render()
{
    skyBox->Render();

    //�� �Լ����� ������� �ؽ�ó�� �׸��ڿ��� ���� ������� ����
    shadow->SetRender();

    //�׸��ڸ� �ޱ� ���� ���̴� ����
    forest->SetShader(L"Light/Shadow.hlsl");
    player->SetShader(L"Light/Shadow.hlsl");
    valphalk->SetShader(L"Light/Shadow.hlsl");
    //���̴��� ���õ� ���� �ΰ��� ��¥ ȣ��
    forest->Render();
    player->Render();
    valphalk->Render();
    
}

void ShadowScene::PostRender()
{
    //shadow->PostRender(); // ���� ��¿�
    player->PostRender();
    UIManager::Get()->PostRender();
}

void ShadowScene::GUIRender()
{
    player->GUIRender(); // ����� ���ۿ�
    valphalk->GUIRender();
}
