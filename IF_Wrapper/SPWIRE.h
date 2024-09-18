/**
 * @file SPWIRE.h
 * @brief SPWIRE(�X�y�[�X���C��)�ʐM���b�p�[�̃N���X�ł��B
 * 
 * SPWIRE(�X�y�[�X���C��)�ʐM���b�p�[�́A
 * SPWIRE�̃C���^�[�t�F�[�X���������A
 * SPWIRE�|�[�g�̏������A�f�[�^���M�A�f�[�^��M���s���A
 * SPWIRE�ʐM���b�p�[�̃N���X�ł��B
 * �X�̋@��̃C���^�[�t�F�[�X���W���[���Ɍp��?�����Ďg�p���܂��B
 * @note SPWIRE(�X�y�[�X���C��)�̃��[�e�B���O�͕����l�����܂����A
 * ����͐ڑ�����@�킪SOBC(EM)��CPU�{�[�h(J111�`J114�|�[�g)���m�Őڑ������ꍇ�̌o�H�ɂ̂ݑΉ����Ă��܂��B
 * �܂��A�f�[�^�̂��Ƃ��CPU�{�[�h��̃������}�b�v��ɂ̂݌��肳��Ă��܂�(�f�B�X�e�B�l�[�V�����L�[�Œ�:0x24)�B
 * @warning J111,J112�|�[�g��IF�{�[�h������API�Ŏg�p����Ă����肷��̂ŁA�Ȃ�ׂ�����o���Ȃ������ǂ��B
 * �܂��A����J111�|�[�g�ɂ�IF�{�[�h���ڑ�����Ă���͂��Ȃ̂ŁA���̐ݒ�Ŗ{�N���X���g�p���Ȃ��͂��B
 * @author ���� �@���Y
 * @date 2013.04.19
 */

#ifndef SPWIRE_INCLUDE_
#define SPWIRE_INCLUDE_


/**
 * @class SPWIRE_CONFIG_STRUCT
 * @brief SPWIRE�|�[�g�̏������A�f�[�^���M�A�f�[�^��M�̍ۂɕK�v�ƂȂ�ݒ�����i�[����\���̂ł��B
 */
typedef	struct {
		unsigned char	own_port;		/**< @protected @brief �p����̋@��ւȂ����Ă������g�̃|�[�g�ԍ��̉�1��*/
		unsigned char	target_port;	/**< @protected @brief �p����̋@��̂Ȃ����Ă���|�[�g�ԍ��̉�1��*/
		unsigned int	reg_addr;		/**< @protected @brief �p����̋@��̓ǂݏ������s�����W�X�^�A�h���X(�Ȃ�ׂ�4�̔{���A�h���X���w��)*/
}	SPWIRE_CONFIG_STRUCT;


int SPWIRE_init(void *my_spwire_v);
int SPWIRE_RX(void *my_spwire_v, void *data_v, int count);
int SPWIRE_TX(void *my_spwire_v, void *data_v, int count);

#endif // SPWIRE_INCLUDE_
