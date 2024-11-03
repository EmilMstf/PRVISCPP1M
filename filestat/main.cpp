#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

int main() {
  DIR *dir; // Определяем указатели на структуры для сбора инфы
  struct dirent *entry;
  struct stat fileStat;
  int reg_cnt = 0,  dir_cnt = 0, cd_cnt = 0, bd_cnt = 0, np_cnt = 0, socket_cnt = 0, sl_cnt = 0, unknown_cnt = 0;
  dir = opendir(".");
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    if (stat(entry->d_name, &fileStat) < 0) {
        std::cout << "Не удалось получить информацию о файле" << std::endl;
        continue;
    }
    if (S_ISREG(fileStat.st_mode))
        reg_cnt++;
    else if (S_ISDIR(fileStat.st_mode))
        dir_cnt++;
    else if (S_ISCHR(fileStat.st_mode))
        cd_cnt++;
    else if (S_ISBLK(fileStat.st_mode))
        bd_cnt++;
    else if (S_ISFIFO(fileStat.st_mode))
        np_cnt++;
    else if (S_ISSOCK(fileStat.st_mode))
        socket_cnt++;
    else if (S_ISLNK(fileStat.st_mode))
        sl_cnt++;
    else
        unknown_cnt++;
    }

    closedir(dir);
    if (reg_cnt > 0)
        std::cout << "Обычные файлы: " << reg_cnt << std::endl;
    if (dir_cnt > 0)
        std::cout << "Директории: " << dir_cnt << std::endl;
    if (cd_cnt > 0)
        std::cout << "Символьные устройства: " << cd_cnt << std::endl;
    if (bd_cnt > 0)
        std::cout << "Блочные устройства: " << bd_cnt << std::endl;
    if (np_cnt > 0)
        std::cout << "Именованные каналы: " << np_cnt << std::endl;
    if (socket_cnt > 0)
        std::cout << "Сокеты: " << socket_cnt << std::endl;
    if (sl_cnt > 0)
        std::cout << "Символические ссылки: " << sl_cnt << std::endl;
    if (unknown_cnt > 0)
        std::cout << "Неопознанные: " << unknown_cnt << std::endl;

  return 0;
}