void    ft_swap(int *elem1, int *elem2)
{
    int tmp;

    tmp = *elem1;
    *elem1 = *elem2;
    *elem2 = tmp;
}