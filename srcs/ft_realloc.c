
static void	*ft_realloc(void *ptr, size_t old_sz, size_t new_sz)
{
	void *newp; 

	if (new_sz == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_sz));
	newp = malloc(new_sz);
	if (!newp)
		return (NULL);
	if (old_sz > new_sz)
		old_sz = new_sz;
	ft_memcpy(newp, ptr, old_sz);
	free(ptr);
	return (newp);
}