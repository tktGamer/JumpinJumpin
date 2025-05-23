#pragma once
// ヘッダファイルの読み込み ===================================================
#include"pch.h"
#include<unordered_map>
#include<string>

// クラスの定義 ===============================================================
/**
  * @brief リソースの管理
  */
class ResourceManager
{
//エイリアス宣言
private:                                        //ファイル名　ハンドル
	using DDSTextureResource = std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>;
	using SoundResouce = std::unordered_map<std::string, std::unique_ptr<DirectX::SoundEffect>>;
	using ModelResouce = std::unordered_map<std::string,std::unique_ptr<DirectX::Model>>;
// クラス定数の宣言 -------------------------------------------------
public:
	static constexpr  char const* DEFAULT_DDS_TEXTURE_DIRECTORY = "Resources/Dds/";
	static constexpr  char const* DEFAULT_SOUND_DIRECTORY = "Resources/Sounds/";
	static constexpr  char const* DEFAULT_MODELS_DIRECTORY = "Resources/Models/";


// データメンバの宣言 -----------------------------------------------
private:
	DirectX::AudioEngine* m_audioEngine;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	//DDS画像データ群
	DDSTextureResource m_texture;
	//音データ群
	SoundResouce m_sounds;
	//モデルデータ群
	ModelResouce m_models;


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	ResourceManager(DirectX::AudioEngine* m_audioEngine, ID3D11DeviceContext* contexth);

	// デストラクタ
	~ResourceManager();


// 操作
public:
	//画像データ読み込み
	void LoadDDSTexture(ID3D11Device* device, wchar_t const*     filename);
	void LoadDDSTexture(ID3D11Device* device, const std::string& filename);
	//画像データ要求
	ID3D11ShaderResourceView* RequestDDSTexture(wchar_t const*     filename);
	ID3D11ShaderResourceView* RequestDDSTexture(const std::string& filename);

	//音データ要求
	DirectX::SoundEffect* RequestSound(wchar_t const*     filename);
	DirectX::SoundEffect* RequestSound(const std::string& filename);

	//モデルデータ読み込み
	void LoadModel(ID3D11Device* device, wchar_t const*     filename);
	void LoadModel(ID3D11Device* device, const std::string& filename);
	//モデルデータ要求
	DirectX::Model* RequestModel(wchar_t const*     filename);
	DirectX::Model* RequestModel(const std::string& filename);

	//全リソース削除
	void Clear();
	//wchar_tからstingに変換
	std::string WcharToString(wchar_t const* wchar_str);
	//stringからwchar_tに変換
	wchar_t* StringToWchar(const std::string& str);

	//SpriteBatchの取得
	DirectX::SpriteBatch* GetSpriteBatch();
};
