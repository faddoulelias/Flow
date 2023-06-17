#include <iostream>
#include "./headers/LinqComponents.hpp"

#define MAIN_MENU 0
#define CONNECT_MENU 1
#define CREATE_GAME_MENU 2
#define CONNECTION_LOBBY 3
#define GAME_PAGE 5

int main(int argc, char *argv[])
{
	Flow::InitializeGUI();

	Flow::Window window;
	window.setBackground({125, 125, 255, 255});
	window.setDimension({1400, 800});
	window.setResizable(true);
	window.setTitle("Linq : 1910");

	// *****************
	// * Main Menu Page *
	// *****************
	Flow::Image *main_menu_background = LinqComponents::setPageBackground(&window, MAIN_MENU, LinqComponents::MainBackgroundImagePath);
	Flow::Image *spy_board = LinqComponents::createMenuBoard(&window, main_menu_background, "Linq : 1910", MAIN_MENU);
	LinqComponents::createBoardNavigationButton(&window, spy_board, "Create Game", 1.5, MAIN_MENU, CREATE_GAME_MENU);
	LinqComponents::createBoardNavigationButton(&window, spy_board, "Connect", -1.5, MAIN_MENU, CONNECT_MENU);

	// // *****************
	// * Create Game Page *
	// *****************

	Flow::Image *create_game_background = LinqComponents::setPageBackground(&window, CREATE_GAME_MENU, LinqComponents::MainBackgroundImagePath);
	Flow::Image *create_game_spy_board = LinqComponents::createMenuBoard(&window, create_game_background, "Create Game", CREATE_GAME_MENU);
	Flow::Text *port_input = LinqComponents::createInputFrame(&window, create_game_spy_board, "Server Port", -3, CREATE_GAME_MENU);
	LinqComponents::createBoardNavigationButton(&window, create_game_spy_board, "Back", 0, CREATE_GAME_MENU, MAIN_MENU);
	LinqComponents::createBoardActionButton(&window, create_game_spy_board, "Create", 3, CREATE_GAME_MENU, [port_input](Flow::Window *window, Flow::Component *component)
											{ std::cout << "Creating Game on port " << port_input->getText() << std::endl;
											  window->setCurrentPage(CONNECTION_LOBBY); });

	// *****************
	// * Connect Page *
	// *****************
	Flow::Image *connect_background = LinqComponents::setPageBackground(&window, CONNECT_MENU, LinqComponents::MainBackgroundImagePath);
	Flow::Image *connect_spy_board = LinqComponents::createMenuBoard(&window, connect_background, "Connect", CONNECT_MENU);
	LinqComponents::createBoardNavigationButton(&window, connect_spy_board, "Back", -1.5, CONNECT_MENU, MAIN_MENU);
	LinqComponents::createBoardActionButton(&window, connect_spy_board, "Connect", 1.5, CONNECT_MENU, [](Flow::Window *window, Flow::Component *component)
											{ std::cout << "Connect" << std::endl; });

	// *****************
	// * Waiting for connection Page *
	// *****************
	Flow::Image *waiting_for_connection_background = LinqComponents::setPageBackground(&window, CONNECTION_LOBBY, LinqComponents::MainBackgroundImagePath);
	Flow::Image *waiting_for_connection_spy_board = LinqComponents::createMenuBoard(&window, waiting_for_connection_background, "Game Lobby", CONNECTION_LOBBY);
	LinqComponents::createTextLine(&window, waiting_for_connection_spy_board, "Game open on port ????:", LinqComponents::OldStandardTTBold, 24, 3, CONNECTION_LOBBY);
	LinqComponents::createTextLine(&window, waiting_for_connection_spy_board, "Connected players:", LinqComponents::OldStandardTTBold, 24, 3, CONNECTION_LOBBY);

	// *****************
	// * Game Page *
	// *****************

	Flow::Image *game_background = LinqComponents::setPageBackground(&window, GAME_PAGE, LinqComponents::GameBackgroundImagePath);
	Flow::Image *game_board = LinqComponents::createGameBoard(&window, game_background, "Mira", LinqComponents::Role::Spy, "Pumpkin", GAME_PAGE);

	std::pair<std::string, std::string> selected_spies = {"", ""};

	LinqComponents::createVoteDataSection(
		&window, game_board, GAME_PAGE, true, "Yara", {"Pierre", "Claude", "Elias", "Mira", "Yara"},
		[](std::pair<std::string, std::string> vote)
		{
			std::cout << "Voted " << vote.first << " " << vote.second << std::endl;
		},
		selected_spies,
		LinqComponents::Role::Spy);

	window.setCurrentPage(GAME_PAGE);

	window.mainLoop();
	return 0;
}