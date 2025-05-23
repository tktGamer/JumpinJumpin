/**
 * @file   StageSelectScene.cpp
 *
 * @brief  タイトルシーンに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "StageSelectScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"




// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] sceneManager    シーンを管理しているマネージャ
 * @param[in] resourceManager リソースを管理しているマネージャ
 */
StageSelectScene::StageSelectScene(SceneManager* pSceneManager, ResourceManager* pResourceManager)
	: Scene{ pSceneManager }
	, m_pResourceManager{ pResourceManager }
	, m_spriteBatch{}
	, m_titleTexture{}
	, m_backTexture{}
	, m_pressTexture{}
	, m_arrowTexture{}
	, m_stage1Texture{}
	, m_stage2Texture{}
	, m_decideSound{}
	, m_selectStage{}
	, m_traker{}

{
	m_decideSound = std::make_unique<Sound>(m_pResourceManager->RequestSound("decide.wav"));
	m_bgm = std::make_unique<Sound>(m_pResourceManager->RequestSound("titlebgm.wav"));
	m_selectSound = std::make_unique<Sound>(m_pResourceManager->RequestSound("btn.wav"));
}



/**
 * @brief デストラクタ
 */
StageSelectScene::~StageSelectScene()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void StageSelectScene::Initialize()
{
	m_spriteBatch = m_pResourceManager->GetSpriteBatch();
	m_titleTexture = m_pResourceManager->RequestDDSTexture("title.dds");
	m_backTexture = m_pResourceManager->RequestDDSTexture("titleback.dds");
	m_pressTexture = m_pResourceManager->RequestDDSTexture("pressspace.dds");
	m_arrowTexture = m_pResourceManager->RequestDDSTexture("arrow.dds");
	m_stage1Texture = m_pResourceManager->RequestDDSTexture("stage1.dds");
	m_stage2Texture = m_pResourceManager->RequestDDSTexture("stage2.dds");
	m_selectStage = Stage::STAGE1;
	m_bgm->SetVolume(0.3f);
	m_bgm->Play(true);
}



/**
 * @brief 更新処理
 *
 * @param[in] inputDevice 入力デバイス
 *
 * @return なし
 */
void StageSelectScene::Update(DirectX::Keyboard::KeyboardStateTracker* traker, float elapsedTime)
{

	// シーンの切り替え
	if (traker->pressed.Space) 
	{
		m_bgm->Stop();
		m_decideSound->Play(false);
		WriteSharedData("stage", m_selectStage);
		ChangeScene("Game");
	}

	if (traker->pressed.Up) 
	{
		m_selectStage--;
		m_selectSound->Play(false);
	}
	else if(traker->pressed.Down)
	{
		m_selectStage++;
		m_selectSound->Play(false);
	}

	if (m_selectStage <= Stage::NONE)
	{
		m_selectStage = Stage::STAGE1;
	}
	else if (m_selectStage >= Stage::NUM)
	{
		m_selectStage = Stage::STAGE2;
	}
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void StageSelectScene::Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj)
{
	DirectX::SimpleMath::Matrix world;
	//平行移動行列を作成する
	DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation({0,-1,0});
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(1.0f);
	world = scale  * tras;


	m_spriteBatch->Begin();

	m_spriteBatch->Draw(m_backTexture, DirectX::SimpleMath::Vector2(0, 0));
	m_spriteBatch->Draw(m_arrowTexture, DirectX::SimpleMath::Vector2(300, 200*m_selectStage));
	m_spriteBatch->Draw(m_stage1Texture, DirectX::SimpleMath::Vector2(400, 200));
	m_spriteBatch->Draw(m_stage2Texture, DirectX::SimpleMath::Vector2(400, 400));
	
	m_spriteBatch->End();



}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void StageSelectScene::Finalize()
{
	
}
