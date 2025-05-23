//
// Game.cpp
//

#include "pch.h"
#include "Game/Game.h"

#include "Game/Scene/GameScene.h"
#include"Game/Scene/TitleScene.h"
#include"Game/Scene/StageSelectScene.h"
#include"Game/Scene/LogoScene.h"
#include"Game/Scene/ResultScene.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
    : m_resourceManager{}
    , m_sceneManager{}
    
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    // TODO: Provide parameters for swapchain format, depth/stencil format, and backbuffer count.
    //   Add DX::DeviceResources::c_AllowTearing to opt-in to variable rate displays.
    //   Add DX::DeviceResources::c_EnableHDR for HDR10 display.
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{

    //�I�[�f�B�I�G���W���̍쐬
    AUDIO_ENGINE_FLAGS eflags=AudioEngine_Default;
#ifdef _DEBUG
    eflags |= AudioEngine_Debug;
#endif // DEBUG
    m_audioEngine = std::make_unique<AudioEngine>(eflags);
    m_audioEngine->SetMasterVolume(1.0f); // 1.0f�͍ő剹��



    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */


    
    //�V�[������
    m_sceneManager->Register("Title", std::make_unique<TitleScene>(m_sceneManager.get(), m_resourceManager.get()));
    m_sceneManager->Register("Game", std::make_unique<GameScene>(m_sceneManager.get(), m_resourceManager.get()));
	m_sceneManager->Register("Result", std::make_unique<ResultScene>(m_sceneManager.get(), m_resourceManager.get()));
	m_sceneManager->Register("StageSelect", std::make_unique<StageSelectScene>(m_sceneManager.get(), m_resourceManager.get()));
    // �J�n�V�[���̐ݒ�
    m_sceneManager->SetStratScene("Title");



    // �f�o�b�O�J�����̍쐬
    m_debugCamera = std::make_unique<Imase::DebugCamera>(width, height);


}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;
    auto key = Keyboard::Get().GetState();

    // �f�o�b�O�J�����̍X�V
    //m_debugCamera->Update();

	//�V�[���̍X�V
	m_sceneManager->Update(key, elapsedTime);


	// �I�[�f�B�I�̍X�V
	if (!m_audioEngine->Update())
	{
		if (m_audioEngine->IsCriticalError())
		{
			// �G���[����
			OutputDebugString(L"AudioEngine Error\n");
		}
	}
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

    // �f�o�b�O�J��������r���[�s����擾����
    //SimpleMath::Matrix view = m_debugCamera->GetCameraMatrix();

    // �O���b�h�̏��v�̕`��
    //m_gridFloor->Render(context, view, m_proj);


    // FPS���擾����
    uint32_t fps = m_timer.GetFramesPerSecond();

     
	//�V�[���̕`��
	m_sceneManager->Render(*context,*m_states,m_proj);
    
    // FPS�̕\��
    m_debugFont->AddString(0, 0, Colors::White, L"FPS=%d", fps);

	//CapsuleCollider capsule=m_player.GetCollider();
	//DirectX::SimpleMath::Vector3 start= capsule.GetStart();
	//DirectX::SimpleMath::Vector3 end= capsule.GetEnd();
	//m_debugFont->AddString(0, 20, Colors::White, L"start=(%f,%f,%f)", start.x, start.y, start.z);
	//m_debugFont->AddString(0, 40, Colors::White, L"end=(%f,%f,%f)", end.x, end.y, end.z);
    // �f�o�b�O�t�H���g�̕`��
    m_debugFont->Render(m_states.get());


    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto const viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
	m_audioEngine->Suspend();
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
	m_audioEngine->Resume();
}

void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 1280;
    height = 720;
}


#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

    // ���ʃX�e�[�g�̍쐬
    m_states = std::make_unique<CommonStates>(device);

    // �f�o�b�O�t�H���g�̍쐬
    m_debugFont = std::make_unique<Imase::DebugFont>(device
        , context, L"Resources\\Font\\SegoeUI_18.spritefont");

    // �O���b�h���̍쐬
    m_gridFloor = std::make_unique<Imase::GridFloor>(device, context, m_states.get());


    //�}�l�[�W���[����
    m_resourceManager = std::make_unique<ResourceManager>(m_audioEngine.get(), context);
    m_sceneManager = std::make_unique<SceneManager>();

    m_resourceManager->LoadModel(device, "JumpinPlayer.sdkmesh");
    m_resourceManager->LoadModel(device, "block.sdkmesh");
    m_resourceManager->LoadModel(device, "flag.sdkmesh");
	m_resourceManager->LoadDDSTexture(device, "pressspace.dds");
	m_resourceManager->LoadDDSTexture(device, "title.dds");
	m_resourceManager->LoadDDSTexture(device, "clear.dds");
	m_resourceManager->LoadDDSTexture(device, "gameover.dds");
	m_resourceManager->LoadDDSTexture(device, "titleback.dds");
	m_resourceManager->LoadDDSTexture(device, "arrow.dds");
	m_resourceManager->LoadDDSTexture(device, "stage1.dds");
	m_resourceManager->LoadDDSTexture(device, "stage2.dds");
	m_resourceManager->LoadDDSTexture(device, "clearback.dds");
	m_resourceManager->LoadDDSTexture(device, "gameoverback.dds");
	m_resourceManager->LoadDDSTexture(device, "guide.dds");


}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
    
    // ��ʃT�C�Y�̎擾
    RECT rect = m_deviceResources->GetOutputSize();

    // �ˉe�s��̍쐬
    m_proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
        XMConvertToRadians(45.0f)
        , static_cast<float>(rect.right) / static_cast<float>(rect.bottom)
        , 0.1f, 100.0f);

}


void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
