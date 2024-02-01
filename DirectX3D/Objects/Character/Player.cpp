#include "Framework.h"
#include "Player.h"

Player::Player() : ModelAnimator("Player")
{
	mainHand = new Transform();
	head = new Transform();
	realPos = new Transform();
	lastPos = new Transform();
	longSword = new Model("longSwd");
	longSword->SetParent(mainHand);
	
	tmpCollider = new SphereCollider();
	tmpCollider->Scale() *= 3.0f;
	tmpCollider->SetParent(head);



	ReadClips();

	CAM->SetTarget(head);
}

Player::~Player()
{
	delete mainHand;
	delete head;
	delete realPos;
	delete tmpCollider;
}

void Player::Update()
{
	Control();
	ResetPlayTime();


	mainHand->SetWorld(GetTransformByNode(108));
	realPos->Pos() = GetTranslationByNode(1);	
	head->Pos() = realPos->Pos() + Vector3::Up() * 200;


	realPos->UpdateWorld();
	lastPos->UpdateWorld();
	ModelAnimator::Update();
	longSword->UpdateWorld();
	head->UpdateWorld();
	tmpCollider->UpdateWorld();
}

void Player::Render()
{
	ModelAnimator::Render();
	tmpCollider->Render();
	longSword->Render();
}

void Player::GUIRender()
{
	ModelAnimator::GUIRender();

	float t = GetClip(L_004)->GetPlaytime();
	ImGui::DragFloat("pt_0", &t); 
	Vector3 pos = realPos->Pos();

	ImGui::DragFloat3("RealPos", (float*)&pos);

	int U = Keyboard::Get()->ReturnFirst();
	ImGui::SliderInt("keyboard", &U, 0, 200);


	ImGui::SliderInt("node", &node, 0, 100);


	longSword->GUIRender();


	// t = GetClip(1)->GetRatio();
	// ImGui::DragFloat("ratio_1", &t);

	//Matrix x = GetTransformByNode(0);
	//Vector3 S, R, T;
	//XMMatrixDecompose(S.GetValue(), R.GetValue(), T.GetValue(), x);
	//
	//string temp = "_Pos";
	//ImGui::DragFloat3(temp.c_str(), (float*)&T, 0.1f);
	//
	//temp = "_GlobalPos";
	//Vector3 globalPos = GetTranslationByNode(0);
	//ImGui::DragFloat3(temp.c_str(), (float*)&globalPos, 0.1f);
	//
	//temp = "Real_GlobalPos";
	//Vector3 Pos = root->GlobalPos();
	//ImGui::DragFloat3(temp.c_str(), (float*)&Pos, 0.1f);
}

void Player::PostRender()
{
	vector<string> strStatus;

	strStatus.push_back("L_001 발도 상태 대기");
	strStatus.push_back("L_002 발도");
	strStatus.push_back("L_003 서서납도");
	strStatus.push_back("L_004 발도상태 걷기");
	strStatus.push_back("L_005 발도상태 걷기 시작");
	strStatus.push_back("L_006 발도상태 좌로 걷기 시작");
	strStatus.push_back("L_007 발도상태 우로 걷기 시작");
	strStatus.push_back("L_008 멈춤");
	strStatus.push_back("L_009 걸으면서 납도 ");
	strStatus.push_back("L_010 앞구르기");
	strStatus.push_back("L_011 왼쪽구르기");
	strStatus.push_back("L_012 오른쪽구르기");
	strStatus.push_back("L_013 뒤구르기");
	strStatus.push_back("L_014 구른후걷기");
	strStatus.push_back("L_015 구른후뒤걷기");
	strStatus.push_back("L_071 낮은높이언덕파쿠르");
	strStatus.push_back("L_072 중간높이언덕파쿠르");
	strStatus.push_back("L_073 높은높이언덕파쿠르");
	strStatus.push_back("L_077 ?");
	strStatus.push_back("L_078 ?");
	strStatus.push_back("L_079 ?");
	strStatus.push_back("L_101 내디뎌베기");
	strStatus.push_back("L_102 세로베기");
	strStatus.push_back("L_103 베어내리기");
	strStatus.push_back("L_104 찌르기");
	strStatus.push_back("L_105 베어올리기");
	strStatus.push_back("L_106 기인베기1");
	strStatus.push_back("L_107 기인베기2");
	strStatus.push_back("L_108 기인베기3");
	strStatus.push_back("L_109 기인큰회전베기");
	strStatus.push_back("L_110 기인내디뎌베기");
	strStatus.push_back("L_111 일자베기");

	string fps = "Status : " + strStatus.at((UINT)curState);
	Font::Get()->RenderText(fps, { 150, WIN_HEIGHT - 30 });
}

