/*
 * Lightweight uBASIC Interpreter for Contiki OS on RV32IM
 * Supports: PRINT, LET, IF/THEN, FOR/TO/NEXT, GOTO, GOSUB/RETURN, PEEK, POKE,
 * END
 */

#include "ubasic.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARNUM 26
#define MAX_GOSUB_STACK 16
#define MAX_FOR_STACK 8

enum {
  TOKEN_ERROR = 0,
  TOKEN_EOF,
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_VARIABLE,
  TOKEN_LET,
  TOKEN_PRINT,
  TOKEN_IF,
  TOKEN_THEN,
  TOKEN_ELSE,
  TOKEN_FOR,
  TOKEN_TO,
  TOKEN_NEXT,
  TOKEN_GOTO,
  TOKEN_GOSUB,
  TOKEN_RETURN,
  TOKEN_PEEK,
  TOKEN_POKE,
  TOKEN_END,
  TOKEN_REM,
  TOKEN_CR,
  TOKEN_COMMA,
  TOKEN_SEMICOLON,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_MUL,
  TOKEN_DIV,
  TOKEN_MOD,
  TOKEN_EQ,
  TOKEN_LT,
  TOKEN_GT,
  TOKEN_LE,
  TOKEN_GE,
  TOKEN_NE,
  TOKEN_LPAREN,
  TOKEN_RPAREN
};

static const char *prog_ptr;
static const char *cur_ptr;
static int cur_token;
static int cur_num;
static char cur_var;
static char cur_str[64];

static int variables[MAX_VARNUM];

static const char *gosub_stack[MAX_GOSUB_STACK];
static int gosub_stack_ptr;

struct for_state {
  char var;
  int to;
  const char *step_ptr;
};
static struct for_state for_stack[MAX_FOR_STACK];
static int for_stack_ptr;

static int is_finished;
static ubasic_output_fn out_fn = NULL;

static void statement(void);
static int expr(void);

void ubasic_set_output(ubasic_output_fn fn) { out_fn = fn; }

static void ub_print(const char *str) {
  if (out_fn) {
    out_fn(str);
  }
}

