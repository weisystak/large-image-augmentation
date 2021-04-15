#include <unistd.h>
#include <pwd.h>
#include <stdio.h>

int main()
{
    struct passwd *pw = getpwuid(getuid());

    const char *homedir = pw->pw_dir;
    printf("%s\n", homedir);
}
