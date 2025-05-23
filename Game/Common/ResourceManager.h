#pragma once
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"pch.h"
#include<unordered_map>
#include<string>

// �N���X�̒�` ===============================================================
/**
  * @brief ���\�[�X�̊Ǘ�
  */
class ResourceManager
{
//�G�C���A�X�錾
private:                                        //�t�@�C�����@�n���h��
	using DDSTextureResource = std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>;
	using SoundResouce = std::unordered_map<std::string, std::unique_ptr<DirectX::SoundEffect>>;
	using ModelResouce = std::unordered_map<std::string,std::unique_ptr<DirectX::Model>>;
// �N���X�萔�̐錾 -------------------------------------------------
public:
	static constexpr  char const* DEFAULT_DDS_TEXTURE_DIRECTORY = "Resources/Dds/";
	static constexpr  char const* DEFAULT_SOUND_DIRECTORY = "Resources/Sounds/";
	static constexpr  char const* DEFAULT_MODELS_DIRECTORY = "Resources/Models/";


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	DirectX::AudioEngine* m_audioEngine;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	//DDS�摜�f�[�^�Q
	DDSTextureResource m_texture;
	//���f�[�^�Q
	SoundResouce m_sounds;
	//���f���f�[�^�Q
	ModelResouce m_models;


// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	ResourceManager(DirectX::AudioEngine* m_audioEngine, ID3D11DeviceContext* contexth);

	// �f�X�g���N�^
	~ResourceManager();


// ����
public:
	//�摜�f�[�^�ǂݍ���
	void LoadDDSTexture(ID3D11Device* device, wchar_t const*     filename);
	void LoadDDSTexture(ID3D11Device* device, const std::string& filename);
	//�摜�f�[�^�v��
	ID3D11ShaderResourceView* RequestDDSTexture(wchar_t const*     filename);
	ID3D11ShaderResourceView* RequestDDSTexture(const std::string& filename);

	//���f�[�^�v��
	DirectX::SoundEffect* RequestSound(wchar_t const*     filename);
	DirectX::SoundEffect* RequestSound(const std::string& filename);

	//���f���f�[�^�ǂݍ���
	void LoadModel(ID3D11Device* device, wchar_t const*     filename);
	void LoadModel(ID3D11Device* device, const std::string& filename);
	//���f���f�[�^�v��
	DirectX::Model* RequestModel(wchar_t const*     filename);
	DirectX::Model* RequestModel(const std::string& filename);

	//�S���\�[�X�폜
	void Clear();
	//wchar_t����sting�ɕϊ�
	std::string WcharToString(wchar_t const* wchar_str);
	//string����wchar_t�ɕϊ�
	wchar_t* StringToWchar(const std::string& str);

	//SpriteBatch�̎擾
	DirectX::SpriteBatch* GetSpriteBatch();
};