/* Tokenizer */
static int next_token(void) {
  while (*cur_ptr == ' ' || *cur_ptr == '\t')
    cur_ptr++;

  if (*cur_ptr == '\0')
    return (cur_token = TOKEN_EOF);
  if (*cur_ptr == '\n' || *cur_ptr == '\r') {
    while (*cur_ptr == '\n' || *cur_ptr == '\r')
      cur_ptr++;
    return (cur_token = TOKEN_CR);
  }

  if (isdigit((int)*cur_ptr)) {
    cur_num = 0;
    while (isdigit((int)*cur_ptr)) {
      cur_num = cur_num * 10 + (*cur_ptr - '0');
      cur_ptr++;
    }
    return (cur_token = TOKEN_NUMBER);
  }

  if (*cur_ptr == '"') {
    cur_ptr++;
    int i = 0;
    while (*cur_ptr != '"' && *cur_ptr != '\0' && *cur_ptr != '\n') {
      if (i < sizeof(cur_str) - 1)
        cur_str[i++] = *cur_ptr;
      cur_ptr++;
    }
    if (*cur_ptr == '"')
      cur_ptr++;
    cur_str[i] = '\0';
    return (cur_token = TOKEN_STRING);
  }

  if (strncmp(cur_ptr, "PRINT", 5) == 0 && !isalnum((int)cur_ptr[5])) {
    cur_ptr += 5;
    return (cur_token = TOKEN_PRINT);
  }
  if (strncmp(cur_ptr, "LET", 3) == 0 && !isalnum((int)cur_ptr[3])) {
    cur_ptr += 3;
    return (cur_token = TOKEN_LET);
  }
  if (strncmp(cur_ptr, "IF", 2) == 0 && !isalnum((int)cur_ptr[2])) {
    cur_ptr += 2;
    return (cur_token = TOKEN_IF);
  }
  if (strncmp(cur_ptr, "THEN", 4) == 0 && !isalnum((int)cur_ptr[4])) {
    cur_ptr += 4;
    return (cur_token = TOKEN_THEN);
  }
  if (strncmp(cur_ptr, "ELSE", 4) == 0 && !isalnum((int)cur_ptr[4])) {
    cur_ptr += 4;
    return (cur_token = TOKEN_ELSE);
  }
  if (strncmp(cur_ptr, "FOR", 3) == 0 && !isalnum((int)cur_ptr[3])) {
    cur_ptr += 3;
    return (cur_token = TOKEN_FOR);
  }
  if (strncmp(cur_ptr, "TO", 2) == 0 && !isalnum((int)cur_ptr[2])) {
    cur_ptr += 2;
    return (cur_token = TOKEN_TO);
  }
  if (strncmp(cur_ptr, "NEXT", 4) == 0 && !isalnum((int)cur_ptr[4])) {
    cur_ptr += 4;
    return (cur_token = TOKEN_NEXT);
  }
  if (strncmp(cur_ptr, "GOTO", 4) == 0 && !isalnum((int)cur_ptr[4])) {
    cur_ptr += 4;
    return (cur_token = TOKEN_GOTO);
  }
  if (strncmp(cur_ptr, "GOSUB", 5) == 0 && !isalnum((int)cur_ptr[5])) {
    cur_ptr += 5;
    return (cur_token = TOKEN_GOSUB);
  }
  if (strncmp(cur_ptr, "RETURN", 6) == 0 && !isalnum((int)cur_ptr[6])) {
    cur_ptr += 6;
    return (cur_token = TOKEN_RETURN);
  }
  if (strncmp(cur_ptr, "PEEK", 4) == 0 && !isalnum((int)cur_ptr[4])) {
    cur_ptr += 4;
    return (cur_token = TOKEN_PEEK);
  }
  if (strncmp(cur_ptr, "POKE", 4) == 0 && !isalnum((int)cur_ptr[4])) {
    cur_ptr += 4;
    return (cur_token = TOKEN_POKE);
  }
  if (strncmp(cur_ptr, "END", 3) == 0 && !isalnum((int)cur_ptr[3])) {
    cur_ptr += 3;
    return (cur_token = TOKEN_END);
  }
  if (strncmp(cur_ptr, "REM", 3) == 0 && !isalnum((int)cur_ptr[3])) {
    while (*cur_ptr != '\n' && *cur_ptr != '\r' && *cur_ptr != '\0')
      cur_ptr++;
    return (cur_token = TOKEN_REM);
  }

  if (isalpha((int)*cur_ptr)) {
    cur_var = tolower((int)*cur_ptr) - 'a';
    cur_ptr++;
    return (cur_token = TOKEN_VARIABLE);
  }

  if (*cur_ptr == '+') {
    cur_ptr++;
    return (cur_token = TOKEN_PLUS);
  }
  if (*cur_ptr == '-') {
    cur_ptr++;
    return (cur_token = TOKEN_MINUS);
  }
  if (*cur_ptr == '*') {
    cur_ptr++;
    return (cur_token = TOKEN_MUL);
  }
  if (*cur_ptr == '/') {
    cur_ptr++;
    return (cur_token = TOKEN_DIV);
  }
  if (*cur_ptr == '%') {
    cur_ptr++;
    return (cur_token = TOKEN_MOD);
  }
  if (*cur_ptr == '(') {
    cur_ptr++;
    return (cur_token = TOKEN_LPAREN);
  }
  if (*cur_ptr == ')') {
    cur_ptr++;
    return (cur_token = TOKEN_RPAREN);
  }
  if (*cur_ptr == ',') {
    cur_ptr++;
    return (cur_token = TOKEN_COMMA);
  }
  if (*cur_ptr == ';') {
    cur_ptr++;
    return (cur_token = TOKEN_SEMICOLON);
  }
  if (*cur_ptr == '=') {
    cur_ptr++;
    return (cur_token = TOKEN_EQ);
  }
  if (*cur_ptr == '<') {
    cur_ptr++;
    if (*cur_ptr == '=') {
      cur_ptr++;
      return (cur_token = TOKEN_LE);
    }
    if (*cur_ptr == '>') {
      cur_ptr++;
      return (cur_token = TOKEN_NE);
    }
    return (cur_token = TOKEN_LT);
  }
  if (*cur_ptr == '>') {
    cur_ptr++;
    if (*cur_ptr == '=') {
      cur_ptr++;
      return (cur_token = TOKEN_GE);
    }
    return (cur_token = TOKEN_GT);
  }

  cur_ptr++;
  return (cur_token = TOKEN_ERROR);
}

