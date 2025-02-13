#pragma once
#include <GameEngineCore/GameEngineFBXAnimationRenderer.h>
//
//struct PaperBurnInfo
//{
//	unsigned int	muOnOffPaperBurn;
//	float			mfEffectTime;
//	float			mfPadding1;
//	float			mfPadding2;
//};

// ���� :
class PaperburnRenderer : public GameEngineFBXRenderer
{
public:
	// constrcuter destructer
	PaperburnRenderer();
	~PaperburnRenderer();

	// delete Function
	PaperburnRenderer(const PaperburnRenderer& _Other) = delete;
	PaperburnRenderer(PaperburnRenderer&& _Other) noexcept = delete;
	PaperburnRenderer& operator=(const PaperburnRenderer& _Other) = delete;
	PaperburnRenderer& operator=(PaperburnRenderer&& _Other) noexcept = delete;

	void InitializePaperBurn(std::shared_ptr <GameEngineFBXAnimationRenderer>& _sptrFBXAnimationRenderer);
	void SetPaperBurnInfo(unsigned int _uOnOffPaperBurn, float _fEffectTime);

protected:
	void Start();
	void Update(float _fDeltatime);
	void End();

private:

public:

protected:

private:
	// PaperBurnInfo mPaperBurnInfo;

};

