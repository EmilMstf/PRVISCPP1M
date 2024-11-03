#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

const char *hiddenDir = "./.hidden_directory";
char *needHide;

int main(int argc, char *argv[]) {
    struct stat st;
    char hiddenPath[1024];
    if (argc < 2) {
        std::cerr << "Путь к файлу не найден.\n";
        return 1;
    }
    else
    {
        needHide = argv[1];
        if (stat(needHide, &st) != 0) {
            std::cerr << "Файл  " << needHide << " не найден\n";
            return 1;
        }

        if (stat(hiddenDir, &st) != 0) {
            if (mkdir(hiddenDir, 0755) != 0) {
                perror("Не удалось создать скрытый каталог");
                return 1;
            }
        }
        snprintf(hiddenPath, sizeof(hiddenPath), "%s/%s", hiddenDir, needHide);
        if (rename(needHide, hiddenPath) != 0) {
            perror("Не удалось переместить файл");
            return 1;
        }

        if (chmod(hiddenDir, 0111) != 0) {
            perror("Не удалось установить права доступа для скрытого каталога");
            return 1;
        }

        std::cout << "Файл " << needHide << " был скрыт в " << hiddenPath << '\n';
    }
    return 0;
}