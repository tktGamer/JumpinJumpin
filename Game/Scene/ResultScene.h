/**
 * @file   ResultScene.h
 *
 * @brief  リザルトシーンに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Scene.h"

#include"Game/Common/Sound.h"


// クラスの宣言 ===============================================================
class ResourceManager;    ///< リソースマネージャ
class SceneManager;       ///< シーンマネージャ




// クラスの定義 ===============================================================
/**
 * @brief リザルトシーン
 */
class ResultScene : public Scene
{
// クラス定数の宣言 -------------------------------------------------
public:



// データメンバの宣言 -----------------------------------------------
private:
	// システム関連
	ResourceManager* m_pResourceManager;    ///< リソースマネージャ
	DirectX::SpriteBatch* m_spriteBatch;    ///< スプライトバッチ
	ID3D11ShaderResourceView* m_resultTexture;	///< リザルト画像
	ID3D11ShaderResourceView* m_pressTexture;	///< プレス画像
	ID3D11ShaderResourceView* m_backTexture;	///< 背景画像

	bool m_isClear;	///< クリアしたかどうか
	std::unique_ptr<Sound> m_clearSound;///< クリア音
	std::unique_ptr<Sound> m_gameoverSound;///< 失敗音

	// オブジェクト関連
	


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	ResultScene(SceneManager* pSceneManager, ResourceManager* pResourceManager);

	// デストラクタ
	~ResultScene();


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
