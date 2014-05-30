/*!
 @file Wnd.h
 @brief Windows�v���O���~���O�ɂ�����E�B���h�E�֘A����舵���Ă��܂��D
 @author icona<br>
		 <https://twitter.com/iconaHimeno><br>
		 <icona@outlook.jp>
 @date 14/05/09
*/

#pragma once

#include "tstring.h"
#include "ScreenResolution.h"
#include "Direct2D.h"
#include "Direct3D.h"

/*! �E�B���h�E�Ɋւ���N���X�E�֐��Q���܂ޖ��O��� */
namespace WndStuff
{
	/*! �E�B���h�E�̐����E�Ǘ����s���N���X */
	class Wnd
	{
	private: /* �v���p�e�B */
		HWND hWnd;
		std::shared_ptr <ID2D1HwndRenderTarget> renderTarget;

	public: /* �R���X�g���N�^�E�f�X�g���N�^ */
		/*!
		 �R���X�g���N�^�D
		 @param classname �E�B���h�E�N���X��
		 @param title �E�B���h�E��
		 @param rc = Utl::ScrRes::VGA �E�B���h�E�T�C�Y(�f�t�H���g��VGA)
		 */
		Wnd(const Utl::tstring& classname, const Utl::tstring& title, const RECT& rc = Utl::ScrRes::VGA);
		~Wnd();

	public: /* �A�N�Z�T */
		/*!
		 �A�N�Z�T�D
		 @return �E�B���h�E�n���h��
		 */
		HWND getHWND() const
		{
			return hWnd;
		};

		/*!
		�A�N�Z�T�D
		@return �����_�����O�^�[�Q�b�g�T�[�t�F�C�X
		*/
		std::shared_ptr <ID2D1HwndRenderTarget> getRenderTarget() const
		{
			return renderTarget;
		};

	public: /* ���� */
		/*!
		�E�B���h�E�̏������E�������s���D
		@param classname �E�B���h�E�N���X��
		@param title �E�B���h�E��
		@param rc �E�B���h�E�T�C�Y(�f�t�H���g��VGA)
		@return �E�B���h�E�����̐���
		*/
		bool InitWnd(const Utl::tstring& classname, const Utl::tstring& title, RECT rc);

	};
}