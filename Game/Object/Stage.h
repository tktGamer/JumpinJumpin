#pragma once

class ResourceManager;
// ヘッダファイルの読み込み ===================================================
#include"Game/Object/Block.h"
#include"Game/Object/Goal.h"
#include<iostream>
#include <string>
#include<ostream>
#include<sstream>
#include<fstream>
// クラスの定義 ===============================================================
/**
  * @brief ステージ
  */
class Stage
{
// クラス定数の宣言 -------------------------------------------------
public:
	enum StageType
	{
		NONE = 0,

		STAGE1 = 1,
		STAGE2,

		NUM
	};
	enum  TileType
	{
		None = 0,
		WALL,
		GOAL,
	};
	//ステージの左端
	static constexpr DirectX::SimpleMath::Vector3 LEFT_TOP = {-5.0f,15.0f,0.0f};

private:

	//ブロックのモデル
	DirectX::Model* m_blockModel;
	DirectX::Model* m_goalModel;
	
	std::unique_ptr<Goal> m_goal;
	std::vector<std::unique_ptr<Block>> m_blocks;


	int   m_gridWidth;     ///< グリッドの幅
	int   m_gridHeight;    ///< グリッドの高さ
	int** m_grid;          ///< グリッドデータ

	// メンバ関数の宣言 -------------------------------------------------
public:
	Stage();
	~Stage();
	void Initialize(ResourceManager* pResourceManager,int stageType);
	void Update(float& elapsedTime);
	void Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);
	void Finalize();

	//ブロックの取得
	std::vector<std::unique_ptr<Block>>& GetBlock();
	//ゴールの取得
	Goal* GetGoal();
// 内部実装
private:
	bool LoadCSV(const std::string& filename);

};

