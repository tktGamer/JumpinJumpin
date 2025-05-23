// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Stage.h"
#include "Game/Common/ResourceManager.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Stage::Stage()
	:m_blockModel{}
	,m_goalModel{}
	, m_blocks{}
	, m_goal{}
	, m_gridWidth{}
	, m_gridHeight{}
	, m_grid{}
{
}

/**
 * @brief デストラクタ
 */
Stage::~Stage()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Stage::Initialize(ResourceManager* pResourceManager, int stageType)
{
	m_blockModel = pResourceManager->RequestModel("block.sdkmesh");
	m_goalModel  = pResourceManager->RequestModel("flag.sdkmesh");
	LoadCSV(std::to_string(stageType));
}
/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime フレーム時間
 *
 * @return なし
 */
void Stage::Update(float& elapsedTime)
{
}

/**
 * @brief 描画処理
 *
 * @param[in] context
 * @param[in] states
 * @param[in] view
 * @param[in] proj
 *
 * @return なし
 */
void Stage::Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj)
{
	for(auto& block : m_blocks)
	{
		block->Draw(context, states, view, proj);
	}
	m_goal->Draw(context, states, view, proj);
}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Stage::Finalize()
{
	for (int cy = 0; cy < m_gridHeight; cy++)
	{
		delete[] m_grid[cy];
	}
	delete[] m_grid;
	m_blocks.clear();
	m_goal.reset();
}

std::vector<std::unique_ptr<Block>>& Stage::GetBlock()
{
	return m_blocks;
}

Goal* Stage::GetGoal()
{
	return m_goal.get();
}

/**
 * @brief CSVファイルの読み込み
 *
 * @param[in] ファイル名
 *
 * @return なし
 */
bool Stage::LoadCSV(const std::string& filename)
{
	//パスの生成
	std::string path = "Resources/Data/stage" + filename + ".csv";
	//ファイルのオープン
	std::ifstream ifs{ path };
	if (!ifs.is_open())
	{
		//読み込み失敗
		return false;
	}

	//先頭行から幅と高さを取得
	ifs >> m_gridWidth;
	ifs.ignore();
	ifs >> m_gridHeight;
	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	//グリッドを動的に生成
	m_grid = new int* [m_gridHeight];
	for (int cy = 0; cy < m_gridHeight; cy++)
	{
		m_grid[cy] = new int[m_gridWidth];
	}

	//データの読み込み
	int cy = 0;//何行目か
	std::string record;
	while (std::getline(ifs, record) && cy < m_gridHeight) //1行ずつ
	{
		std::istringstream iss(record);

		int cx = 0;

		std::string field;
		while (std::getline(iss, field, ',') && cx < m_gridWidth)
		{
			m_grid[cy][cx] = std::stoi(field);//文字列からintへ
			if (m_grid[cy][cx] == TileType::WALL)
			{
				// ワールド座標の算出
				DirectX::SimpleMath::Vector3 position{ cx * Block::LENGTH.x, - cy * Block::LENGTH.y, 0.0f };
				m_blocks.push_back(std::make_unique<Block>());
				m_blocks.back()->Initialize(m_blockModel, LEFT_TOP + position);
				
			}
			else if (m_grid[cy][cx] == TileType::GOAL)
			{
				DirectX::SimpleMath::Vector3 position{ cx * Block::LENGTH.x, -cy * Block::LENGTH.y, 0.0f };

				m_goal = std::make_unique<Goal>();
				m_goal->Initialize(m_goalModel, LEFT_TOP + position);
			}

			cx++;
		}
		cy++;
	}

	ifs.close();
	return true;

}
