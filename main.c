#include "stdio.h"
#include "stdbool.h"
#include "dictionary.h"
#include "iniparser.h"

#define CONFIGURE_FILE "/home/gcp/wisdom/tmp/ini/configure.ini"

static dictionary *ini;

int load_ini()
{
    ini = iniparser_load(CONFIGURE_FILE);
    if(ini == NULL)
    {
        printf("can not parse file! \n");
        return -1;
    }
    return 0;
}

int write_ini(const dictionary *d, char *sec, char *key, char *value)
{
    char sectionkey[32] = {0};

    if(d == NULL) return 1;

    sprintf(sectionkey,"%s:%s",sec,key);

    if(iniparser_set(d,sectionkey,value))
    {
        printf("Setvalue have not key =- %s",sectionkey);
        return 1;
    }
}

int savesec(const dictionary *d,char *sec)
{
        FILE *out;
        printf("wis_savesec all! \n");
        if((out = fopen(CONFIGURE_FILE,"w")) == NULL)
        {
            printf("Get Configure File Error!");
            return 1;
        }

        iniparser_dump_ini(d,out);

        fflush(out);
        fclose(out);

        return 0;
}

void main()
{

    char buf[16] = {"gcp"};
    if(0 == load_ini())
        printf("load ini ok\n");
    bool test = 1;
    char buf1[10];
    sprintf(buf1,"%d",test);
    printf("buf1 = %s\n",buf1);
    write_ini(ini,"sec2","test4",buf1);

// write ini
    write_ini(ini, "sec1", "test1", buf);
    savesec(ini,"sec2");

//read ini
    int b;
    bool c;

    c = iniparser_getboolean(ini,"sec2:test3",0);
    printf("%d\n",c);

    b = iniparser_getint(ini,"sec2:test2",2);
    printf("%d\n",b);

    memset(buf,0,sizeof(buf));
    strncpy(buf,iniparser_getstring(ini,"sec2:test1",""),sizeof(buf));
    printf("%s\n",buf);

    printf("hello world!\n");
}
