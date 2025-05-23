/**
 * @file   TitleScene.h
 *
 * @brief  タイトルシーンに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Scene.h"
#include"Game/Object/Camera.h"
#include"Game/Common/Sound.h"


// クラスの宣言 ===============================================================
class ResourceManager;    ///< リソースマネージャ
class SceneManager;       ///< シーンマネージャ




// クラスの定義 ===============================================================
/**
 * @brief タイトルシーン
 */
class TitleScene : public Scene
{
// クラス定数の宣言 -------------------------------------------------
public:



// データメンバの宣言 -----------------------------------------------
private:
	// システム関連
	ResourceManager* m_pResourceManager;    ///< リソースマネージャ
	DirectX::SpriteBatch* m_spriteBatch;    ///< スプライトバッチ
	ID3D11ShaderResourceView* m_titleTexture;	///< タイトル画像
	ID3D11ShaderResourceView* m_backTexture;	///< 背景画像
	ID3D11ShaderResourceView* m_pressTexture;	
	float m_rotationY;    ///< 回転角度
	// オブジェクト関連
	DirectX::Model* m_model;    ///< モデル
	std::unique_ptr<Camera> m_camera;    ///< カメラオブジェクト
	std::unique_ptr<Sound> m_decideSound;
	std::unique_ptr<Sound> m_bgm;

	//キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker m_traker;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	TitleScene(SceneManager* pSceneManager, ResourceManager* pResourceManager);

	// デストラクタ
	~TitleScene();


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
