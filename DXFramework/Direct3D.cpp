#include "Direct3D.h"
#include "GraphicsInfrastructure.h"
#include "WindowsImagingComponent.h"
#include "ReleaseIUnknown.h"

namespace DX11
{
	namespace D3D
	{
		namespace init
		{
			std::shared_ptr<ID3D11Device> CreateD3Device()
			{
				D3D_DRIVER_TYPE driverTypes[] = {
					D3D_DRIVER_TYPE_HARDWARE,
					D3D_DRIVER_TYPE_WARP,
					D3D_DRIVER_TYPE_REFERENCE,
					D3D_DRIVER_TYPE_SOFTWARE,
				};

				UINT createDeviceFlag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(DEBUG) || defined(_DEBUG)
				createDeviceFlag &= D3D11_CREATE_DEVICE_DEBUG;
#endif

				D3D_FEATURE_LEVEL featureLevels[] = {
					D3D_FEATURE_LEVEL_11_1,
					D3D_FEATURE_LEVEL_11_0,
					D3D_FEATURE_LEVEL_10_1,
					D3D_FEATURE_LEVEL_10_0,
				};

				ID3D11Device *device = nullptr;
				for (auto type : driverTypes) {
					auto hr = ::D3D11CreateDevice(
						nullptr,            // �g�p����A�_�v�^�[��ݒ�Bnullptr�̏ꍇ�̓f�t�H���g�̃A�_�v�^�[�B
						type,               // D3D_DRIVER_TYPE�̂����ꂩ�B�h���C�o�[�̎�ށB
						// pAdapter�� nullptr �ȊO�̏ꍇ�́AD3D_DRIVER_TYPE_UNKNOWN���w�肷��B
						nullptr,            // �\�t�g�E�F�A���X�^���C�U����������DLL�ւ̃n���h���B
						// D3D_DRIVER_TYPE �� D3D_DRIVER_TYPE_SOFTWARE �ɐݒ肵�Ă���ꍇ�� nullptr �ɂł��Ȃ��B
						createDeviceFlag,   // D3D11_CREATE_DEVICE_FLAG�̑g�ݍ��킹�B�f�o�C�X���쐬���Ɏg�p�����p�����[�^�B
						featureLevels,      // D3D_FEATURE_LEVEL�̃|�C���^
						_countof(featureLevels), // D3D_FEATURE_LEVEL�z��̗v�f��
						D3D11_SDK_VERSION,  // DirectX SDK�̃o�[�W�����B���̒l�͌Œ�B
						&device,            // ���������ꂽ�f�o�C�X
						nullptr,            // �̗p���ꂽ�t�B�[�`���[���x��
						nullptr             // ���������ꂽ�f�o�C�X�R���e�L�X�g
						);
					if (SUCCEEDED(hr)) break;
				}
				if (!device) throw;
				return std::shared_ptr<ID3D11Device>(device, ReleaseIUnknown);
			}
		}

		namespace shader
		{
			namespace detail
			{
				template<typename S> std::shared_ptr<S> CreateShader(
					ID3D11Device *device, BYTE *shader, size_t size,
					HRESULT(__stdcall ID3D11Device::*func)(const void *, SIZE_T, ID3D11ClassLinkage *, S **)
					)
				{
					S * shaderObject = nullptr;
					auto hr = (device->*func)(shader, size, nullptr, &shaderObject);
					if (FAILED(hr)) throw;
					return std::shared_ptr<S>(shaderObject, ReleaseIUnknown);
				}

				std::shared_ptr<ID3D11PixelShader> CreatePixelShader(ID3D11Device *device, BYTE* shader, size_t size)
				{
					return detail::CreateShader(device, shader, size, &ID3D11Device::CreatePixelShader);
				}

				std::shared_ptr<ID3D11VertexShader> CreateVertexShader(ID3D11Device *device, BYTE *shader, size_t size)
				{
					return detail::CreateShader(device, shader, size, &ID3D11Device::CreateVertexShader);
				}

				std::shared_ptr<ID3D11GeometryShader> CreateGeometryShader(ID3D11Device *device, BYTE *shader, size_t size)
				{
					return detail::CreateShader(device, shader, size, &ID3D11Device::CreateGeometryShader);
				}

				std::shared_ptr<ID3D11InputLayout> CreateInputLayout(
					ID3D11Device *device, D3D11_INPUT_ELEMENT_DESC layoutDesc[], UINT numOfLayout, BYTE *shader, size_t size
					)
				{
					ID3D11InputLayout *layout;
					auto hr = device->CreateInputLayout(layoutDesc, numOfLayout, shader, size, &layout);
					if (FAILED(hr))throw;
					return std::shared_ptr<ID3D11InputLayout>(layout, ReleaseIUnknown);
				}
			}

