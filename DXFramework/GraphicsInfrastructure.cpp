#include "GraphicsInfrastructure.h"
#include "ReleaseIUnknown.h"

namespace DX11
{
	namespace GI
	{
		namespace display
		{
			namespace
			{
				std::shared_ptr<IDXGIFactory> CreateFactory() {
					IDXGIFactory *factory = nullptr;
					auto hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&factory));
					if (FAILED(hr)) throw;
					return std::shared_ptr<IDXGIFactory>(factory, ReleaseIUnknown);
				}

				std::shared_ptr<IDXGIAdapter> CreateAdapter() {
					IDXGIAdapter *adapter = nullptr;
					auto hr = CreateFactory()->EnumAdapters(0, &adapter);
					if (FAILED(hr)) throw;
					return std::shared_ptr<IDXGIAdapter>(adapter, ReleaseIUnknown);
				}
			}

			std::shared_ptr<IDXGIOutput> AccessDisplay(UINT i)
			{
				IDXGIOutput *display = nullptr;
				auto hr = CreateAdapter()->EnumOutputs(i, &display);
				if (FAILED(hr)) throw;
				return std::shared_ptr<IDXGIOutput>(display, ReleaseIUnknown);
			}

			DXGI_MODE_DESC GetOptDisplayMode(int width, int height)
			{
				// ディスプレイモード一覧の数を取得する 
				UINT num;
				GetDisplayModes(nullptr, &num);

				auto pModeDescArray = std::shared_ptr<DXGI_MODE_DESC>(
					new DXGI_MODE_DESC[num],
					std::default_delete<DXGI_MODE_DESC[]>()
					);
				GetDisplayModes(pModeDescArray.get(), &num);

				// 適切な解像度のディスプレイモードを検索する 
				DXGI_MODE_DESC  modeDesc;
				for (UINT i = 0; i < num; i++) {
					if (pModeDescArray.get()[i].Width == width && pModeDescArray.get()[i].Height == height) {
						::CopyMemory(&modeDesc, &pModeDescArray.get()[i], sizeof(DXGI_MODE_DESC));
						return modeDesc;
					}
				}
				throw;
			}

			void GetDisplayModes(DXGI_MODE_DESC *pModeDesc, UINT *pNum) {
				auto hr = AccessDisplay(0)->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, pNum, pModeDesc);
				if (FAILED(hr)) throw;
				if (pModeDesc == nullptr) {
					if (*pNum == 0) throw;
				}
			}

		} // namespace Display


		std::shared_ptr<IDXGIFactory> AccessGIFactory(IDXGIAdapter *adapter) {
			IDXGIFactory *factory = nullptr;
			auto hr = adapter->GetParent(__uuidof(IDXGIFactory), (void**)&factory);
			if (FAILED(hr)) throw;
			return std::shared_ptr<IDXGIFactory>(factory, ReleaseIUnknown);
		}

		std::shared_ptr<IDXGIFactory> AccessGIFactory(ID3D11Device *device) {
			return AccessGIFactory(AccessAdapter(device).get());
		}

		std::shared_ptr<IDXGIDevice1> AccessInterface(ID3D11Device *device) {
			IDXGIDevice1 *dxgiDevice = nullptr;
			auto hr = device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgiDevice);
			if (FAILED(hr)) throw;
			return std::shared_ptr<IDXGIDevice1>(dxgiDevice, ReleaseIUnknown);
		}

		std::shared_ptr<IDXGIAdapter> AccessAdapter(ID3D11Device *device) {
			IDXGIAdapter *adapter = nullptr;
			auto hr = AccessInterface(device)->GetAdapter(&adapter);
			if (FAILED(hr)) throw;
			return std::shared_ptr<IDXGIAdapter>(adapter, ReleaseIUnknown);
		}

		std::shared_ptr<IDXGISurface> AccessSurface(ID3D11Texture2D *tex) {
			IDXGISurface *surface;
			auto hr = tex->QueryInterface(__uuidof(IDXGISurface), (void**)&surface);
			if (FAILED(hr)) throw;
			return std::shared_ptr<IDXGISurface>(surface, ReleaseIUnknown);
		}

	} // namespace GI
} // namespace DX11
