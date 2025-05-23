// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Stage.h"
#include "Game/Common/ResourceManager.h"

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
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
 * @brief �f�X�g���N�^
 */
Stage::~Stage()
{
}

/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Stage::Initialize(ResourceManager* pResourceManager, int stageType)
{
	m_blockModel = pResourceManager->RequestModel("block.sdkmesh");
	m_goalModel  = pResourceManager->RequestModel("flag.sdkmesh");
	LoadCSV(std::to_string(stageType));
}
/**
 * @brief �X�V����
 *
 * @param[in] elapsedTime �t���[������
 *
 * @return �Ȃ�
 */
void Stage::Update(float& elapsedTime)
{
}

/**
 * @brief �`�揈��
 *
 * @param[in] context
 * @param[in] states
 * @param[in] view
 * @param[in] proj
 *
 * @return �Ȃ�
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
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
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
 * @brief CSV�t�@�C���̓ǂݍ���
 *
 * @param[in] �t�@�C����
 *
 * @return �Ȃ�
 */
bool Stage::LoadCSV(const std::string& filename)
{
	//�p�X�̐���
	std::string path = "Resources/Data/stage" + filename + ".csv";
	//�t�@�C���̃I�[�v��
	std::ifstream ifs{ path };
	if (!ifs.is_open())
	{
		//�ǂݍ��ݎ��s
		return false;
	}

	//�擪�s���畝�ƍ������擾
	ifs >> m_gridWidth;
	ifs.ignore();
	ifs >> m_gridHeight;
	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	//�O���b�h�𓮓I�ɐ���
	m_grid = new int* [m_gridHeight];
	for (int cy = 0; cy < m_gridHeight; cy++)
	{
		m_grid[cy] = new int[m_gridWidth];
	}

	//�f�[�^�̓ǂݍ���
	int cy = 0;//���s�ڂ�
	std::string record;
	while (std::getline(ifs, record) && cy < m_gridHeight) //1�s����
	{
		std::istringstream iss(record);

		int cx = 0;

		std::string field;
		while (std::getline(iss, field, ',') && cx < m_gridWidth)
		{
			m_grid[cy][cx] = std::stoi(field);//�����񂩂�int��
			if (m_grid[cy][cx] == TileType::WALL)
			{
				// ���[���h���W�̎Z�o
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
