#include <unordered_set>
#include "client.h"
#ifdef _WIN64
#include <conio.h>
#elif __linux__
#endif


int main() {
    int client_socket = create_socket();
    if (client_socket == -1) {
        return -1;
    }

    connect_to_server(client_socket, "127.0.0.1", 7777);

    bool connect = true;
    while (connect) {
        int data_size = get_data_size(client_socket);
        if (data_size > 0) {
            auto data = receive_package(client_socket, data_size);
            switch (data->flag) {
            case '1': {
                std::cout << data->message << std::endl;
                Package message{ "0", '0' };
                std::cin >> message.flag;
                send_package(client_socket, message);
                break;
            }
            case '2': {
                std::cout << data->message << std::endl;
                break;
            }
            case '3': {
                std::cout << data->message << std::endl;
                Package message{ "0", '0' };
                std::cin >> message.message;
                send_package(client_socket, message);
                break;
            }
            case '4': {
                std::cout << data->message << std::endl;

                char ch;
                Package message{ "0", '0' };
                while (std::cin.get(ch) && ch != '\n');
                std::getline(std::cin, message.message);
                send_package(client_socket, message);
                continue;

            }
            case '5': {
                std::cout << data->message << std::endl;
                connect = false;
                break;
            }
            default: {
                std::cout << "error flag" << std::endl;
            }
            }
        }
    }




    close_socket(client_socket);

#ifdef _WIN64
    _getch();
#elif __linux__
#endif

    return 0;
}