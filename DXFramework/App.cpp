#include "App.h"

/*!
@file App.cpp
@brief App�N���X�̎���
@author icona<br>
<https://twitter.com/iconaHimeno><br>
<icona@outlook.jp>
@date 14/05/09
*/

namespace DxFramework
{
	App::App(Utl::tstring title, RECT rc) :
		wnd( new WndStuff::Wnd(title, title, rc) )
		// ���������X�g�ŗ�O�����������App�̃f�X�g���N�^�͌Ă΂�܂���D
	{
	}

	
	App::~App()
	{
	}
}