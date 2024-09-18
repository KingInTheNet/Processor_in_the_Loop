/**
 * @file PA.h
 * @brief PA(PassiveAnalog)���b�p�[�̃N���X�ł��B(AOBC�p)
 * 
 * PA(PassiveAnalog)���b�p�[�́A
 * PA�̃C���^�[�t�F�[�X���������A
 * PA�|�[�g�̏������A�d���l�擾���s���A
 * PA���b�p�[�̃N���X�ł��B
 * �X�̋@��̃C���^�[�t�F�[�X���W���[���Ɍp��?�����Ďg�p���܂��B
 * @author ���� �@���Y
 * @date 2013.06.20
 */

#ifndef PA_INCLUDE_
#define PA_INCLUDE_


/**
 * @class PA_CONFIG_STRUCT
 * @brief PA�|�[�g�̏������A�d���l�擾�̍ۂɕK�v�ƂȂ�ݒ�����i�[����\���̂ł��B
 */
typedef	struct {
		unsigned short	ch;	/**< @protected @brief  �`���l���w���bit0���|�[�g1�ɁAbit15���|�[�g16�ɑΉ����A1��ݒ肵���|�[�g�̓d���l�������擾���܂��B*/
}	PA_CONFIG_STRUCT;


int PA_init(void *my_pa_v);
int PA_Middlewear_RX(unsigned char call_counter);
int PA_RX(void *my_pa_v, void *data_v, int count);
int PA_TX(void *my_pa_v, void *data_v, int count);

#endif // PA_INCLUDE_
