#include "i_utils.h"
#define IFNAMSIZ 1024

void apcli_scan(int nvram, char *input)
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

	get_nth_value(2, input, '&', special_if, sizeof(special_if));
//	get_nth_value(3, input, '&', filter, sizeof(filter));

//	if (nvram == RTDEV_NVRAM)
//		strncpy(wif, "rai0", sizeof(wif));
//	else
		strncpy(wif, "ra0", sizeof(wif));

	// special interface
	if (strlen(special_if) > 0)
		strncpy(wif, special_if, sizeof(wif));

	do_system("iwpriv %s set SiteSurvey=1", wif);

	sleep(6); // for get the SCAN result. (2G + 5G may enough for 5 seconds)

	sprintf(cmd, "iwpriv %s get_site_survey", wif);
	if(!(pp = popen(cmd, "r"))) {
		DBG_MSG("execute get_site_survey fail!");
		return;
	}

	memset(cmd, 0, sizeof(cmd));

	web_debug_header();
#if defined (FIRST_MT7615_SUPPORT) || defined (SECOND_MT7615_SUPPORT)
	fgets(cmd, sizeof(cmd), pp);
	fgets(cmd, sizeof(cmd), pp);
	ptr = cmd;
	total_ssid_num = 0;
	sscanf(ptr, "Total=%d", &total_ssid_num);
	get_ssid_times = (total_ssid_num / 32) + 1;
	DBG_MSG("total_ssid_num=%d, get_ssid_times=%d", total_ssid_num, get_ssid_times);

	fgets(cmd, sizeof(cmd), pp);
	//TODO: Get more than 1 page of site survey result.
	int index = 0;
	printf("{");
	for (round = 0; round < get_ssid_times; round++) {
		if(round != 0) {
			memset(cmd, 0, sizeof(cmd));
			snprintf(cmd, sizeof(cmd), "iwpriv %s get_site_survey %d", wif, round*32);

			if(pp != NULL)
				pclose(pp);

			if(!(pp = popen(cmd, "r"))) {
				DBG_MSG("execute get_site_survey fail!");
				return;
			}

			fgets(cmd, sizeof(cmd), pp);
			fgets(cmd, sizeof(cmd), pp);
			fgets(cmd, sizeof(cmd), pp);
		}

		while (fgets(cmd, sizeof(cmd), pp)) {
			if (strlen(cmd) < 4)
				break;
			ptr = cmd;
			sscanf(ptr, "%d %d ", &no, &channeld);
			ptr += 41;
			sscanf(ptr, "%20s %23s %d %9s %7s %3s %4s", bssid, security, &signald, mode, ext_ch, net_type, wps);
			ptr = cmd+8;
			i = 0;
			while (i < 33) {
				if ((ptr[i] == 0x20) && (i == 0 || ptr[i-1] != 0x20))
					space_start = i;
				i++;
			}
			ptr[space_start] = '\0';
			strcpy(ssid, cmd+8);
			convert_string_display(ssid);

			if (!strcmp(filter, "WPS")) {
				if (!strcmp(wps, "YES")) {
					printf("\"%d\":{", index++);
					printf("\"channeld\":\"%d\",", channeld);
					printf("\"ssid\":\"%s\",", ssid);
					printf("\"bssid\":\"%s\",", bssid);
					printf("\"security\":\"%s\",", security);
					printf("\"signald\":\"%d\",", signald);
					printf("\"mode\":\"%s\",", mode);
					printf("\"ext_ch\":\"%s\",", ext_ch);
					printf("\"net_type\":\"%s\",", net_type);
					printf("\"wps\":\"%s\"},", wps);
				}
			} else {
				printf("\"%d\":{", no);
				printf("\"channeld\":\"%d\",", channeld);
				printf("\"ssid\":\"%s\",", ssid);
				printf("\"bssid\":\"%s\",", bssid);
				printf("\"security\":\"%s\",", security);
				printf("\"signald\":\"%d\",", signald);
				printf("\"mode\":\"%s\",", mode);
				printf("\"ext_ch\":\"%s\",", ext_ch);
				printf("\"net_type\":\"%s\",", net_type);
				printf("\"wps\":\"%s\"},", wps);
			}
		}
	}

	if (!strcmp(filter, "WPS"))
		printf("\"%d\":\"NULL\"}", index);
	else
		printf("\"%d\":\"NULL\"}", ++no);
#else
	fgets(cmd, sizeof(cmd), pp);
	fgets(cmd, sizeof(cmd), pp);
	int index = 0;
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

		if (!strcmp(filter, "WPS")) {
			if (!strcmp(wps, "YES")) {
				printf("<tr>\n");
				printf("<td>%d</td>\n", index++);
				printf("<td>%s</td><td>%s</td>\n", channel, ssid);
				printf("<td>%s</td><td>%s</td>\n", bssid, security);
				printf("<td>%s</td><td>%s</td>\n", signal, mode);
				printf("<td>%s</td><td>%s</td>\n", ext_ch, net_type);
				printf("<td>%s</td>\n", wps);
				printf("</tr>\n");
			}
		} else {
			printf("<tr>\n");
			printf("<td>%d</td>\n", index++);
			printf("<td>%s</td><td>%s</td>\n", channel, ssid);
			printf("<td>%s</td><td>%s</td>\n", bssid, security);
			printf("<td>%s</td><td>%s</td>\n", signal, mode);
			printf("<td>%s</td><td>%s</td>\n", ext_ch, net_type);
			printf("<td>%s</td>\n", wps);
			printf("</tr>\n");
		}
	}
#endif
	pclose(pp);
}

int main()
{
	int nvram_id = 1;
	char *input = "iwpriv apcli_scan";
	apcli_scan(nvram_id, input);
	return 0;
}
