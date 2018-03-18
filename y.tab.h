#define NEWLINE 257
#define GREAT 258
#define LESS 259
#define GREATGREAT 260
#define GREATAMP 261
#define PIPE 262
#define AMP 263
#define NOTOKEN 264
#define WORD 265
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	char *string_val;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
