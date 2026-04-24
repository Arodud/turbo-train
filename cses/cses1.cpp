#include <unistd.h>
#include <climits>

char u_buf[2048];
int pos = 0;

void flush()
{
    if(pos) write(STDOUT_FILENO, u_buf, pos);
    pos = 0;
}

void put_char(char c)
{
    if (pos == sizeof(u_buf)) flush();
    u_buf[pos++] = c;
}

void print_ull(unsigned long long n)
{
    char buf[24]; int i = sizeof(buf) - 1;

    if (n == 0) buf[--i] = '0';
    else while (n != 0)
    {
        buf[--i] = '0' + (n % 10);
        n /= 10;
    }

    while (buf[i]) put_char(buf[i++]);
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

    print_ull(n);

    while(n != 1)
    {
        put_char(' ');
        n = (n % 2 == 0)? n / 2 : n * 3 + 1;
        print_ull(n);
    }
    flush();
}