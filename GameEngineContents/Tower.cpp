#include "PreCompile.h"
#include "Tower.h"
#include "Player.h"

#include"SnapBase.h"
#include"SnapCircle.h"
#include"LaserTarget.h"
#include "TowerLaser.h"
#include "RealLaserMgr.h"

#include "TowerBossUI.h"


#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"

#include "GameEngineBase/GameEngineRandom.h"

#include "Spike.h"
Tower::Tower() :
	StartPostion()
	, DirPower()
	, Pos()
{
}

Tower::~Tower()
{
}
 
void Tower::Start()
{
	

	m_Info.m_Hp = 30;
	m_Info.m_MaxHp = 10;
	m_Info.Dammage = 1;
	m_fSpeed = 100.f;
	
	//GetTransform().SetLocalRotation({0.f,-45.f,0.f});
	GetTransform().SetWorldPosition({ 356.f,3000.F,25.f });


	MainUI = GetLevel()->CreateActor<TowerBossUI>(OBJECTORDER::UI);




	FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXAnimationRenderer->ChangeCamera(CAMERAORDER::USER1);
	for (size_t i = 0; i < 10; ++i) 
	{
		if (8 == i ||  5 == i || 6 == i )
		{
			
			continue;
		}
		FBXAnimationRenderer->SetFBXMesh("Tower.fbx", "PaperBurn", i);

		InitializePaperBurn(FBXAnimationRenderer, i);
	}

#pragma region PaperBurn

		m_fAccTimeForPaperburn = 0.f;
		mfPaperburnDeathTime = 2.0f;

#pragma endregion


	FBXAnimationRenderer->GetTransform().SetLocalScale(float4{ 100.5f, 100.5f, 100.5f });
	FBXAnimationRenderer->GetTransform().SetLocalRotation(float4{ 0.f, 225.f,0.f });

	{
		Event.ResourcesName = "Tower_Idle.FBX";
		Event.Loop = true;
		Event.Inter = 0.05f;
		FBXAnimationRenderer->CreateFBXAnimation("Tower_Idle", Event);

	
	}


	{
		Event.ResourcesName = "Tower_Fall_Start.FBX";
		Event.Loop = false;
		Event.Inter = 0.05f;
		FBXAnimationRenderer->CreateFBXAnimation("Tower_Fall_Start", Event);


	}


	{
		Event.ResourcesName = "Tower_Jump.FBX";
		Event.Loop = false;
		Event.Inter = 0.05f;
		FBXAnimationRenderer->CreateFBXAnimation("Tower_Jump", Event);
		FBXAnimationRenderer->AnimationBindEnd("Tower_Jump", std::bind(&Tower::AniJumpEnd, this, std::placeholders::_1));
		FBXAnimationRenderer->AnimationBindFrame("Tower_Jump", std::bind(&Tower::AniJumpFrame, this, std::placeholders::_1));


	}



	{
		Event.ResourcesName = "Tower_Laser.FBX";
		Event.Loop = false;
		Event.Inter = 0.05f;
		FBXAnimationRenderer->CreateFBXAnimation("Tower_Laser", Event);
		FBXAnimationRenderer->AnimationBindEnd("Tower_Laser", std::bind(&Tower::AniLaserEnd, this, std::placeholders::_1));
		FBXAnimationRenderer->AnimationBindFrame("Tower_Laser", std::bind(&Tower::AniLaserFrame, this, std::placeholders::_1));


	}


	{
		Event.ResourcesName = "Tower_Laser_E.FBX";
		Event.Loop = false;
		Event.Inter = 0.05f;
		FBXAnimationRenderer->CreateFBXAnimation("Tower_Laser_E", Event);
		FBXAnimationRenderer->AnimationBindEnd("Tower_Laser_E", std::bind(&Tower::AniLaserEEnd, this, std::placeholders::_1));


	}



	{
		Event.ResourcesName = "Tower_Slam.FBX";
		Event.Loop = false;
		Event.Inter = 0.05f;
		FBXAnimationRenderer->CreateFBXAnimation("Tower_Slam", Event);
		FBXAnimationRenderer->AnimationBindEnd("Tower_Slam", std::bind(&Tower::AniSlamEnd, this, std::placeholders::_1));
		FBXAnimationRenderer->AnimationBindFrame("Tower_Slam", std::bind(&Tower::AniSlamFrame, this, std::placeholders::_1));


	}




	{
		Event.ResourcesName = "Tower_Snap.FBX";
		Event.Loop = false;
		Event.Inter = 0.05f;
		FBXAnimationRenderer->CreateFBXAnimation("Tower_Snap", Event);
		FBXAnimationRenderer->AnimationBindEnd("Tower_Snap", std::bind(&Tower::AniSnapEnd, this, std::placeholders::_1));


	}

	{
		Event.ResourcesName = "Tower_Stand.FBX";
		Event.Loop = true;
		Event.Inter = 0.05f;
		FBXAnimationRenderer->CreateFBXAnimation("Tower_Stand", Event);


	}



	FBXAnimationRenderer->ChangeAnimation("Tower_Slam");
	FBXAnimationRenderer->PauseSwtich();


	{
		StartCollision = CreateComponent<GameEngineCollision>();
		StartCollision->GetTransform().SetLocalScale({ 500.0f, 500.0f, 200.0f });
		StartCollision->GetTransform().SetWorldPosition({-1010.f, 0.f , -1200.f});
		StartCollision->ChangeOrder(OBJECTORDER::Monster);

	}



	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 100.0f, 500.0f, 100.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);
	
	}

	StateManager.CreateStateMember("Start"
		, std::bind(&Tower::StateStartUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tower::StateStart, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("Idle"
		, std::bind(&Tower::IdleUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tower::IdleStart,this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Move"
		, std::bind(&Tower::MoveUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tower::MoveStart,this, std::placeholders::_1)
		, std::bind(&Tower::MoveEnd,this, std::placeholders::_1)
	);



	StateManager.CreateStateMember("Laser"
		, std::bind(&Tower::LaserUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tower::LaserStart,this, std::placeholders::_1)
		, std::bind(&Tower::LaserEnd,this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("Att"
		, std::bind(&Tower::AttUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tower::AttStart,this, std::placeholders::_1)
		, std::bind(&Tower::AttEnd,this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Jump"
		, std::bind(&Tower::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tower::JumpStart, this, std::placeholders::_1)
		, std::bind(&Tower::JumpEnd, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Death"
		, std::bind(&Tower::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tower::DeathStart, this, std::placeholders::_1)
		, std::bind(&Tower::DeathEnd, this, std::placeholders::_1)
	);



	StateManager.ChangeState("Start");
}


void Tower::DeathStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("Tower_Laser_E");
	//레이저
	//if (m_CLaserTarget.lock())
	//{
	//	m_CLaserTarget.lock()->Death();
	//	m_CLaserTarget.reset();


	//}
	//if (m_CLaser.lock())
	//{
	//	m_CLaser.lock()->Death();
	//	m_CLaser.reset();


	//}

	if(m_RealLaserMgr)
	{

		m_RealLaserMgr->DeleteAll();
		m_RealLaserMgr->Death();
		m_RealLaserMgr = nullptr;
	}




}

void Tower::DeathEnd(const StateInfo& _Info)
{

}

void Tower::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{

}




void Tower::Update(float _DeltaTime)
{



#pragma region PaperBurn
	if (m_Info.m_Hp <= 0 && false == mbOnce)
	{
		Death(mfPaperburnDeathTime);
		m_cSpike.lock()->Death(mfPaperburnDeathTime);
		m_structSoundPlayer.Stop();
		m_structSoundPlayer = GameEngineSound::SoundPlayControl("24_MiddleBossDeath.mp3");
		mbOnce = true;
		mbOnDeath = true;
		return;
	}

	if (m_Info.m_Hp <= 0 && true == mbOnDeath && true == m_bDeathEnd)
	{
		StateManager.ChangeState("Death");
		Collision->Off();
		m_fAccTimeForPaperburn += _DeltaTime;
		SetPaperBurnInfo(1u, m_fAccTimeForPaperburn);


		return;
	}
#pragma endregion




	BaseUpdate(_DeltaTime);

	//맞을때 이 함수만 추가해 주세요
	HitUpdate(_DeltaTime, 0.5f);


	if (!m_bstart)
	{
		if (true == StartCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB))
		{

			m_bstart = true;
			StateManager.ChangeState("Move");
		}
	}








	if (m_Info.m_Hp <= 0)
	{
		// Death();
		m_bDeathEnd = true;
	}
	else
	{


	}

	StateManager.Update(_DeltaTime);



}



void Tower::MoveStart(const StateInfo& _Info)
{
	Player::GetMainPlayer()->m_bTowerCameraCheck = true;
	GetLevel()->GetMainCameraActorTransform().SetWorldRotation({ -12.f,43.f,0.f });
	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({-1185.f,68.f,-1445.f });
	FBXAnimationRenderer->ChangeAnimation("Tower_Slam");

	

}
void Tower::MoveEnd(const StateInfo& _Info)
{

	MainUI.lock()->Off();

	GetLevel()->GetMainCameraActorTransform().SetWorldRotation({ 45.f,0.f,0.f });
	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	PlayerPos.y +=  1700.f;
	PlayerPos.z -=  1700.f;
	GetLevel()->GetMainCameraActorTransform().SetWorldPosition(PlayerPos);
	


	Player::GetMainPlayer()->m_bTowerCameraCheck = false;
	m_bstart = false;
}
void Tower::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	m_fSpeed += _DeltaTime * 1200.f;

	//GetTransform().SetWorldDownMove(m_fSpeed, _DeltaTime);

	float4 MyPos = GetTransform().GetWorldPosition();
	if (MyPos.y <= 0.f)
	{

		MainUI.lock()->m_bStartCheck = true;
		MyPos.y = 0.f;
		GetTransform().SetWorldPosition(MyPos);
		
		GetLevel()->GetMainCameraActor();


		if (!ShakeOneCheck)
		{
			CameraShake(1.f);
			ShakeOneCheck = true;
		}
		

		m_fLifeTime += _DeltaTime;
		if (m_fLifeTime >= 5.f)
		{
			StateManager.ChangeState("Idle");
			float4 MyPos = GetTransform().GetWorldPosition();
			MyPos.y = 25.f;
			GetTransform().SetWorldPosition(MyPos);

		}

		if(!m_bStartPause)
		{
			m_bStartPause = true;
			FBXAnimationRenderer->PauseSwtich();
		}

	}
	else
	{
		GetTransform().SetWorldDownMove(m_fSpeed, _DeltaTime);
	}


}
void Tower::AniSlamFrame(const GameEngineRenderingEvent& _Data)
{
	if (1u == _Data.CurFrame)
	{
		m_structSoundPlayer.Stop();
		m_structSoundPlayer = GameEngineSound::SoundPlayControl("22_MiddleBossJump.mp3");
	}
}
void Tower::AniSlamEnd(const GameEngineRenderingEvent& _Data)
{

	FBXAnimationRenderer->ChangeAnimation("Tower_Stand");

}









void Tower::LaserStart(const StateInfo& _Info)
{
	m_bLaserUP = true;
	m_bLaserDown = false;
	m_fLaserMoveTime = 0.f;

	


}
void Tower::LaserEnd(const StateInfo& _Info)
{

	

}
void Tower::LaserUpdate(float _DeltaTime, const StateInfo& _Info)
{
	m_fLaserMoveTime += _DeltaTime;


	if (m_bLaserUP)
	{
		
		GetTransform().SetWorldUpMove(35.f, _DeltaTime);


		if (m_fLaserMoveTime >= 2.f)
		{
			m_bLaserUP = false;
			m_fLaserMoveTime = 0.f;
			FBXAnimationRenderer->ChangeAnimation("Tower_Laser");



		}
	}

	if (m_bLaserDown)
	{

		GetTransform().SetWorldDownMove(55.f, _DeltaTime);
		float4 MyPos = GetTransform().GetWorldPosition();
		if (MyPos.y <= 5.f)
		{
			m_bLaserDown = false;
			
		}

	}

}
	 
void Tower::AniLaserEnd(const GameEngineRenderingEvent& _Data)
{
	m_bLaserDown = true;
	m_bLaserUP = false;
	m_fLaserMoveTime = 0.f;

	//레이저
	//m_CLaserTarget.lock()->Death();
	//m_CLaserTarget.reset();

	//m_CLaser.lock()->Death();
	//m_CLaser.reset();
	//RealLaserMgr
	FBXAnimationRenderer->ChangeAnimation("Tower_Laser_E");
	m_RealLaserMgr->DeleteAll();
	m_RealLaserMgr->Death();
	m_RealLaserMgr = nullptr;
}

void Tower::AniLaserFrame(const GameEngineRenderingEvent& _Data)
{


	if (m_RealLaserMgr == nullptr)
	{
		m_RealLaserMgr = GetLevel()->CreateActor<RealLaserMgr>(OBJECTORDER::MonsterAtt);
		m_RealLaserMgr->MakeTarget();
		m_RealLaserMgr->MakeLaser();
	}

	if (_Data.CurFrame == 63)
	{
		m_structSoundPlayer.Stop();
		m_structSoundPlayer = GameEngineSound::SoundPlayControl("23_MiddleBossLaser.mp3");
		m_RealLaserMgr->StartLaser();
	}

}








void Tower::AniLaserEEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Idle");
}





void Tower::AttStart(const StateInfo& _Info)
{

	FBXAnimationRenderer->ChangeAnimation("Tower_Snap");
}
void Tower::AttEnd(const StateInfo& _Info)
{
	
	/*std::weak_ptr < SnapBase> Bullet = */
	GetLevel()->CreateActor<SnapBase>(OBJECTORDER::MonsterAtt);


}
void Tower::AttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	


}




void Tower::JumpStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("Tower_Jump");
	
	

}

