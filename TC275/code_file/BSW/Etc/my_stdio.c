#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdarg.h"
#include "asclin.h"
#include "IfxAsclin_Asc.h"
#include "IfxStdIf_DPipe.h"


void Init_Mystdio(void)
{
    _init_uart3();
}


#define BUFSIZE     128
#define KB_BS '\x7F'
#define KB_CR '\r'

void my_puts(const char *str)
{
    char buffer[BUFSIZE];
    char *ptr;

    sprintf(buffer, "%s\r\n", str);

    for (ptr = buffer; *ptr; ++ptr)
        _out_uart3((const unsigned char) *ptr);
}

int my_printf(const char *format, ...)
{
    if (!Ifx_g_console.standardIo->txDisabled)
    {
        char      message[STDIF_DPIPE_MAX_PRINT_SIZE + 1];
        char      message2[STDIF_DPIPE_MAX_PRINT_SIZE + 1]; // add \r before \n
        Ifx_SizeT count;
        va_list   args;
        va_start(args, format);
        vsprintf((char *)message, format, args);
        va_end(args);
        int j = 0;
        for(int i=0; message[i]; i++)
        {
            if(message[i] == '\n')
            {
                message2[j++] = '\r';
                message2[j++] = message[i];
            }
            else
                message2[j++] = message[i];
        }
        message2[j] = '\0';
        count = (Ifx_SizeT)strlen(message2);
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, count < STDIF_DPIPE_MAX_PRINT_SIZE);

        return IfxStdIf_DPipe_write(Ifx_g_console.standardIo, (void *)message2, &count, TIME_INFINITE);
    }
    else
    {
        return TRUE;
    }
}

void remove_null(char *s)
{
    int i, start_idx;
    char buf[512];

    start_idx = 0;
    while (*(s + start_idx++) == '\0');
    memset(buf, 0, 512);
    strcpy(buf, (s + (start_idx - 1)));

    memset(s, 0, 512);
    i = 0;
    while (buf[i] != '\0')
    {
        *(s + i) = buf[i];
        ++i;
    }
    *(s + i) = '\0';
}


void my_scanf(const char *fmt, ...)
{
    char c = 0, buf[512];
    int idx, i;
    char *pstr, *pidx;
    va_list ap;
    va_start(ap, fmt);

    idx = 0;
    memset(buf, 0, 512);
    while (c != '\r')
    {
        c = _in_uart3();
        if (c == KB_BS)
        {
            if (idx != 0) { buf[idx--] = 0; }
            else { continue; }
        }
        else
        {
            if (c == KB_CR) { buf[idx++] = '\0'; }
            else { buf[idx++] = c; }
        }
        my_printf("%c", c);
    }
    my_printf("\r\n");

    while ((c = *fmt++) != 0)
    {
        if (c == '%')
        {
            c = *fmt++;
            switch (c)
            {
                case 'c':
                    *va_arg(ap, char *) = buf[0];
                    buf[0] = '\0';
                    break;
                case 'd':
                    *va_arg(ap, int *) = atoi(buf);
                    pidx = strchr(buf, ' ');
                    if (pidx != NULL) { *pidx = '\0'; }
                    for (i = 0; ; i++)
                    {
                        if (buf[i] == '\0' || buf[i] == ' ') { buf[i] = '\0'; break; }
                        buf[i] = '\0';
                    }
                    break;
                case 's':
                    pstr = va_arg(ap, char *);
                    for (i = 0; buf[i] != '\0'; i++)
                    {
                        *pstr++ = buf[i];
                        buf[i] = '\0';
                    }
                    *pstr = '\0';
                    break;
                default:
                    break;
            }
            remove_null(buf);
        }
    }
    va_end(ap);
}





