char *alphSort;
char *lenSort;
int word_size;
int word_size1;
int word_size2;
for (int i = 0; i < strlen(param_1) + 1; i++)
{
    if (i == 0 || (param_1[i - 1] == 32 || param_1[i] == 9))
    {
            int j = i;
            int k = 0;
            while (param_1[j - 1] != 32 || param_1[j - 1] != 9)
            {
                j++;
                k++;
            }
        }
    }
}
for (int i = 0; i < strlen(param_1); i++)
{
    if (i == 0 || (param_1[i - 1] == 32 || param_1[i] == 9))
    {
        if (param_1[i] >= 65 && param_1[i] <= 90)
        {
            int j = i;
            int k = 0;
            while (param_1[j - 1] != 32 || param_1[j - 1] != 9)
            {
                upSort[k] = param_1[j];
                j++;
                k++;
            }
        }
    }
}
for (int i = 0; i < strlen(downSort); i++)
{
    int alphLow = 65;
    int alphHi = 97;
    if (i == 0 || (downSort[i - 1] == 32 || downSort[i] == 9))
    {
      if(downsort[i]
    }

    int is_upper(char c)
    {
        return c >= 'A' && c <= 'Z';
    }

    int my_lower(char c)
    {
        if (is_upper(c))
            return c + 32;
        return c;
    }

    int my_is(char c)
    {
        return c == ' ' || c == '\t';
    }

    char *my_strsub(char *s, int start, int end)
    {
        char *res = malloc(end - start + 1);
        int i = 0;
        while (start < end)
            res[i++] = s[start++];
        res[i] = 0;
        return res;
    }

    int cmp_alpha(char *a, char *b)
    {
        while (*a && *b && *a == *b)
        {
            a++;
            b++;
        }
        return my_lower(*a) <= my_lower(*b);
    }

    int cmp_len(char *a, char *b)
    {
        return strlen(a) <= strlen(b);
    }

    void my_sort(char *arr[], int n, int (*cmp)(char *, char *))
    {
        char *tmp;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n - 1; j++)
            {
                if ((*cmp)(arr[j], arr[j + 1]) == 0)
                {
                    tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                }
            }
    }

    char *ord_alphlong(char *s)
    {
        int start = 0, idx = 0;
        char *words[my_strlen(s) / 2 + 1];
        for (int i = 0; s[i]; i++)
        {
            if (!my_is(s[i]) && i > 0 && my_is(s[i - 1]))
                start = i;
            if (my_is(s[i]) && i > 0 && !my_is(s[i - 1]))
                words[idx++] = my_strsub(s, start, i);
            if (!s[i + 1] && !my_is(s[i]))
                words[idx++] = my_strsub(s, start, i + 1);
        }
        my_sort(words, idx, &cmp_alpha);
        my_sort(words, idx, &cmp_len);
        char *res = malloc(100);
        int pushed = 0;
        for (int i = 0; i < idx - 1; i++)
        {
            res[pushed] = *words[i];
            if (my_strlen(&res[pushed]) < my_strlen(&res[pushed + 1]))
            {
                res[pushed] = res[94];
            }
            else
            {
                res[pushed] = res[32];
            }
            pushed++;
        }
        res[pushed] = '\0';
        return res;
    }