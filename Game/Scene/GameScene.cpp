/**
 * @file   GameScene.cpp
 *
 * @brief  ゲームシーンに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GameScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"




// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] sceneManager    シーンを管理しているマネージャ
 * @param[in] resourceManager リソースを管理しているマネージャ
 */
GameScene::GameScene(SceneManager* pSceneManager, ResourceManager* pResourceManager)
	: Scene{ pSceneManager }
	, m_pResourceManager{ pResourceManager }
	, m_player{}
	, m_camera{}
{
	m_player = std::make_unique<Player>();
	m_camera = std::make_unique<Camera>();
	m_stage = std::make_unique<Stage>();
	m_gameBGM = std::make_unique<Sound>(m_pResourceManager->RequestSound("gamebgm.wav"));
	m_hitBlockSound = std::make_unique<Sound>(m_pResourceManager->RequestSound("death.wav"));
}



/**
 * @brief デストラクタ
 */
GameScene::~GameScene()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameScene::Initialize()
{
	int stageType;
	ReadSharedData("stage",&stageType);
	m_player->Initialize(m_pResourceManager);
	m_camera->Initialize({0,3,50.0f});
	m_stage->Initialize(m_pResourceManager,stageType);
	m_gameBGM->SetVolume(0.5f);
	m_gameBGM->Play(true);
}



/**
 * @brief 更新処理
 *
 * @param[in] inputDevice 入力デバイス
 *
 * @return なし
 */
void GameScene::Update(DirectX::Keyboard::KeyboardStateTracker* traker, float elapsedTime)
{

	m_stage->Update(elapsedTime);
	m_player->Update(elapsedTime, traker);
	DirectX::SimpleMath::Vector3 targetPos = { m_player->GetPosition().x,3.0f,m_player->GetPosition().z};
	m_camera->Update(targetPos);
	m_camera->SetPositionX(m_player->GetPosition().x);


	std::vector <std::unique_ptr<Block>> & block = m_stage->GetBlock();

	for (std::unique_ptr<Block>& target : block)
	{
		//当たり判定
		CapsuleCollider capsule = m_player->GetCollider();
		if (IsHit({ capsule.GetStart(),capsule.GetRadius() }, target->GetCollider())) 
		{
			m_player->Jump();
		}
		if (IsHit({ capsule.GetEnd(),capsule.GetRadius() }, target->GetCollider())) 
		{
			//ゲームオーバー
			m_hitBlockSound->Play(false);
			m_gameBGM->Stop();
			WriteSharedData("result", false);
			ChangeScene("Result");
		}
	}

	Goal* pGoal = m_stage->GetGoal();
	//当たり判定
	if (CapsuleToAABB(m_player->GetCollider(), pGoal->GetCollider()))
	{
		m_gameBGM->Stop();
		WriteSharedData("result", true);
		ChangeScene("Result");
	}
}



/**
 * @brief 描画処理
 *
 * @param[in] context
 * @param[in] states
 * @param[in] proj
 *
 * @return なし
 */
void GameScene::Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj)
{
	//ビュー行列取得
	DirectX::SimpleMath::Matrix view = m_camera->GetView();
	m_stage->Draw(context, states, view, proj);
	m_player->Draw(context, states, view, proj);
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameScene::Finalize()
{
	m_player->Finalize();
	m_stage->Finalize();

}


/**
 * @brief カプセルとボックスの当たり判定
 *
 * @param[in] capsule カプセル
 * @param[in] box	 ボックス
 *
 * @return true:当たっている
		   false:当たっていない
 */
bool GameScene::CapsuleToAABB(CapsuleCollider capsule, BoxCollider box)
{
	//分からないからとりあえず球とAABB
	DirectX::SimpleMath::Vector3 min = box.GetMin();
	DirectX::SimpleMath::Vector3 max = box.GetMax();
	DirectX::SimpleMath::Vector3 center = capsule.GetStart();
	float radius = capsule.GetRadius();
	// AABBの最も近い点を計算
	float x = std::max(min.x, std::min(center.x, max.x));
	float y = std::max(min.y, std::min(center.y, max.y));
	float z = std::max(min.z, std::min(center.z, max.z));

	// 球の中心と最も近い点との距離の二乗を計算
	float distanceSquared = (x - center.x) * (x - center.x) +
		(y - center.y) * (y - center.y) +
		(z - center.z) * (z - center.z);

	// 距離の二乗が球の半径の二乗以下であれば当たり
	return distanceSquared <= (radius * radius);
}



/**
 * @brief 球とボックスの当たり判定
 *
 * @param[in] circle 球
 * @param[in] box	 ボックス
 *
 * @return true:当たっている
		   false:当たっていない
 */
bool GameScene::IsHit(Circle circle, BoxCollider box)
{
	//球とAABB
	DirectX::SimpleMath::Vector3 min = box.GetMin();
	DirectX::SimpleMath::Vector3 max = box.GetMax();
	DirectX::SimpleMath::Vector3 center = circle.pos;
	float radius = circle.radius;
	// AABBの最も近い点を計算
	float x = std::max(min.x, std::min(center.x, max.x));
	float y = std::max(min.y, std::min(center.y, max.y));
	float z = std::max(min.z, std::min(center.z, max.z));

	// 球の中心と最も近い点との距離の二乗を計算
	float distanceSquared = (x - center.x) * (x - center.x) +
		(y - center.y) * (y - center.y) +
		(z - center.z) * (z - center.z);

	// 距離の二乗が球の半径の二乗以下であれば当たり
	return distanceSquared <= (radius * radius);
}
