/*!
@file Singleton.h
@brief �C���X�^���X�̗B�ꐫ��ۏ؂�����N���X�̃e���v���[�gSingleton���`���Ă��܂��D
@author icona<br>
<https://twitter.com/iconaHimeno><br>
<icona@outlook.jp>
@date 14/05/21
*/

#pragma once

/*! �ėp�I�ȃN���X��֐��C�e���v���[�g�Ȃǂ��܂ޖ��O��� */
namespace Utl
{
	
	template<typename T>
	/*! �C���X�^���X�̗B�ꐫ��ۏ؂�����N���X�̃e���v���[�g */
	class Singleton
	{
	protected:
		/*! �O������̐����̋֎~ */
		Singleton(){};
		virtual ~Singleton(){};

	public:
		/*!
			�C���X�^���X���Ƃ��̎Q�Ƃ̎擾�D
			@return �C���X�^���X�̎Q��
		*/
		static T& getInstance()
		{
			static T instance;
			return instance;
		}
	};
}
