/**
 * @file STT.h
 * @brief STTとのインターフェースモジュール群です。
 * 
 * STTインターフェースモジュールは、AxelSpace社AXELSTAR-2とのインターフェースを実現し、
 * 初期化、データリクエスト、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.11.01
 */

#ifndef	STT_INCLUDE_
#define	STT_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"
#include "../../../IF_Wrapper/DC.h"
#include "../../Super/Driver_Super.h"


/**
 * @brief 恒星検出情報を格納するための構造体です。
 */
typedef struct {
	unsigned int	hipparcos_id;	/**< @public @brief Hipparcos ID(AXELSTAR-2ユーザーズマニュアル参照)*/
	unsigned int	luminance;	/**< @public @brief 輝度(AXELSTAR-2ユーザーズマニュアル参照)*/
	double			tan_azimuth;	/**< @public @brief tan方位角(AXELSTAR-2ユーザーズマニュアル参照)*/
	double			tan_elevation;	/**< @public @brief tan仰角(AXELSTAR-2ユーザーズマニュアル参照)*/
} STAR_INFO_STRUCT;


/**
 * @class STT_STRUCT
 * @extends DRIVER_SUPER_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @extends DC_CONFIG_STRUCT
 * @brief STTの情報を格納する構造体です。
 * 
 * STT1台に対して、1つのグローバルインスタンスとして定義します。
 *  STT_init() により初期化して使用します。
 */
typedef	struct {
	DRIVER_SUPER_STRUCT	driver_super;	/**< @public @brief DRIVER_Superクラスの構造体*/
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422クラスの構造体*/
	DC_CONFIG_STRUCT	dc_config;	/**< @private @brief DCクラスの構造体*/
	unsigned short		capture_id; /**< @public @brief 撮影ごとにインクリメントされるカウンタ(AXELSTAR-2ユーザーズマニュアル参照)*/
	union{
		unsigned char		byte[2];
		struct{
			unsigned complexity : 8; /**< @public @brief 計算の複雑さ(AXELSTAR-2ユーザーズマニュアル参照)*/
			unsigned : 2; /**< @public @brief 無効bit(AXELSTAR-2ユーザーズマニュアル参照)*/
			unsigned master_data : 1; /**< @public @brief マスタのデータ(AXELSTAR-2ユーザーズマニュアル参照)*/
			unsigned slave_data : 1; /**< @public @brief スレーブのデータ(AXELSTAR-2ユーザーズマニュアル参照)*/
			unsigned status : 4; /**< @public @brief ステータス(AXELSTAR-2ユーザーズマニュアル参照)*/
		} bit;
	} integration_state; /**< @public @brief 姿勢統合ステータス(AXELSTAR-2ユーザーズマニュアル参照)*/
	double				attitude[4]; /**< @public @brief 統合された推定姿勢(quaternion)(AXELSTAR-2ユーザーズマニュアル参照)*/
	double				error_covariance_matrix[3][3]; /**< @public @brief 統合された誤差共分散行列(AXELSTAR-2ユーザーズマニュアル参照)*/
	float				master_imager_temperature; /**< @public @brief マスタのイメージセンサ温度(AXELSTAR-2ユーザーズマニュアル参照)*/
	unsigned char		master_detected_star_count; /**< @public @brief マスタの検出恒星数(AXELSTAR-2ユーザーズマニュアル参照)*/
	STAR_INFO_STRUCT	master_star_info[6]; /**< @public @brief マスタの検出恒星情報(AXELSTAR-2ユーザーズマニュアル参照)*/
	union{
		unsigned char		byte[4];
		struct{
			unsigned : 12; /**< @public @brief 無効bit(AXELSTAR-2ユーザーズマニュアル参照)*/
			unsigned reliability : 8; /**< @public @brief 出力姿勢の計算の信頼度(AXELSTAR-2ユーザーズマニュアル参照)*/
			unsigned nearness : 7; /**< @public @brief 近似姿勢からの「近さ」(AXELSTAR-2ユーザーズマニュアル参照)*/
			unsigned algorithm : 1; /**< @public @brief 姿勢推定に使用したアルゴリズム(AXELSTAR-2ユーザーズマニュアル参照)*/
			unsigned status : 4; /**< @public @brief ステータス(AXELSTAR-2ユーザーズマニュアル参照)*/
		} bit;
	} master_estimation_status; /**< @public @brief マスタの姿勢推定ステータス(AXELSTAR-2ユーザーズマニュアル参照)*/
}	STT_STRUCT;

/**
 * @brief 恒星検出情報(Get Detected Star Info コマンド用)を格納するための構造体です。
 */
