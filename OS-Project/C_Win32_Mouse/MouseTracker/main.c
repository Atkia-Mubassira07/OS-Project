#include <windows.h>
#include <stdio.h>

int main() {
    POINT pt;
    while (1) {
        if (GetCursorPos(&pt)) {
            printf("%ld,%ld\n", pt.x, pt.y);
        }
        Sleep(50);
    }
    return 0;
}
