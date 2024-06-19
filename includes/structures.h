/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:08:04 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/14 19:49:15 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_rule
{
	ADD,
	GET,
	QUOTES,
	NO_QUOTES,
	OLDPWD,
	PWD,
	HOME,
	PREV,
}					t_rule;

typedef enum e_token_tp
{
	APPEND = 1,
	HEREDOC,
	RED_IN,
	RED_OUT,
	PIPE,
	WORD,
	WHITESPACE,
}					t_token_tp;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_redir
{
	t_token_tp		type;
	char			*path;
	struct s_redir	*next;
	struct s_redir	*prev;
}					t_redir;

typedef struct s_cmds
{
	t_redir			*redir;
	char			*env_path;
	char			**cmd_path;
	char			*right_path;
	char			*cmd;
	char			**args;
	int				curr_pipe[2];
	int				prev_pipe[2];
	int				i;
	int				cmd_count;
	int				here_doc_count;
	char			*tmp_file;
	char			*name;
	char			*index;
	int				code_status;
	int				dev_stdin;
	int				dev_stdout;
	int				hd_read;
	int				hd_write;
	int				infile;
	int				outfile;
	pid_t			pid;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}					t_cmds;

typedef struct s_token
{
	t_token_tp		type;
	char			*value;
	int				flag_exp;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_data
{
	int				pidlist[1024];
	int				flag_null_exp;
	char			*input;
	char			**mini_env;
	t_token			*token_list;
	t_cmds			*cmd_list;
	t_env			*env;
	t_env			*env_export;
}					t_data;

#endif