void Tower::JumpEnd(const StateInfo& _Info)
{

}

void Tower::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{

}


void Tower::AniJumpEnd(const GameEngineRenderingEvent& _Data)
{

	StateManager.ChangeState("Idle");
}

void Tower::AniJumpFrame(const GameEngineRenderingEvent& _Data)
{
	if (19u == _Data.CurFrame)
	{
		m_structSoundPlayer.Stop();
		m_structSoundPlayer = GameEngineSound::SoundPlayControl("22-1_MiddleBossSmash.mp3");
	}
	if (_Data.CurFrame == 22)
	{
		
		std::weak_ptr < SnapCircle> Bullet = GetLevel()->CreateActor<SnapCircle>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
		CameraShake(1.f);
	}


	if (50u == _Data.CurFrame)
	{
		m_structSoundPlayer.Stop();
		m_structSoundPlayer = GameEngineSound::SoundPlayControl("22-1_MiddleBossSmash.mp3");
	}
	if (_Data.CurFrame == 55)
	{
		
		m_structSoundPlayer.Stop();
		m_structSoundPlayer = GameEngineSound::SoundPlayControl("22-1_MiddleBossSmash.mp3");
		std::weak_ptr < SnapCircle> Bullet = GetLevel()->CreateActor<SnapCircle>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
		CameraShake(0.5f);
	}

	if (93u == _Data.CurFrame)
	{
		m_structSoundPlayer.Stop();
		m_structSoundPlayer = GameEngineSound::SoundPlayControl("22-1_MiddleBossSmash.mp3");
	}
	if (_Data.CurFrame == 100)
	{
		m_structSoundPlayer.Stop();
		m_structSoundPlayer = GameEngineSound::SoundPlayControl("22-1_MiddleBossSmash.mp3");
		std::weak_ptr < SnapCircle> Bullet = GetLevel()->CreateActor<SnapCircle>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
		CameraShake(0.5f);
	}
}