void Player::Control()
{
	switch (curState)
	{
					// 이동 모션
	case Player::L_001:
		L001();
		break;
	case Player::L_002:
		break;
	case Player::L_003:
		break;
	case Player::L_004:
		L004();
		break;
	case Player::L_005:
		L005();
		break;
	case Player::L_006:
		break;
	case Player::L_007:
		break;
	case Player::L_008:
		L008();
		break;
	case Player::L_009:
		break;
	case Player::L_010:
		L010();
		break;
	case Player::L_011:
		break;
	case Player::L_012:
		break;
	case Player::L_013:
		break;
	case Player::L_014:
		break;
	case Player::L_015:
		break;
	case Player::L_071:
		break;
	case Player::L_072:
		break;
	case Player::L_073:
		break;
	case Player::L_077:
		break;
	case Player::L_078:
		break;
	case Player::L_079:
		break;
					// 공격 모션
	case Player::L_101: 
		L101();
		break;
	case Player::L_102:
		L102();
		break;
	case Player::L_103:
		L103();
		break;
	case Player::L_104:
		L104();
		break;
	case Player::L_105:
		L105();
		break;
	case Player::L_106:
		L106();
		break;
	case Player::L_107:
		L107();
		break;
	case Player::L_108:
		L108();
		break;
	case Player::L_109:
		L109();
		break;
	case Player::L_110:
		L110();
		break;
	case Player::L_111:
		break;
	case Player::L_112:
		break;
	case Player::L_113:
		break;
	case Player::L_114:
		break;
	case Player::L_115:
		break;
	case Player::L_116:
		break;
	case Player::L_117:
		break;
	case Player::L_118:
		break;
	case Player::L_119:
		break;
	case Player::L_120:
		break;
	case Player::L_121:
		break;
	case Player::L_122:
		break;
	case Player::L_123:
		break;
	default:
		break;
	}
}

void Player::Move()
{
	bool isMoveZ = false; // 전후 이동 중 아님
	bool isMoveX = false; // 좌우 이동 중 아님

	if (KEY_PRESS('W'))
	{
		velocity.z = 1;//+= DELTA; // 속도(범용변수)에 델타만큼 전후값 주기		
		isMoveZ = true; //전후 이동 수행 중
	}

	if (KEY_PRESS('S'))
	{
		velocity.z -= DELTA;
		isMoveZ = true; //전후 이동 수행 중
	}

	if (KEY_PRESS('A'))
	{
		velocity.x -= DELTA;
		isMoveX = true; //좌우 이동 수행 중
	}

	if (KEY_PRESS('D'))
	{
		velocity.x += DELTA;
		isMoveX = true; //좌우 이동 수행 중
	}

	if (velocity.Length() > 1) //속도의 전체 가치가 1을 넘으면 (선으로 표현한 벡터의 길이가 1 초과)
		velocity.Normalize(); //정규화
	// 생각할 거리 : 이 코드가 만약 없으면....?


	if (!isMoveZ) // 전후 이동 중이 아니면
		velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //보간에 의해 감속

	if (!isMoveX) // 좌우이동에 적용
		velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

	//좌우회전과 행렬계산에 의한 면법선 내기 ( = 정면 구하기)
	Matrix rotY = XMMatrixRotationY(Rot().y);
	Vector3 direction = XMVector3TransformCoord(velocity, rotY); // 현재의 공간이 가지는 "정면"의 실제 벡터 방향

	Pos() += direction * -1 * moveSpeed * DELTA; //"정면" 방향대로 이동

}

void Player::ResetPlayTime()
{
	if (preState != curState)
		GetClip(preState)->ResetPlayTime();


}

void Player::Rotate()
{
	Vector3 newForward;
	newForward = Lerp(Forward(), CAM->Back(), rotSpeed * DELTA);
	float rot = atan2(newForward.x, newForward.z);
	Rot().y = rot;
}

