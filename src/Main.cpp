#include <iostream>
#include "headers/Flow.hpp"
#include "headers/FlowComponents.hpp"

void onDockClick(Flow::Window *window, Flow::Component *component)
{
	std::cout << "Dock clicked" << std::endl;
}

void onHelloWorldClick(Flow::Window *window, Flow::Component *component)
{
	std::cout << "Hello World clicked" << std::endl;
}

int main(int argc, char *argv[])
{
	Flow::Window window;
	window.setBackground({125, 125, 255, 255});
	window.setDimension({500, 500});
	window.setResizable(true);
	window.setTitle("Testing Flow");

	Flow::Frame *frame = new Flow::Frame(&window);
	frame->setDimension({300, 300});
	frame->setRelativePosition({0, 0});
	frame->setBackground({255, 0, 0, 255});
	frame->setChildReference(Flow::ReferencePoint::Center);
	frame->setParentReference(Flow::ReferencePoint::Center);

	Flow::Text *text = new Flow::Text(frame);
	text->setText("Hello World");
	text->setDimension({100, 100});
	text->setRelativePosition({0, 0});
	text->setBackground({0, 255, 0, 255});
	text->setChildReference(Flow::ReferencePoint::TopLeft);
	text->setParentReference(Flow::ReferencePoint::TopLeft);
	text->onClick(onHelloWorldClick);

	Flow::Image *image = new Flow::Image(frame);
	image->setPath("./res/images/Duck.png");
	image->setRelativePosition({0, 0});
	image->setDimension({125, 62});
	image->setBackground({0, 0, 255, 255});
	image->setChildReference(Flow::ReferencePoint::BottomRight);
	image->setParentReference(Flow::ReferencePoint::BottomRight);
	image->onClick(onDockClick);

	window.addComponent(0, frame);
	window.addComponent(1, text);
	window.addComponent(2, image);
	window.addComponent(-3, frame);

	window.mainLoop();
	return 0;
}