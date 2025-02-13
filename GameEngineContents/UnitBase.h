#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "GlobalContentsValue.h"

struct PaperBurnInfo
{
	unsigned int	muOnOffPaperBurn;
	float			mfEffectTime;
	float			mfHitted;
	float			mfPadding2;
};

struct AdditionalInfoForLight
{
	unsigned int uOnOffLight;
	float4 f4Padding;
};

// 설명 :
class GameEngineFBXStaticRenderer;
class UnitBase : public GameEngineActor
{
public:
	// constrcuter destructer
	UnitBase();
	~UnitBase();

	// delete Function
	UnitBase(const UnitBase& _Other) = delete;
	UnitBase(UnitBase&& _Other) noexcept = delete;
	UnitBase& operator=(const UnitBase& _Other) = delete;
	UnitBase& operator=(UnitBase&& _Other) noexcept = delete;

protected:
	void BaseUpdate(float _DeltaTime);

public:
	std::shared_ptr < GameEngineDefaultRenderer> Renderer;
	std::shared_ptr < GameEngineFBXStaticRenderer> FBXStaticRenderer;
	std::shared_ptr <GameEngineFBXAnimationRenderer> FBXAnimationRenderer;
	
	std::shared_ptr < GameEngineTextureRenderer> TexRenderer;
	std::shared_ptr < GameEngineTextureRenderer> TexRenderer2;

	std::shared_ptr < GameEngineCollision> Collision;
	std::shared_ptr < GameEngineCollision> AttCollision;
	GameEngineRenderingEvent Event;
public:
	GameEngineStateManager StateManager;



public :
	float4 GetDegree3D(const float4& _Left, const float4& _Right)
	{

		float4 v3 = _Right - _Left;
		if (v3.z > 0)
		{
			v3 *= -1;
		}



		float xAngle = atan2(v3.y, v3.z) * 180 / GameEngineMath::PI;
		float yAngle = atan2(v3.x, -v3.z) * 180 / GameEngineMath::PI;
		float zAngle = atan2(v3.y, -v3.x) * 180 / GameEngineMath::PI;




		if (_Right.z < _Left.z)
		{
			yAngle = 360.f - yAngle;
			xAngle = 360.f - xAngle;
		}
		if (_Right.x < _Left.x)
		{
			yAngle = 360.f - yAngle;
			zAngle = 360.f - zAngle;
		}




		float4 Result = { xAngle , yAngle, zAngle };

		
		return Result;
	}


	float DirToRotY(float4 u, float4 v)
	{

		u.y = -u.z;
		v.y = -v.z;


		u.z = 0.f;
		u.w = 0.f;

		v.z = 0.f;
		v.w = 0.f;

		float Angle = float4::VectorXYtoDegree(v, u);

	

		if (Angle >= 360.f)
		{
			Angle -= 360.f;
		}
		else if (Angle <= 0.f)
		{
			Angle += 360.f;
		}

		return Angle;

	}



	float DirToRot(float4 u, float4 v)
	{

		u.y = -u.z;
		v.y = -v.z;


		u.z = 0.f;
		u.w = 0.f;

		v.z = 0.f;
		v.w = 0.f;

		float Angle = float4::VectorXYtoDegree(v, u);

		Angle += 90.f;

		if (Angle >= 360.f)
		{
			Angle -= 360.f;
		}
		else if (Angle <= 0.f)
		{
			Angle += 360.f;
		}

		return Angle;

	}
	//x = zy
	//y = xz 
	//z = yx

	float DirToRotX(float4 u, float4 v)
	{
		
		u.x = u.z;
		v.x = v.z;

		u.z = 0.f;
		u.w = 0.f;

		v.z = 0.f;
		v.w = 0.f;

		float Angle = float4::VectorXYtoDegree(v, u);

	

		if (Angle >= 360.f)
		{
			Angle -= 360.f;
		}
		else if (Angle <= 0.f)
		{
			Angle += 360.f;
		}


		if (Angle > 180.f)
		{
			int a = 0;
		}

		return Angle;

	}

	float DirToRotZ(float4 u, float4 v)
	{

	
		u.z = 0.f;
		u.w = 0.f;

		v.z = 0.f;
		v.w = 0.f;

		float Angle = float4::VectorXYtoDegree(v, u);

		//Angle += 90.f;

		if (Angle >= 360.f)
		{
			Angle -= 360.f;
		}
		else if (Angle <= 0.f)
		{
			Angle += 360.f;
		}

		if (Angle > 180.f)
		{
			int a = 0;
		}
		return Angle;

	}


public:
	bool	m_bHitActionCheck = false;
	float m_fcurHitTime = 0.f;
	//맞을때 이 함수만 추가해 주세요
	void HitUpdate(float _Delta , float HitTime)
	{

		if (!m_bHitActionCheck)
			return;

		if (false == m_bHittedSound)
		{
			HittedSound();
			m_bHittedSound = true;
		}



		m_fcurHitTime += _Delta;
		SetHitted(m_fcurHitTime);

		if (m_fcurHitTime >= HitTime)
		{
			m_bHitActionCheck = false;
			m_bHittedSound = false;
			m_fcurHitTime = 0.f;
			SetHitted(m_fcurHitTime);
		}
	
	}



public:
	UINFO	m_Info;
	float m_fLifeTime;
	float m_fSpeed;


	float4 m_fHitPos = {0};
	bool m_bHitCheck = false;
	float4 m_fHitDir = {0};
	float hitTime = 0.f;


	float m_fHitTime = 0.f;
	bool m_bhitCheck = false;

public:
	void CameraShake(float _Time);

	void InitializePaperBurn(std::shared_ptr <GameEngineFBXAnimationRenderer>& _sptrFBXAnimationRenderer);
	void InitializePaperBurn(std::shared_ptr <GameEngineFBXAnimationRenderer>& _sptrFBXAnimationRenderer, const size_t& _uMeshIndex);
	void InitializePaperBurn(std::shared_ptr <GameEngineFBXStaticRenderer>& _sptrFBXStaticRenderer);
	void SetPaperBurnInfo(unsigned int _uOnOffPaperBurn, float _fEffectTime);

	void SetHitted(float _fHitted) { mPaperBurnInfo.mfHitted = _fHitted; };

	virtual void HittedSound() {};

private:
	float ShakeMaxTime = 0.f;
	float ShakeTime = 0.f;

	float ShakeForce = 1000.f;
	float ShakeTCheck = 0.f;
	bool ShakeDirCheck = false;


	bool ShakeCheck = false;

	float4 CameraLastDir = {};

protected:
	PaperBurnInfo mPaperBurnInfo;
	float mfPaperburnDeathTime;
	bool mbOnce;
	bool mbOnDeath;
	float m_fAccTimeForPaperburn;
	bool m_bDeathEnd;
	
	float m_fAccTimeForHitted;

	class GameEngineSoundPlayer m_structSoundPlayer;

	bool m_bHittedSound;
	
};

