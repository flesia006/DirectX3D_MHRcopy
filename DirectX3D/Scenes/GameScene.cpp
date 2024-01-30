#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	//naruto = new Naruto();
	player = new Player();

//	boss = new ModelAnimator("boss");
//	boss->Pos().z -= 2200;
//	boss->Rot().y += XM_PI;
//	boss->ReadClip("boss2");

	ground = new Model("forest");
	ground->Scale() *= 10.0f;
	ground->UpdateWorld();

	sky = new SkyBox(L"Textures/Landscape/SpaceSky.dds");
	sky->Scale() *= 100.0f;
	sky->UpdateWorld();


	shadow = new Shadow();
	light = Environment::Get()->GetLight(0);
	light->type = 0;
	light->pos = { 0, 550, -500 };
	light->range = 3000;
	light->direction = { 0, -1, 1 };
	light->color = { 1, 1, 1, 1 };
	light->length = 3000; 
	light->inner;  
	light->outer;   

	FOR(2)
		blendState[i] = new BlendState();
	blendState[1]->AlphaToCoverage(true);

	//RobotManager::Get()->SetTarget(naruto);

	//CAM->SetTarget(player);
	//KunaiManager::Get();
	/////
}

GameScene::~GameScene()
{
	//delete naruto;

	//RobotManager::Delete();
	//KunaiManager::Delete();
}

void GameScene::Update()
{
//	naruto->Update();
//	RobotManager::Get()->Update();
//	KunaiManager::Get()->Update();
//	boss->Update();
	//
	if (KEY_DOWN('1')) light->type = 0; 
	if (KEY_DOWN('2')) light->type = 1; 
	if (KEY_DOWN('3')) light->type = 2; 
	if (KEY_DOWN('4')) light->type = 3;
	player->Update();
}

void GameScene::PreRender()
{
	shadow->SetRenderTarget();
	player->SetShader(L"Light/DepthMap.hlsl");
	player->Render();
	ground->SetShader(L"Light/DepthMap.hlsl");
	blendState[1]->SetState();
	ground->Render();
	blendState[0]->SetState();


}

void GameScene::Render()
{
	// naruto->Render();
	// RobotManager::Get()->Render();
	// KunaiManager::Get()->Render();
	shadow->SetRender();
	ground->SetShader(L"Light/Shadow.hlsl");
	player->SetShader(L"Light/Shadow.hlsl");
	sky->Render();
	//boss->Render();
	//
	ground->Render();
	player->Render();
}

void GameScene::PostRender()
{
	//	naruto->PostRender();
	shadow->PostRender();
	player->PostRender();
}

void GameScene::GUIRender()
{
	//   naruto->GUIRender();
	shadow->GUIRender(); // 디버그 조작용
	player->GUIRender();
//	boss->GUIRender();
}