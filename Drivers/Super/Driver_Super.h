/**
 * @file Driver_Super.h
 * @brief �e����Z���T�E�A�N�`���G�[�^���Ƃ̃C���^�[�t�F�[�X���W���[���Q�̃X�[�p�[�N���X�ł��B
 * 
 * Driver_Super�C���^�[�t�F�[�X���W���[���́A
 * �e����Z���T�E�A�N�`���G�[�^���Ƃ̃C���^�[�t�F�[�X���������A
 * �������A�f�[�^���N�G�X�g(���)�A�f�[�^�擾(���)�A�����ݒ�R�}���h�E���X�|���X��M���s���A
 * ���W���[���Q�̃X�[�p�[�N���X�ł��B
 * �X�̋@��̃C���^�[�t�F�[�X���W���[���Ɍp��?�����Ďg�p���܂��B
 * @date 2013.06.29
 */

#ifndef	DRIVER_SUPER_INCLUDE_
#define	DRIVER_SUPER_INCLUDE_


#include "../../IF_Wrapper/IF_list.h"


#define	DRIVER_SUPER_RX_BUFFER_SIZE_MAX	512	/**< @brief ��M�f�[�^�o�b�t�@�̍ő咷*/
#define	DRIVER_SUPER_RX_FRAME_SIZE_MAX	512	/**< @brief ��M�f�[�^�t���[���̍ő咷*/


/**
 * @brief �R�}���h���s�E�f�[�^��M�̍ۂɕK�v�ƂȂ�ݒ�����i�[����\���̂ł��B
 * 
 * DRIVER_SUPER�\���̓��ɂ����āA���/�������ꂼ��ɂ����Ē�`���Ă��܂��B
 * @warning rx_frame_size����(��M�f�[�^���ϒ��̏ꍇ) ���� rx_framelength_place��0(�t���[���T�C�Y�f�[�^���Ȃ��ꍇ)�ɂ����āA�w�b�_,�t�b�^��0�Ƃ������Ƃ͋�����܂���B
 */
typedef	struct {
	//�y�p����܂Ō��J�z
		/** @name �R�}���h���s�ݒ�*/
		/** @{*/
		unsigned char	*tx_frame;		/**< @protected @brief ���M�f�[�^�t���[��*/
		int				tx_frame_size;	/**< @protected @brief ���M�f�[�^�T�C�Y
										 * 
										 * ���M�f�[�^���Ȃ��ꍇ��0�ɐݒ肵�܂��B
										 */
		/** @}*/
		
		/** @name �f�[�^��M�ݒ�*/
		/** @{*/
		unsigned char	*rx_header;		/**< @protected @brief ��M�f�[�^�̃w�b�_*/
		int				rx_header_size;	/**< @protected @brief ��M�f�[�^�̃w�b�_�T�C�Y
										 * 
										 * �w�b�_���Ȃ��ꍇ��0�ɐݒ肵�܂�(���̏ꍇ�ɂ�rx_frame_size����(��M�f�[�^���ϒ�)�͋�����܂���)�B
										 */
		unsigned char	*rx_footer;		/**< @protected  @brief ��M�f�[�^�̃t�b�^*/
		int				rx_footer_size;	/**< @protected @brief ��M�f�[�^�̃t�b�^�T�C�Y
										 * 
										 * �t�b�^���Ȃ��ꍇ��0�ɐݒ肵�܂�(���̏ꍇ�ɂ�rx_frame_size����(��M�f�[�^���ϒ�)�͋�����܂���)�B
										 */
		int				rx_frame_size;	/**< @protected @brief ��M�f�[�^�t���[���T�C�Y
										 * 
										 * ��M�f�[�^���ϒ��̏ꍇ�͕��̒l�ɐݒ肵�܂��B
										 * �܂��A��M�f�[�^���Ȃ��ꍇ��0�ɐݒ肵�܂��B
										 */
		unsigned char	rx_framelength_place;	/**< @protected @brief ��M�f�[�^���̃t���[���T�C�Y�f�[�^�̑��݂���ꏊ(�擪(1�o�C�g)���琔���ĉ��o�C�g�ڂɈʒu���邩)
												 * 
												 * ��M�f�[�^���ϒ��̏ꍇ�ɂ̂ݎg�p�����ݒ�l�ł���܂��B
												 * �t���[���T�C�Y�f�[�^�̑��݂���ꏊ(�擪(1�o�C�g)���琔���ĉ��o�C�g�ڂɈʒu���邩)���w�肵�܂��B
												 * �t���[���T�C�Y�f�[�^���Ȃ��ꍇ�ɂ�0�ɐݒ肵�܂�(���̏ꍇ�ɂ�rx_header_size��rx_footer_size��0�Ƃ������Ƃ͋�����܂���)�B
												 */
		unsigned char	rx_framelength_offset;	/**< @protected @brief ��M�f�[�^���̃t���[���T�C�Y�f�[�^�ւ̃I�t�Z�b�g�l
												 * 
												 * ��M�f�[�^���ϒ��̏ꍇ�ɂ̂ݎg�p�����ݒ�l�ł���܂��B
												 * �t���[���T�C�Y�f�[�^�ɂ��ϒ��f�[�^�̉�͂́u�t���[���̑S�T�C�Y�v�ɂ��s���܂����A
												 * �@��̒��ɂ̓w�b�_�ƃt�b�^�̕��͏������f�[�^���Ƃ��ĕ\������Ă���ꍇ������܂��B
												 * ���̂悤�ȏꍇ�ɂ��̕ϐ��ɑ΂��āA������Ă���f�[�^������ݒ肵�Ă�邱�ƂŁA��M�����t���[���T�C�Y�f�[�^�ɑ΂��ĉ��Z����A����ɉ�͂��邱�Ƃ��ł��܂��B
												 * �t���[���T�C�Y�f�[�^���u�t���[���̑S�T�C�Y�v�������Ă���ꍇ�ɂ�0�ɐݒ肵�܂��B
												 */
		/** @}*/
		
		
	//�y����J�z
		int				rx_frame_count;	/**< @private @brief ��M�f�[�^�t���[���J�E���^*/
		int				rx_except_footer_size;	/**< @private @brief �t�b�^����������M�t���[���f�[�^�T�C�Y*/
		int				rx_frame_size_v;	/**< @private @brief �ϒ��̏ꍇ�̎�M�f�[�^�t���[���T�C�Y( DRIVER_SUPER_Analyze_variable() �ł̂ݎg�p)*/
		int 			rx_footer_flag;	/**< @private @brief �t�b�^�����t���O�J�E���^( DRIVER_SUPER_Analyze_variable_not_fsd() �ł̂ݎg�p)*/
}	DRIVER_SUPER_CONFIG_STRUCT;


