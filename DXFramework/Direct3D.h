#pragma once

#include "directX.h"
#include <memory>

/*! DirectX11�̃��b�p�S */
namespace DX11
{
	/*! DirectX3D�̃��b�p�S */
	namespace D3D{

		/*! �������Ɋւ��郉�b�p�S */
		namespace init{
			/*!
			 @fn std::shared_ptr<ID3D11Device> CreateD3Device()
			 @brief �f�B�X�v���C�A�_�v�^�[��\���f�o�C�X���쐬����D
			 @return �쐬���ꂽ�f�o�C�X���w���X�}�[�g�|�C���^

			 @description �@�\���x�����ō��̂��̂��珇�Ɏ����C�쐬�����f�o�C�X���w���X�}�[�g�|�C���^��Ԃ��D
							�p����h���C�o�[�^�C�v��D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_SOFTWARE
							�̂S�D�֗��֐��̈��ŁCD3D11CreateDevice��p���ăf�o�C�X���쐬����ꍇ�ɔ�ׂāC�ώG�ȏ������ȗ����邱�Ƃ��ł��܂��D
			*/
			std::shared_ptr<ID3D11Device> CreateD3Device();
		}

		/*! �e��R���e�L�X�g�̊ȈՏ����ݒ�֐��Q */
		namespace context
		{
			/*!
			 @fn void SetDefaultRenderTarget(IDXGISwapChain *swapChain)
			 @brief ���\�[�X�f�[�^�ւ̃A�N�Z�X�p�Ƀ����_�[�Q�b�g�r���[���쐬���C�o�͌����X�e�[�W�Ƀo�C���h����D
			 @param IDXGISwapChain *swapChain
			 
			 @description ���\�[�X�f�[�^�ւ̃A�N�Z�X�p�Ƀ����_�[�Q�b�g�r���[���쐬���C�o�͌����X�e�[�W�Ƀo�C���h���܂��D
			*/
			void SetDefaultRenderTarget(IDXGISwapChain *swapChain);

			/*!
			 @fn void SetDefaultViewport(IDXGISwapChain *swapChain)
			 @brief �p�C�v���C���̃��X�^���C�U�X�e�[�W�ɊȈՓI�ȃr���[�|�[�g���o�C���h���܂��D
			 @param IDXGISwapChain *swapChain

			 @description �֗��֐��̈��ŁC��ʓI�ȃr���[�|�[�g�̃o�C���h�������ȗ������邱�Ƃ��ł��܂��D
							�r���[�|�[�g�𕡐��o�C���h����ꍇ�C����ȃr���[�|�[�g��ݒ肷��ꍇ�͎g�p�ł��܂���D
			*/
			void SetDefaultViewport(IDXGISwapChain *swapChain);

			/*!
			 @fn void SetDefaultRasterize(IDXGISwapChain *swapChain)
			 @brief �ȈՂȃ��X�^���C�U�X�e�[�g�I�u�W�F�N�g���쐬����D
			 @param IDXGISwapChain *swapChain

			 @description �֗��֐��̈��ŁC��ʓI�ȃ��X�^���C�U�X�e�[�g�I�u�W�F�N�g�̍쐬���ȗ������邱�Ƃ��ł��܂��D
							�ڍׂȐݒ肪�K�v�ȏꍇ�͗��p�ł��܂���D�쐬����郉�X�^���C�U�̐ݒ�͈ȉ��̃\�[�X�R�[�h��
							�Q�Ƃ��Ă��������D
			*/
			void SetDefaultRasterize(IDXGISwapChain *swapChain);
		}

