#ifndef _MOD_INTERFASE_H__
#define _MOD_INTERFASE_H__

#ifdef __cplusplus
extern "C" {
#endif
	int process_init(void);
	int process_pkt_callback(void* data,uint16_t data_len);

#ifdef __cplusplus
}
#endif

#endif