void Player::Attack()
{
}

void Player::SetAnimation()
{
}

void Player::SetState(State state)
{
	if (curState == state)
		return;

	Pos() = realPos->Pos();
	preState = curState;
	curState = state;
//	PlayClip(state);
}

void Player::Throw()
{
}

void Player::EndThrow()
{
}

void Player::ReadClips()
{
	ReadClip("L_001");
	ReadClip("L_002");
	ReadClip("L_003");
	ReadClip("L_004");
	ReadClip("L_005");
	ReadClip("L_006");
	ReadClip("L_007");
	ReadClip("L_008");
	ReadClip("L_009");
	ReadClip("L_010");
	ReadClip("L_011");
	ReadClip("L_012");
	ReadClip("L_013");
	ReadClip("L_014");
	ReadClip("L_015");
	ReadClip("L_071");
	ReadClip("L_072");
	ReadClip("L_073");
	ReadClip("L_077");
	ReadClip("L_078");
	ReadClip("L_079");
	ReadClip("L_101");
	ReadClip("L_102");
	ReadClip("L_103");
	ReadClip("L_104");
	ReadClip("L_105");
	ReadClip("L_106");
	ReadClip("L_107");
	ReadClip("L_108");
	ReadClip("L_109");
	ReadClip("L_110");
	ReadClip("L_111");
	ReadClip("L_112");
	ReadClip("L_113");
	ReadClip("L_114");
	ReadClip("L_115");
	ReadClip("L_116");
	ReadClip("L_117");
	ReadClip("L_118");
	ReadClip("L_119");
	ReadClip("L_120");
	ReadClip("L_121");
	ReadClip("L_122");
	ReadClip("L_123");
}

void Player::RecordLastPos()
{
	//Pos() = root->GlobalPos();
	Pos() = GetTranslationByNode(1);
}

void Player::L001()
{
	PLAY;

	if (KEY_PRESS('W'))
		SetState(L_005);

	if (KEY_DOWN(VK_LBUTTON))
		SetState(L_101);

	if (KEY_DOWN(VK_SPACE))
		SetState(L_010);
}

void Player::L002()
{
}

void Player::L003()
{
}

void Player::L004()
{
	PLAY;

	if (KEY_UP('W'))
	{
		SetState(L_008);
		return;
	}

	Move();
	Rotate();

	// 101 내디뎌 베기
	if (KEY_FRONT(Keyboard::LMB))
	{		
		SetState(L_101);		
		return;
	}

	// 106 기인 베기
	{

	}

	// 이동 : 
	{

	}

	if (KEY_DOWN(VK_SPACE))
	{
		SetState(L_010);
		return;
	}

	if (RATIO > 0.98)
	{
		GetClip(L_004)->SetPlayTime(-100.3f);
	}
}

void Player::L005()
{
	PLAY;

	if (KEY_UP('W'))
	{
		SetState(L_008);
		return;
	}

	if (RATIO < 0.2)
		Rotate();

	if (RATIO > 0.94 && KEY_PRESS('W'))
	{
		SetState(L_004);
		return;
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
	}

	if (KEY_DOWN(VK_SPACE))
		SetState(L_010);
}

void Player::L006()
{
}

void Player::L007()
{
}

void Player::L008()
{
	PLAY;

	Rotate();

	if (RATIO > 0.5 && RATIO <= 0.94)
	{
		if (KEY_PRESS('W'))
		{
			SetState(L_005);
		}
		if (KEY_DOWN(VK_SPACE))
		{
			SetState(L_010);
		}
	}

	if (RATIO > 0.94)
	{
		GetClip(L_008)->SetPlayTime(-100.3f);
		ReturnIdle();
		SetState(L_001);
	}
}

void Player::L009()
{
}

void Player::L010()
{
	PLAY;

	//if (GetClip(L_010)->GetRatio() > 0.65 && GetClip(L_010)->GetRatio() <= 0.94)
	//	if (KEY_PRESS('W'))
	//		SetState(L_005);

	if (GetClip(L_010)->GetRatio() > 0.98)
	{
		ReturnIdle();
	}
}

