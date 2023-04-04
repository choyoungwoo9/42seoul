#include "../include/main.h"

extern int exit_code;

char *make_exit_code(char *str, int index)
{
	char *left_str = ft_substr(str, 0, index);
	char *middle_str = ft_itoa(exit_code);
	char *right_str = ft_substr(str, index + 2, ft_strlen(str)-index-2);
	char *tmp_str = ft_strjoin(left_str, middle_str);
	char *ret_str = ft_strjoin(tmp_str, right_str);

	free(left_str);
	free(middle_str);
	free(right_str);
	free(tmp_str);
	free(str);
	return ret_str;
}

int is_env_var(char *str)
{
	int i = -1;
	if(str[++i] != '$')
		return 0;
	while(str[++i])
	{
		if(ft_isalpha(str[i]) || str[i] == '_')
			return 1;
	}
	return 0;
}
int get_env_var_length(char *str)
{
	int i = 1;
	while(ft_isalpha(str[++i]) || ft_isdigit(str[i]) || str[i] == '_')
	{
	}
	return i - 1;
}

char *change_env_var(char *token, int start, int end, char ***envp)
{
	char *left_str = ft_substr(token, 0, start);
	char *key = ft_substr(token, start+1, end - start);
	char *middle_str = get_env_value(*envp, key);
	if(!middle_str)
		middle_str = "";
	char *right_str = ft_substr(token, end + 1, ft_strlen(token)-end-1);
	char *tmp_str = ft_strjoin(left_str, middle_str);
	char *ret_str = ft_strjoin(tmp_str, right_str);
	free(left_str);
	free(key);
	free(right_str);
	free(tmp_str);
	free(token);
	return ret_str;
}

char *change_single_quote(char *token, int start, int end)
{
	char *left_str = ft_substr(token, 0, start);
	char *middle_str = ft_substr(token, start+1, end-start-1);
	char *right_str = ft_substr(token, end + 1, ft_strlen(token)-end-1);
	char *tmp_str = ft_strjoin(left_str, middle_str);
	char *ret_str = ft_strjoin(tmp_str, right_str);
	free(left_str);
	free(middle_str);
	free(right_str);
	free(tmp_str);
	free(token);
	return ret_str;
}

char *change_double_quote(char *token, int *start, int end, char ***envp)
{
	char *left_str = ft_substr(token, 0, *start);
	char *middle_str = ft_substr(token, *start+1, end-*start-1);
	int i = -1;
	while(middle_str[++i])
	{
		if(middle_str[i] == '$')
		{
			if(middle_str[i+1] == '?')
			{
				middle_str = make_exit_code(middle_str, i);
				i --;
			}
			else if(is_env_var(middle_str + i))
			{
				middle_str = change_env_var(middle_str, i, i + get_env_var_length(middle_str + i), envp);
				i --;
			}
		}
	}
	*start += (ft_strlen(middle_str) - 1);
	char *right_str = ft_substr(token, end + 1, ft_strlen(token)-end-1);
	char *tmp_str = ft_strjoin(left_str, middle_str);
	char *ret_str = ft_strjoin(tmp_str, right_str);

	free(left_str);
	free(middle_str);
	free(right_str);
	free(tmp_str);
	free(token);

	return ret_str;
}

char *token_to_good_token(char *token, char ***envp)
{
	if(!token)
		return NULL;
	int i = -1;
	while(token[++i])
	{
		if(token[i] == 39)
		{
			int j = 1;
			while(token[i + j] != 39)
				j ++;
			token = change_single_quote(token, i, i+j);
			i = i + j - 2;
			if(i == -1)
				continue;
			if(!token[i])
				return token;
			continue;
		}
		if(token[i] == 34)
		{
			int j = 1;
			while(token[i + j] != 34)
				j ++;
			token = change_double_quote(token, &i, i+j, envp);
			if(i == -1)
				continue;
			if(!token[i])
				return token;
			continue;
		}
		if(token[i] == '$')
		{
			if(token[i+1] == '?')
			{
				token = make_exit_code(token, i);
				i --;
			}
			else if(is_env_var(token + i))
			{
				token = change_env_var(token, i, i + get_env_var_length(token + i) , envp);
				i --;
			}
			if(i == -1)
				continue;
			if(!token[i])
				return token;
			continue;
		}
	}
	return token;
}
