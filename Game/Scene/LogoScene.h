/**
 * @file   LogoScene.h
 *
 * @brief  ロゴシーンに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Scene.h"




// クラスの宣言 ===============================================================
class ResourceManager;    ///< リソースマネージャ
class SceneManager;       ///< シーンマネージャ




// クラスの定義 ===============================================================
/**
 * @brief ロゴシーン
 */
class LogoScene : public Scene
{
// クラス定数の宣言 -------------------------------------------------
public:
	//static constexpr SpriteAnimator::AnimationClip LOGO_CLIP =    ///< ロゴアニメーションのクリップ
	//{
	//	{0,0,640,480},    // 開始フレームの領域[pixel]
	//	18,               // 総フレーム数
	//	6,                // 列数(１行当たりのフレーム数)
	//	9 * 14,           // 再生時間[frames]
	//	false              // ループさせるかどうか
	//};



// データメンバの宣言 -----------------------------------------------
private:
	// システム関連
	ResourceManager* m_pResourceManager;    ///< リソースマネージャ
	//テクスチャ
	//int m_texture;
	//ロゴの座標
	//GameLib::Point2D m_spritePostion;
	////シーン遷移許可
	//bool m_change;
	//// リソース関連
	////スプライト
	//Sprite m_sprite;
	//SpriteAnimator m_spriteAnimator;


	// オブジェクト関連



// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	LogoScene(SceneManager* pSceneManager, ResourceManager* pResourceManager);

	// デストラクタ
	~LogoScene();


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


};
