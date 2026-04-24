#include <unistd.h>
#include <climits>

int printer(unsigned long long n)
{
    char buf[24]; int i = sizeof(buf) - 1;

    if (n == 0)
    {
        buf[--i] = '0';
    }
    else
    {
        if (n < 0)
        {
            // out of task bounds
            return -1;
        }
        while (n != 0)
        {
            buf[--i] = '0' + (n % 10);
            n /= 10;
        }
    }

    int last = sizeof(buf) - 1;
    write(STDOUT_FILENO, buf + i, last - i);
    
    return 1;
}

int main ()
{
    char buf[32];
    auto sz = read(STDIN_FILENO, buf, sizeof(buf) - 1);
    if (sz <= 0) return 1;

    buf[sz] = '\0';

    unsigned long long n{}; int i{};
    while (buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\t') i++;
    if (buf[i] == '-') return 1;
    while (buf[i] >= '0' && buf[i] <= '9')
    {
        if (n > (ULLONG_MAX - (buf[i] - '0')) / 10) return 1; // out of ull bounds

        n = n * 10 + (buf[i] - '0');
        ++i;
    }

    printer(n);

    while(n != 1)
    {
        write(STDOUT_FILENO, " ", 1);
        n = (n % 2 == 0)? n / 2: n * 3 + 1;
        printer(n);
    }
}