/**
 * @file SPWIRE.c
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

/* �C���N���[�h�t�@�C���錾 */
#include <string.h>
#include "t_services.h"        		/* TOPPERS�p�w�b�_�t�@�C��              */
#include "../source/mw_header.h"	/* �~�h���E�F�A�p�w�b�_�t�@�C��         */
#include "IF_Board_Number.h"

#include "SPWIRE.h"

/* �ϐ���` */
static M_T_RMAP_PKT_ATTR	rmap_cfg[4][4];	/**< @brief �~�h���E�G�A�̐ݒ�����i�[����\���̂̕ϐ�(4�~4�ʂ�|�[�g��)�ł��B*/
static unsigned char		rmap_buf[0xFFF];	/**< @brief �o�b�t�@*/

//***************************************************
//	Init	wrapper
//***************************************************
/**
 * @memberof SPWIRE_CONFIG_STRUCT
 * @protected
 * @brief SPWIRE_CONFIG�\���̂��O���[�o���C���X�^���X�Ƃ��Ē�`���A�|�C���^��n�����ƂŃ|�[�g�����������܂��B
 * @note SPWIRE�ʐM���b�p�[�̃N���X���g�p���鎞�͋N�����ɕK�����{���Ă��������B
 * @warning ���̊֐������s����O��SPWIRE_CONFIG�\���̓��̐ݒ�l��ݒ肵�Ă����K�v������܂��B
 * @param void *my_spwire_v : ����������SPWIRE_CONFIG�\���̂ւ̃|�C���^
 * @return 0 : ����I��
 * @return -100 : ���g�̃|�[�g�ԍ��l�s��
 * @return -200 : ����̃|�[�g�ԍ��l�s��
 */
int	SPWIRE_init(void *my_spwire_v){
    SPWIRE_CONFIG_STRUCT *my_spwire = (SPWIRE_CONFIG_STRUCT *)my_spwire_v;
    int				i_ret = 0;
	unsigned char	own = my_spwire->own_port;
	unsigned char	tar = my_spwire->target_port;
	unsigned int	addr = my_spwire->reg_addr;
	
	
	if((own < 1) || (own > 4)){
		return (-100);
	}
	
	if((tar < 1) || (tar > 4)){
		return (-200);
	}
	
	
	/********************************************************/
	/* �|�[�g�ݒ�						                    */
	/********************************************************/
	rmap_cfg[own][tar].ui_destLogAdd = 0x42;
	rmap_cfg[own][tar].ui_srcLogAdd = 0x42;
	rmap_cfg[own][tar].ui_ackMode = 1;
	rmap_cfg[own][tar].ui_incAddMode = 1;
	rmap_cfg[own][tar].ui_destKey = 0x24;
	rmap_cfg[own][tar].ui_exAdd = 0;
	
	
	// �o�H�ݒ�
	rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00000000;
	rmap_cfg[own][tar].t_destPathAdd.ui_add[1] = 0x00000000;
	rmap_cfg[own][tar].t_destPathAdd.ui_add[2] = 0x00000000;
	rmap_cfg[own][tar].t_destPathAdd.ui_addNum = 1;
	rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00000000;
	rmap_cfg[own][tar].t_srcPathAdd.ui_add[1] = 0x00000000;
	rmap_cfg[own][tar].t_srcPathAdd.ui_add[2] = 0x00000000;
	rmap_cfg[own][tar].t_srcPathAdd.ui_addNum = 1;
	if(own == 1){
		if(tar == 1){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00000105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00000105;
		}else if(tar == 2){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00010105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00030305;
		}else if(tar == 3){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00000105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00000205;
		}else{
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00010105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00030205;
		}
	}else if(own == 2){
		if(tar == 1){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00030305;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00010105;
		}else if(tar == 2){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x03030105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x03030105;
		}else if(tar == 3){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00030305;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00020105;
		}else{
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x03030105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x03020105;
		}
	}else if(own == 3){
		if(tar == 1){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00000205;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00000105;
		}else if(tar == 2){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00020105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00030305;
		}else if(tar == 3){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00000205;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00000205;
		}else{
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00020105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00030205;
		}
	}else{
		if(tar == 1){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00030205;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00010105;
		}else if(tar == 2){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x03020105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x03030105;
		}else if(tar == 3){
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x00030205;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x00020105;
		}else{
			rmap_cfg[own][tar].t_destPathAdd.ui_add[0] = 0x03020105;
			rmap_cfg[own][tar].t_srcPathAdd.ui_add[0] = 0x03020105;
		}
	}
	
	
	// ��������������
	rmap_cfg[own][tar].ui_RdWrMode = 0;
	rmap_cfg[own][tar].ui_verifyMode = 0;
	rmap_cfg[own][tar].ui_accessAdd = 0x00000000;
	rmap_cfg[own][tar].ui_dataLen = 0;
	
	return (0);
}


