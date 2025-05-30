//
// Game.h
//

#pragma once
// クラスの宣言 ===============================================================
#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"

#include "DeviceResources.h"
#include "StepTimer.h"

#include "ImaseLib/DebugFont.h"
#include "ImaseLib/GridFloor.h"
#include "ImaseLib/DebugCamera.h"


#include"Game/Object/Player.h"
#include"Game/Object/Block.h"
#include"Game/Object/Stage.h"
// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;


private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;
private:

    // 射影行列
    DirectX::SimpleMath::Matrix m_proj;

    // 共通ステート
    std::unique_ptr<DirectX::CommonStates> m_states;

    // デバッグフォント
    std::unique_ptr<Imase::DebugFont> m_debugFont;

    // グリッドの床
    std::unique_ptr<Imase::GridFloor> m_gridFloor;

    // デバッグカメラ
    std::unique_ptr<Imase::DebugCamera> m_debugCamera;

    //オーディオ
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;

    // マネージャ関連
    std::unique_ptr<ResourceManager> m_resourceManager;    ///< リソースマネージャ
    std::unique_ptr<SceneManager>    m_sceneManager;       ///< シーンマネージャ
};