/**
 * @class DRIVER_SUPER_STRUCT
 * @brief �e�@��S�Ăŋ��ʂɕK�v�ƂȂ�����i�[����\���̂ł��B
 * 
 * DRIVER_SUPER�\���̂́A�e�Z���T��1�̃O���[�p���C���X�^���X�̒��Ɋ܂܂��Ē�`���܂��B
 *  Driver_Super_init() �ɂ�菉�������Ă���g�p���܂��B
 */
typedef	struct {
	//�y�S�ĂɌ��J�z
		int				tx_count;	/**< @public @brief ����f�[�^���N�G�X�g���M��*/
		int				rx_count;	/**< @public @brief ����f�[�^�p�P�b�g��M��*/
		int				update_flg;	/**< @public @brief ��������������Ȃ������f�[�^���N�G�X�g���M�̉�
									 * 
									 * 0�ȊO�̏ꍇ�f�[�^�͍ŐV�łȂ��댯��������܂��B
									 * ���̐��l��3�ł���ꍇ�A���݂̃f�[�^��3��������̊ԍX�V����Ă��܂���B
									 */
		unsigned long	cmd_time;	/**< @public @brief ����f�[�^���N�G�X�g�𑗐M��������(msec)*/
		unsigned long	update_time;	/**< @public @brief ����f�[�^�p�P�b�g����M��������(msec)*/
		
		
	//�y�p����܂Ō��J�z
		/** @name �n�[�h�̐ݒ�*/
		/** @{*/
		IF_LIST_ENUM	inter_face;	/**< @protected @brief �p����̋@��̎g�pIF*/
		/** @}*/
		
		/** @name ����R�}���h���s�E�f�[�^��M�֌W*/
		/** @{*/
		DRIVER_SUPER_CONFIG_STRUCT	periodic_config;	/**< @protected @brief ����֌W�̐ݒ�f�[�^�\����*/
		unsigned char		periodic_rx_frame[DRIVER_SUPER_RX_FRAME_SIZE_MAX];	/**< @protected @brief �����M�f�[�^*/
		/** @}*/
		
		/** @name �����R�}���h���s�E�f�[�^��M�֌W*/
		/** @{*/
		DRIVER_SUPER_CONFIG_STRUCT	non_periodic_config;	/**< @protected @brief �����֌W�̐ݒ�f�[�^�\����*/
		unsigned char		non_periodic_rx_frame[DRIVER_SUPER_RX_FRAME_SIZE_MAX];	/**< @protected @brief ������M�f�[�^*/
		/** @}*/
		
		
	//�y����J�z
		unsigned char	rx_buffer[DRIVER_SUPER_RX_BUFFER_SIZE_MAX];	/**< @private @brief �f�[�^��M�o�b�t�@*/
}	DRIVER_SUPER_STRUCT;


int DRIVER_Super_init(DRIVER_SUPER_STRUCT *my_super, void *if_config);
int DRIVER_Super_cycle(DRIVER_SUPER_STRUCT *my_super, void *if_config);
int DRIVER_Super_rec(DRIVER_SUPER_STRUCT *my_super, void *if_config);
int DRIVER_Super_conf(DRIVER_SUPER_STRUCT *my_super, void *if_config);
int DRIVER_Super_debug_message(DRIVER_SUPER_STRUCT *my_super);

#endif // DRIVER_SUPER_INCLUDE_