//***************************************************
//	RX wrapper
//***************************************************
/**
 * @memberof SPWIRE_CONFIG_STRUCT
 * @protected
 * @brief SPWIRE_CONFIG�\���̂ɂĎw�肳�ꂽch����f�[�^����M���܂��B
 * @note �ʐM����ɑ΂���4�o�C�g�o�E���_���A�N�Z�X�ɂȂ�悤�ɍ׍H���Ă���
 * @param void *my_spwire_v : �ΏۂƂ���SPWIRE_CONFIG�\���̂ւ̃|�C���^
 * @param void *data_v : ��M�f�[�^�i�[��ւ̃|�C���^
 * @param int *count : ��M�f�[�^�i�[��̃f�[�^�T�C�Y
 * @return 0 : ��M�f�[�^�Ȃ�
 * @return -100 : ��M����f�[�^�T�C�Y���傫������(0xFFF�ȏ�)
 * @return -200�ԑ� : �ُ�I��(�ڍׂ�+200������ M_AP_nobc_sendRmapPacket() �̖߂�l���Q��)
 * @return ��L�ȊO : ��M�f�[�^�o�C�g��(����I��)
 */
int		SPWIRE_RX(void *my_spwire_v, void *data_v, int count){
	SPWIRE_CONFIG_STRUCT *my_spwire = (SPWIRE_CONFIG_STRUCT *)my_spwire_v;
	unsigned char *data = (unsigned char *)data_v;
    int		i_ret = 0;
	unsigned char	own = my_spwire->own_port;
	unsigned char	tar = my_spwire->target_port;
	unsigned int	addr = my_spwire->reg_addr;
	unsigned char	addr_mod = addr % 4;
	unsigned char	cnt_mod = ((4 - (count + addr_mod) % 4) % 4);
	
	
	if(count <= 0){
		return (0);
	}
	
	if(count > sizeof(rmap_buf)){
		return (-100);
	}
	
	rmap_cfg[own][tar].ui_RdWrMode = 0;		// Read
	rmap_cfg[own][tar].ui_verifyMode = 0;
	rmap_cfg[own][tar].ui_accessAdd = addr - addr_mod;
	rmap_cfg[own][tar].ui_dataLen = count + addr_mod + cnt_mod;
	i_ret = M_AP_nobc_sendRmapPacket(rmap_cfg[own][tar] , rmap_buf);
	if(i_ret != 0){
		return (-200 + i_ret);
	}
	
	memcpy(data, (rmap_buf + addr_mod), count);
	
	
	return (count);
}


//***************************************************
//	TX wrapper
//***************************************************
/**
 * @memberof SPWIRE_CONFIG_STRUCT
 * @protected
 * @brief SPWIRE_CONFIG�\���̂ɂĎw�肳�ꂽch�փf�[�^�𑗐M���܂��B
 * @note �ʐM����ɑ΂���4�o�C�g�o�E���_���A�N�Z�X�ɂȂ�悤�ɍ׍H���Ă���
 * @param void *my_spwire_v : �ΏۂƂ���SPWIRE_CONFIG�\���̂ւ̃|�C���^
 * @param void *data_v : ���M�f�[�^�i�[��ւ̃|�C���^
 * @param int *count : ���M�f�[�^�T�C�Y
 * @return 0 : ����I��
 * @return -100 : ���M����f�[�^�T�C�Y���傫������(0xFFF�ȏ�)
 * @return -200�ԑ� : �ُ�I��(���[�h��)(�ڍׂ�+200������ M_AP_nobc_sendRmapPacket() �̖߂�l���Q��)
 * @return -300�ԑ� : �ُ�I��(���C�g��)(�ڍׂ�+300������ M_AP_nobc_sendRmapPacket() �̖߂�l���Q��)
 */
int		SPWIRE_TX(void *my_spwire_v, void *data_v, int count){
	SPWIRE_CONFIG_STRUCT *my_spwire = (SPWIRE_CONFIG_STRUCT *)my_spwire_v;
	unsigned char *data = (unsigned char *)data_v;
    int		i_ret = 0;
	unsigned char	own = my_spwire->own_port;
	unsigned char	tar = my_spwire->target_port;
	unsigned int	addr = my_spwire->reg_addr;
	unsigned char	addr_mod = addr % 4;
	unsigned char	cnt_mod = ((4 - (count + addr_mod) % 4) % 4);
	
	
	if(count <= 0){
		return (0);
	}
	
	if(count > sizeof(rmap_buf)){
		return (-100);
	}
	
	rmap_cfg[own][tar].ui_RdWrMode = 0;		// Read
	rmap_cfg[own][tar].ui_verifyMode = 0;
	rmap_cfg[own][tar].ui_accessAdd = addr - addr_mod;
	rmap_cfg[own][tar].ui_dataLen = count + addr_mod + cnt_mod;
	i_ret = M_AP_nobc_sendRmapPacket(rmap_cfg[own][tar] , rmap_buf);
	if(i_ret != 0){
		return (-200 + i_ret);
	}
	
	memcpy((rmap_buf + addr_mod), data, count);
	
	rmap_cfg[own][tar].ui_RdWrMode = 1;		// Write
	rmap_cfg[own][tar].ui_verifyMode = 1;
	rmap_cfg[own][tar].ui_accessAdd = addr - addr_mod;
	rmap_cfg[own][tar].ui_dataLen = count + addr_mod + cnt_mod;
	i_ret = M_AP_nobc_sendRmapPacket(rmap_cfg[own][tar] , rmap_buf);
	if(i_ret != 0){
		return (-300 + i_ret);
	}
	
	
	return (0);
}
