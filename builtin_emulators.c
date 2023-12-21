#include "shell.h"

/**
 * _myexit - function that exits the shell
 * @info: Structure containing potential arguments.
 *  Return: exits the shell based on input
 */
int _myexit(info_t *info)
{
	int shellext;

	if (info->argv[1])
	{
		shellext = func_erratoi(info->argv[1]);
		if (shellext == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			func_eputs(info->argv[1]);
			func_eputchar('\n');
			return (1);
		}
		info->err_num = func_erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory
 * @info: arguments structure
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int dir_rn;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			dir_rn =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			dir_rn = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		dir_rn =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		dir_rn = chdir(info->argv[1]);
	if (dir_rn == -1)
	{
		print_error(info, "can't cd to ");
		func_eputs(info->argv[1]), func_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory
 * @info: Structure containing potential arguments. Used to maintain
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
