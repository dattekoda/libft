

// calc mpn * val
void	ft_mpn_mul_1(t_mpn *mpn, mp_limb_t val)
{
	mp_size_t	i;
	__uint128_t	p;
	mp_limb_t	carry;

	i = 0;
	carry = 0;
	while (i < mpn->size)
	{
		p = (__uint128_t)mpn->limbs[i] * val + carry;
		mpn->limbs[i] = (mp_limb_t)p;
		carry = (mp_limb_t)(p >> BITS_PER_MP_LIMB);
		i++;
	}
	if (carry != 0)
	{
		mpn->limbs[i] = carry;
		mpn->size++;
	}
}

void	ft_mpn_add_1(t_mpn *mpn, mp_limb_t val)
{
	mp_size_t	i;
	__uint128_t	p;

	i = 0;
	while (i < mpn->size)
	{
		p = (__uint128_t)mpn->limbs[i] + val;
		mpn->limbs[i] = (mp_limb_t)p;
		i++;
	}
	if (val != 0)
	{
		mpn->limbs[i] = val;
		mpn->size++;
	}
}

void	set_tod_num(t_strtod *tod, int low, mp_limb_t mul_val)
{
	if (tod->num.size == 0)
	{
		tod->num.limbs[0] = low;
		tod->num.size = 1;
		return ;
	}
	ft_mpn_mul_1(&tod->num, mul_val);
	ft_mpn_add_1(&tod->num, low);
}

void	str_to_mpn(t_strtod *tod)
{
	mp_limb_t		low;
	int				cnt;
	mp_limb_t		ten_in_limb[MAX_DIG_PER_LIMB + 1];

	tod->cp = tod->start_of_digits;
	low = 0;
	cnt = 0;
	set_ten_in_limb(ten_in_limb);
	while (0 < (tod->dig_no))
	{
		if (cnt == MAX_DIG_PER_LIMB)
		{
			set_tod_num(tod, low, MAX_FAC_PER_LIMB);
			low = 0;
			cnt = 0;
		}
		if (*(tod->cp) == '.')
			tod->cp++;
		if (ft_isdigit(*(tod->cp)))
		{
			low = low * 10 + (*(tod->cp) - '0');
			cnt++;
			(tod->dig_no)--;
		}
		tod->cp++;
	}
	if (0 < cnt)
		set_tod_num(tod, low, ten_in_limb[cnt]);
}