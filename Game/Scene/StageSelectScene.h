/**
 * @file   StageSelectScene.h
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
#include"Game/Object/Stage.h"

// クラスの宣言 ===============================================================
class ResourceManager;    ///< リソースマネージャ
class SceneManager;       ///< シーンマネージャ




// クラスの定義 ===============================================================
/**
 * @brief タイトルシーン
 */
class StageSelectScene : public Scene
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
	ID3D11ShaderResourceView* m_stage1Texture;
	ID3D11ShaderResourceView* m_stage2Texture;
	ID3D11ShaderResourceView* m_arrowTexture;


	int m_selectStage;
	// オブジェクト関連
	std::unique_ptr<Sound> m_decideSound;
	std::unique_ptr<Sound> m_selectSound;
	std::unique_ptr<Sound> m_bgm;

	//キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker m_traker;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	StageSelectScene(SceneManager* pSceneManager, ResourceManager* pResourceManager);

	// デストラクタ
	~StageSelectScene();


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