		/*!	�V�F�[�_�̃��b�p�S	*/
		namespace shader
		{
			/*! DX11::D3D::shader���̊֐��Q�̂��߂̕⏕�֐� */
			namespace detail
			{
				/*!
				 @fn template<typename S> std::shared_ptr<S> CreateShader(
					ID3D11Device *device,
					BYTE *shader,
					size_t size,
					HRESULT(__stdcall ID3D11Device::*func)(const void *, SIZE_T, ID3D11ClassLinkage *, S **)
					);
				@brief �n���ꂽ�֐������ɃV�F�[�_���쐬����D����Create~Shadar�̂��߂̃e���v���[�g�ł��D
				@param ID3D11Device *device
				@param BYTE *shader
				@param size_t size
				@param HRESULT(__stdcall ID3D11Device::*func)(const void *, SIZE_T, ID3D11ClassLinkage *, S **)
				@return �쐬���ꂽ�V�F�[�_���w���X�}�[�g�|�C���^

				@description ���C�u�������̊֐������̊֐��Œʏ탆�[�U�����p���邱�Ƃ͑z�肵�Ă��܂���D
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
				@brief �s�N�Z���V�F�[�_���쐬����D
				@param ID3D11Device *device
				@param BYTE *shader
				@param size_t size
				@return �쐬���ꂽ�s�N�Z���V�F�[�_���w���X�}�[�g�|�C���^

				@description ���C�u�������̊֐������̊֐��Œʏ탆�[�U�����p���邱�Ƃ͑z�肵�Ă��܂���D
							DX11::D3D::shader::CreatePixelShader(ID3D11Device *device, ID3DBlob *blob)�𗘗p���Ă��������D
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
				 @brief ���_�V�F�[�_���쐬����D
				 @param ID3D11Device *device
				 @param BYTE *shader
				 @param size_t size
				 @return �쐬���ꂽ���_�V�F�[�_���w���X�}�[�g�|�C���^

				 @description ���C�u�������̊֐������̊֐��Œʏ탆�[�U�����p���邱�Ƃ͑z�肵�Ă��܂���D
								DX11::D3D::shader::CreateVertexShader(ID3D11Device *device, ID3DBlob *blob)�𗘗p���Ă��������D
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
				 @brief �W�I���g���V�F�[�_���쐬����D
				 @param ID3D11Device *device,
				 @param BYTE *shader,
				 @param size_t size
				 @reutrn �쐬���ꂽ�W�I���g���V�F�[�_���w���X�}�[�g�|�C���^

				 @description ���C�u�������̊֐������̊֐��Œʏ탆�[�U�����p���邱�Ƃ͑z�肵�Ă��܂���D
								DX11::D3D::shader::CreateGeometryShader(ID3D11Device *device, ID3DBlob *blob)�𗘗p���Ă��������D
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
			 @brief �w�肳�ꂽ�t�@�C���̃V�F�[�_���R���p�C������D
			 @param TCHAR source[]
			 @param CHAR entryPoint[]
			 @param CHAR target[]
			 @return �o�b�t�@�[�H

			 @description ���̊֐���Windows�X�g�A�A�v���̊J���ɂ̂ݎg�p�ł��CWindows�X�g�A�ɒ�o����A�v���ɂ͗��p�ł��܂���D
							http://msdn.microsoft.com/ja-jp/library/windows/bg182880.aspx�@���Q�ƁD
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
			@brief ���_�V�F�[�_���쐬����D
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
			 @brief ���_�V�F�[�_���쐬����D
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
			 @brief ���̓��C�A�E�g�I�u�W�F�N�g���쐬����D
			 @param ID3D11Device *device
			 @param D3D11_INPUT_ELEMENT_DESC layoutDesc[] ���̓A�Z���u���X�e�[�W�̓��̓f�[�^�^�̔z��ł�D�e�f�[�^�^�͗v�f�̋L�q�ɂ���Ď�����܂��D
			 @param UINT numOfLayout ���͗v�f�̔z����̓��̓f�[�^�^�ł��D
			 @param ID3DBlob *blob �o�b�t�@�[�H

			 @description ���̓A�Z���u���[�X�e�[�W�Ŏg�p�������̓o�b�t�@�[�f�[�^���L�q���邽�߂̓��̓��C�A�E�g�I�u�W�F�N�g���쐬���܂��D
			*/
			std::shared_ptr<ID3D11InputLayout> CreateInputLayout(
				ID3D11Device *device,
				D3D11_INPUT_ELEMENT_DESC layoutDesc[],
				UINT numOfLayout,
				ID3DBlob *blob
				);
		}

		/*!	�o�b�t�@�Ɋւ���֐��S */
		namespace buffer
		{
			/*! �⏕�֐��Q */
			namespace detail
			{
				/*!
				@fn std::shared_ptr<ID3D11GeometryShader> CreateGeometryShader(
				ID3D11Device *device,
				BYTE *shader,
				size_t size
				)
				@brief DX11::D3D::buffer���̊֐��̂��߂̕⏕�֐�
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
		DirectX11�̃��b�p�S
		*/
		namespace detail
		{
			/*!
			DirectX11�̃��b�p�S
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