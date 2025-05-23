/**
 * @file   LogoScene.cpp
 *
 * @brief  ロゴシーンに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "LogoScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"




// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] sceneManager    シーンを管理しているマネージャ
 * @param[in] resourceManager リソースを管理しているマネージャ
 */
LogoScene::LogoScene(SceneManager* pSceneManager, ResourceManager* pResourceManager)
	: Scene{ pSceneManager }
	, m_pResourceManager{ pResourceManager }

{

}



/**
 * @brief デストラクタ
 */
LogoScene::~LogoScene()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void LogoScene::Initialize()
{
	//m_texture = m_pResourceManager->RequestTexture("Logo.png");
	//// ロゴ用スプライトの初期化
	//m_sprite.Initialize(m_texture, { 0,0,60,80 }, 2.0f);

	//// ロゴ用アニメーターの初期化
	//m_spriteAnimator.Initialize(&m_sprite, LOGO_CLIP);
	//m_spritePostion = { 640.0f,360.0f };

	//m_spriteAnimator.Play();
	//m_change = false;

}



/**
 * @brief 更新処理
 *
 * @param[in] inputDevice 入力デバイス
 *
 * @return なし
 */
void LogoScene::Update(DirectX::Keyboard::KeyboardStateTracker* traker, float elapsedTime)
{
	//アニメーションが終わったら遷移許可
	//if (m_spriteAnimator.IsFinished() || joypad.IsButtonPressed(PAD_INPUT_10))
	//{
	//	m_change = true;
	//}
	// ロゴ用アニメーターの更新
	//m_spriteAnimator.Update();
	//// シーンの切り替え
	//if (m_change)
	//{
	//	ChangeScene("Title");
	//}

}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void LogoScene::Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj)
{

	//ロゴ描画
	//m_sprite.Draw(m_spritePostion);

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void LogoScene::Finalize()
{
	
}