void Tower::AniSnapEnd(const GameEngineRenderingEvent& _Data)
{

	StateManager.ChangeState("Idle");

}



void Tower::IdleStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("Tower_Idle");
	m_bIdleUpDown = false;
	m_fUpDownTime = 0.f;
	//AttType = 0;

	float4 MyPos = GetTransform().GetWorldPosition();
	MyPos.y = 25.f;

	GetTransform().SetWorldPosition(MyPos);




}

void Tower::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{

	m_fUpDownTime += _DeltaTime;

	m_fAttCTime += _DeltaTime;

	if (m_bIdleUpDown)
	{
		if (m_fUpDownTime > 1.f)
		{
			m_fUpDownTime = 0.f;
			m_bIdleUpDown = !m_bIdleUpDown;
		}
		GetTransform().SetWorldDownMove(25.f, _DeltaTime);
	}
	else
	{

		if (m_fUpDownTime > 1.f)
		{
			m_fUpDownTime = 0.f;
			m_bIdleUpDown = !m_bIdleUpDown;
		}


		GetTransform().SetWorldUpMove(25.f, _DeltaTime);
	}


	if (m_fAttCTime >= 3.f)
	{
		m_fAttCTime = 0.;
		//++AttType;// = GameEngineRandom::MainRandom.RandomInt(1, 3);
		++AttType2;


		if (AttType2 > 3)
		{
			AttType2 = 1;
		}


		AttType = AttType2;
		//레이저
		//AttType = 1;
	}
	
	
	if (AttType == 1)
	{
		StateManager.ChangeState("Laser");
		AttType = 0;
	}
	else if (AttType == 2)
	{
		StateManager.ChangeState("Jump");
		AttType = 0;
	}
	else if (AttType == 3)
	{
		StateManager.ChangeState("Att");
		AttType = 0;
	}



}


void Tower::StateStart(const StateInfo& _Info)
{
}
void Tower::StateStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
}