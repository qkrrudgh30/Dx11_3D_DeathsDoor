#pragma once
#include "GameEngineShader.h"
#include "GameEngineRes.h"

// ���� :
class GameEnginePixelShader 
	: public GameEngineShader
	, public GameEngineRes<GameEnginePixelShader>
{
	friend GameEngineShader;
public:
	static std::shared_ptr < GameEnginePixelShader> Load(
		const std::string& _Path, 
		const std::string& _EntryPoint, 
		UINT _VersionHigh = 5, UINT _VersionLow = 0);

	static std::shared_ptr < GameEnginePixelShader> Load(
		const std::string& _Path, 
		const std::string& _Name,
		const std::string& _EntryPoint,
		UINT _VersionHigh, UINT _VersionLow);

	// constrcuter destructer
	GameEnginePixelShader();
	~GameEnginePixelShader();


	// delete Function
	GameEnginePixelShader(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader(GameEnginePixelShader&& _Other) noexcept = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader& operator=(GameEnginePixelShader&& _Other) noexcept = delete;

	void Setting();

	bool GetIsDeferred()
	{
		return IsDeferred;
	}

protected:
	void ShaderCompile(
		const std::string& _Path,
		const std::string& _EntryPoint,
		UINT _VersionHigh, UINT _VersionLow);

private:
	bool IsDeferred;
	ID3D11PixelShader* ShaderPtr;
};

