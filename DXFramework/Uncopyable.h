/*!
 \file Uncopyable.h
 \brief �R�s�[�Ƒ�����֎~������N���XUncopyable���`���Ă��܂��D<br>
		Effective C++ ��O��, Scott Meyers, p32-p33�ɋL�ڂ���Ă���R�[�h�ł�.
 \author icona<br>
		 <https://twitter.com/iconaHimeno><br>
		 <icona@outlook.jp>
 \date 14/05/09
*/

#pragma once

//! �ėp�I�ȃN���X��֐��C�e���v���[�g�Ȃǂ��܂ޖ��O���
namespace Utl
{
	/*!
	 �R�s�[�Ƒ�����֎~������N���X�D
	 private�p�����ėp����D
	*/
	class Uncopyable
	{
	protected:
		/*! �����Ɣj���̋��� */
		Uncopyable(){}
		~Uncopyable(){}

	private:
		/*! �R�s�[(�R���X�g���N�^)�̋֎~ */
		Uncopyable(const Uncopyable&);

		/*! ����̋֎~ */
		Uncopyable& operator=(const Uncopyable&);
	};
}
