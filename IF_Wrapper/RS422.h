/**
 * @file RS422.h
 * @brief RS422(UART)�ʐM���b�p�[�̃N���X�ł��B(AOBC�p)
 * 
 * RS422(UART)�ʐM���b�p�[�́A
 * RS422�̃C���^�[�t�F�[�X���������A
 * RS422�|�[�g�̏������A�f�[�^���M�A�f�[�^��M���s���A
 * RS422�ʐM���b�p�[�̃N���X�ł��B
 * �X�̋@��̃C���^�[�t�F�[�X���W���[���Ɍp��?�����Ďg�p���܂��B
 * @note RS422(UART)�̃`�����l����ch0�`21����A����͂��̂���ch0�`16�̌v16ch���O���֏o�Ă��܂��B
 * @author ���� �@���Y
 * @date 2013.03.13
 */

#ifndef RS422_INCLUDE_
#define RS422_INCLUDE_


/**
 * @class RS422_CONFIG_STRUCT
 * @brief RS422�|�[�g�̏������A�f�[�^���M�A�f�[�^��M�̍ۂɕK�v�ƂȂ�ݒ�����i�[����\���̂ł��B
 */
typedef	struct {
		unsigned char	ch;	/**< @protected @brief �p����̋@�킪�Ȃ����Ă���|�[�g�ԍ�*/
		unsigned int	baudrate;	/**< @protected @brief �p����̋@��̃{�[���[�g�l*/
		unsigned char	stop_bit;	/**< @protected @brief �p����̋@��̃X�g�b�v�r�b�g��*/
}	RS422_CONFIG_STRUCT;


int RS422_init(void *my_rs422_v);
int RS422_Middlewear_TRX(unsigned char call_counter);
int RS422_RX(void *my_rs422_v, void *data_v, int count);
int RS422_TX(void *my_rs422_v, void *data_v, int count);

#endif // RS422_INCLUDE_
