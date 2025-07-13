#include "ast.h"

// wrapper for project specific matrix handling
void	print_string_matrix(char **matrix)
{
	size_t	i;

	if (!matrix)
	{
		printf("(null matrix)\n");
		return ;
	}
	i = 0;
	while (matrix[i])
	{
		printf("[%zu]: \"%s\"\n", i, matrix[i]);
		i++;
	}
}
