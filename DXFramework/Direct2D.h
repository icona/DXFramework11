#pragma once

#include "directX.h"
#include <memory>

/*!
 DirectX11のラッパ郡
*/
namespace DX11
{
	/*! Direct2Dに関するラッパ郡 */
	namespace D2D
	{
		/*! 初期化に関するラッパ郡 */
		namespace init{
			/*!
			 @fn std::shared_ptr<ID2D1Device> CreateD2Device(ID3D11Device *device)
			 @brief 与えられたID3D11から新しいDirect2Dデバイスを作成する．
			 @param ID3D11Device *device
			 @return 作成されたDirect2Dデバイスを指すスマートポインタが返ります．
			*/
			std::shared_ptr<ID2D1Device> CreateD2Device(ID3D11Device *device);
			
			/*!
			 @fn std::shared_ptr<ID2D1HwndRenderTarget> CreateRenderTarget(HWND hWnd)
			 @brief 与えられたウィンドウハンドルが指すウィンドウを対象とした，
				レンダリングターゲットサーフェイスを作成する．
			 @param ID3D11Device *device
			 @return 作成されたレンダリングターゲットサーフェイスを指すスマートポインタを返します．
			*/
			std::shared_ptr<ID2D1HwndRenderTarget> CreateRenderTarget(HWND hWnd);
		};

		/*! 描画に関するラッパ郡 */
		namespace drawer
		{
			/*!
			 @fn std::shared_ptr<ID2D1SolidColorBrush> CreateBrush(D2D1::ColorF color, ID2D1RenderTarget *renderTarget)
			 @brief 与えられたレンダリングターゲットサーフェイスの指定された色の論理ブラシを作成する．
			 @param D2D1::ColorF color
			 @param ID2D1RenderTarget *renderTarget
			 @return 作成された論理ブラシを指すスマートポインタ
			*/
			std::shared_ptr<ID2D1SolidColorBrush> CreateBrush(D2D1::ColorF color, ID2D1RenderTarget *renderTarget);

			/*!
			 @fn std::shared_ptr<ID2D1BitmapBrush> CreateBitmapBrush(ID2D1Bitmap *bitmap, ID2D1RenderTarget *target);
			 @brief 与えられたレンダリングターゲットサーフェイスの指定されたビットマップのブラシを作成する．
			 @param ID2D1Bitmap *bitmap
			 @param ID2D1RenderTarget *target
			 @return 作成されたビットマップブラシを指すスマートポインタ
			*/
			std::shared_ptr<ID2D1BitmapBrush> CreateBitmapBrush(ID2D1Bitmap *bitmap, ID2D1RenderTarget *target);

			/*!
			 @fn std::shared_ptr<ID2D1BitmapBrush> CreateBitmapBrush(const TCHAR *path, ID2D1RenderTarget *target)
			 @brief 与えられたレンダリングターゲットサーフェイスの指定されたパスのビットマップのブラシを作成する．
			 @param const TCHAR *path
			 @param ID2D1RenderTarget *target
			 @return 作成されたビットマップブラシを指すスマートポインタを返す．
			*/
			std::shared_ptr<ID2D1BitmapBrush> CreateBitmapBrush(const TCHAR *path, ID2D1RenderTarget *target);
		};

		/*!
		 @fn std::shared_ptr<ID2D1Factory1> AccessD2Factory()
		 @brief Direct2Dのリソースの作成に使用できるファクトリオブジェクトを作成する．
		 @return 作成したファクトリオブジェクトを指すスマートポインタを返す．
		*/
		std::shared_ptr<ID2D1Factory1> AccessD2Factory();

		/*!
		 @fn std::shared_ptr<ID2D1DeviceContext> AccessD2Context(ID2D1Device *device2d)
	 	 @brief 指定されたデバイスのコンテキストを作成する．
		 @param ID2D1Device *device2d
		 @return 作成したデバイスコンテキストを指すスマートポインタを返す．

		 @description 詳細な解説が求められています（TODO）．
		*/
		std::shared_ptr<ID2D1DeviceContext> AccessD2Context(ID2D1Device *device2d);

		/*!
		 @fn std::shared_ptr<ID2D1Bitmap> AccessBitmap(ID3D11Texture2D *tex, ID2D1DeviceContext *deviceContext2d)
		 @brief ID3D11Texture2Dのサーフェイスを元にBitmapを作成する．
		 @param ID3D11Texture2D *tex
		 @param ID2D1DeviceContext *deviceContext2d
		 @return 作成されたBitmapを指すスマートポインタを返す．

		 @description この関数は，DX11::D3D::AccessBackBuffer(IDXGISwapChain *swapChain)と組み合わせて用いる．
			D3D11CreateDeviceAndSwapChainなどによって生成されたDirect3D用のswapchainのバックバッファにAccessBackBufferでアクセスし，得られた
			ID3D11Texture2Dのサーフェイスを元にBitmapを作成する．
		*/
		std::shared_ptr<ID2D1Bitmap> AccessBitmap(ID3D11Texture2D *tex, ID2D1DeviceContext *deviceContext2d);

		/*!
		 @fn std::shared_ptr<ID2D1Bitmap> CreateBitmap(const TCHAR *path, ID2D1RenderTarget *target)
		 @brief 指定されたレンダリングターゲットに指定されたパスの画像のBitmapを作成する．
		 @param const TCHAR *path
		 @param ID2D1RenderTarget *target
		 @return 作成されたBitmapを指すスマートポインタを返す．
		*/
		std::shared_ptr<ID2D1Bitmap> CreateBitmap(const TCHAR *path, ID2D1RenderTarget *target);

	}
}