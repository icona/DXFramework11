#pragma once

#include "directX.h"
#include <memory>

/*! DirectX11のラッパ郡 */
namespace DX11
{
	/*! DirectX3Dのラッパ郡 */
	namespace D3D{

		/*! 初期化に関するラッパ郡 */
		namespace init{
			/*!
			 @fn std::shared_ptr<ID3D11Device> CreateD3Device()
			 @brief ディスプレイアダプターを表すデバイスを作成する．
			 @return 作成されたデバイスを指すスマートポインタ

			 @description 機能レベルを最高のものから順に試し，作成したデバイスを指すスマートポインタを返す．
							用いるドライバータイプはD3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_SOFTWARE
							の４つ．便利関数の一種で，D3D11CreateDeviceを用いてデバイスを作成する場合に比べて，煩雑な処理を省略することができます．
			*/
			std::shared_ptr<ID3D11Device> CreateD3Device();
		}

		/*! 各種コンテキストの簡易初期設定関数群 */
		namespace context
		{
			/*!
			 @fn void SetDefaultRenderTarget(IDXGISwapChain *swapChain)
			 @brief リソースデータへのアクセス用にレンダーゲットビューを作成し，出力結合ステージにバインドする．
			 @param IDXGISwapChain *swapChain
			 
			 @description リソースデータへのアクセス用にレンダーゲットビューを作成し，出力結合ステージにバインドします．
			*/
			void SetDefaultRenderTarget(IDXGISwapChain *swapChain);

			/*!
			 @fn void SetDefaultViewport(IDXGISwapChain *swapChain)
			 @brief パイプラインのラスタライザステージに簡易的なビューポートをバインドします．
			 @param IDXGISwapChain *swapChain

			 @description 便利関数の一種で，一般的なビューポートのバインド処理を簡略化することができます．
							ビューポートを複数バインドする場合，特殊なビューポートを設定する場合は使用できません．
			*/
			void SetDefaultViewport(IDXGISwapChain *swapChain);

			/*!
			 @fn void SetDefaultRasterize(IDXGISwapChain *swapChain)
			 @brief 簡易なラスタライザステートオブジェクトを作成する．
			 @param IDXGISwapChain *swapChain

			 @description 便利関数の一種で，一般的なラスタライザステートオブジェクトの作成を簡略化することができます．
							詳細な設定が必要な場合は利用できません．作成されるラスタライザの設定は以下のソースコードを
							参照してください．
			*/
			void SetDefaultRasterize(IDXGISwapChain *swapChain);
		}

		/*!	シェーダのラッパ郡	*/
		namespace shader
		{
			/*! DX11::D3D::shader内の関数群のための補助関数 */
			namespace detail
			{
				/*!
				 @fn template<typename S> std::shared_ptr<S> CreateShader(
					ID3D11Device *device,
					BYTE *shader,
					size_t size,
					HRESULT(__stdcall ID3D11Device::*func)(const void *, SIZE_T, ID3D11ClassLinkage *, S **)
					);
				@brief 渡された関数を元にシェーダを作成する．他のCreate~Shadarのためのテンプレートです．
				@param ID3D11Device *device
				@param BYTE *shader
				@param size_t size
				@param HRESULT(__stdcall ID3D11Device::*func)(const void *, SIZE_T, ID3D11ClassLinkage *, S **)
				@return 作成されたシェーダを指すスマートポインタ

				@description ライブラリ内の関数向けの関数で通常ユーザが利用することは想定していません．
				*/
				template<typename S>
				std::shared_ptr<S> CreateShader(
					ID3D11Device *device,
					BYTE *shader,
					size_t size,
					HRESULT(__stdcall ID3D11Device::*func)(const void *, SIZE_T, ID3D11ClassLinkage *, S **)
					);

				/*!
				 @fn std::shared_ptr<ID3D11PixelShader> CreatePixelShader(
					ID3D11Device *device,
					BYTE *shader,
					size_t size
					);
				@brief ピクセルシェーダを作成する．
				@param ID3D11Device *device
				@param BYTE *shader
				@param size_t size
				@return 作成されたピクセルシェーダを指すスマートポインタ

				@description ライブラリ内の関数向けの関数で通常ユーザが利用することは想定していません．
							DX11::D3D::shader::CreatePixelShader(ID3D11Device *device, ID3DBlob *blob)を利用してください．
				*/
				std::shared_ptr<ID3D11PixelShader> CreatePixelShader(
					ID3D11Device *device,
					BYTE *shader,
					size_t size
					);

