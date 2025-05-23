// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ResourceManager.h"
#include <codecvt>  // std::wstring_convert と std::codecvt_utf8 を使用

using namespace DirectX;



// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
ResourceManager::ResourceManager(DirectX::AudioEngine* audioEngine, ID3D11DeviceContext* context)
	:m_texture{}
	, m_sounds{}
	,m_models{}
{
	m_audioEngine = audioEngine;
	m_spriteBatch = std::make_unique<SpriteBatch>(context);
}

/**
 * @brief デストラクタ
 */
ResourceManager::~ResourceManager()
{
	//全リソースの削除
	Clear();
}



/**
 * @brief DDS画像データの読み込み
 *
 * @param[in] device   デバイス
 * @param[in] filename DDS画像データファイル名
 *
 * @return なし
 */
void ResourceManager::LoadDDSTexture(ID3D11Device* device, wchar_t const* filename)
{
	std::string stringFilename =  WcharToString(filename);
	//未登録の場合
	if (m_models.count(stringFilename) == 0) 
	{
		//画像ファイルの読み込み
		std::string fullPath = DEFAULT_DDS_TEXTURE_DIRECTORY + stringFilename;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureHandle;
		//DDSファイルの読み込み
		CreateDDSTextureFromFile(device, StringToWchar(fullPath), nullptr, textureHandle.ReleaseAndGetAddressOf());

		//画像データのハンドルを登録
		m_texture.insert(std::make_pair(stringFilename, std::move(textureHandle)));

	}

}
void ResourceManager::LoadDDSTexture(ID3D11Device* device, const std::string& filename)
{
	//未登録の場合
	if (m_models.count(filename) == 0)
	{
		//画像ファイルの読み込み
		std::string fullPath = DEFAULT_DDS_TEXTURE_DIRECTORY + filename;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureHandle;
		//DDSファイルの読み込み
		CreateDDSTextureFromFile(device, StringToWchar(fullPath), nullptr, textureHandle.ReleaseAndGetAddressOf());

		//画像データのハンドルを登録
		m_texture.insert(std::make_pair(filename, std::move(textureHandle)));

	}
}

/**
 * @brief DDS画像データの要求
 *
 * @param[in] 画像ファイル名
 *
 * @return 　画像データのハンドル
 */
ID3D11ShaderResourceView* ResourceManager::RequestDDSTexture(wchar_t const* filename)
{
	//未登録の場合
	if (m_texture.count(WcharToString(filename)) == 0)
	{
		return nullptr;
	}

	//登録してある画像データのハンドルを返却
	return m_texture[WcharToString(filename)].Get();
}
ID3D11ShaderResourceView* ResourceManager::RequestDDSTexture(const std::string& filename)
{
	//未登録の場合
	if (m_texture.count(filename) == 0)
	{
		return nullptr;
	}

	////登録してある画像データのハンドルを返却
	return m_texture[filename].Get();

}

/**
 * @brief 音データの要求
 *
 * @param[in] 音ファイル名
 *
 * @return 音データのポインタ
 */
DirectX::SoundEffect* ResourceManager::RequestSound(wchar_t const* filename)
{
	std::string stringFilename = WcharToString(filename);
	//未登録の場合
	if (m_sounds.count(stringFilename) == 0)
	{
		//音ファイルの読み込み
		std::string fullPath = DEFAULT_SOUND_DIRECTORY + stringFilename;


		//画像データのハンドルを登録
		std::unique_ptr<SoundEffect> soundEffect = std::make_unique<SoundEffect>(m_audioEngine, StringToWchar(fullPath));
		m_sounds.insert(std::make_pair(stringFilename, std::move(soundEffect)));
	}

	//登録してある画像データのハンドルを返却
	return m_sounds[stringFilename].get();
}
DirectX::SoundEffect* ResourceManager::RequestSound(const std::string& filename)
{
	//未登録の場合
	if (m_sounds.count(filename) == 0)
	{
		//音ファイルの読み込み
		std::string fullPath = DEFAULT_SOUND_DIRECTORY + filename;

		
		//画像データのハンドルを登録
		std::unique_ptr<SoundEffect> soundEffect = std::make_unique<SoundEffect>(m_audioEngine, StringToWchar(fullPath));
		m_sounds.insert(std::make_pair(filename,std::move(soundEffect)));
	}

	//登録してある画像データのハンドルを返却
	return m_sounds[filename].get();
}

/**
 * @brief モデルデータの読み込み
 *
 * @param[in] device   デバイス
 * @param[in] filename モデルデータファイル名
 *
 * @return なし
 */
void ResourceManager::LoadModel(ID3D11Device* device, wchar_t const* filename)
{
	//未登録の場合
	if (m_models.count(WcharToString(filename))== 0)
	{
		std::string fullPath = DEFAULT_MODELS_DIRECTORY + WcharToString(filename);
		EffectFactory fx(device);
		std::unique_ptr<Model> model = Model::CreateFromSDKMESH(device, StringToWchar(fullPath), fx);
		 m_models.insert(std::make_pair(WcharToString(filename), std::move(model)));
	}

}
void ResourceManager::LoadModel(ID3D11Device* device, const std::string& filename)
{
	//未登録の場合
	if (m_models.count(filename) == 0)
	{
		std::string fullPath = DEFAULT_MODELS_DIRECTORY + filename;
		EffectFactory fx(device);
		std::unique_ptr<Model> model = Model::CreateFromSDKMESH(device, StringToWchar(fullPath), fx);
		m_models.insert(std::make_pair(filename, std::move(model)));

	}

}

/**
 * @brief モデルデータの要求
 *
 * @param[in] モデルデータファイル名
 *
 * @return  モデルデータのポインタ
 */
DirectX::Model* ResourceManager::RequestModel(wchar_t const* filename)
{
	//未登録の場合
	if (m_models.count(WcharToString(filename)) == 0) 
	{
		return nullptr;
	}

	return m_models[WcharToString(filename)].get();
}
DirectX::Model* ResourceManager::RequestModel(const std::string& filename)
{
	//未登録の場合
	if (m_models.count(filename) == 0) 
	{
		return nullptr;
	}

	return m_models[filename].get();
}


/**
 * @brief データ削除
 *
 * @param[in] なし
 *
 * @return なし
 */
void ResourceManager::Clear()
{
	////画像データの削除
	//for (auto& element : m_texture)
	//{
	//	DeleteGraph(element.second);
	//}
	//m_texture.clear();

	////音データの削除
	//for (auto& element : m_sounds)
	//{
	//	DeleteGraph(element.second);
	//}
	//m_sounds.clear();
}

/**
 * @brief wchar_tからstringに変換
 *
 * @param[in] wchar_t文字列
 *
 * @return string文字列
 */
std::string ResourceManager::WcharToString(wchar_t const* wchar_str)
{
	// wchar_t から UTF-8 への変換
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(wchar_str);
}

/**
 * @brief stringからwchar_tに変換
 *
 * @param[in] string文字列
 *
 * @return wchar_t文字列
 */
wchar_t* ResourceManager::StringToWchar(const std::string& str)
{
	// UTF-8 から wchar_t に変換
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring wide_str = converter.from_bytes(str);

	// wchar_t* を返す
	size_t size_needed = wide_str.size() + 1;  // +1 for null-terminator
	wchar_t* result = new wchar_t[size_needed];

	// wcscpy_s を使って安全にコピー
	wcscpy_s(result, size_needed, wide_str.c_str());

	return result;
}

DirectX::SpriteBatch* ResourceManager::GetSpriteBatch()
{
	return m_spriteBatch.get();
}
