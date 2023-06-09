#include <iostream>
#include "headers/Flow.hpp"
#include "headers/FlowComponents.hpp"

#define MAIN_MENU 0
#define CONNECT_MENU 1
#define CREATE_GAME_MENU 2

void onConnectButtonClick(Flow::Window *window, Flow::Component *component)
{
	window->setCurrentPage(CONNECT_MENU);
}

void onCreateGameButtonClick(Flow::Window *window, Flow::Component *component)
{
	window->setCurrentPage(CREATE_GAME_MENU);
}

void onBackButtonClick(Flow::Window *window, Flow::Component *component)
{
	window->setCurrentPage(MAIN_MENU);
}

void onButtonHoverEnter(Flow::Component *component)
{
	((Flow::Image *)component)->setPath("./res/images/ButtonFrameHover.png");
}

void onButtonHoverExit(Flow::Component *component)
{
	((Flow::Image *)component)->setPath("./res/images/ButtonFrame.png");
}

void onWrite(Flow::Window *window, Flow::Component *component, std::string characters)
{
	if (((Flow::Text *)component)->isFocused() == false)
	{
		return;
	}

	std::string new_text;
	if (characters == "\b")
	{
		if (((Flow::Text *)component)->getText().size() > 1)
		{
			new_text = ((Flow::Text *)component)->getText().substr(0, ((Flow::Text *)component)->getText().size() - 1);
			((Flow::Text *)component)->setText(new_text);
		}
		else
		{
			((Flow::Text *)component)->setText(" ");
		}
	}
	else
	{
		new_text = ((Flow::Text *)component)->getText() + characters;
		((Flow::Text *)component)->setText(new_text);
	}
}

