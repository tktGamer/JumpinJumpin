/**
 * @file   GameScene.h
 *
 * @brief  ゲームシーンに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Scene.h"
#include "Game/Object/Player.h"
#include "Game/Object/Camera.h"
#include"Game/Object/Block.h"
#include"Game/Object/Stage.h"
#include"Game/Common/Sound.h"
// クラスの宣言 ===============================================================
class ResourceManager;    ///< リソースマネージャ
class SceneManager;       ///< シーンマネージャ




// クラスの定義 ===============================================================
/**
 * @brief ゲームシーン
 */
class GameScene : public Scene
{
// クラス定数の宣言 -------------------------------------------------
public:

	//球
	struct Circle
	{
		DirectX::SimpleMath::Vector3 pos;
		float radius;
	};

// データメンバの宣言 -----------------------------------------------
private:
	// システム関連
	ResourceManager* m_pResourceManager;    ///< リソースマネージャ
	std::unique_ptr<Sound> m_gameBGM;
	std::unique_ptr<Sound> m_hitBlockSound;
	// オブジェクト関連
	std::unique_ptr<Player> m_player;    ///< プレイヤーオブジェクト
	std::unique_ptr<Camera> m_camera;    ///< カメラオブジェクト
	std::unique_ptr<Stage> m_stage;

	
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GameScene(SceneManager* pSceneManager, ResourceManager* pResourceManager);

	// デストラクタ
	~GameScene();


// 操作
public:
	// 初期化処理
	void Initialize() override;

	// 更新処理
	void Update(DirectX::Keyboard::KeyboardStateTracker* traker, float elapsedTime) override;

	// 描画処理
	void Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj) override;

	// 終了処理
	void Finalize() override;


// 取得/設定
public:


// 内部実装
private:
	bool CapsuleToAABB(CapsuleCollider capsule, BoxCollider box);

	bool IsHit(Circle circle, BoxCollider box);
};
