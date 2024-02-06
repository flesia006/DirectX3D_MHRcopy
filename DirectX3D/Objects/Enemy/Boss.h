#pragma once
class Boss : public ModelAnimator
{
private:
	enum State
	{
		// �ִϸ��̼� Ŭ������ ���°ſ� ���� �ٲ���
		// ���� ���

	};

	enum Type // ��� ���� ���Ұ��� 
	{
		// ���� �����
		TypeA, // �̰� �Ӹ��� ������
		TypeB, // �̰� ���� ������
		TypeC // �̰� �Ѵ� ������
	};
	
public:
	Boss();
	~Boss();

	void Update();
	void Render();
	void GUIRender();
	void PostRender();

	//�׼� : ���±�
	void Hit();

	//�׼� : �����Ǳ�
	void Spawn(Vector3 pos);

	//ǥ�� ����
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
	void UpdateUI(); //ĳ���� UI�� ������ ���� ������Ʈ

private:
	Transform* transform;
	vector<CapsuleCollider*> collider;

	
	 // ���� : �ν��Ͻ�
	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;

	Transform* root;
	Transform* target;

	float speed = 50; //�ӷ� : �⺻ ����
	float maxHP = 100;
	float curHP = 100;

	Vector3 velocity; //�ӷ� : ���� ������

	UINT index; //�κ��� ���� �ε��� (�ν��Ͻ��� �ִٸ� �̰ɷ� ���� ���� ����)
	//State curState = �⺻ ������Ʈ;
	//Type curType = �⺻ Ÿ��;

	//������Ʈ Ȥ�� �����ӿ� ���� �̺�Ʈ ����
	vector<map<float, Event>> totalEvent;
	vector<map<float, Event>::iterator> eventIters;
};