				/*!
				 @fn std::shared_ptr<ID311VertexShader> CreateVertexShader(
					ID3D11Device *device,
					BYTE *shader,
					size_t size
					);
				 @brief 頂点シェーダを作成する．
				 @param ID3D11Device *device
				 @param BYTE *shader
				 @param size_t size
				 @return 作成された頂点シェーダを指すスマートポインタ

				 @description ライブラリ内の関数向けの関数で通常ユーザが利用することは想定していません．
								DX11::D3D::shader::CreateVertexShader(ID3D11Device *device, ID3DBlob *blob)を利用してください．
				*/
				std::shared_ptr<ID3D11VertexShader> CreateVertexShader(
					ID3D11Device *device,
					BYTE *shader,
					size_t size
					);

				/*!
				 @fn std::shared_ptr<ID3D11GeometryShader> CreateGeometryShader(
					ID3D11Device *device,
					BYTE *shader,
					size_t size
					);
				 @brief ジオメトリシェーダを作成する．
				 @param ID3D11Device *device,
				 @param BYTE *shader,
				 @param size_t size
				 @reutrn 作成されたジオメトリシェーダを指すスマートポインタ

				 @description ライブラリ内の関数向けの関数で通常ユーザが利用することは想定していません．
								DX11::D3D::shader::CreateGeometryShader(ID3D11Device *device, ID3DBlob *blob)を利用してください．
				*/
				std::shared_ptr<ID3D11GeometryShader> CreateGeometryShader(
					ID3D11Device *device,
					BYTE *shader,
					size_t size
					);
			}

			/*!
			 @fn std::shared_ptr<ID3DBlob> CompileShader(
				TCHAR source[],
				CHAR entryPoint[],
				CHAR target[]
				);
			 @brief 指定されたファイルのシェーダをコンパイルする．
			 @param TCHAR source[]
			 @param CHAR entryPoint[]
			 @param CHAR target[]
			 @return バッファー？

			 @description この関数はWindowsストアアプリの開発にのみ使用でき，Windowsストアに提出するアプリには利用できません．
							http://msdn.microsoft.com/ja-jp/library/windows/bg182880.aspx　を参照．
			*/
			std::shared_ptr<ID3DBlob> CompileShader(TCHAR source[], CHAR entryPoint[], CHAR target[]);
			
			/*!
			@fn std::shared_ptr<ID3D11GeometryShader> CreateGeometryShader(
				ID3D11Device *device,
				BYTE *shader,
				size_t size
				)
			@brief
			@param ID3D11Device *device
			@param BYTE *shader
			@param size_t size
			*/
			std::shared_ptr<ID3D11PixelShader> CreatePixelShader(ID3D11Device *device, ID3DBlob *blob);
			
			/*!
			@fn std::shared_ptr<ID3D11GeometryShader> CreateVertexShader(
				ID3D11Device *device,
				BYTE *shader,
				size_t size
			)
			@brief 頂点シェーダを作成する．
			@param ID3D11Device *device
			@param BYTE *shader
			@param size_t size
			*/
			std::shared_ptr<ID3D11VertexShader> CreateVertexShader(ID3D11Device *device, ID3DBlob *blob);
			
			/*!
			 @fn std::shared_ptr<ID3D11GeometryShader> CreateGeometryShader(
				ID3D11Device *device,
				BYTE *shader,
				size_t size
				)
			 @brief 頂点シェーダを作成する．
			 @param ID3D11Device *device
			 @param BYTE *shader
			 @param size_t size
			*/
			std::shared_ptr<ID3D11GeometryShader> CreateGeometryShader(ID3D11Device *device, ID3DBlob *blob);
			
