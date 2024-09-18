/**
 * @file DC.h
 * @brief DC(Discrete)���b�p�[�̃N���X�ł��B(AOBC�p)
 * 
 * DC(Discrete)���b�p�[�́A
 * DC�̃C���^�[�t�F�[�X���������A
 * DC�|�[�g�̏������ADC�M�����o�͂��s���A
 * DC���b�p�[�̃N���X�ł��B
 * �X�̋@��̃C���^�[�t�F�[�X���W���[���Ɍp��?�����Ďg�p���܂��B
 * @author ���� �@���Y
 * @date 2013.06.20
 */

#ifndef DC_INCLUDE_
#define DC_INCLUDE_


/**
 * @class DC_CONFIG_STRUCT
 * @brief DC�|�[�g�̏������ADC�M�����o�͂̍ۂɕK�v�ƂȂ�ݒ�����i�[����\���̂ł��B
 */
typedef	struct {
		unsigned short	ch_in;	/**< @protected @brief  �`���l���w���bit0���|�[�g1�ɁAbit15���|�[�g16�ɑΉ����A1��ݒ肵���|�[�g��DC�M���������擾���܂��B*/
		unsigned short	ch_out;	/**< @protected @brief  �`���l���w���bit0���|�[�g1�ɁAbit15���|�[�g16�ɑΉ����A1��ݒ肵���|�[�g��DC�M���������o�͂��܂��B*/
}	DC_CONFIG_STRUCT;


int DC_init(void *my_dc_v);
int DC_Middlewear_RX(unsigned char call_counter);
int DC_RX(void *my_dc_v, void *data_v, int count);
int DC_TX(void *my_dc_v, void *data_v, int count);

extern	unsigned short	dc_val_out;	/**< @public @brief �ŐV��DC�o�͒l�f�[�^���i�[����ϐ��ł�(�e�����g���p)�B*/
extern	unsigned short	dc_val_in;	/**< @public @brief �ŐV��DC���͒l�f�[�^���i�[����ϐ��ł�(�e�����g���p)�B*/

#endif // DC_INCLUDE_
