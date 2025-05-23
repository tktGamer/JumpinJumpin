/**
 * @file   TitleScene.cpp
 *
 * @brief  タイトルシーンに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "TitleScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"




// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] sceneManager    シーンを管理しているマネージャ
 * @param[in] resourceManager リソースを管理しているマネージャ
 */
TitleScene::TitleScene(SceneManager* pSceneManager, ResourceManager* pResourceManager)
	: Scene{ pSceneManager }
	, m_pResourceManager{ pResourceManager }
	, m_spriteBatch{}
	, m_titleTexture{}
	, m_backTexture{}

	, m_rotationY{ 0.0f }
	, m_model{}
{
	m_camera = std::make_unique<Camera>();
	m_decideSound = std::make_unique<Sound>(m_pResourceManager->RequestSound("decide.wav"));
	m_bgm = std::make_unique<Sound>(m_pResourceManager->RequestSound("titlebgm.wav"));
}



/**
 * @brief デストラクタ
 */
TitleScene::~TitleScene()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void TitleScene::Initialize()
{
	m_spriteBatch = m_pResourceManager->GetSpriteBatch();
	m_titleTexture = m_pResourceManager->RequestDDSTexture("title.dds");
	m_backTexture = m_pResourceManager->RequestDDSTexture("titleback.dds");
	m_pressTexture = m_pResourceManager->RequestDDSTexture("pressspace.dds");
	m_model = m_pResourceManager->RequestModel("JumpinPlayer.sdkmesh");

	m_camera->Initialize({0,5.0f,10.0f});
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
void TitleScene::Update(DirectX::Keyboard::KeyboardStateTracker* traker, float elapsedTime)
{

	// シーンの切り替え
	if (traker->pressed.Space) 
	{
		m_bgm->Stop();
		m_decideSound->Play(false);
		ChangeScene("StageSelect");
	}

	m_rotationY += DirectX::XMConvertToRadians(36.0f)*elapsedTime;

	m_camera->Update({0,2,0});
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void TitleScene::Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj)
{
	DirectX::SimpleMath::Matrix world;
	//平行移動行列を作成する
	DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation({0,-1,0});
	//Z軸の回転行列を作成する
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(m_rotationY);
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(1.0f);
	world = scale * rotY * tras;
	//ビュー行列取得
	DirectX::SimpleMath::Matrix view = m_camera->GetView();


	m_spriteBatch->Begin();

	m_spriteBatch->Draw(m_backTexture, DirectX::SimpleMath::Vector2(0, 0));
	m_spriteBatch->Draw(m_titleTexture, DirectX::SimpleMath::Vector2(150, 0));
	m_spriteBatch->Draw(m_pressTexture, DirectX::SimpleMath::Vector2(150, 600));
	
	m_spriteBatch->End();
	m_model->Draw(&context, states, world, view, proj);



}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void TitleScene::Finalize()
{
	
}
