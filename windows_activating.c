#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wininet.h>
#pragma comment(lib,"Wininet.lib")

#define GETCHAR printf("Appuyer sur ENTRER pour continuer ...\r\n")

#if !_WIN64
#error Can only be launched in x86_64 architecture
#endif

char* exec(const char* cmd) {
    char buffer[128];
    char* result=(char *)malloc(1000000);
    FILE* pipe = _popen(cmd, "r");
    if (pipe == NULL) {
        printf("popen() failed!");
    }
    while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            strcat(result,buffer);
        }

    _pclose(pipe);
    return result;
}

BOOL IsElevated( ) {
    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if( OpenProcessToken( GetCurrentProcess( ),TOKEN_QUERY,&hToken ) ) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof( TOKEN_ELEVATION );
        if( GetTokenInformation( hToken, TokenElevation, &Elevation, sizeof( Elevation ), &cbSize ) ) {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if( hToken ) {
        CloseHandle( hToken );
    }
    return fRet;
}



int main(int argc, char *argv[])
{
	char real_version[256];
	char res2[1000000];
	char model[256];
	if (IsElevated() == FALSE)
	{
		printf("Vous devez lancer cette utilitaire en mode ADMIN uniquement\r\n");
		GETCHAR;
		getchar();
		return 1;
	}

	char url[128];
	strcat(url, "http://www.google.com");
	BOOL bConnect = InternetCheckConnection(url, FLAG_ICC_FORCE_CONNECTION, 0);

	if (bConnect == FALSE)
	{
		printf("Vous n'avez pas de connexion internet active\r\n");
		GETCHAR;
		getchar();
		return 1;
	}
	

	printf("\r\n\r\nAUTEUR: HICHEM BEN YOUSSEF\r\nContact:h.benyoussef@yahoo.fr\r\n\r\n");
	printf("Cette utilitaire permet d'activer windows 10 sans action specifique de votre part.\r\n");
	GETCHAR;
	getchar();
	printf("Lancement ...\r\n\r\n");
	char *res=exec("systeminfo");
	
	strcpy(res2,strstr(res,"Microsoft Windows"));
	char *line_feed = strchr(res2, '\n');
	
	*line_feed = '\0';
	
	strncpy(real_version,res2,strlen(res2));
	printf("Votre version est %s\r\n",real_version);
	
	
	char license_key[128];
	if (strcmp(real_version, "Microsoft Windows 10 Professionnel N") == 0)
	{
		strcpy(license_key, "MH37W-N47XK-V7XM9-C7227-GCQG9");
	}
	else if (strcmp(real_version, "Microsoft Windows 10 Famille") == 0)
	{
		strcpy(license_key, "TX9XD-98N7V-6WMQ6-BX7FG-H8Q99");
	}
	else if (strcmp(real_version, "Microsoft Windows 10 Famille N") == 0)
	{
		strcpy(license_key, "3KHY7-WNT83-DGQKR-F7HPR-844BM");
	}
	else if (strcmp(real_version, "Microsoft Windows 10 Professionnel") == 0)
	{
		strcpy(license_key, "W269N-WFGWX-YVC9B-4J6C9-T83GX");
	}
	else if (strcmp(real_version, "Microsoft Windows 10 Education") == 0)
	{
		strcpy(license_key, "NW6C2-QMPVW-D7KKK-3GKT6-VCFB2");
	}
	else if (strcmp(real_version, "Microsoft Windows 10 Education N") == 0)
	{
		strcpy(license_key, "2WH4N-8QGBV-H22JP-CT43Q-MDWWJ");
	}
	else if (strcmp(real_version, "Microsoft Windows 10 Entreprise") == 0)
	{
		strcpy(license_key, "NPPR9-FWDCX-D2C8J-H872K-2YT43");
	}
	else if (strcmp(real_version, "Microsoft Windows 10 Entreprise N") == 0)
	{
		strcpy(license_key, "DPH2V-TTNVB-4X9Q3-TJR4H-KHJW4");
	}
	else
	{
		printf("Votre version windows n'a pas ete trouve");
		free(res);
		return -1;
	}


	char cmdArgs[256] = "slmgr /ipk ";
	strcat(cmdArgs,license_key);
	system(cmdArgs);
	system("slmgr /skms kms8.msguides.com");
	system("slmgr /ato");
	
	printf("\r\nVotre version Windows est active !\r\nAppuyez sur n'importe quelle touche pour sortir ...\r\n");
	getchar();
	
	free(res);
	return 0;
}