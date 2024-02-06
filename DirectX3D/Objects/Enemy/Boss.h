#pragma once
class Boss : public ModelAnimator
{
private:
	enum State
	{
		// 애니메이션 클립들이 들어가는거에 따라서 바뀔예정
		// 예를 들면

	};

	enum Type // 어디가 색이 변할건지 
	{
		// 예를 든거임
		TypeA, // 이건 머리만 빨간색
		TypeB, // 이건 날개 빨간색
		TypeC // 이건 둘다 빨간색
	};
	
public:
	Boss();
	~Boss();

	void Update();
	void Render();
	void GUIRender();
	void PostRender();

	//액션 : 얻어맞기
	void Hit();

	//액션 : 생성되기
	void Spawn(Vector3 pos);

	//표적 설정
	void SetTarget(Transform* target);

	Transform* GetTransform() { return transform; }
	CapsuleCollider* GetCollider(int index) { return collider[index]; }

private:
	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	void EndStandUp();
	void EndHit();
	void EndDying();

	void SetState(State state);
	void SetType(Type type);

	void Move();
	void UpdateUI(); //캐릭터 UI가 있으면 이후 업데이트

private:
	Transform* transform;
	vector<CapsuleCollider*> collider;

	
	 // 샘플 : 인스턴싱
	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;

	Transform* root;
	Transform* target;

	float speed = 50; //속력 : 기본 스탯
	float maxHP = 100;
	float curHP = 100;

	Vector3 velocity; //속력 : 실제 움직임

	UINT index; //로봇의 개별 인덱스 (인스턴싱이 있다면 이걸로 서로 구분 가능)
	//State curState = 기본 스테이트;
	//Type curType = 기본 타입;

	//스테이트 혹은 움직임에 따른 이벤트 지정
	vector<map<float, Event>> totalEvent;
	vector<map<float, Event>::iterator> eventIters;
};

