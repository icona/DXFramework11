#pragma once

#include "directX.h"
#include <memory>

/*!
 DirectX11�̃��b�p�S
*/
namespace DX11
{
	/*! Direct2D�Ɋւ��郉�b�p�S */
	namespace D2D
	{
		/*! �������Ɋւ��郉�b�p�S */
		namespace init{
			/*!
			 @fn std::shared_ptr<ID2D1Device> CreateD2Device(ID3D11Device *device)
			 @brief �^����ꂽID3D11����V����Direct2D�f�o�C�X���쐬����D
			 @param ID3D11Device *device
			 @return �쐬���ꂽDirect2D�f�o�C�X���w���X�}�[�g�|�C���^���Ԃ�܂��D
			*/
			std::shared_ptr<ID2D1Device> CreateD2Device(ID3D11Device *device);
			
			/*!
			 @fn std::shared_ptr<ID2D1HwndRenderTarget> CreateRenderTarget(HWND hWnd)
			 @brief �^����ꂽ�E�B���h�E�n���h�����w���E�B���h�E��ΏۂƂ����C
				�����_�����O�^�[�Q�b�g�T�[�t�F�C�X���쐬����D
			 @param ID3D11Device *device
			 @return �쐬���ꂽ�����_�����O�^�[�Q�b�g�T�[�t�F�C�X���w���X�}�[�g�|�C���^��Ԃ��܂��D
			*/
			std::shared_ptr<ID2D1HwndRenderTarget> CreateRenderTarget(HWND hWnd);
		};

		/*! �`��Ɋւ��郉�b�p�S */
		namespace drawer
		{
			/*!
			 @fn std::shared_ptr<ID2D1SolidColorBrush> CreateBrush(D2D1::ColorF color, ID2D1RenderTarget *renderTarget)
			 @brief �^����ꂽ�����_�����O�^�[�Q�b�g�T�[�t�F�C�X�̎w�肳�ꂽ�F�̘_���u���V���쐬����D
			 @param D2D1::ColorF color
			 @param ID2D1RenderTarget *renderTarget
			 @return �쐬���ꂽ�_���u���V���w���X�}�[�g�|�C���^
			*/
			std::shared_ptr<ID2D1SolidColorBrush> CreateBrush(D2D1::ColorF color, ID2D1RenderTarget *renderTarget);

			/*!
			 @fn std::shared_ptr<ID2D1BitmapBrush> CreateBitmapBrush(ID2D1Bitmap *bitmap, ID2D1RenderTarget *target);
			 @brief �^����ꂽ�����_�����O�^�[�Q�b�g�T�[�t�F�C�X�̎w�肳�ꂽ�r�b�g�}�b�v�̃u���V���쐬����D
			 @param ID2D1Bitmap *bitmap
			 @param ID2D1RenderTarget *target
			 @return �쐬���ꂽ�r�b�g�}�b�v�u���V���w���X�}�[�g�|�C���^
			*/
			std::shared_ptr<ID2D1BitmapBrush> CreateBitmapBrush(ID2D1Bitmap *bitmap, ID2D1RenderTarget *target);

			/*!
			 @fn std::shared_ptr<ID2D1BitmapBrush> CreateBitmapBrush(const TCHAR *path, ID2D1RenderTarget *target)
			 @brief �^����ꂽ�����_�����O�^�[�Q�b�g�T�[�t�F�C�X�̎w�肳�ꂽ�p�X�̃r�b�g�}�b�v�̃u���V���쐬����D
			 @param const TCHAR *path
			 @param ID2D1RenderTarget *target
			 @return �쐬���ꂽ�r�b�g�}�b�v�u���V���w���X�}�[�g�|�C���^��Ԃ��D
			*/
			std::shared_ptr<ID2D1BitmapBrush> CreateBitmapBrush(const TCHAR *path, ID2D1RenderTarget *target);
		};

		/*!
		 @fn std::shared_ptr<ID2D1Factory1> AccessD2Factory()
		 @brief Direct2D�̃��\�[�X�̍쐬�Ɏg�p�ł���t�@�N�g���I�u�W�F�N�g���쐬����D
		 @return �쐬�����t�@�N�g���I�u�W�F�N�g���w���X�}�[�g�|�C���^��Ԃ��D
		*/
		std::shared_ptr<ID2D1Factory1> AccessD2Factory();

		/*!
		 @fn std::shared_ptr<ID2D1DeviceContext> AccessD2Context(ID2D1Device *device2d)
	 	 @brief �w�肳�ꂽ�f�o�C�X�̃R���e�L�X�g���쐬����D
		 @param ID2D1Device *device2d
		 @return �쐬�����f�o�C�X�R���e�L�X�g���w���X�}�[�g�|�C���^��Ԃ��D

		 @description �ڍׂȉ�������߂��Ă��܂��iTODO�j�D
		*/
		std::shared_ptr<ID2D1DeviceContext> AccessD2Context(ID2D1Device *device2d);

		/*!
		 @fn std::shared_ptr<ID2D1Bitmap> AccessBitmap(ID3D11Texture2D *tex, ID2D1DeviceContext *deviceContext2d)
		 @brief ID3D11Texture2D�̃T�[�t�F�C�X������Bitmap���쐬����D
		 @param ID3D11Texture2D *tex
		 @param ID2D1DeviceContext *deviceContext2d
		 @return �쐬���ꂽBitmap���w���X�}�[�g�|�C���^��Ԃ��D

		 @description ���̊֐��́CDX11::D3D::AccessBackBuffer(IDXGISwapChain *swapChain)�Ƒg�ݍ��킹�ėp����D
			D3D11CreateDeviceAndSwapChain�Ȃǂɂ���Đ������ꂽDirect3D�p��swapchain�̃o�b�N�o�b�t�@��AccessBackBuffer�ŃA�N�Z�X���C����ꂽ
			ID3D11Texture2D�̃T�[�t�F�C�X������Bitmap���쐬����D
		*/
		std::shared_ptr<ID2D1Bitmap> AccessBitmap(ID3D11Texture2D *tex, ID2D1DeviceContext *deviceContext2d);

		/*!
		 @fn std::shared_ptr<ID2D1Bitmap> CreateBitmap(const TCHAR *path, ID2D1RenderTarget *target)
		 @brief �w�肳�ꂽ�����_�����O�^�[�Q�b�g�Ɏw�肳�ꂽ�p�X�̉摜��Bitmap���쐬����D
		 @param const TCHAR *path
		 @param ID2D1RenderTarget *target
		 @return �쐬���ꂽBitmap���w���X�}�[�g�|�C���^��Ԃ��D
		*/
		std::shared_ptr<ID2D1Bitmap> CreateBitmap(const TCHAR *path, ID2D1RenderTarget *target);

	}
}