			std::shared_ptr<ID3DBlob> CompileShader(TCHAR source[], CHAR entryPoint[], CHAR target[])
			{
				// �s����D��Őݒ肵�A�Â��`���̋L�q�������Ȃ��悤�ɂ���
				UINT flag1 = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS;
				// �œK�����x����ݒ肷��
#if defined(DEBUG) || defined(_DEBUG)
				flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL0;
#else
				flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif

				ID3DBlob *blob = nullptr;
				auto hr = ::D3DCompileFromFile(source, nullptr, nullptr, entryPoint, target, flag1, 0, &blob, nullptr);
				if (FAILED(hr)) throw;
				return std::shared_ptr<ID3DBlob>(blob, ReleaseIUnknown);
			}

			std::shared_ptr<ID3D11PixelShader> CreatePixelShader(ID3D11Device *device, ID3DBlob *blob)
			{
				return detail::CreatePixelShader(device, (BYTE*)blob->GetBufferPointer(), blob->GetBufferSize());
			}

			std::shared_ptr<ID3D11VertexShader> CreateVertexShader(ID3D11Device *device, ID3DBlob *blob)
			{
				return detail::CreateVertexShader(device, (BYTE*)blob->GetBufferPointer(), blob->GetBufferSize());
			}

			std::shared_ptr<ID3D11GeometryShader> CreateGeometryShader(ID3D11Device *device, ID3DBlob *blob)
			{
				return detail::CreateGeometryShader(device, (BYTE*)blob->GetBufferPointer(), blob->GetBufferSize());
			}

			std::shared_ptr<ID3D11InputLayout> CreateInputLayout(
				ID3D11Device *device, D3D11_INPUT_ELEMENT_DESC layoutDesc[], UINT numOfLayout, ID3DBlob *blob
				)
			{
				return detail::CreateInputLayout(
					device, layoutDesc, numOfLayout, (BYTE*)blob->GetBufferPointer(), blob->GetBufferSize());
			}
		}
		namespace context
		{
			void SetDefaultRenderTarget(IDXGISwapChain *swapChain)
			{
				auto targetView = detail::CreateRenderTargetView(swapChain);
				ID3D11RenderTargetView *targetViews[] = { targetView.get() };
				AccessD3Context(swapChain)->OMSetRenderTargets(1, targetViews, detail::CreateDepthStencilView(swapChain).get());
			}
			void SetDefaultViewport(IDXGISwapChain *swapChain)
			{
				// �X���b�v�`�F�[���̐ݒ���擾����
				DXGI_SWAP_CHAIN_DESC chainDesc;
				auto hr = swapChain->GetDesc(&chainDesc);
				if (FAILED(hr)) throw;

				D3D11_VIEWPORT Viewport[1];
				Viewport[0].TopLeftX = 0;
				Viewport[0].TopLeftY = 0;
				Viewport[0].Width = (FLOAT)chainDesc.BufferDesc.Width;
				Viewport[0].Height = (FLOAT)chainDesc.BufferDesc.Height;
				Viewport[0].MinDepth = 0.0f;
				Viewport[0].MaxDepth = 1.0f;
				AccessD3Context(swapChain)->RSSetViewports(1, Viewport);
			}

			void SetDefaultRasterize(IDXGISwapChain *swapChain)
			{
				D3D11_RASTERIZER_DESC rsState;
				rsState.FillMode = D3D11_FILL_SOLID;
				rsState.CullMode = D3D11_CULL_NONE;
				rsState.FrontCounterClockwise = FALSE;
				rsState.DepthBias = 0;
				rsState.DepthBiasClamp = 0;
				rsState.SlopeScaledDepthBias = 0;
				rsState.DepthClipEnable = TRUE;
				rsState.ScissorEnable = FALSE;
				rsState.AntialiasedLineEnable = FALSE;

				// �X���b�v�`�F�[���̃}���`�T���v�����O�̐ݒ�ɂ��킹��
				DXGI_SWAP_CHAIN_DESC swapDesc;
				swapChain->GetDesc(&swapDesc);
				rsState.MultisampleEnable = (swapDesc.SampleDesc.Count != 1) ? TRUE : FALSE;

				ID3D11RasterizerState *rasterState_raw = nullptr;
				HRESULT hr = AccessD3Device(swapChain)->CreateRasterizerState(&rsState, &rasterState_raw);
				if (FAILED(hr)) throw;
				auto rasterState = std::shared_ptr<ID3D11RasterizerState>(rasterState_raw, ReleaseIUnknown);
				AccessD3Context(swapChain)->RSSetState(rasterState_raw);
			}
		};

