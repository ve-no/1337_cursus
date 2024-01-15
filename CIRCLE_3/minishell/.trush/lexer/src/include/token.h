#ifndef TOKEN_H
#define TOKEN_H
# include "../libft/inc/libft.h"
typedef struct TOKEN_STRUCT
{
    enum
    {
        TOKEN_ID,
        TOKEN_PIPE,
        TOKEN_TILDE,
        TOKEN_VAR,
        TOKEN_FLAG,
        TOKEN_INPUT,
        TOKEN_OUTPUT,
        HERDOC_R,
        HERDOC_L,
        TOKEN_ERR
    } type;

    char* value;
} token_T;

token_T* init_token(int type, char* value);
#endif