int main(int argc, char *argv[])
{
	Flow::InitializeGUI();

	// *****************
	// * Main Menu Page *
	// *****************
	Flow::Window window;
	window.setBackground({125, 125, 255, 255});
	window.setDimension({800, 800});
	window.setResizable(true);
	window.setTitle("Linq : 1910");

	Flow::Image *background = new Flow::Image(&window);
	background->setPath("./res/images/Background.png");
	background->setRelativePosition({0, 0});
	background->setBackground({0, 0, 255, 255});
	background->setRatioDimension({1, 1, 1});
	background->setChildReference(Flow::ReferencePoint::BottomRight);
	background->setParentReference(Flow::ReferencePoint::BottomRight);

	Flow::Image *spy_board = new Flow::Image(background);
	spy_board->setPath("./res/images/SpyBoard.png");
	spy_board->setRelativePosition({0, 0});
	spy_board->setBackground({0, 0, 255, 255});
	spy_board->setDimension({350, 600});
	spy_board->setChildReference(Flow::ReferencePoint::Center);
	spy_board->setParentReference(Flow::ReferencePoint::Center);

	Flow::Text *text = new Flow::Text(spy_board);
	text->setText("Linq : 1910");
	text->loadFont("res/fonts/Old_Standard_TT/OldStandardTT-Regular.ttf", 30);
	text->setRelativePosition({0, 30});
	text->setAutoSize(true);
	text->setBackground({0, 0, 0, 0});
	text->setColor({12, 12, 12, 255});
	text->setChildReference(Flow::ReferencePoint::TopCenter);
	text->setParentReference(Flow::ReferencePoint::TopCenter);

	Flow::Image *create_game_button_frame = new Flow::Image(spy_board);
	create_game_button_frame->setPath("./res/images/ButtonFrame.png");
	create_game_button_frame->setRelativePosition({0, -25});
	create_game_button_frame->setBackground({0, 0, 255, 255});
	create_game_button_frame->setDimension({300, 50});
	create_game_button_frame->setChildReference(Flow::ReferencePoint::Center);
	create_game_button_frame->setParentReference(Flow::ReferencePoint::Center);
	create_game_button_frame->onClick(onCreateGameButtonClick);
	create_game_button_frame->onHoverEnter(onButtonHoverEnter);
	create_game_button_frame->onHoverExit(onButtonHoverExit);

	Flow::Text *create_game_button_text = new Flow::Text(create_game_button_frame);
	create_game_button_text->setText("Create Game");
	create_game_button_text->loadFont("res/fonts/Old_Standard_TT/OldStandardTT-Regular.ttf", 30);
	create_game_button_text->setRelativePosition({0, 0});
	create_game_button_text->setAutoSize(true);
	create_game_button_text->setBackground({0, 0, 0, 0});
	create_game_button_text->setColor({12, 12, 12, 255});
	create_game_button_text->setChildReference(Flow::ReferencePoint::Center);
	create_game_button_text->setParentReference(Flow::ReferencePoint::Center);

	Flow::Image *connect_button_frame = new Flow::Image(spy_board);
	connect_button_frame->setPath("./res/images/ButtonFrame.png");
	connect_button_frame->setRelativePosition({0, 35});
	connect_button_frame->setBackground({0, 0, 255, 255});
	connect_button_frame->setDimension({300, 50});
	connect_button_frame->setChildReference(Flow::ReferencePoint::Center);
	connect_button_frame->setParentReference(Flow::ReferencePoint::Center);
	connect_button_frame->onClick(onConnectButtonClick);
	connect_button_frame->onHoverEnter(onButtonHoverEnter);
	connect_button_frame->onHoverExit(onButtonHoverExit);

	Flow::Text *connect_button_text = new Flow::Text(connect_button_frame);
	connect_button_text->setText("Connect");
	connect_button_text->loadFont("res/fonts/Old_Standard_TT/OldStandardTT-Regular.ttf", 30);
	connect_button_text->setRelativePosition({0, 0});
	connect_button_text->setAutoSize(true);
	connect_button_text->setBackground({0, 0, 0, 0});
	connect_button_text->setColor({12, 12, 12, 255});
	connect_button_text->setChildReference(Flow::ReferencePoint::Center);
	connect_button_text->setParentReference(Flow::ReferencePoint::Center);
	connect_button_text->onWrite(onWrite);

	// *****************
	// * Create Game Page *
	// *****************

	Flow::Image *create_game_background = new Flow::Image(&window);
	create_game_background->setPath("./res/images/Background.png");
	create_game_background->setRelativePosition({0, 0});
	create_game_background->setBackground({0, 0, 255, 255});
	create_game_background->setRatioDimension({1, 1, 1});
	create_game_background->setChildReference(Flow::ReferencePoint::BottomRight);
	create_game_background->setParentReference(Flow::ReferencePoint::BottomRight);

	Flow::Image *create_game_spy_board = new Flow::Image(create_game_background);
	create_game_spy_board->setPath("./res/images/SpyBoard.png");
	create_game_spy_board->setRelativePosition({0, 0});
	create_game_spy_board->setBackground({0, 0, 255, 255});
	create_game_spy_board->setDimension({350, 600});
	create_game_spy_board->setChildReference(Flow::ReferencePoint::Center);
	create_game_spy_board->setParentReference(Flow::ReferencePoint::Center);

	Flow::Text *create_game_text = new Flow::Text(create_game_spy_board);
	create_game_text->setText("Create Game");
	create_game_text->loadFont("res/fonts/Old_Standard_TT/OldStandardTT-Regular.ttf", 30);
	create_game_text->setRelativePosition({0, 30});
	create_game_text->setAutoSize(true);
	create_game_text->setBackground({0, 0, 0, 0});
	create_game_text->setColor({12, 12, 12, 255});
	create_game_text->setChildReference(Flow::ReferencePoint::TopCenter);
	create_game_text->setParentReference(Flow::ReferencePoint::TopCenter);

	Flow::Image *return_button_frame = new Flow::Image(create_game_spy_board);
	return_button_frame->setPath("./res/images/ButtonFrame.png");
	return_button_frame->setRelativePosition({0, -30});
	return_button_frame->setBackground({0, 0, 255, 255});
	return_button_frame->setDimension({300, 50});
	return_button_frame->setChildReference(Flow::ReferencePoint::BottomCenter);
	return_button_frame->setParentReference(Flow::ReferencePoint::BottomCenter);
	return_button_frame->onClick(onBackButtonClick);
	return_button_frame->onHoverEnter(onButtonHoverEnter);
	return_button_frame->onHoverExit(onButtonHoverExit);

	Flow::Text *return_button_text = new Flow::Text(return_button_frame);
	return_button_text->setText("Return");
	return_button_text->loadFont("res/fonts/Old_Standard_TT/OldStandardTT-Regular.ttf", 30);
	return_button_text->setRelativePosition({0, 0});
	return_button_text->setAutoSize(true);
	return_button_text->setBackground({0, 0, 0, 0});
	return_button_text->setColor({12, 12, 12, 255});
	return_button_text->setChildReference(Flow::ReferencePoint::Center);
	return_button_text->setParentReference(Flow::ReferencePoint::Center);
	return_button_text->onWrite(onWrite);

	// *****************
	// * Connect Page *
	// *****************

	// Main Menu
	window.addComponent(MAIN_MENU, 0, background);
	window.addComponent(MAIN_MENU, 1, spy_board);
	window.addComponent(MAIN_MENU, 2, text);
	window.addComponent(MAIN_MENU, 3, create_game_button_frame);
	window.addComponent(MAIN_MENU, 4, create_game_button_text);
	window.addComponent(MAIN_MENU, 5, connect_button_frame);
	window.addComponent(MAIN_MENU, 6, connect_button_text);

	// Create Game
	window.addComponent(CREATE_GAME_MENU, 7, create_game_background);
	window.addComponent(CREATE_GAME_MENU, 8, create_game_spy_board);
	window.addComponent(CREATE_GAME_MENU, 9, create_game_text);
	window.addComponent(CREATE_GAME_MENU, 10, return_button_frame);
	window.addComponent(CREATE_GAME_MENU, 11, return_button_text);

	window.setCurrentPage(MAIN_MENU);

	window.mainLoop();
	return 0;
}