#include "command.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "connection.h"

//Размер целого числа в байтах
const int int_size = 4;

//Список команд сервера
enum class server_command
{
    exit = 0,
    echo = 1,

    search = 0b0001'0000,

    linear_search = 0b0001'0001,
    sentinel_linear_search = 0b0001'0010,
    binary_search = 0b0001'0011,
    linear_search_with_sort = 0b0001'0100,

    sort = 0b0010'0000,

    selection_sort = 0b0010'0001,
    shell_sort = 0b0010'0010
};

void command_exit(int socket)
{
    std::vector<char> message = { char(server_command::exit) };
    send_message(socket, message);

    return;
}

int command_echo(int socket)
{
    //Ввод сообщения от пользователя
    std::string input;
    std::cin >> input;

    //Создаём vector<char> message
    std::vector<char> message = std::vector<char>(input.length() + 1);

    //Записываем сообщение в message
    message[0] = char(server_command::echo);
    for (int i = 0; i < input.length(); i++)
    {
        message[i + 1] = input[i];
    }

    //Отправляем сообщение на сервер
    if (send_message(socket, message) < 0)
    {
        return -1;
    }

    //Очищаем сообщение и принимаем его с сервера
    message.clear();
    if (recieve_message(socket, message) < 0)
    {
        return -1;
    }

    //Выводим полученное сообщение
    std::cout << "[Server] ";
    for (int i = 0; i < message.size(); i++)
    {
        std::cout << message[i];
    }
    std::cout << "\n";

    return 0;
}

