#include <iostream>
#include "headers/Flow.hpp"
#include "headers/FlowComponents.hpp"

void onConnectButtonClick(Flow::Window *window, Flow::Component *component)
{
	std::cout << "Connect button clicked" << std::endl;
}

void onCreateGameButtonClick(Flow::Window *window, Flow::Component *component)
{
	std::cout << "Create Games button clicked" << std::endl;
}

void onConnectButtonHoverEnter(Flow::Component *component)
{
	((Flow::Image *)component)->setPath("./res/images/ButtonFrameHover.png");
}

void onConnectButtonHoverExit(Flow::Component *component)
{
	((Flow::Image *)component)->setPath("./res/images/ButtonFrame.png");
}

int main(int argc, char *argv[])
{
	Flow::InitializeGUI();

	Flow::Window window;
	window.setBackground({125, 125, 255, 255});
	window.setDimension({800, 800});
	window.setResizable(true);
	window.setTitle("Testing Flow");

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
	create_game_button_frame->onHoverEnter(onConnectButtonHoverEnter);
	create_game_button_frame->onHoverExit(onConnectButtonHoverExit);

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
	connect_button_frame->onHoverEnter(onConnectButtonHoverEnter);
	connect_button_frame->onHoverExit(onConnectButtonHoverExit);

	Flow::Text *connect_button_text = new Flow::Text(connect_button_frame);
	connect_button_text->setText("Connect");
	connect_button_text->loadFont("res/fonts/Old_Standard_TT/OldStandardTT-Regular.ttf", 30);
	connect_button_text->setRelativePosition({0, 0});
	connect_button_text->setAutoSize(true);
	connect_button_text->setBackground({0, 0, 0, 0});
	connect_button_text->setColor({12, 12, 12, 255});
	connect_button_text->setChildReference(Flow::ReferencePoint::Center);
	connect_button_text->setParentReference(Flow::ReferencePoint::Center);

	window.addComponent(0, background);
	window.addComponent(1, spy_board);
	window.addComponent(2, text);
	window.addComponent(3, connect_button_frame);
	window.addComponent(4, connect_button_text);
	window.addComponent(5, create_game_button_frame);
	window.addComponent(6, create_game_button_text);

	window.mainLoop();
	return 0;
}