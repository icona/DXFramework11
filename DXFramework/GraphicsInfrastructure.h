#pragma once

#include "directX.h"
#include <memory>

namespace DX11
{
	namespace GI
	{
		namespace display{
			std::shared_ptr<IDXGIOutput> AccessDisplay(UINT i);
			void GetDisplayModes(DXGI_MODE_DESC *pModeDesc, UINT *pNum);
			DXGI_MODE_DESC GetOptDisplayMode(int width, int height);
		};

		std::shared_ptr<IDXGIFactory> AccessGIFactory(IDXGIAdapter *adapter);

		std::shared_ptr<IDXGIFactory> AccessGIFactory(ID3D11Device *device);

		std::shared_ptr<IDXGIDevice1> AccessInterface(ID3D11Device *device);

		std::shared_ptr<IDXGIAdapter> AccessAdapter(ID3D11Device *device);

		std::shared_ptr<IDXGISurface> AccessSurface(ID3D11Texture2D *tex);
	}
}