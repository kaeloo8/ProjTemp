#pragma once
class Animator
{
public:
	Animator();
	~Animator();
	void Update();
	void PlayAnimation();
	void StopAnimation();
	void SetAnimationSpeed(float speed);
	void SetAnimation(int animationIndex);
	void SetAnimation(int animationIndex, float speed);
	void SetAnimation(int animationIndex, float speed, bool loop);
	void SetAnimation(int animationIndex, float speed, bool loop, bool play);
	void SetAnimation(int animationIndex, float speed, bool loop, bool play, bool stop);
	void SetAnimation(int animationIndex, float speed, bool loop, bool play, bool stop, bool reset);
};

