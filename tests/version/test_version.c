/* ************************************************************************** */
/*                                                                            */
/*                                                 _______ _______ _____      */
/*   test_version.c                               |    |  |   |   |     |_    */
/*                                                |       |       |       |   */
/*   By: stales <stales@numlog.fr>                |__|____|__|_|__|_______|   */
/*                                                                            */
/*   Created: 2025/04/01 09:07:09 by stales           NumLog - CopyRight      */
/*   Updated: 2025/04/01 09:07:11 by stales              1993-2025            */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libjson.h"

int	main(void)
{
	puts(libjson_version());
	return (0);
}