/* Recursive Descent Expression Parser */
static int primary(void) {
  int val = 0;
  if (cur_token == TOKEN_NUMBER) {
    val = cur_num;
    next_token();
  } else if (cur_token == TOKEN_VARIABLE) {
    val = variables[(int)cur_var];
    next_token();
  } else if (cur_token == TOKEN_PEEK) {
    next_token();
    int addr = primary();
    val = *(volatile uint8_t *)(uintptr_t)addr;
  } else if (cur_token == TOKEN_LPAREN) {
    next_token();
    val = expr();
    if (cur_token == TOKEN_RPAREN)
      next_token();
  }
  return val;
}

static int term(void) {
  int val = primary();
  while (cur_token == TOKEN_MUL || cur_token == TOKEN_DIV ||
         cur_token == TOKEN_MOD) {
    int op = cur_token;
    next_token();
    int val2 = primary();
    if (op == TOKEN_MUL)
      val *= val2;
    else if (op == TOKEN_DIV)
      val = (val2 != 0) ? (val / val2) : 0;
    else if (op == TOKEN_MOD)
      val = (val2 != 0) ? (val % val2) : 0;
  }
  return val;
}

static int add_expr(void) {
  int val = term();
  while (cur_token == TOKEN_PLUS || cur_token == TOKEN_MINUS) {
    int op = cur_token;
    next_token();
    int val2 = term();
    if (op == TOKEN_PLUS)
      val += val2;
    else
      val -= val2;
  }
  return val;
}

static int expr(void) {
  int val = add_expr();
  while (cur_token >= TOKEN_EQ && cur_token <= TOKEN_NE) {
    int op = cur_token;
    next_token();
    int val2 = add_expr();
    if (op == TOKEN_EQ)
      val = (val == val2);
    else if (op == TOKEN_LT)
      val = (val < val2);
    else if (op == TOKEN_GT)
      val = (val > val2);
    else if (op == TOKEN_LE)
      val = (val <= val2);
    else if (op == TOKEN_GE)
      val = (val >= val2);
    else if (op == TOKEN_NE)
      val = (val != val2);
  }
  return val;
}

/* Find Line Number in Program */
static const char *find_line(int linenum) {
  const char *p = prog_ptr;
  while (*p != '\0') {
    while (*p == ' ' || *p == '\t')
      p++;
    if (isdigit((int)*p)) {
      int num = atoi(p);
      if (num == linenum)
        return p;
    }
    while (*p != '\n' && *p != '\0')
      p++;
    if (*p == '\n')
      p++;
  }
  return NULL;
}

