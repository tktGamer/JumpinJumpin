#pragma once

class ResourceManager;
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"Game/Object/Block.h"
#include"Game/Object/Goal.h"
#include<iostream>
#include <string>
#include<ostream>
#include<sstream>
#include<fstream>
// �N���X�̒�` ===============================================================
/**
  * @brief �X�e�[�W
  */
class Stage
{
// �N���X�萔�̐錾 -------------------------------------------------
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
	//�X�e�[�W�̍��[
	static constexpr DirectX::SimpleMath::Vector3 LEFT_TOP = {-5.0f,15.0f,0.0f};

private:

	//�u���b�N�̃��f��
	DirectX::Model* m_blockModel;
	DirectX::Model* m_goalModel;
	
	std::unique_ptr<Goal> m_goal;
	std::vector<std::unique_ptr<Block>> m_blocks;


	int   m_gridWidth;     ///< �O���b�h�̕�
	int   m_gridHeight;    ///< �O���b�h�̍���
	int** m_grid;          ///< �O���b�h�f�[�^

	// �����o�֐��̐錾 -------------------------------------------------
public:
	Stage();
	~Stage();
	void Initialize(ResourceManager* pResourceManager,int stageType);
	void Update(float& elapsedTime);
	void Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);
	void Finalize();

	//�u���b�N�̎擾
	std::vector<std::unique_ptr<Block>>& GetBlock();
	//�S�[���̎擾
	Goal* GetGoal();
// ��������
private:
	bool LoadCSV(const std::string& filename);

};

