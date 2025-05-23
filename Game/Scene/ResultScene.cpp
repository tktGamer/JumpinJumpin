/**
 * @file   ResultScene.cpp
 *
 * @brief  リザルトシーンに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ResultScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"




// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] sceneManager    シーンを管理しているマネージャ
 * @param[in] resourceManager リソースを管理しているマネージャ
 */
ResultScene::ResultScene(SceneManager* pSceneManager, ResourceManager* pResourceManager)
	: Scene{ pSceneManager }
	, m_pResourceManager{ pResourceManager }
	, m_spriteBatch{}
	, m_resultTexture{}
	, m_pressTexture{}
	, m_clearSound{}
	, m_gameoverSound{}
	, m_isClear{}
{
	m_clearSound = std::make_unique<Sound>(m_pResourceManager->RequestSound("clear.wav"));
	m_gameoverSound = std::make_unique<Sound>(m_pResourceManager->RequestSound("gameover.wav"));
}



/**
 * @brief デストラクタ
 */
ResultScene::~ResultScene()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ResultScene::Initialize()
{
	ReadSharedData("result",&m_isClear);
	m_spriteBatch = m_pResourceManager->GetSpriteBatch();
	if (m_isClear)
	{
		m_backTexture = m_pResourceManager->RequestDDSTexture("clearback.dds");
		m_resultTexture = m_pResourceManager->RequestDDSTexture("clear.dds");
		m_clearSound->Play(false);

	}
	else
	{
		m_backTexture = m_pResourceManager->RequestDDSTexture("gameoverback.dds");
		m_resultTexture = m_pResourceManager->RequestDDSTexture("gameover.dds");
		m_gameoverSound->Play(false);
	}
	m_pressTexture = m_pResourceManager->RequestDDSTexture("guide.dds");

}



/**
 * @brief 更新処理
 *
 * @param[in] inputDevice 入力デバイス
 *
 * @return なし
 */
void ResultScene::Update(DirectX::Keyboard::KeyboardStateTracker* traker, float elapsedTime)
{

	// シーンの切り替え
	if (traker->pressed.Space) 
	{
		m_clearSound->Stop();
		m_gameoverSound->Stop();
		ChangeScene("Title");
	}
	else if (traker->pressed.Enter)
	{
		m_clearSound->Stop();
		m_gameoverSound->Stop();
		ChangeScene("Game");
	}

}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ResultScene::Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj)
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_backTexture, DirectX::SimpleMath::Vector2(0, 0));
	m_spriteBatch->Draw(m_resultTexture, DirectX::SimpleMath::Vector2(300, 50));
	m_spriteBatch->Draw(m_pressTexture, DirectX::SimpleMath::Vector2(300, 400));
	m_spriteBatch->End();
	//DrawFormatString(10, 10, Colors::WHITE, "タイトルシーン");
	//DrawFormatString(500, 200, Colors::WHITE, "JumpinJumpin");
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ResultScene::Finalize()
{
	
}