typedef struct {
	unsigned char	read_star_count;	/**< @public @brief 読み出し星数(AXELSTAR-2ユーザーズマニュアル参照)*/
	unsigned short	index;	/**< @public @brief 星の画面内index(AXELSTAR-2ユーザーズマニュアル参照)*/
	unsigned char	flag;	/**< @public @brief 星の状態フラグ(AXELSTAR-2ユーザーズマニュアル参照)*/
	unsigned int	hipparcos_id;	/**< @public @brief 星のHipparcos ID(AXELSTAR-2ユーザーズマニュアル参照)*/
	unsigned short	area;	/**< @public @brief 星の面積(AXELSTAR-2ユーザーズマニュアル参照)*/
	unsigned int	luminance;	/**< @public @brief 星の輝度(AXELSTAR-2ユーザーズマニュアル参照)*/
	double			tan_azimuth;	/**< @public @brief 星のtan方位角(AXELSTAR-2ユーザーズマニュアル参照)*/
	double			tan_elevation;	/**< @public @brief 星のtan仰角(AXELSTAR-2ユーザーズマニュアル参照)*/
} GET_DETECTED_STAR_INFO_COMMAND_STRUCT;

/**
 * @brief 姿勢推定ステータス(Get Estimation Status コマンド用)を格納するための構造体です。
 */
typedef union{
	unsigned char		byte[4];
	struct{
		unsigned : 12; /**< @public @brief 無効bit*/
		unsigned confidence : 8; /**< @public @brief 計算の信頼度(AXELSTAR-2ユーザーズマニュアル参照)*/
		unsigned nearness : 7; /**< @public @brief 設定した近似姿勢からの「近さ」を表す指標(AXELSTAR-2ユーザーズマニュアル参照)*/
		unsigned algorithm : 1; /**< @public @brief 姿勢推定に使用したアルゴリズム(AXELSTAR-2ユーザーズマニュアル参照)*/
		unsigned status : 4; /**< @public @brief ステータス(AXELSTAR-2ユーザーズマニュアル参照)*/
	} bit;
} GET_ESTIMATION_STATUS_UNION;


int STT_init(STT_STRUCT *my_stt, unsigned char ch, unsigned short up_enable_bit);
int STT_cycle(STT_STRUCT *my_stt);
int STT_rec(STT_STRUCT *my_stt);
int STT_debug_message(STT_STRUCT* my_stt);
int STT_auto_mode(STT_STRUCT *my_stt);
int STT_stop(STT_STRUCT* my_stt);
int STT_Up_Enable_Power_Down(STT_STRUCT *my_stt);
int STT_Up_Enable_Idle(STT_STRUCT *my_stt);
int STT_Get_Temperature(STT_STRUCT *my_stt, float *image_sensor_board, float *fpga, float *image_sensor);
int STT_Change_Power_State_Capture(STT_STRUCT *my_stt);
int STT_Change_Power_State_Idle(STT_STRUCT *my_stt);
int STT_Get_Power_State(STT_STRUCT *my_stt, unsigned char *state);
int STT_Get_Exposure_Time(STT_STRUCT *my_stt, unsigned short *get_time);
int STT_Set_Exposure_Time(STT_STRUCT *my_stt, unsigned short *get_time, unsigned short set_time);
int STT_System_Reset(STT_STRUCT *my_stt);
int STT_Capture_Only(STT_STRUCT *my_stt);
int STT_PostProc_Only(STT_STRUCT *my_stt);
int STT_Capture_And_PostProc(STT_STRUCT *my_stt);
int STT_Get_Detected_Star_Count(STT_STRUCT *my_stt, unsigned char *star_count);
int STT_Get_Detected_Star_Info(STT_STRUCT *my_stt, unsigned short read_index, unsigned char count, GET_DETECTED_STAR_INFO_COMMAND_STRUCT *info_data, unsigned int size);
int STT_Set_Approximate_Attitude(STT_STRUCT *my_stt, double quaternion1, double quaternion2, double quaternion3, double quaternion4);
int STT_Get_Estimation_Status(STT_STRUCT *my_stt, GET_ESTIMATION_STATUS_UNION *st_data);
int STT_Get_Attitude(STT_STRUCT *my_stt, double *quaternion1, double *quaternion2, double *quaternion3, double *quaternion4);
int STT_Get_Error_Covariance_Matrix(STT_STRUCT *my_stt, double *ecm00, double *ecm01, double *ecm02, double *ecm11, double *ecm12, double *ecm22);
int STT_Change_Output_Mode(STT_STRUCT *my_stt, unsigned char *state);
int STT_Get_SEU_Error_Correction_Count(STT_STRUCT *my_stt, unsigned short *seu_error_count);
int STT_Get_Error(STT_STRUCT *my_stt, unsigned char *error);
int STT_Clear_Error(STT_STRUCT *my_stt, unsigned char *error);
int STT_Get_Output_Interval(STT_STRUCT *my_stt, unsigned char *interval);
int STT_Set_Output_Interval(STT_STRUCT *my_stt, unsigned char set_interval, unsigned char *interval);
int STT_Start_Output(STT_STRUCT *my_stt);
int STT_Stop_Output(STT_STRUCT *my_stt);

#endif // STT_INCLUDE_