			/*!
			 @fn std::shared_ptr<ID3D11InputLayout> CreateInputLayout(
				ID3D11Device *device,
				D3D11_INPUT_ELEMENT_DESC layoutDesc[],
				UINT numOfLayout,
				ID3DBlob *blob
				);
			 @brief 入力レイアウトオブジェクトを作成する．
			 @param ID3D11Device *device
			 @param D3D11_INPUT_ELEMENT_DESC layoutDesc[] 入力アセンブラステージの入力データ型の配列でる．各データ型は要素の記述によって示されます．
			 @param UINT numOfLayout 入力要素の配列内の入力データ型です．
			 @param ID3DBlob *blob バッファー？

			 @description 入力アセンブラーステージで使用される入力バッファーデータを記述するための入力レイアウトオブジェクトを作成します．
			*/
			std::shared_ptr<ID3D11InputLayout> CreateInputLayout(
				ID3D11Device *device,
				D3D11_INPUT_ELEMENT_DESC layoutDesc[],
				UINT numOfLayout,
				ID3DBlob *blob
				);
		}

		/*!	バッファに関する関数郡 */
		namespace buffer
		{
			/*! 補助関数群 */
			namespace detail
			{
				/*!
				@fn std::shared_ptr<ID3D11GeometryShader> CreateGeometryShader(
				ID3D11Device *device,
				BYTE *shader,
				size_t size
				)
				@brief DX11::D3D::buffer内の関数のための補助関数
				@param ID3D11Device *device
				@param ID3DBlob *blob
				*/
				std::shared_ptr<ID3D11Buffer> CreateBuffer(
					ID3D11Device *device,
					void *data,
					size_t size,
					UINT cpuAccessFlag,
					D3D11_BIND_FLAG BindFlag
					);
			}

			/*!
			@fn inline std::shared_ptr<ID3D11Buffer> CreateVertexBuffer(
			@param ID3D11Device *device,
			@param void *data,
			@param size_t size,
			@param UINT cpuAccessFlag = 0
			*/
			inline std::shared_ptr<ID3D11Buffer> CreateVertexBuffer(
				ID3D11Device *device,
				void *data,
				size_t size,
				UINT cpuAccessFlag = 0
				)
			{
				return detail::CreateBuffer(
					device,
					data,
					size,
					cpuAccessFlag,
					D3D11_BIND_VERTEX_BUFFER
					);
			}

			inline std::shared_ptr<ID3D11Buffer> CreateIndexBuffer(
				ID3D11Device *device,
				void *data,
				size_t size,
				UINT cpuAccessFlag = 0
				)
			{
				return detail::CreateBuffer(
					device,
					data,
					size,
					cpuAccessFlag,
					D3D11_BIND_INDEX_BUFFER);
			}

			inline std::shared_ptr<ID3D11Buffer> CreateConstantBuffer(
				ID3D11Device *device,
				void *data,
				size_t size,
				UINT cpuAccessFlag = 0
				)
			{
				return detail::CreateBuffer(
					device,
					data,
					size,
					cpuAccessFlag,
					D3D11_BIND_CONSTANT_BUFFER
					);
			}
		}

		/*!
		DirectX11のラッパ郡
		*/
		namespace detail
		{
			/*!
			DirectX11のラッパ郡
			*/
			namespace depth
			{
				std::shared_ptr<ID3D11Texture2D> CreateDepthBuffer(
					ID3D11Device *device,
					D3D11_TEXTURE2D_DESC descDS
					);

				D3D11_TEXTURE2D_DESC CreateDepthBufferDESC(IDXGISwapChain *swapChain);

				DXGI_FORMAT TextureFormat2DepthStencilViewFormat(DXGI_FORMAT format);
			}
			std::shared_ptr<ID3D11RenderTargetView> CreateRenderTargetView(IDXGISwapChain *swapChain);
			std::shared_ptr<ID3D11DepthStencilView> CreateDepthStencilView(IDXGISwapChain *swapChain);
		}

		std::shared_ptr<IDXGISwapChain> CreateSwapChain(
			DXGI_MODE_DESC *displayMode, HWND hWnd, ID3D11Device *device, bool useMultiSample
			);
		std::shared_ptr<ID3D11Texture2D> AccessBackBuffer(IDXGISwapChain *swapChain);
		std::shared_ptr<ID3D11Device> AccessD3Device(IDXGISwapChain *swapChain);
		std::shared_ptr<ID3D11DeviceContext> AccessD3Context(ID3D11Device *device);
		std::shared_ptr<ID3D11DeviceContext> AccessD3Context(IDXGISwapChain *swapChain);
	}
}