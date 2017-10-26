
void	fill_pixel(char **img, int x, int y, int color)
{
	if (x < WIN_W && y < WIN_H && x >= 0 && y >= 0)
	{
		((int*)*img)[x + (y * WIN_W)] = color;
	}
}


void    put_pxl(t_env *e, int x, int y, unsigned int c)
{
	int    i;

	if (x >= (WIN_W - MINI_MAPW) && y <= (MINI_MAPH))
		return ;

	i = (x * 4) + (y * e->s_line);
	e->pxl[i] = c;
	e->pxl[++i] = c >> 8;
	e->pxl[++i] = c >> 16;
}