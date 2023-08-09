#include "chat.h"
#include "mysql.h"

int  main()
{
	int server_socket = create_socket();
	if (server_socket == -1) {
		return -1;
	}

	int client_socket = accept_client(server_socket);
	if (client_socket == -1) {
		return -1;
	}

	MYSQL mysql;
	mysql_init(&mysql);

	if (&mysql == NULL) {

		std::cout << "Error: can't create MySQL-descriptor" << std::endl;
	}
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "testdb", 0, NULL, 0)) {
		std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
	}
	else {
		std::cout << "Success!" << std::endl;
	}

	mysql_set_character_set(&mysql, "utf8");
	std::cout << "connection characterset: " << mysql_character_set_name(&mysql) << std::endl;
	mysql_query(&mysql, "CREATE TABLE table_messages(id INT AUTO_INCREMENT PRIMARY KEY, sender VARCHAR(255), receiver VARCHAR(255), sender TEXT)");


	Chat chat; // is_chat_work = false

	chat.start(); // is_chat_work = true

	while (chat.is_chat_work()) {
		chat.show_login_menu(client_socket); // making user login
		while (chat.get_current_user()) {
			chat.show_user_menu(client_socket);
		}
	}

	close_socket(server_socket, client_socket);

	return 0;
}