		namespace buffer
		{
			namespace detail
			{
				std::shared_ptr<ID3D11Buffer> CreateBuffer(
					ID3D11Device *device, void *data, size_t size, UINT cpuAccessFlag, D3D11_BIND_FLAG BindFlag
					)
				{
					auto resource = std::make_shared<D3D11_SUBRESOURCE_DATA>();
					resource->pSysMem = data;
					resource->SysMemPitch = 0;
					resource->SysMemSlicePitch = 0;

					D3D11_BUFFER_DESC BufferDesc = { 0 };
					BufferDesc.ByteWidth = size;
					BufferDesc.CPUAccessFlags = cpuAccessFlag;
					BufferDesc.Usage = (cpuAccessFlag == 0) ? D3D11_USAGE_DEFAULT : D3D11_USAGE_DYNAMIC;
					BufferDesc.MiscFlags = 0;
					BufferDesc.BindFlags = BindFlag;
					if (BindFlag == D3D11_BIND_STREAM_OUTPUT) BufferDesc.BindFlags |= D3D11_BIND_VERTEX_BUFFER;

					ID3D11Buffer *buffer = nullptr;
					auto hr = device->CreateBuffer(&BufferDesc, (data == nullptr) ? nullptr : resource.get(), &buffer);
					if (FAILED(hr)) throw;
					return std::shared_ptr<ID3D11Buffer>(buffer, ReleaseIUnknown);
				}
			}
		}

		namespace detail
		{
			namespace depth
			{
				DXGI_FORMAT TextureFormat2DepthStencilViewFormat(DXGI_FORMAT format)
				{
					switch (format) {
					case DXGI_FORMAT_R8_TYPELESS:
						return DXGI_FORMAT_R8_UNORM;
					case DXGI_FORMAT_R16_TYPELESS:
						return DXGI_FORMAT_D16_UNORM;
					case DXGI_FORMAT_R32_TYPELESS:
						return DXGI_FORMAT_D32_FLOAT;
					case DXGI_FORMAT_R24G8_TYPELESS:
						return DXGI_FORMAT_D24_UNORM_S8_UINT;
					default:
						return format;
					}
				}
				
				D3D11_TEXTURE2D_DESC CreateDepthBufferDESC(IDXGISwapChain * swapChain)
				{
					// �X���b�v�`�F�[���̐ݒ���擾����
					DXGI_SWAP_CHAIN_DESC chainDesc;
					auto hr = swapChain->GetDesc(&chainDesc);
					if (FAILED(hr)) throw;

					D3D11_TEXTURE2D_DESC descDS;
					::ZeroMemory(&descDS, sizeof(D3D11_TEXTURE2D_DESC));
					descDS.Width = chainDesc.BufferDesc.Width;
					descDS.Height = chainDesc.BufferDesc.Height;
					descDS.MipLevels = 1;                             // �~�b�v�}�b�v���쐬���Ȃ�
					descDS.ArraySize = 1;
					descDS.Format = DXGI_FORMAT_R32_TYPELESS;
					descDS.SampleDesc.Count = chainDesc.SampleDesc.Count;
					descDS.SampleDesc.Quality = chainDesc.SampleDesc.Quality;
					descDS.Usage = D3D11_USAGE_DEFAULT;
					descDS.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
					descDS.CPUAccessFlags = 0;
					descDS.MiscFlags = 0;
					return descDS;
				}
				std::shared_ptr<ID3D11Texture2D> CreateDepthBuffer(ID3D11Device *device, D3D11_TEXTURE2D_DESC descDS) {
					ID3D11Texture2D *depthBuffer = nullptr;
					auto hr = device->CreateTexture2D(&descDS, nullptr, &depthBuffer);
					if (FAILED(hr)) throw;
					return std::shared_ptr<ID3D11Texture2D>(depthBuffer, ReleaseIUnknown);
				}
			};

			std::shared_ptr<ID3D11RenderTargetView> CreateRenderTargetView(IDXGISwapChain *swapChain) {
				ID3D11RenderTargetView *view = nullptr;
				auto hr = AccessD3Device(swapChain)->CreateRenderTargetView(AccessBackBuffer(swapChain).get(), nullptr, &view);
				if (FAILED(hr)) throw;
				return std::shared_ptr<ID3D11RenderTargetView>(view, ReleaseIUnknown);
			}

