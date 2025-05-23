// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "ResourceManager.h"
#include <codecvt>  // std::wstring_convert �� std::codecvt_utf8 ���g�p

using namespace DirectX;



// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
ResourceManager::ResourceManager(DirectX::AudioEngine* audioEngine, ID3D11DeviceContext* context)
	:m_texture{}
	, m_sounds{}
	,m_models{}
{
	m_audioEngine = audioEngine;
	m_spriteBatch = std::make_unique<SpriteBatch>(context);
}

/**
 * @brief �f�X�g���N�^
 */
ResourceManager::~ResourceManager()
{
	//�S���\�[�X�̍폜
	Clear();
}



/**
 * @brief DDS�摜�f�[�^�̓ǂݍ���
 *
 * @param[in] device   �f�o�C�X
 * @param[in] filename DDS�摜�f�[�^�t�@�C����
 *
 * @return �Ȃ�
 */
void ResourceManager::LoadDDSTexture(ID3D11Device* device, wchar_t const* filename)
{
	std::string stringFilename =  WcharToString(filename);
	//���o�^�̏ꍇ
	if (m_models.count(stringFilename) == 0) 
	{
		//�摜�t�@�C���̓ǂݍ���
		std::string fullPath = DEFAULT_DDS_TEXTURE_DIRECTORY + stringFilename;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureHandle;
		//DDS�t�@�C���̓ǂݍ���
		CreateDDSTextureFromFile(device, StringToWchar(fullPath), nullptr, textureHandle.ReleaseAndGetAddressOf());

		//�摜�f�[�^�̃n���h����o�^
		m_texture.insert(std::make_pair(stringFilename, std::move(textureHandle)));

	}

}
void ResourceManager::LoadDDSTexture(ID3D11Device* device, const std::string& filename)
{
	//���o�^�̏ꍇ
	if (m_models.count(filename) == 0)
	{
		//�摜�t�@�C���̓ǂݍ���
		std::string fullPath = DEFAULT_DDS_TEXTURE_DIRECTORY + filename;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureHandle;
		//DDS�t�@�C���̓ǂݍ���
		CreateDDSTextureFromFile(device, StringToWchar(fullPath), nullptr, textureHandle.ReleaseAndGetAddressOf());

		//�摜�f�[�^�̃n���h����o�^
		m_texture.insert(std::make_pair(filename, std::move(textureHandle)));

	}
}

/**
 * @brief DDS�摜�f�[�^�̗v��
 *
 * @param[in] �摜�t�@�C����
 *
 * @return �@�摜�f�[�^�̃n���h��
 */
ID3D11ShaderResourceView* ResourceManager::RequestDDSTexture(wchar_t const* filename)
{
	//���o�^�̏ꍇ
	if (m_texture.count(WcharToString(filename)) == 0)
	{
		return nullptr;
	}

	//�o�^���Ă���摜�f�[�^�̃n���h����ԋp
	return m_texture[WcharToString(filename)].Get();
}
ID3D11ShaderResourceView* ResourceManager::RequestDDSTexture(const std::string& filename)
{
	//���o�^�̏ꍇ
	if (m_texture.count(filename) == 0)
	{
		return nullptr;
	}

	////�o�^���Ă���摜�f�[�^�̃n���h����ԋp
	return m_texture[filename].Get();

}

/**
 * @brief ���f�[�^�̗v��
 *
 * @param[in] ���t�@�C����
 *
 * @return ���f�[�^�̃|�C���^
 */
DirectX::SoundEffect* ResourceManager::RequestSound(wchar_t const* filename)
{
	std::string stringFilename = WcharToString(filename);
	//���o�^�̏ꍇ
	if (m_sounds.count(stringFilename) == 0)
	{
		//���t�@�C���̓ǂݍ���
		std::string fullPath = DEFAULT_SOUND_DIRECTORY + stringFilename;


		//�摜�f�[�^�̃n���h����o�^
		std::unique_ptr<SoundEffect> soundEffect = std::make_unique<SoundEffect>(m_audioEngine, StringToWchar(fullPath));
		m_sounds.insert(std::make_pair(stringFilename, std::move(soundEffect)));
	}

	//�o�^���Ă���摜�f�[�^�̃n���h����ԋp
	return m_sounds[stringFilename].get();
}
DirectX::SoundEffect* ResourceManager::RequestSound(const std::string& filename)
{
	//���o�^�̏ꍇ
	if (m_sounds.count(filename) == 0)
	{
		//���t�@�C���̓ǂݍ���
		std::string fullPath = DEFAULT_SOUND_DIRECTORY + filename;

		
		//�摜�f�[�^�̃n���h����o�^
		std::unique_ptr<SoundEffect> soundEffect = std::make_unique<SoundEffect>(m_audioEngine, StringToWchar(fullPath));
		m_sounds.insert(std::make_pair(filename,std::move(soundEffect)));
	}

	//�o�^���Ă���摜�f�[�^�̃n���h����ԋp
	return m_sounds[filename].get();
}

