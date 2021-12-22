#include "pipex.h"

char	*ft_strndup(char *src, int n)
{
	int		i;
	char 	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (n + 1));
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	find_in_env(char **src, char *to_find)
{
	int	i;

	i = 0;
	while (src[i] && ft_strncmp(src[i], to_find, ft_strlen(to_find)))
		i++;
	return (i);
}

int	str_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*create_path(char *path, char *cmd)
{
	int		i;
	int		j;
	char	*dest;

	dest = (char *)malloc(sizeof(char) * str_search(path, '\0') + str_search(cmd, '\0') + 2);
	if (!dest)
		return (NULL);
	i = -1;
	while (path[++i])
		dest[i] = path[i];
	dest[i] = '/';
	i++;
	j = -1;
	while (cmd[++j])
		dest[i + j] = cmd[j];
	dest[i + j] = '\0';
	return (dest);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*dir;
	char	*bin;
	char	*path;

	i = 0;
	i = find_in_env(env, "PATH=");
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && str_search(path, ':') > -1)
	{
		dir = ft_strndup(path, str_search(path, ':'));
		bin = create_path(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += str_search(path, ':') + 1;
	}
	return (cmd);
}
