#include "Direct2D.h"
#include "GraphicsInfrastructure.h"
#include "WindowsImagingComponent.h"
#include "ReleaseIUnknown.h"

namespace DX11{
	namespace D2D{
		namespace init{
			std::shared_ptr<ID2D1HwndRenderTarget> CreateRenderTarget(HWND hWnd)
			{
				RECT rc;
				::GetClientRect(hWnd, &rc);

				ID2D1HwndRenderTarget *renderTarget = nullptr;
				HRESULT hr = AccessD2Factory()->CreateHwndRenderTarget(
					::D2D1::RenderTargetProperties(),
					::D2D1::HwndRenderTargetProperties(
						hWnd,
						D2D1::SizeU(
							rc.right - rc.left,
							rc.bottom - rc.top
						)
						),
						&renderTarget
					);
				if (FAILED(hr)) throw;
				return std::shared_ptr<ID2D1HwndRenderTarget>(renderTarget, ReleaseIUnknown);
			}

			std::shared_ptr<ID2D1Device> CreateD2Device(ID3D11Device *device)
			{
				ID2D1Device *device2d;
				auto hr = AccessD2Factory()->CreateDevice((IDXGIDevice*)device, &device2d);
				if (FAILED(hr)) throw;
				return std::shared_ptr<ID2D1Device>(device2d, ReleaseIUnknown);
			}
		};
		namespace drawer
		{
			std::shared_ptr<ID2D1SolidColorBrush> CreateBrush(D2D1::ColorF color, ID2D1RenderTarget *renderTarget)
			{
				ID2D1SolidColorBrush *brush = nullptr;
				auto hr = renderTarget->CreateSolidColorBrush(color, &brush);
				if (FAILED(hr)) throw;
				return std::shared_ptr<ID2D1SolidColorBrush>(brush, ReleaseIUnknown);
			}

			std::shared_ptr<ID2D1BitmapBrush> CreateBitmapBrush(ID2D1Bitmap *bitmap, ID2D1RenderTarget *target)
			{
				ID2D1BitmapBrush *brush;
				auto brushProp = D2D1::BitmapBrushProperties(D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP);
				auto hr = target->CreateBitmapBrush(bitmap, brushProp, D2D1::BrushProperties(), &brush);
				if (FAILED(hr)) throw;
				return std::shared_ptr<ID2D1BitmapBrush>(brush, ReleaseIUnknown);
			}

			std::shared_ptr<ID2D1BitmapBrush> CreateBitmapBrush(const TCHAR *path, ID2D1RenderTarget *target)
		 	{
				auto bitmap = CreateBitmap(path, target);
				return CreateBitmapBrush(bitmap.get(), target);
			}
		};

		std::shared_ptr<ID2D1Factory1> AccessD2Factory()
		{
			ID2D1Factory1 *factory = nullptr;
			HRESULT hr = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory1), (void**)&factory);
			if (FAILED(hr)) throw;
			return std::shared_ptr<ID2D1Factory1>(factory, ReleaseIUnknown);
		}

		std::shared_ptr<ID2D1DeviceContext> AccessD2Context(ID2D1Device *device2d)
		{
			ID2D1DeviceContext *deviceContext2d;
			auto hr = device2d->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &deviceContext2d);
			if (FAILED(hr)) throw;
			return std::shared_ptr<ID2D1DeviceContext>(deviceContext2d, ReleaseIUnknown);
		}

		std::shared_ptr<ID2D1Bitmap> AccessBitmap(ID2D1DeviceContext *deviceContext2d, ID3D11Texture2D *tex)
		{
			D2D1_BITMAP_PROPERTIES1 bitmapProps = {};
			bitmapProps.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
			bitmapProps.pixelFormat = ::D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE);
			AccessD2Factory()->GetDesktopDpi(&bitmapProps.dpiX, &bitmapProps.dpiY);

			ID2D1Bitmap1 *bitmap;
			auto surface = DX11::GI::AccessSurface(tex);
			auto hr = deviceContext2d->CreateBitmapFromDxgiSurface(surface.get(), &bitmapProps, &bitmap);
			if (FAILED(hr)) throw;
			return std::shared_ptr<ID2D1Bitmap1>(bitmap, ReleaseIUnknown);
		}

		std::shared_ptr<ID2D1Bitmap> CreateBitmap(const TCHAR *path, ID2D1RenderTarget *target)
		{
			auto decoder = wic::CreateDecoder(path);
			auto frame = wic::AccessFrame(decoder.get());
			auto converter = wic::CreateConverter();
			auto hr = converter->Initialize(
				frame.get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut
				);
			if (FAILED(hr)) throw;

			ID2D1Bitmap *bitmap = nullptr;
			if (FAILED(target->CreateBitmapFromWicBitmap(converter.get(), &bitmap))) throw;
			return std::shared_ptr<ID2D1Bitmap>(bitmap, ReleaseIUnknown);
		}
	}
}