/* Statement Executor */
static void statement(void) {
  if (cur_token == TOKEN_NUMBER) {
    /* Skip line number */
    next_token();
  }

  if (cur_token == TOKEN_PRINT) {
    char outbuf[64];
    next_token();
    while (cur_token != TOKEN_CR && cur_token != TOKEN_EOF) {
      if (cur_token == TOKEN_STRING) {
        ub_print(cur_str);
        next_token();
      } else {
        int val = expr();
        snprintf(outbuf, sizeof(outbuf), "%d", val);
        ub_print(outbuf);
      }
      if (cur_token == TOKEN_COMMA) {
        ub_print("\t");
        next_token();
      } else if (cur_token == TOKEN_SEMICOLON) {
        next_token();
      } else {
        break;
      }
    }
    ub_print("\n");
  } else if (cur_token == TOKEN_LET || cur_token == TOKEN_VARIABLE) {
    if (cur_token == TOKEN_LET)
      next_token();
    if (cur_token == TOKEN_VARIABLE) {
      char v = cur_var;
      next_token();
      if (cur_token == TOKEN_EQ) {
        next_token();
        variables[(int)v] = expr();
      }
    }
  } else if (cur_token == TOKEN_GOTO) {
    next_token();
    int target = expr();
    const char *loc = find_line(target);
    if (loc) {
      cur_ptr = loc;
      next_token();
      return;
    }
  } else if (cur_token == TOKEN_IF) {
    next_token();
    int condition = expr();
    if (cur_token == TOKEN_THEN)
      next_token();
    if (condition) {
      statement();
      return;
    } else {
      while (cur_token != TOKEN_CR && cur_token != TOKEN_EOF)
        next_token();
    }
  } else if (cur_token == TOKEN_FOR) {
    next_token();
    if (cur_token == TOKEN_VARIABLE) {
      char v = cur_var;
      next_token();
      if (cur_token == TOKEN_EQ) {
        next_token();
        variables[(int)v] = expr();
        if (cur_token == TOKEN_TO) {
          next_token();
          int to_val = expr();
          if (for_stack_ptr < MAX_FOR_STACK) {
            for_stack[for_stack_ptr].var = v;
            for_stack[for_stack_ptr].to = to_val;
            for_stack[for_stack_ptr].step_ptr = cur_ptr;
            for_stack_ptr++;
          }
        }
      }
    }
  } else if (cur_token == TOKEN_NEXT) {
    next_token();
    if (for_stack_ptr > 0) {
      struct for_state *f = &for_stack[for_stack_ptr - 1];
      variables[(int)f->var]++;
      if (variables[(int)f->var] <= f->to) {
        cur_ptr = f->step_ptr;
        next_token();
        return;
      } else {
        for_stack_ptr--;
      }
    }
  } else if (cur_token == TOKEN_GOSUB) {
    next_token();
    int target = expr();
    const char *loc = find_line(target);
    if (loc && gosub_stack_ptr < MAX_GOSUB_STACK) {
      gosub_stack[gosub_stack_ptr++] = cur_ptr;
      cur_ptr = loc;
      next_token();
      return;
    }
  } else if (cur_token == TOKEN_RETURN) {
    next_token();
    if (gosub_stack_ptr > 0) {
      cur_ptr = gosub_stack[--gosub_stack_ptr];
      next_token();
      return;
    }
  } else if (cur_token == TOKEN_POKE) {
    next_token();
    int addr = expr();
    if (cur_token == TOKEN_COMMA)
      next_token();
    int val = expr();
    *(volatile uint8_t *)(uintptr_t)addr = (uint8_t)val;
  } else if (cur_token == TOKEN_END) {
    is_finished = 1;
    return;
  }

  while (cur_token != TOKEN_CR && cur_token != TOKEN_EOF) {
    next_token();
  }
}

void ubasic_init(const char *program) {
  prog_ptr = program;
  cur_ptr = program;
  gosub_stack_ptr = 0;
  for_stack_ptr = 0;
  is_finished = 0;
  memset(variables, 0, sizeof(variables));
  next_token();
}

void ubasic_run(void) {
  if (cur_token != TOKEN_EOF && !is_finished) {
    statement();
    if (cur_token == TOKEN_CR)
      next_token();
  } else {
    is_finished = 1;
  }
}

int ubasic_finished(void) { return is_finished || cur_token == TOKEN_EOF; }