void Player::L101()
{
	// PlayClip 하는데 계속 반복해서 호출되면 모션 반복되니까 방지 + 딱 한번만 실행되는거 놓기
	if (INIT)
	{
		PlayClip(L_101);
		MotionRotate(30);
	}

	if (RATIO < 0.3)
		Rot().y = Lerp(Rot().y, rad, 0.001f);


	// 해당 클립이 60% 이상 재생됐으면 if 조건 충족
	if (RATIO > 0.6)
	{
		if (KEY_FRONT(Keyboard::LMB))
		{
			SetState(L_102);
		}
		else if (KEY_FRONT(Keyboard::RMB))
		{
			SetState(L_104);
		}
		else if (KEY_FRONT(Keyboard::LMBRMB))
		{
			SetState(L_103);
		}
		else if (KEY_FRONT(Keyboard::SPACE))
		{
			SetState(L_010);
		}
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
	}

}

void Player::L102()
{
	if (INIT)
	{
		PlayClip(L_102);
		MotionRotate(30);
	}

	if (RATIO < 0.3)
		Rot().y = Lerp(Rot().y, rad, 0.001f);

	if (RATIO > 0.5)
	{
		if (KEY_FRONT(Keyboard::LMB))
		{
			SetState(L_104);
		}
		else if (KEY_FRONT(Keyboard::RMB))
		{
			SetState(L_104);
		}
		else if (KEY_FRONT(Keyboard::LMBRMB))
		{
			SetState(L_103);
		}
		else if (KEY_FRONT(Keyboard::SPACE))
		{
			SetState(L_010);
		}
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
	}
}

void Player::L103() // 베어내리기
{
	if (INIT)
	{
		PlayClip(L_103);
		MotionRotate(30);
	}

	if (RATIO < 0.3) // 30%
		Rot().y = Lerp(Rot().y, rad, 0.001f);

	if (RATIO > 0.95)
	{
		if (KEY_FRONT(Keyboard::RMB))
		{
			SetState(L_104);
		}
		else if (KEY_FRONT(Keyboard::SPACE))
		{
			SetState(L_010);
		}
	}

	if (RATIO > 0.98) 
	{
		ReturnIdle();
	}
}

void Player::L104()
{
	PLAY;


	if (RATIO > 0.6)
	{
		if (KEY_FRONT(Keyboard::LMB))
		{
			SetState(L_105);
		}
		else if (KEY_FRONT(Keyboard::RMB))
		{
			SetState(L_105);
		}
		else if (KEY_FRONT(Keyboard::LMBRMB))
		{
			SetState(L_103);
		}
		else if (KEY_FRONT(Keyboard::SPACE))
		{
			SetState(L_010);
		}
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
	}
}

void Player::L105() // 배어올리기
{
	PLAY;

	if (RATIO > 0.6)
	{
		// 세로베기
		if (KEY_FRONT(Keyboard::LMB))
			SetState(L_102);

		// 찌르기
		else if (KEY_FRONT(Keyboard::RMB))
			SetState(L_104);

		// 베어내리기
		else if (KEY_FRONT(Keyboard::LMBRMB))
			SetState(L_103);

		else if (KEY_FRONT(Keyboard::SPACE))
			SetState(L_010);

	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L106() // 기인 베기 1
{
	PLAY;

	if (RATIO > 0.6)
	{
		// 찌르기
		if (KEY_FRONT(Keyboard::RMB) || KEY_FRONT(Keyboard::LMB))
		{
			SetState(L_104);
		}
		// 베어내리기
		else if (KEY_FRONT(Keyboard::LMBRMB))
		{
			SetState(L_103);
		}
		// 기인 베기2
		else if (KEY_FRONT(Keyboard::CTRL))
		{
			SetState(L_107);
		}
		else if (KEY_FRONT(Keyboard::SPACE))
		{
			SetState(L_010);
		}
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L107()
{
}

void Player::L108()
{
}

void Player::L109()
{
}

void Player::L110()
{
}

void Player::MotionRotate(float degree)
{
	Vector3 forword = CAM->Back();
	camRot = atan2(forword.x, forword.z);

	float radian = XMConvertToRadians(degree);

	if (camRot > Rot().y)
	{
		rad = abs(camRot - Rot().y) > radian ?
			Rot().y + radian : camRot;
	}
	else
	{
		rad = abs(camRot - Rot().y) > radian ?
			Rot().y - radian : camRot;
	}

}