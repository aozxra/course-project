#include <iostream>

//Подключаем заголовочный файл с объявлениями взаимодействия клиента и сервера
#include "connection.h"
//Подключаем заголовочный файл с обявлением функции обработки комманд
#include "command.h"

using namespace std;

int main()
{
    int client_socket = connect_to_server();

    if (client_socket < 0)
    {
        return -1;
    }
    
    std::string command;
    std::cin >> command;

    while (handle_command(client_socket, command) == 0)
    {
        std::cin >> command;
    }

    disconnect_from_server(client_socket);
    return 0;
}