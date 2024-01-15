/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exemple.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:02:06 by ael-bako          #+#    #+#             */
/*   Updated: 2023/04/11 03:38:27 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 1024

typedef enum
{
	TOKEN_INVALID,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_BACKGROUND,
	TOKEN_INPUT,
	TOKEN_OUTPUT
} TokenType;

typedef struct
{
	TokenType type;
	char* value;
} Token;

Token* create_token(TokenType type, char* value)
{
	Token* token = (Token*)malloc(sizeof(Token));
	token->type = type;
	token->value = value;
	return token;
}

void destroy_token(Token* token)
{
	if (token == NULL)
	{
		return;
	}
	free(token->value);
	free(token);
}

void print_token(Token* token)
{
	if (token == NULL || !token->value)
	{
		return;
	}
	printf("Token(type=%d, value='%s')\n", token->type, token->value);
}

void destroy_tokens(Token** tokens, int count)
{
	if (tokens == NULL)
	{
		return;
	}
	for (int i = 0; i < count; i++)
	{
		destroy_token(tokens[i]);
	}
	free(tokens);
}

Token** tokenize_input(char* input, int* count)
{
	if (input == NULL || count == NULL)
	{
		return NULL;
	}
	Token** tokens = (Token**)malloc(sizeof(Token*) * MAX_INPUT_SIZE);
	char* token_value = (char*)malloc(sizeof(char) * MAX_INPUT_SIZE);
	int token_count = 0;
	TokenType token_type;
	int token_value_index = 0;
	int input_index = 0;
	int input_length = strlen(input);
	while (input_index < input_length)
	{
		char current_char = input[input_index];
		if (isspace(current_char))
		{
			if (token_value_index > 0)
			{
				token_value[token_value_index] = '\0';
				token_type = TOKEN_WORD;
				if (strcmp(token_value, "|") == 0)
				{
					token_type = TOKEN_PIPE;
				} else if (strcmp(token_value, "&") == 0)
				{
					token_type = TOKEN_BACKGROUND;
				} else if (strcmp(token_value, "<") == 0)
				{
					token_type = TOKEN_INPUT;
				} else if (strcmp(token_value, ">") == 0)
				{
					token_type = TOKEN_OUTPUT;
				}
				tokens[token_count] = create_token(token_type, token_value);
				token_value = (char*)malloc(sizeof(char) * MAX_INPUT_SIZE);
				token_value_index = 0;
				token_count++;
			}
		} else
		{
			token_value[token_value_index] = current_char;
			token_value_index++;
		}
		input_index++;
	}
	// if (token_value_index > 0)
	// {
	// 	token_value[token_value_index] = '\0';
	// 	TokenType token_type = TOKEN_WORD;
	// 	if (strcmp(token_value, "|") == 0)
	// 	{
	// 		token_type = TOKEN_PIPE;
	// 	} else if (strcmp(token_value, "&") == 0)
	// 	{
	// 		token_type = TOKEN_BACKGROUND;
	// 	} else if (strcmp(token_value, "<") == 0)
	// 	{
	// 		token_type = TOKEN_INPUT;
	// 	} else if (strcmp(token_value, ">") == 0)
	// 	{
	// 		token_type = TOKEN_OUTPUT;
	// 	}
	// 	tokens[token_count] = create_token(token_type, token_value);
	// 	token_count++;
	// }
	// free(token_value);
	*count = token_count;
	return tokens;
}

int main()
{
	char input[MAX_INPUT_SIZE];
	while (1)
	{
		printf("$ ");
		fgets(input, MAX_INPUT_SIZE, stdin);
		input[strcspn(input, "\n")] = '\0';
		int token_count;
		// printf("\n::%s::\n",input);
		Token** tokens = tokenize_input(input, &token_count);
		for (int i = 0; i < token_count; i++)
		{
			print_token(tokens[i]);
		}
		destroy_tokens(tokens, token_count);
	}
	return 0;
}


