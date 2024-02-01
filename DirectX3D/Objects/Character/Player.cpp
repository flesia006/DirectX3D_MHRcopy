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

	strStatus.push_back("L_001 �ߵ� ���� ���");
	strStatus.push_back("L_002 �ߵ�");
	strStatus.push_back("L_003 ��������");
	strStatus.push_back("L_004 �ߵ����� �ȱ�");
	strStatus.push_back("L_005 �ߵ����� �ȱ� ����");
	strStatus.push_back("L_006 �ߵ����� �·� �ȱ� ����");
	strStatus.push_back("L_007 �ߵ����� ��� �ȱ� ����");
	strStatus.push_back("L_008 ����");
	strStatus.push_back("L_009 �����鼭 ���� ");
	strStatus.push_back("L_010 �ձ�����");
	strStatus.push_back("L_011 ���ʱ�����");
	strStatus.push_back("L_012 �����ʱ�����");
	strStatus.push_back("L_013 �ڱ�����");
	strStatus.push_back("L_014 �����İȱ�");
	strStatus.push_back("L_015 �����ĵڰȱ�");
	strStatus.push_back("L_071 �������̾������");
	strStatus.push_back("L_072 �߰����̾������");
	strStatus.push_back("L_073 �������̾������");
	strStatus.push_back("L_077 ?");
	strStatus.push_back("L_078 ?");
	strStatus.push_back("L_079 ?");
	strStatus.push_back("L_101 ���𵮺���");
	strStatus.push_back("L_102 ���κ���");
	strStatus.push_back("L_103 �������");
	strStatus.push_back("L_104 ���");
	strStatus.push_back("L_105 ����ø���");
	strStatus.push_back("L_106 ���κ���1");
	strStatus.push_back("L_107 ���κ���2");
	strStatus.push_back("L_108 ���κ���3");
	strStatus.push_back("L_109 ����ūȸ������");
	strStatus.push_back("L_110 ���γ��𵮺���");
	strStatus.push_back("L_111 ���ں���");

	string fps = "Status : " + strStatus.at((UINT)curState);
	Font::Get()->RenderText(fps, { 150, WIN_HEIGHT - 30 });
}

void Player::Control()
{
	switch (curState)
	{
					// �̵� ���
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
					// ���� ���
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
	bool isMoveZ = false; // ���� �̵� �� �ƴ�
	bool isMoveX = false; // �¿� �̵� �� �ƴ�

	if (KEY_PRESS('W'))
	{
		velocity.z = 1;//+= DELTA; // �ӵ�(���뺯��)�� ��Ÿ��ŭ ���İ� �ֱ�		
		isMoveZ = true; //���� �̵� ���� ��
	}

	if (KEY_PRESS('S'))
	{
		velocity.z -= DELTA;
		isMoveZ = true; //���� �̵� ���� ��
	}

	if (KEY_PRESS('A'))
	{
		velocity.x -= DELTA;
		isMoveX = true; //�¿� �̵� ���� ��
	}

	if (KEY_PRESS('D'))
	{
		velocity.x += DELTA;
		isMoveX = true; //�¿� �̵� ���� ��
	}

	if (velocity.Length() > 1) //�ӵ��� ��ü ��ġ�� 1�� ������ (������ ǥ���� ������ ���̰� 1 �ʰ�)
		velocity.Normalize(); //����ȭ
	// ������ �Ÿ� : �� �ڵ尡 ���� ������....?


	if (!isMoveZ) // ���� �̵� ���� �ƴϸ�
		velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //������ ���� ����

	if (!isMoveX) // �¿��̵��� ����
		velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

	//�¿�ȸ���� ��İ�꿡 ���� ����� ���� ( = ���� ���ϱ�)
	Matrix rotY = XMMatrixRotationY(Rot().y);
	Vector3 direction = XMVector3TransformCoord(velocity, rotY); // ������ ������ ������ "����"�� ���� ���� ����

	Pos() += direction * -1 * moveSpeed * DELTA; //"����" ������ �̵�

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

	// 101 ���� ����
	if (KEY_FRONT(Keyboard::LMB))
	{		
		SetState(L_101);		
		return;
	}

	// 106 ���� ����
	{

	}

	// �̵� : 
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
	// PlayClip �ϴµ� ��� �ݺ��ؼ� ȣ��Ǹ� ��� �ݺ��Ǵϱ� ���� + �� �ѹ��� ����Ǵ°� ����
	if (INIT)
	{
		PlayClip(L_101);
		MotionRotate(30);
	}

	if (RATIO < 0.3)
		Rot().y = Lerp(Rot().y, rad, 0.001f);


	// �ش� Ŭ���� 60% �̻� ��������� if ���� ����
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

void Player::L103() // �������
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

void Player::L105() // ���ø���
{
	PLAY;

	if (RATIO > 0.6)
	{
		// ���κ���
		if (KEY_FRONT(Keyboard::LMB))
			SetState(L_102);

		// ���
		else if (KEY_FRONT(Keyboard::RMB))
			SetState(L_104);

		// �������
		else if (KEY_FRONT(Keyboard::LMBRMB))
			SetState(L_103);

		else if (KEY_FRONT(Keyboard::SPACE))
			SetState(L_010);

	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L106() // ���� ���� 1
{
	PLAY;

	if (RATIO > 0.6)
	{
		// ���
		if (KEY_FRONT(Keyboard::RMB) || KEY_FRONT(Keyboard::LMB))
		{
			SetState(L_104);
		}
		// �������
		else if (KEY_FRONT(Keyboard::LMBRMB))
		{
			SetState(L_103);
		}
		// ���� ����2
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