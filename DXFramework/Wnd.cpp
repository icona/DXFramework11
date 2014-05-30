/*!
@file Wnd.cpp
@brief Windows�v���O���~���O�ɂ�����E�B���h�E�֘A����舵���Ă��܂��D<br>
		�E�B���h�E�v���V�[�W����Wnd�N���X�̎������܂܂�Ă��܂��D<br>
		�e�X�g�p�ɍ쐬���Ă��邾���őS�ʓI�ɔp�~�E���P�\��ł��D
@author icona<br>
<https://twitter.com/iconaHimeno><br>
<icona@outlook.jp>
@date 14/05/09
*/

#include "Wnd.h"


namespace WndStuff{
	namespace{
		/*!
		�E�B���h�E�v���V�[�W��
		@param hWnd �E�B���h�E�n���h��
		@param message ���b�Z�[�W�R�[�h
		@param wParam ���b�Z�[�W�Ɋւ���ǉ����
		@param lParam ���b�Z�[�W�Ɋւ���ǉ����
		*/
		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			case WM_CLOSE:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			return 0;
		}

		/*!
		�E�B���h�E�̏������E�������s���D
		@param classname �E�B���h�E�N���X��
		@param hIcon = nullptr �A�C�R���̃n���h��(�f�t�H���g��nullptr)
		@param hCursor = nullptr �J�[�\���̃n���h��(�f�t�H���g��nullptr)
		@return �E�B���h�E�����̐���
		*/
		ATOM MyRegisterClass(Utl::tstring classname, HICON hIcon = nullptr, HCURSOR hCursor = nullptr)
		{
			WNDCLASSEX wcex;

			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = GetModuleHandle(NULL);
			wcex.hIcon = hIcon;
			wcex.hCursor = hCursor;
			wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName = NULL;
			wcex.lpszClassName = classname.c_str();
			wcex.hIconSm = nullptr;

			return RegisterClassEx(&wcex);
		}
	}

	Wnd::Wnd(const Utl::tstring& classname, const Utl::tstring& title, const RECT& rc)
	{
		InitWnd(classname, title, rc);
		renderTarget = DX11::D2D::init::CreateRenderTarget(hWnd);
	}

	Wnd::~Wnd()
	{

	}

	bool Wnd::InitWnd(const Utl::tstring& classname, const Utl::tstring& title, RECT rc)
	{
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		MyRegisterClass(classname);

		hWnd = CreateWindow(
			classname.c_str(), title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			(rc.right - rc.left), (rc.bottom - rc.top),
			NULL,
			NULL,
			GetModuleHandle(NULL),
			NULL
			);

		if (!hWnd)
		{
			return FALSE;
		}

		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);

		return true;
	}

}
