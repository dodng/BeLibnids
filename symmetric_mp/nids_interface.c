/*
 *   <dodng12@163.com>. 
 *     */
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <pcap.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include "nids_interface.h"
#include "nids.h"
#include <time.h>
#include "../pkt_plugin/sniff.c"

#define UNUSED(x)      (void)(x)

int g_proc_id = 0;
int g_port = 0;
FILE *write_file = NULL;
uint64_t pkt_num = 0;
struct timeval prev_time,cur_time;

void ip_frag_func_callback(struct ip * a_packet, int len);
void ip_frag_func_callback(struct ip * a_packet, int len)
{
	UNUSED(a_packet);
	UNUSED(len);
#if 0
	pkt_num++;
	gettimeofday(&cur_time,NULL);

	if (cur_time.tv_sec - prev_time.tv_sec >= 3) 
	{
		//print time
		char my_time[64] = {0};
		strftime(my_time,sizeof(my_time),"%Y-%m-%d %T",localtime(&(cur_time.tv_sec)));
		fprintf(write_file, "%s,pkt_num:%ld\n",my_time,pkt_num);
		fflush(write_file);
		//reset time
		prev_time = cur_time;
		pkt_num = 0;
	}
#endif
}

int process_init(void)
{
#if 0
	if (!nids_init ())
	{
		fprintf (stderr, "%s\n", nids_errbuf);
		exit (1);
	}
	nids_register_ip_frag(ip_frag_func_callback);
#endif
	test_main();
	//log info
	char file_name[32] = {0};
	snprintf(file_name,sizeof(file_name),"./port[%d]_proc[%d].pid",g_port,g_proc_id);
	write_file = fopen(file_name,"w+");
	fprintf(write_file, "%d\n",(int)getpid());
	fflush(write_file);
	//init time
	gettimeofday(&prev_time,NULL);
	gettimeofday(&cur_time,NULL);
	return 0;
}

int process_pkt_callback(void* data,uint16_t data_len)
{
	struct pcap_pkthdr pkthdr;
	u_char *pkt_data = data;
	//cook pkt header
	gettimeofday(&pkthdr.ts, NULL);
	pkthdr.caplen = data_len;
	pkthdr.caplen = data_len;
	//trigger libnids
	nids_pcap_handler(0,&pkthdr,pkt_data);
	return 0;
#if 0
	UNUSED(data);
	UNUSED(data_len);
	pkt_num++;
	gettimeofday(&cur_time,NULL);

	if (cur_time.tv_sec - prev_time.tv_sec >= 3)
	{
		//print time
		char my_time[64] = {0};
		strftime(my_time,sizeof(my_time),"%Y-%m-%d %T",localtime(&(cur_time.tv_sec)));
		fprintf(write_file, "%s,pkt_num:%ld\n",my_time,pkt_num);
		fflush(write_file);
		//reset time
		prev_time = cur_time;
		pkt_num = 0;
	}
#endif
}