/**
 * @brief ���f���f�[�^�̓ǂݍ���
 *
 * @param[in] device   �f�o�C�X
 * @param[in] filename ���f���f�[�^�t�@�C����
 *
 * @return �Ȃ�
 */
void ResourceManager::LoadModel(ID3D11Device* device, wchar_t const* filename)
{
	//���o�^�̏ꍇ
	if (m_models.count(WcharToString(filename))== 0)
	{
		std::string fullPath = DEFAULT_MODELS_DIRECTORY + WcharToString(filename);
		EffectFactory fx(device);
		std::unique_ptr<Model> model = Model::CreateFromSDKMESH(device, StringToWchar(fullPath), fx);
		 m_models.insert(std::make_pair(WcharToString(filename), std::move(model)));
	}

}
void ResourceManager::LoadModel(ID3D11Device* device, const std::string& filename)
{
	//���o�^�̏ꍇ
	if (m_models.count(filename) == 0)
	{
		std::string fullPath = DEFAULT_MODELS_DIRECTORY + filename;
		EffectFactory fx(device);
		std::unique_ptr<Model> model = Model::CreateFromSDKMESH(device, StringToWchar(fullPath), fx);
		m_models.insert(std::make_pair(filename, std::move(model)));

	}

}

/**
 * @brief ���f���f�[�^�̗v��
 *
 * @param[in] ���f���f�[�^�t�@�C����
 *
 * @return  ���f���f�[�^�̃|�C���^
 */
DirectX::Model* ResourceManager::RequestModel(wchar_t const* filename)
{
	//���o�^�̏ꍇ
	if (m_models.count(WcharToString(filename)) == 0) 
	{
		return nullptr;
	}

	return m_models[WcharToString(filename)].get();
}
DirectX::Model* ResourceManager::RequestModel(const std::string& filename)
{
	//���o�^�̏ꍇ
	if (m_models.count(filename) == 0) 
	{
		return nullptr;
	}

	return m_models[filename].get();
}


/**
 * @brief �f�[�^�폜
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void ResourceManager::Clear()
{
	////�摜�f�[�^�̍폜
	//for (auto& element : m_texture)
	//{
	//	DeleteGraph(element.second);
	//}
	//m_texture.clear();

	////���f�[�^�̍폜
	//for (auto& element : m_sounds)
	//{
	//	DeleteGraph(element.second);
	//}
	//m_sounds.clear();
}

/**
 * @brief wchar_t����string�ɕϊ�
 *
 * @param[in] wchar_t������
 *
 * @return string������
 */
std::string ResourceManager::WcharToString(wchar_t const* wchar_str)
{
	// wchar_t ���� UTF-8 �ւ̕ϊ�
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(wchar_str);
}

/**
 * @brief string����wchar_t�ɕϊ�
 *
 * @param[in] string������
 *
 * @return wchar_t������
 */
wchar_t* ResourceManager::StringToWchar(const std::string& str)
{
	// UTF-8 ���� wchar_t �ɕϊ�
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring wide_str = converter.from_bytes(str);

	// wchar_t* ��Ԃ�
	size_t size_needed = wide_str.size() + 1;  // +1 for null-terminator
	wchar_t* result = new wchar_t[size_needed];

	// wcscpy_s ���g���Ĉ��S�ɃR�s�[
	wcscpy_s(result, size_needed, wide_str.c_str());

	return result;
}

DirectX::SpriteBatch* ResourceManager::GetSpriteBatch()
{
	return m_spriteBatch.get();
}
