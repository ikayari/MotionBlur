/*!
 * @brief	�L�����N�^�R���g���[���[�B
 */

#pragma once

#include "CapsuleCollider.h"
#include "RigidBody.h"

namespace nsK2EngineLow {
	/*!
	* @brief	�L�����N�^�R���g���[���[�B
	*@details
	* �L�����N�^�[�Ɣw�i�̏Փˉ������s�����Ƃ��ł��܂��B\n
	* ���L�̃T���v���v���O�������Q�l�ɂ��Ă��������B\n
	* Sample/Sample07
	*/
	class CharacterController {
	public:
		CharacterController() {

		}
		~CharacterController()
		{
			RemoveRigidBoby();
		}
		/*!
			* @brief	�������B
			*@param[in]	radius		�J�v�Z���R���C�_�[�̔��a�B
			*@param[in]	height		�J�v�Z���R���C�_�[�̍����B
			*@param[in]	position	�����ʒu�B
			*/
		void Init(float radius, float height, const Vector3& position);
		/*!
			* @brief	�������B
			*@param[in]	size		�{�b�N�X�R���C�_�[�̃T�C�Y�B
			*@param[in]	position	�����ʒu�B
			*/
		void BoxInit(const Vector3& size, const Vector3& position, const float& restitution);
		/*!
			* @brief	���s�B
			*@param[in, out]	moveSpeed		�ړ����x�B
			*@param[in]	deltaTime		�o�ߎ��ԁB�P�ʂ͕b�B�f�t�H���g�ł́A�P�t���[���̌o�ߎ��Ԃ��n����Ă��܂��B
			*@return �ړ���̃L�����N�^�[�̍��W�B
			*/
		const Vector3& Execute(Vector3& moveSpeed, float deltaTime);
		/*!
			* @brief	���W���擾�B
			*/
		const Vector3& GetPosition() const
		{
			return m_position;
		}
		/*!
			* @brief	���W��ݒ�B
			*/
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}

		/*!
			* @brief	�W�����v��������
			*/
		bool IsJump() const
		{
			return m_isJump;
		}
		/*!
		* @brief	�n�ʏ�ɂ��邩����B
		*/
		bool IsOnGround() const
		{
			return m_isOnGround;
		}
		/*!
		* @brief	�R���C�_�[���擾�B
		*/
		CCapsuleCollider* GetCollider()
		{
			return &m_collider;
		}
		/*!
		* @brief	���̂��擾�B
		*/
		RigidBody* GetRigidBody()
		{
			return &m_rigidBody;
		}
		/*!
		* @brief	���̂𕨗��G���W������폜�B�B
		*/
		void RemoveRigidBoby();
	private:
		bool				m_isInited = false;				//!<�������ς݁H
		Vector3 			m_position;						//!<���W�B
		bool 				m_isJump = false;				//!<�W�����v���H
		bool				m_isOnGround = true;			//!<�n�ʂ̏�ɂ���H
		CCapsuleCollider	m_collider;						//!<�R���C�_�[�B
		BoxCollider			m_boxCollider;					//!<�{�b�N�X�R���C�_�[�B
		float				m_radius = 0.0f;				//!<�J�v�Z���R���C�_�[�̔��a�B
		float				m_height = 0.0f;				//!<�J�v�Z���R���C�_�[�̍����B
		float				m_boxheight = 0.0f;				//!<�{�b�N�X�R���C�_�[�̍����B
		float				m_restitution = 0.0f;			//!<�����́B
		Vector3				m_size = Vector3::Zero;			//!<�T�C�Y�B
		RigidBody			m_rigidBody;					//���́B
	};
}