			std::shared_ptr<ID3D11DepthStencilView> CreateDepthStencilView(IDXGISwapChain *swapChain) {
				auto device = AccessD3Device(swapChain);
				auto descDS = depth::CreateDepthBufferDESC(swapChain);
				auto depthBuffer = depth::CreateDepthBuffer(device.get(), descDS);

				D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
				::ZeroMemory(&descDSV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
				descDSV.Format = depth::TextureFormat2DepthStencilViewFormat(descDS.Format);
				descDSV.ViewDimension = (descDS.SampleDesc.Count > 1) ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
				descDSV.Texture2D.MipSlice = 0;

				ID3D11DepthStencilView *depthStencilView = nullptr;
				auto hr = device->CreateDepthStencilView(depthBuffer.get(), &descDSV, &depthStencilView);
				if (FAILED(hr)) throw;

				return std::shared_ptr<ID3D11DepthStencilView>(depthStencilView, ReleaseIUnknown);
			}
		}

		std::shared_ptr<IDXGISwapChain> CreateSwapChain(
			DXGI_MODE_DESC *displayMode, HWND hWnd, ID3D11Device *device, bool useMultiSample
			)
		{
			DXGI_SWAP_CHAIN_DESC sd;
			::ZeroMemory(&sd, sizeof(sd));

			::CopyMemory(&(sd.BufferDesc), displayMode, sizeof(DXGI_MODE_DESC));
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
			sd.BufferCount = 1;
			sd.OutputWindow = hWnd;
			sd.Windowed = TRUE;
			sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			sd.SampleDesc.Count = (useMultiSample == true) ? 4 : 1;
			sd.SampleDesc.Quality = 0;

			// �T���v�����O���̌���
			int numOfSample = (useMultiSample == true) ? D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT : 1;

			UINT quality = 0;
			IDXGISwapChain *swapChain = nullptr;
			for (int i = numOfSample; i >= 0; i--) {
				// �T�|�[�g����N�H���e�B���x���̍ő�l���擾����
				auto hr = device->CheckMultisampleQualityLevels(displayMode->Format, (UINT)i, &quality);
				if (FAILED(hr)) throw;

				// 0 �ȊO�̂Ƃ��t�H�[�}�b�g�ƃT���v�����O���̑g�ݍ��킹���T�|�[�g����
				// �I�����C���w���v�ł�CheckMultisampleQualityLevels�̖߂�l�� 0 �̂Ƃ��T�|�[�g����Ȃ��Ƃ�����Ă��邪
				// pNumQualityLevels �̖߂�l�� 0 ���Ŕ��f����B
				// Direct3D 10 �� �̃I�����C���w���v�ɂ͂���������Ă���̂ŁA�I�����C���w���v�̊ԈႢ�B
				if (quality != 0) {
					sd.SampleDesc.Count = i;
					sd.SampleDesc.Quality = quality - 1;

					hr = GI::AccessGIFactory(device)->CreateSwapChain(device, &sd, &swapChain);
					if (SUCCEEDED(hr)) break;
				}
			}
			if (swapChain == nullptr) throw;
			return std::shared_ptr<IDXGISwapChain>(swapChain, ReleaseIUnknown);
		}

		std::shared_ptr<ID3D11Texture2D> AccessBackBuffer(IDXGISwapChain *swapChain)
		{
			ID3D11Texture2D *backBuffer = nullptr;
			auto hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
			if (FAILED(hr)) throw;
			return std::shared_ptr<ID3D11Texture2D>(backBuffer, ReleaseIUnknown);
		}

		std::shared_ptr<ID3D11Device> AccessD3Device(IDXGISwapChain *swapChain)
		{
			ID3D11Device *device = nullptr;
			auto hr = swapChain->GetDevice(__uuidof(ID3D11Device), (void **)&device);
			if (FAILED(hr)) throw;
			return std::shared_ptr<ID3D11Device>(device, ReleaseIUnknown);
		}

		std::shared_ptr<ID3D11DeviceContext> AccessD3Context(ID3D11Device *device)
		{
			ID3D11DeviceContext *context = nullptr;
			device->GetImmediateContext(&context);
			return std::shared_ptr<ID3D11DeviceContext>(context, ReleaseIUnknown);
		}

		std::shared_ptr<ID3D11DeviceContext> AccessD3Context(IDXGISwapChain *swapChain)
		{
			return AccessD3Context(AccessD3Device(swapChain).get());
		}
	}
}