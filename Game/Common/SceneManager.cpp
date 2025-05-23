// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Common/SceneManager.h"
#include"Game//Common/Scene.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
SceneManager::SceneManager()
	:m_scenes{}
	, m_pCurrentScene{ nullptr }
	, m_pRequestedScene{ nullptr }
	, m_sharedData{}
	, m_traker{}
{
	m_traker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
}



/**
 * @brief デストラクタ
 */
SceneManager::~SceneManager()
{

}

/**
 * @brief シーンの登録
 *
 * @param[in] sceneName　シーンの登録名
 * @param[in] scene　登録シーン
 *
 * @return なし
 */
void SceneManager::Register(const std::string& sceneName, std::unique_ptr<Scene> scene)
{
	m_scenes.emplace(sceneName, std::move(scene));
}

/**
 * @brief 更新処理
 *
 * @param[in] key		 　入力デバイス
 * @param[in] elapsedTime　フレーム経過時間
 *
 * @return なし
 */
void SceneManager::Update(DirectX::Keyboard::State key, float elapsedTime)
{
	m_traker->Update(key);
	//シーン変更が必要かどうかをチェック
	if (m_pRequestedScene != nullptr)
	{
		ChangeScene();
	}

	//現在のシーンを更新
	if (m_pCurrentScene)
	{
		m_pCurrentScene->Update(m_traker.get(), elapsedTime);
	}
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void SceneManager::Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj)
{
	//現在のシーンを描画
	if (m_pCurrentScene)
	{
		m_pCurrentScene->Render(context,states,proj);
	}

}

/**
 * @brief 開始シーンの設定
 *
 * @param[in] startSceneName　開始シーン名
 *
 * @return なし
 */
void SceneManager::SetStratScene(const std::string& startSceneName)
{
	if (m_scenes.count(startSceneName) == 0)
	{
		return;
	}
	m_pCurrentScene = m_scenes[startSceneName].get();
	m_pCurrentScene->Initialize();
}

/**
 * @brief シーン変更の要求
 *
 * @param[in] requestSceneName　変更予定のシーン名
 *
 * @return なし
 */
void SceneManager::RequestSceneChange(const std::string& nextSceneName)
{
	if (m_scenes.count(nextSceneName) == 0)
	{
		return;
	}
	m_pRequestedScene = m_scenes[nextSceneName].get();
}

/**
 * @brief 共有データの取得
 *
 * @param[in] key　取得したい共有データのキー
 *
 * @return キー共有データ
 */
std::string SceneManager::GetSharedData(const std::string& key) const
{
	if (m_sharedData.count(key) == 0)
	{
		return std::string{};
	}
	return m_sharedData.at(key);
}

/**
 * @brief 共有データの設定
 *
 * @param[in] key　  設定したい共有データのキー
 * @param[in] vlaue　設定したい共有データの値
 *
 * @return なし
 */
void SceneManager::SetSharedData(const std::string& key, const std::string& value)
{
	m_sharedData[key] = value;
}

/**
 * @brief シーンの変更
 *
 * @param[in] なし
 *
 * @return なし
 */
void SceneManager::ChangeScene()
{
	if (!m_pRequestedScene)
	{
		return;
	}

	if (m_pCurrentScene)
	{
		m_pCurrentScene->Finalize();
	}

	m_pCurrentScene = m_pRequestedScene;
	m_pCurrentScene->Initialize();

	m_pRequestedScene = nullptr;
}



