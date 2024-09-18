/**
 * @file CCSDS.h
 * @brief CCSDS�ʐM���b�p�[�̃N���X�ł��B(AOBC�p �ʏ��荞��Ver)
 * 
 * CCSDS�ʐM���b�p�[�́A
 * CCSDS�̃C���^�[�t�F�[�X���������A
 * CCSDS�|�[�g�̏������A�f�[�^���M�A�f�[�^��M���s���A
 * CCSDS�ʐM���b�p�[�̃N���X�ł��B
 * �X�̋@��̃C���^�[�t�F�[�X���W���[���Ɍp��?�����Ďg�p���܂��B
 * @author ���� �@���Y
 * @date 2012.10.18
 */

#ifndef CCSDS_INCLUDE_
#define CCSDS_INCLUDE_


/**
 * @class CCSDS_CONFIG_STRUCT
 * @brief CCSDS�|�[�g�̏������A�f�[�^���M�A�f�[�^��M�̍ۂɕK�v�ƂȂ�ݒ�����i�[����\���̂ł��B
 */
typedef	struct {
		unsigned char	onoff;	/**< @protected @brief CCSDS�o�͂�ON/OFF(0:OFF 1:ON)*/
		unsigned int	bitrate;	/**< @protected @brief �p����̋@��̃r�b�g���[�g�l(�L��)*/
}	CCSDS_CONFIG_STRUCT;


		int				CCSDS_init(void *my_ccsds_v);
		int				CCSDS_RX(void *my_ccsds_v, void *data_v, int count);
		int				CCSDS_TX(void *my_ccsds_v, void *data_v, int count);

#endif // CCSDS_INCLUDE_
