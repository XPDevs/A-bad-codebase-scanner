/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef LEXER_H
#define LEXER_H
#include "code_scan.h"
typedef struct{char*start;char*cur;char*end;char file[CODE_SCAN_MAX_PATH];int line;int col;int eof;int prev_line;int prev_col;Token prev_tok;int paren_depth;int brace_depth;int bracket_depth;int in_preproc;int error;}LexerState;
Token lexer_next(LexerState*ls);Token lexer_peek(LexerState*ls);Token lexer_prev(LexerState*ls);void lexer_init(LexerState*ls,const char*content,const char*file);int lexer_tokenize(LexerState*ls,Token*tokens,int max_tokens);char*lexer_type_str(TokenType t);int lexer_is_keyword(const char*s);int lexer_is_type_keyword(const char*s);void lexer_skip_whitespace(LexerState*ls);void lexer_skip_comment(LexerState*ls);Token lexer_read_number(LexerState*ls);Token lexer_read_string(LexerState*ls);Token lexer_read_char(LexerState*ls);Token lexer_read_ident(LexerState*ls);Token lexer_read_punct(LexerState*ls);Token lexer_read_preproc(LexerState*ls);int lexer_get_pos(LexerState*ls,int*line,int*col);
#endif
