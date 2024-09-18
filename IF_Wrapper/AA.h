/**
 * @file AA.h
 * @brief AA(ActiveAnalog)���b�p�[�̃N���X�ł��B
 * 
 * AA(ActiveAnalog)���b�p�[�́A
 * AA�̃C���^�[�t�F�[�X���������A
 * AA�|�[�g�̏������A�d���l�擾���s���A
 * AA���b�p�[�̃N���X�ł��B
 * �X�̋@��̃C���^�[�t�F�[�X���W���[���Ɍp��?�����Ďg�p���܂��B
 * @author ���� �@���Y
 * @date 2012.10.26
 */

#ifndef AA_INCLUDE_
#define AA_INCLUDE_


/**
 * @class AA_CONFIG_STRUCT
 * @brief AA�|�[�g�̏������A�d���l�擾�̍ۂɕK�v�ƂȂ�ݒ�����i�[����\���̂ł��B
 */
typedef	struct {
		unsigned char	ch;	/**< @protected @brief  �`���l���w���bit0���|�[�g1�ɁAbit7���|�[�g8�ɑΉ����A1��ݒ肵���|�[�g�̓d���l�������擾���܂��B*/
}	AA_CONFIG_STRUCT;


int AA_init(void *my_aa_v);
int AA_RX(void *my_aa_v, void *data_v, int count);
int AA_TX(void *my_aa_v, void *data_v, int count);

#endif // AA_INCLUDE_
