
#include "PreCompile.h"
#include "PlayerMainUI.h"

PlayerMainUI::PlayerMainUI()	:
	//m_Player()
	RendererArrow()
	,RendererFire()
	,RendererHook()
	,RendererSword()
	,RendererArrowSet()
	,RendererFireSet()
	,RendererHookSet()
	,RendererSwordSet()
	,RendererHp1()
	,RendererHp2()
	,RendererHp3()
	,RendererHp4()
	,RendererHp5()
	,RendererHp6()
	,RendererHp7()
	,RendererHp8()
	,RendererArrow1()
	,RendererArrow2()
	,RendererArrow3()
	,RendererArrow4()
	, FogRender()
{
}

PlayerMainUI::~PlayerMainUI()
{
}

void PlayerMainUI::Start()
{
	{
		RendererSwordSet = CreateComponent<GameEngineUIRenderer>();
		RendererSwordSet->SetTexture("hud_abilty_frame_chipped.png");
		RendererSwordSet->ScaleToTexture();
		RendererSwordSet->GetTransform().SetLocalScale({ 100, 100, 1 });
		RendererSwordSet->GetTransform().SetLocalPosition({ -580.f,250.f, -250.f });
		RendererSwordSet->ChangeCamera(CAMERAORDER::UICAMERA);
	}


	{
		RendererArrowSet = CreateComponent<GameEngineUIRenderer>();
		RendererArrowSet->SetTexture("hud_abilty_frame_chipped.png");
		RendererArrowSet->ScaleToTexture();
		RendererArrowSet->GetTransform().SetLocalScale({ 100, 100, 1 });
		RendererArrowSet->GetTransform().SetLocalPosition({ -525.f,305.f, -250.f });
		RendererArrowSet->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererArrowSet->GetPixelData().MulColor.a = 0.5f;
	}


	{
		RendererFireSet = CreateComponent<GameEngineUIRenderer>();
		RendererFireSet->SetTexture("hud_abilty_frame_chipped.png");
		RendererFireSet->ScaleToTexture();
		RendererFireSet->GetTransform().SetLocalScale({ 100, 100, 1 });
		RendererFireSet->GetTransform().SetLocalPosition({ -470.f,250.f, -250.f });
		RendererFireSet->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererFireSet->GetPixelData().MulColor.a = 0.5f;
	}


	{
		RendererHookSet = CreateComponent<GameEngineUIRenderer>();
		RendererHookSet->SetTexture("hud_abilty_frame_chipped.png");
		RendererHookSet->ScaleToTexture();
		RendererHookSet->GetTransform().SetLocalScale({ 100, 100, 1 });
		RendererHookSet->GetTransform().SetLocalPosition({ -525.f,195.f, -250.f });
		RendererHookSet->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererHookSet->GetPixelData().MulColor.a = 0.5f;
	}


	//무기들
	{
		RendererSword = CreateComponent<GameEngineUIRenderer>();
		RendererSword->SetTexture("cutCursor.png");
		RendererSword->ScaleToTexture();
		RendererSword->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererSword->GetTransform().SetLocalPosition({ -580.f,250.f, -250.f });
		RendererSword->ChangeCamera(CAMERAORDER::UICAMERA);
	}


	{
		RendererArrow = CreateComponent<GameEngineUIRenderer>();
		RendererArrow->SetTexture("Icon_Arrow.png");
		RendererArrow->ScaleToTexture();
		RendererArrow->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererArrow->GetTransform().SetLocalPosition({ -525.f,305.f, -250.f });
		RendererArrow->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererArrow->GetPixelData().MulColor.a = 0.5f;
	}


	{
		RendererFire = CreateComponent<GameEngineUIRenderer>();
		RendererFire->SetTexture("Icon_Fireball.png");
		RendererFire->ScaleToTexture();
		RendererFire->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererFire->GetTransform().SetLocalPosition({ -470.f,250.f, -250.f });
		RendererFire->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererFire->GetPixelData().MulColor.a = 0.5f;
	}


	{
		RendererHook = CreateComponent<GameEngineUIRenderer>();
		RendererHook->SetTexture("Icon_Hook.png");
		RendererHook->ScaleToTexture();
		RendererHook->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererHook->GetTransform().SetLocalPosition({ -525.f,195.f, -250.f });
		RendererHook->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererHook->GetPixelData().MulColor.a = 0.5f;
	}

	//hp 틀

	{
		std::shared_ptr < GameEngineUIRenderer> Renderer = CreateComponent<GameEngineUIRenderer>();
		Renderer->SetTexture("icon_crystal.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalScale({ 55, 55, 1 });
		Renderer->GetTransform().SetLocalPosition({ -445.f,335.f, -250.f });
		Renderer->GetTransform().SetLocalRotation({ 0.f,0.f,-30.f });
		Renderer->ChangeCamera(CAMERAORDER::UICAMERA);
	}

	{
		std::shared_ptr < GameEngineUIRenderer> Renderer = CreateComponent<GameEngineUIRenderer>();
		Renderer->SetTexture("icon_crystal.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalScale({ 55, 55, 1 });
		Renderer->GetTransform().SetLocalPosition({ -395.f,335.f, -250.f });
		Renderer->GetTransform().SetLocalRotation({ 0.f,0.f,-30.f });
		Renderer->ChangeCamera(CAMERAORDER::UICAMERA);
	}

	{
		std::shared_ptr < GameEngineUIRenderer>Renderer = CreateComponent<GameEngineUIRenderer>();
		Renderer->SetTexture("icon_crystal.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalScale({ 55, 55, 1 });
		Renderer->GetTransform().SetLocalPosition({ -345.f,335.f, -250.f });
		Renderer->GetTransform().SetLocalRotation({ 0.f,0.f,-30.f });
		Renderer->ChangeCamera(CAMERAORDER::UICAMERA);
	}

	{
		std::shared_ptr < GameEngineUIRenderer> Renderer = CreateComponent<GameEngineUIRenderer>();
		Renderer->SetTexture("icon_crystal.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalScale({ 55, 55, 1 });
		Renderer->GetTransform().SetLocalPosition({ -295.f,335.f, -250.f });
		Renderer->GetTransform().SetLocalRotation({ 0.f,0.f,-30.f });
		Renderer->ChangeCamera(CAMERAORDER::UICAMERA);
	}

	//hp



	{
		RendererHp1 = CreateComponent<GameEngineUIRenderer>();
		RendererHp1->SetTexture("icon_magic_crystal.png");
		RendererHp1->ScaleToTexture();
		RendererHp1->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererHp1->GetTransform().SetLocalPosition({ -445.f,335.f, -250.f });
		RendererHp1->GetTransform().SetLocalRotation({ 0.f,0.f,-30.f });
		RendererHp1->ChangeCamera(CAMERAORDER::UICAMERA);
		
	}



	{
		RendererHp2 = CreateComponent<GameEngineUIRenderer>();
		RendererHp2->SetTexture("icon_vitality_crystal.png");
		RendererHp2->ScaleToTexture();
		RendererHp2->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererHp2->GetTransform().SetLocalPosition({ -445.f,335.f, -250.f });
		RendererHp2->GetTransform().SetLocalRotation({ 0.f,0.f,-30.f });
		RendererHp2->ChangeCamera(CAMERAORDER::UICAMERA);
		
	}



	{
		RendererHp3 = CreateComponent<GameEngineUIRenderer>();
		RendererHp3->SetTexture("icon_magic_crystal.png");
		RendererHp3->ScaleToTexture();
		RendererHp3->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererHp3->GetTransform().SetLocalPosition({ -395.f,335.f, -250.f });
		RendererHp3->GetTransform().SetLocalRotation({ 0.f,0.f,-30.f });
		RendererHp3->ChangeCamera(CAMERAORDER::UICAMERA);
	
	}



	{
		RendererHp4 = CreateComponent<GameEngineUIRenderer>();
		RendererHp4->SetTexture("icon_vitality_crystal.png");
		RendererHp4->ScaleToTexture();
		RendererHp4->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererHp4->GetTransform().SetLocalPosition({ -395.f,335.f, -250.f });
		RendererHp4->GetTransform().SetLocalRotation({ 0.f,0.f,-30.f });
		RendererHp4->ChangeCamera(CAMERAORDER::UICAMERA);
		
	}



	{
		RendererHp5 = CreateComponent<GameEngineUIRenderer>();
		RendererHp5->SetTexture("icon_magic_crystal.png");
		RendererHp5->ScaleToTexture();
		RendererHp5->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererHp5->GetTransform().SetLocalPosition({ -345.f,335.f, -250.f });
		RendererHp5->GetTransform().SetLocalRotation({ 0.f,0.f,-30.f });
		RendererHp5->ChangeCamera(CAMERAORDER::UICAMERA);
		
	}



	{
		RendererHp6 = CreateComponent<GameEngineUIRenderer>();
		RendererHp6->SetTexture("icon_vitality_crystal.png");
		RendererHp6->ScaleToTexture();
		RendererHp6->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererHp6->GetTransform().SetLocalPosition({ -345.f,335.f, -250.f });
		RendererHp6->GetTransform().SetLocalRotation({ 0.f,0.f,-30.f });
		RendererHp6->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererHp6->Off();
	}



	{
		RendererHp7 = CreateComponent<GameEngineUIRenderer>();
		RendererHp7->SetTexture("icon_magic_crystal.png");
		RendererHp7->ScaleToTexture();
		RendererHp7->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererHp7->GetTransform().SetLocalPosition({ -295.f,335.f, -250.f });
		RendererHp7->GetTransform().SetLocalRotation({ 0.f,0.f,-30.f });
		RendererHp7->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererHp7->Off();
		
	}



	{
		RendererHp8 = CreateComponent<GameEngineUIRenderer>();
		RendererHp8->SetTexture("icon_vitality_crystal.png");
		RendererHp8->ScaleToTexture();
		RendererHp8->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererHp8->GetTransform().SetLocalPosition({ -295.f,335.f, -250.f });
		RendererHp8->GetTransform().SetLocalRotation({ 0.f,0.f,-30.f});
		RendererHp8->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererHp8->Off();
	}


	//화살 틀 

	{
		std::shared_ptr < GameEngineUIRenderer> Renderer = CreateComponent<GameEngineUIRenderer>();
		Renderer->SetTexture("hud_energy_empty.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalScale({ 35, 35, 1 });
		Renderer->GetTransform().SetLocalPosition({ -425.f,300.f, -250.f });
		Renderer->ChangeCamera(CAMERAORDER::UICAMERA);
	}

	{
		std::shared_ptr < GameEngineUIRenderer> Renderer = CreateComponent<GameEngineUIRenderer>();
		Renderer->SetTexture("hud_energy_empty.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalScale({ 35, 35, 1 });
		Renderer->GetTransform().SetLocalPosition({ -390.f,300.f, -250.f });
		Renderer->ChangeCamera(CAMERAORDER::UICAMERA);
	}

	{
		std::shared_ptr < GameEngineUIRenderer> Renderer = CreateComponent<GameEngineUIRenderer>();
		Renderer->SetTexture("hud_energy_empty.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalScale({ 35, 35, 1 });
		Renderer->GetTransform().SetLocalPosition({ -355.f,300.f, -250.f });
		Renderer->ChangeCamera(CAMERAORDER::UICAMERA);
	}

	{
		std::shared_ptr < GameEngineUIRenderer> Renderer = CreateComponent<GameEngineUIRenderer>();
		Renderer->SetTexture("hud_energy_empty.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalScale({ 35, 35, 1 });
		Renderer->GetTransform().SetLocalPosition({ -320.f,300.f, -250.f });
		Renderer->ChangeCamera(CAMERAORDER::UICAMERA);
	}



	//화살

	{
		RendererArrow1 = CreateComponent<GameEngineUIRenderer>();
		RendererArrow1->SetTexture("hud_energy_inactive.png");
		RendererArrow1->ScaleToTexture();
		RendererArrow1->GetTransform().SetLocalScale({ 30, 30, 1 });
		RendererArrow1->GetTransform().SetLocalPosition({ -425.f,300.f, -250.f });
		RendererArrow1->ChangeCamera(CAMERAORDER::UICAMERA);

	}



	{
		RendererArrow2 = CreateComponent<GameEngineUIRenderer>();
		RendererArrow2->SetTexture("hud_energy_inactive.png");
		RendererArrow2->ScaleToTexture();
		RendererArrow2->GetTransform().SetLocalScale({ 30, 30, 1 });
		RendererArrow2->GetTransform().SetLocalPosition({ -390.f,300.f, -250.f });
		RendererArrow2->ChangeCamera(CAMERAORDER::UICAMERA);

	}



	{
		RendererArrow3 = CreateComponent<GameEngineUIRenderer>();
		RendererArrow3->SetTexture("hud_energy_inactive.png");
		RendererArrow3->ScaleToTexture();
		RendererArrow3->GetTransform().SetLocalScale({ 30, 30, 1 });
		RendererArrow3->GetTransform().SetLocalPosition({ -355.f,300.f, -250.f });
		RendererArrow3->ChangeCamera(CAMERAORDER::UICAMERA);

	}



	{
		RendererArrow4 = CreateComponent<GameEngineUIRenderer>();
		RendererArrow4->SetTexture("hud_energy_inactive.png");
		RendererArrow4->ScaleToTexture();
		RendererArrow4->GetTransform().SetLocalScale({ 30, 30, 1 });
		RendererArrow4->GetTransform().SetLocalPosition({ -320.f,300.f, -250.f });
		RendererArrow4->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererArrow4->Off();
	}





	



}

void PlayerMainUI::Update(float _DeltaTime)
{

	PlayerInfoCheck();


}

void PlayerMainUI::PlayerInfoCheck()
{
	PlayerInfoHPCheck();
	PlayerInfoWeaponCheck();
	PlayerInfoArrowCheck();



}

void PlayerMainUI::PlayerInfoHPCheck()
{

	Player* m_Player = Player::GetMainPlayer();


	if (m_Player->m_Info.m_Hp == 0)
	{
		RendererHp1->Off();
		RendererHp2->Off();
		RendererHp3->Off();
		RendererHp4->Off();
		RendererHp5->Off();
		RendererHp6->Off();
		RendererHp7->Off();
		RendererHp8->Off();
	}
	else if (m_Player->m_Info.m_Hp == 1)
	{
		RendererHp1->On();
		RendererHp2->Off();
		RendererHp3->Off();
		RendererHp4->Off();
		RendererHp5->Off();
		RendererHp6->Off();
		RendererHp7->Off();
		RendererHp8->Off();
	}
	else if (m_Player->m_Info.m_Hp == 2)
	{
		RendererHp1->On();
		RendererHp2->On();
		RendererHp3->Off();
		RendererHp4->Off();
		RendererHp5->Off();
		RendererHp6->Off();
		RendererHp7->Off();
		RendererHp8->Off();
	}
	else if (m_Player->m_Info.m_Hp == 3)
	{
		RendererHp1->On();
		RendererHp2->On();
		RendererHp3->On();
		RendererHp4->Off();
		RendererHp5->Off();
		RendererHp6->Off();
		RendererHp7->Off();
		RendererHp8->Off();
	}
	else if (m_Player->m_Info.m_Hp == 4)
	{
		RendererHp1->On();
		RendererHp2->On();
		RendererHp3->On();
		RendererHp4->On();
		RendererHp5->Off();
		RendererHp6->Off();
		RendererHp7->Off();
		RendererHp8->Off();
	}
	else if (m_Player->m_Info.m_Hp == 5)
	{
		RendererHp1->On();
		RendererHp2->On();
		RendererHp3->On();
		RendererHp4->On();
		RendererHp5->On();
		RendererHp6->Off();
		RendererHp7->Off();
		RendererHp8->Off();
	}
	else if (m_Player->m_Info.m_Hp == 6)
	{
		RendererHp1->On();
		RendererHp2->On();
		RendererHp3->On();
		RendererHp4->On();
		RendererHp5->On();
		RendererHp6->On();
		RendererHp7->Off();
		RendererHp8->Off();
	}
	else if (m_Player->m_Info.m_Hp == 7)
	{
		RendererHp1->On();
		RendererHp2->On();
		RendererHp3->On();
		RendererHp4->On();
		RendererHp5->On();
		RendererHp6->On();
		RendererHp7->On();
		RendererHp8->Off();
	}
	else if (m_Player->m_Info.m_Hp == 8)
	{
		RendererHp1->On();
		RendererHp2->On();
		RendererHp3->On();
		RendererHp4->On();
		RendererHp5->On();
		RendererHp6->On();
		RendererHp7->On();
		RendererHp8->On();
	}


}

void PlayerMainUI::PlayerInfoWeaponCheck()
{

	Player* m_Player = Player::GetMainPlayer();


	if (m_Player->m_Info.Weapontype == WEAPONTYPE::Sword)
	{
		RendererArrowSet->GetPixelData().MulColor.a = 0.5f;
		RendererFireSet->GetPixelData().MulColor.a = 0.5f;
		RendererHookSet->GetPixelData().MulColor.a = 0.5f;
		RendererSwordSet->GetPixelData().MulColor.a = 1.f;

		RendererArrow->GetPixelData().MulColor.a = 0.5f;
		RendererFire->GetPixelData().MulColor.a = 0.5f;
		RendererHook->GetPixelData().MulColor.a = 0.5f;
		RendererSword->GetPixelData().MulColor.a = 1.f;
	}
	else if (m_Player->m_Info.Weapontype == WEAPONTYPE::Arrow)
	{
		RendererArrowSet->GetPixelData().MulColor.a = 1.f;
		RendererFireSet->GetPixelData().MulColor.a = 0.5f;
		RendererHookSet->GetPixelData().MulColor.a = 0.5f;
		RendererSwordSet->GetPixelData().MulColor.a = 0.5f;

		RendererArrow->GetPixelData().MulColor.a = 1.f;
		RendererFire->GetPixelData().MulColor.a = 0.5f;
		RendererHook->GetPixelData().MulColor.a = 0.5f;
		RendererSword->GetPixelData().MulColor.a = 0.5f;
	}
	else if (m_Player->m_Info.Weapontype == WEAPONTYPE::Fire)
	{
		RendererArrowSet->GetPixelData().MulColor.a = 0.5f;
		RendererFireSet->GetPixelData().MulColor.a = 1.f;
		RendererHookSet->GetPixelData().MulColor.a = 0.5f;
		RendererSwordSet->GetPixelData().MulColor.a = 0.5f;

		RendererArrow->GetPixelData().MulColor.a = 0.5f;
		RendererFire->GetPixelData().MulColor.a = 1.f;
		RendererHook->GetPixelData().MulColor.a = 0.5f;
		RendererSword->GetPixelData().MulColor.a = 0.5f;
	}
	else if (m_Player->m_Info.Weapontype == WEAPONTYPE::Hook)
	{
		RendererArrowSet->GetPixelData().MulColor.a = 0.5f;
		RendererFireSet->GetPixelData().MulColor.a = 0.5f;
		RendererHookSet->GetPixelData().MulColor.a = 1.f;
		RendererSwordSet->GetPixelData().MulColor.a = 0.5f;

		RendererArrow->GetPixelData().MulColor.a = 0.5f;
		RendererFire->GetPixelData().MulColor.a = 0.5f;
		RendererHook->GetPixelData().MulColor.a = 1.f;
		RendererSword->GetPixelData().MulColor.a = 0.5f;
	}



}

void PlayerMainUI::PlayerInfoArrowCheck()
{


	Player* m_Player = Player::GetMainPlayer();


	if (m_Player->m_Info.ArrowCount == 0)
	{
		RendererArrow1->Off();
		RendererArrow2->Off();
		RendererArrow3->Off();
		RendererArrow4->Off();
	}
	else if (m_Player->m_Info.ArrowCount == 1)
	{
		RendererArrow1->On();
		RendererArrow2->Off();
		RendererArrow3->Off();
		RendererArrow4->Off();
	}
	else if (m_Player->m_Info.ArrowCount == 2)
	{
		RendererArrow1->On();
		RendererArrow2->On();
		RendererArrow3->Off();
		RendererArrow4->Off();
	}

	else if (m_Player->m_Info.ArrowCount == 3)
	{
		RendererArrow1->On();
		RendererArrow2->On();
		RendererArrow3->On();
		RendererArrow4->Off();
	}

	else if (m_Player->m_Info.ArrowCount == 4)
	{
		RendererArrow1->On();
		RendererArrow2->On();
		RendererArrow3->On();
		RendererArrow4->On();
	}


}
