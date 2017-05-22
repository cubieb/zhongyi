#include "utils.h"

/*
 * this module is search ths all can be use ssid
 */

//#define CMDLEN 1024
#define IFNAMSIZ 256

int main(int argc, char *argv[])
{

	FILE *pp;
	char cmd[CMDLEN], *ptr, wif[IFNAMSIZ];
	char channel[4], ssid[186], bssid[20], security[23];
	char signal[9], mode[9], ext_ch[7], net_type[3];
	char wps[4];
#if defined (FIRST_MT7615_SUPPORT) || defined (SECOND_MT7615_SUPPORT)
	//	char no[4];
	int  no = 0; 
	int  channeld = 0;
	int  signald = 0;
#endif
	int i, space_start;
	char special_if[IFNAMSIZ];
	char filter[4];
	int total_ssid_num, get_ssid_times, round;
	
	strncpy(wif, "ra0", sizeof(wif));

	do_system("iwpriv %s set SiteSurvey=1", wif);
	sleep(1); // for get the SCAN result. (2G + 5G may enough for 5 seconds)

	sprintf(cmd, "iwpriv %s get_site_survey", wif);
	if(!(pp = popen(cmd, "r"))) {
		DBG_MSG("execute get_site_survey fail!");
		return;
	}

	memset(cmd, 0, sizeof(cmd));


	web_debug_header();

	//the first time: cmd is get the ra0 get_site_survey message.
	fgets(cmd, sizeof(cmd), pp);
	//the second time:cmd is get the Ch SSID BSSID Security ... message.
	fgets(cmd, sizeof(cmd), pp);

	int index = 0;
	printf("{\n");
	printf("\t\"Scan\":[\n");
	while (fgets(cmd, sizeof(cmd), pp)) {
		if (strlen(cmd) < 4)
			break;
		ptr = cmd;
		sscanf(ptr, "%s ", channel);
		ptr += 37;
		sscanf(ptr, "%s %s %s %s %s %s %s", bssid, security, signal, mode, ext_ch, net_type, wps);
		ptr = cmd+4;
		i = 0;
		while (i < 33) {
			if ((ptr[i] == 0x20) && (i == 0 || ptr[i-1] != 0x20))
				space_start = i;
			i++;
		}
		ptr[space_start] = '\0';
		strcpy(ssid, cmd+4);
		convert_string_display(ssid);

		printf("\t\t{\n");
		//printf("%d\n", index++);
		printf("\t\t\"Channel\":\"%s\", \"ssid\":\"%s\",\n", channel, ssid);
		printf("\t\t\"bssid\":\"%s\", \"security\":\"%s\",\n", bssid, security);
		printf("\t\t\"signal\":\"%s\", \"mode\":\"%s\",\n", signal, mode);
		printf("\t\t\"ext_ch\":\"%s\", \"net_type\":\"%s\",\n", ext_ch, net_type);
		printf("\t\t\"wps\":\"%s\"\n", wps);
		printf("\t\t},\n");
	}
	printf("\t\t{\n\t\t}\n");
	printf("\t]\n");
	printf("}\n");

	pclose(pp);

	return 0;
}