int command_search(int socket)
{
    //Ввод метода поиска
    std::string method;
    std::cin >> method;

    //Ввод ключа поиска key
    int key;
    std::cin >> key;

    //Ввод пути файла
    std::string input_file_name;
    std::cin >> input_file_name;

    //Открываем файл
    std::ifstream input_file;
    input_file.open(input_file_name);

    //Проверяем, открылся ли файл
    if(!input_file.is_open())
    {
        std::cout << "[Error] Failed to open file " << input_file_name << "\n";
        return 0;
    }

    //Размер файла
    unsigned int file_size = 0;

    //Вычисляем размер файла
    while(!input_file.eof())
    {
        int b;
        input_file >> b;

        if (input_file.fail())
        {
            std::cout << "[Error] File contains uncorrect data\n";
            return 0;
        }
        file_size++;
    }

    //Возвращаемся к началу файла
    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    //Создаём сообщение message, которое будет передано на сервер
    std::vector<char> message = std::vector<char>(file_size*int_size + 5);

    //Записываем ключ поиска key в message
    message[1] = (key & 0xFF00'0000) >> 24;
    message[2] = (key & 0x00FF'0000) >> 16;
    message[3] = (key & 0x0000'FF00) >> 8;
    message[4] = (key & 0x0000'00FF);
    
    //Записываем массив чисел в message
    for (int i = 0; i < file_size; i++)
    {
        int b;
        input_file >> b;

        message[i*int_size + 5] = (b & 0xFF00'0000) >> 24;
        message[i*int_size + 6] = (b & 0x00FF'0000) >> 16;
        message[i*int_size + 7] = (b & 0x0000'FF00) >> 8;
        message[i*int_size + 8] = (b & 0x0000'00FF);
    }

    //Закрываем файл
    input_file.close();

    //Линейный поиск
    if (method == "linear")
    {
        message[0] = char(server_command::linear_search);
    }
    //Линейный поиск с барьером
    else if (method == "sentinel-linear")
    {
        message[0] = char(server_command::sentinel_linear_search);
    }
    //Бинарный поиск
    else if (method == "binary")
    {
        message[0] = char(server_command::binary_search);
    }
    //Линейный поиск с сортровкой
    else if (method == "sort-linear")
    {
        message[0] = char(server_command::linear_search_with_sort);
    }
    //Неизвестный метод поиска
    else
    {
        std::cout << "[Info] " << method << " is unknown method\n";
        return 0;
    }

    //Отправка сообщения на сервер
    if (send_message(socket, message) < 0)
    {
        return -1;
    }

    //Приём сообщения от сервера
    if (recieve_message(socket, message) < 0)
    {
        return -1;
    }

    unsigned char a1 = (message[0]);
    unsigned char a2 = (message[1]);
    unsigned char a3 = (message[2]);
    unsigned char a4 = (message[3]);
        
    int b = (a1 << 24) | (a2 << 16) | (a3 << 8) | a4;

    if (b == -1)
    {
        std::cout << "[Server] Searching element is out\n";
    }
    else
    {
        std::cout << "[Server] Key of searching element is " << (b+1) << "\n";
    }

    return 0;
}

int command_sort(int socket)
{
    //Ввод метода сортировки
    std::string method;
    std::cin >> method;

    //Ввод пути файла
    std::string input_file_name;
    std::cin >> input_file_name;

    //Открываем файл
    std::ifstream input_file;
    input_file.open(input_file_name);

    //Проверяем, открылся ли файл
    if(!input_file.is_open())
    {
        std::cout << "[Error] Failed to open file " << input_file_name << "\n";
        return 0;
    }

    //Размер файла
    unsigned int file_size = 0;

    //Вычисляем размер файла
    while(!input_file.eof())
    {
        int b;
        input_file >> b;

        if (input_file.fail())
        {
            std::cout << "[Error] File contains uncorrect data\n";
            return 0;
        }
        file_size++;
    }

    //Возвращаемся к началу файла
    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    //Создаём сообщение message, которое будет передано на сервер
    std::vector<char> message = std::vector<char>(file_size*int_size + 1);

    //Записываем массив чисел в message
    for (int i = 0; i < file_size; i++)
    {
        int b;
        input_file >> b;

        message[i*int_size + 1] = (b & 0xFF00'0000) >> 24;
        message[i*int_size + 2] = (b & 0x00FF'0000) >> 16;
        message[i*int_size + 3] = (b & 0x0000'FF00) >> 8;
        message[i*int_size + 4] = (b & 0x0000'00FF);
    }

    //Закрываем файл
    input_file.close();

    //Сортировка выбором
    if (method == "selection")
    {
        message[0] = char(server_command::selection_sort);
    }
    //Сортировка Шелла
    else if (method == "shell")
    {
        message[0] = char(server_command::shell_sort);
    }
    //Неизвестный метод сортировки
    else
    {
        std::cout << "[Info] " << method << " is unknown method\n";
        return 0;
    }

    //Отправка сообщения на сервер
    if (send_message(socket, message) < 0)
    {
        return -1;
    }

    //Приём сообщения от сервера
    if (recieve_message(socket, message) < 0)
    {
        return -1;
    }

    //Ввод пути файла для записи
    std::string output_file_name;
    std::cin >> output_file_name;

    //Открытие файла для записи
    std::ofstream output_file;
    output_file.open(output_file_name);

    //Проверяем, открылся ли файлa
    if (!output_file.is_open())
    {
        std::cout << "[Error] Failed to open file " << output_file_name << "\n";
        return 0;
    }

    //Вывод массива в файл
    unsigned char a1 = (message[0]);
    unsigned char a2 = (message[1]);
    unsigned char a3 = (message[2]);
    unsigned char a4 = (message[3]);
        
    int b = (a1 << 24) | (a2 << 16) | (a3 << 8) | a4;

    output_file << b;

    for (int i = 1; i < (message.size() / int_size); i++)
    {
        a1 = (message[i*int_size]);
        a2 = (message[i*int_size + 1]);
        a3 = (message[i*int_size + 2]);
        a4 = (message[i*int_size + 3]);
        
        b = (a1 << 24) | (a2 << 16) | (a3 << 8) | a4;

        output_file << "\n" << b;
    }

    //Закрываем файл для записи
    output_file.close();    

    std::cout << "[Info] Data has been written to " << output_file_name << "\n";
    return 0;
}

int handle_command(int socket, const std::string& command)
{
    //Выключение клиента
    if (command == "close")
    {
        return -1;
    }
    //Выключение сервера
    else if (command == "exit")
    {
        command_exit(socket);
        return -1;
    }
    //Эхо
    else if (command == "echo")
    {
        return command_echo(socket);
    }
    //Поиск
    else if (command == "search")
    {
        return command_search(socket);
    }
    //Сортировка
    else if (command == "sort")
    {
        return command_sort(socket);
    }
    //Неизвестная команда
    else
    {
        std::cout << "[Info] " << command << " is unknown command\n";
    }

    return 0;
}