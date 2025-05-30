#pragma once
// ヘッダファイルの読み込み ===================================================
#include<memory>
#include<string>
#include<unordered_map>

class Scene;
class ResourceManager;

class SceneManager
{
	//エイリアス宣言 ----------------------------------------------------
private:
	using SceneCollection = std::unordered_map<std::string, std::unique_ptr<Scene>>;
	using SharedData = std::unordered_map<std::string, std::string>;
	// クラス定数の宣言 -------------------------------------------------
public:



	// データメンバの宣言 -----------------------------------------------
private:
	SceneCollection m_scenes;//シーン群

	Scene* m_pCurrentScene;//現在のシーン
	Scene* m_pRequestedScene;//変更要求のあったシーン

	SharedData m_sharedData;//共有データ

	//キーボードトラッカー
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_traker;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	SceneManager();

	// デストラクタ
	~SceneManager();


	// 操作
public:
	// シーンの登録
	void Register(const std::string& sceneName, std::unique_ptr<Scene> scene);

	// 更新処理
	void Update(DirectX::Keyboard::State key, float elapsedTime);

	// 描画処理
	void Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj);

	// 開始シーンの設定
	void SetStratScene(const std::string& startSceneName);

	// シーン変更の要求
	void RequestSceneChange(const std::string& nextSceneName);


	// 取得/設定
public:
	//共有データの取得
	std::string GetSharedData(const std::string& key) const;

	//共有データの設定
	void SetSharedData(const std::string& key, const std::string& value);

	// 内部実装
private:
	//シーンの変更
	void ChangeScene();


};

