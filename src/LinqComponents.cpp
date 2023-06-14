#include "./headers/LinqComponents.hpp"
#include <iostream>

Flow::Image *LinqComponents::setPageBackground(Flow::Window *window, int page_id, std::string path)
{
    Flow::Image *background = new Flow::Image(window);
    background->setPath(path);
    background->setRelativePosition({0, 0});
    background->setBackground({0, 0, 255, 255});
    background->setRatioDimension({1, 1, 1});
    background->setChildReference(Flow::ReferencePoint::BottomRight);
    background->setParentReference(Flow::ReferencePoint::BottomRight);
    window->addComponent(page_id, background);

    return background;
}

Flow::Image *LinqComponents::createMenuBoard(Flow::Window *window, Flow::Component *parent, std::string title, int page_id)
{
    Flow::Image *spy_board = new Flow::Image(parent);
    spy_board->setPath(LinqComponents::MenuBoardImagePath);
    spy_board->setRelativePosition({0, 0});
    spy_board->setBackground({0, 0, 255, 255});
    spy_board->setDimension({350, 600});
    spy_board->setChildReference(Flow::ReferencePoint::Center);
    spy_board->setParentReference(Flow::ReferencePoint::Center);
    window->addComponent(page_id, spy_board);

    Flow::Text *text = new Flow::Text(spy_board);
    text->setText(title);
    text->loadFont("res/fonts/Old_Standard_TT/OldStandardTT-Regular.ttf", 30);
    text->setRelativePosition({0, 30});
    text->setAutoSize(true);
    text->setBackground({0, 0, 0, 0});
    text->setColor({12, 12, 12, 255});
    text->setChildReference(Flow::ReferencePoint::TopCenter);
    text->setParentReference(Flow::ReferencePoint::TopCenter);
    window->addComponent(page_id, text);

    return spy_board;
}

Flow::Image *LinqComponents::createBoardActionButton(Flow::Window *window, Flow::Component *parent, std::string title, double row_index, int page_id, std::function<void(Flow::Window *, Flow::Component *)> onClick)
{
    std::function<void(Flow::Component *)> onHoverEnter = [](Flow::Component *component)
    { ((Flow::Image *)component)->setPath(LinqComponents::MenuBoardButtonHoverImagePath); };

    std::function<void(Flow::Component *)> onHoverExit = [](Flow::Component *component)
    { ((Flow::Image *)component)->setPath(LinqComponents::MenuBoardButtonImagePath); };

    Flow::Image *create_game_button_frame = new Flow::Image(parent);
    create_game_button_frame->setPath("./res/images/ButtonFrame.png");
    create_game_button_frame->setRelativePosition({0, (int)(25 * row_index)});
    create_game_button_frame->setBackground({0, 0, 255, 255});
    create_game_button_frame->setDimension({300, 50});
    create_game_button_frame->setChildReference(Flow::ReferencePoint::Center);
    create_game_button_frame->setParentReference(Flow::ReferencePoint::Center);
    create_game_button_frame->onClick(onClick);
    create_game_button_frame->onHoverEnter(onHoverEnter);
    create_game_button_frame->onHoverExit(onHoverExit);

    window->addComponent(page_id, create_game_button_frame);

    Flow::Text *create_game_button_text = new Flow::Text(create_game_button_frame);
    create_game_button_text->setText(title);
    create_game_button_text->loadFont("res/fonts/Old_Standard_TT/OldStandardTT-Regular.ttf", 30);
    create_game_button_text->setRelativePosition({0, 0});
    create_game_button_text->setAutoSize(true);
    create_game_button_text->setBackground({0, 0, 0, 0});
    create_game_button_text->setColor({12, 12, 12, 255});
    create_game_button_text->setChildReference(Flow::ReferencePoint::Center);
    create_game_button_text->setParentReference(Flow::ReferencePoint::Center);
    window->addComponent(page_id, create_game_button_text);

    return create_game_button_frame;
}

Flow::Image *LinqComponents::createBoardNavigationButton(Flow::Window *window, Flow::Component *parent, std::string title, double row_index, int page_id, int destination_page_id)
{
    return LinqComponents::createBoardActionButton(window, parent, title, row_index, page_id, [destination_page_id](Flow::Window *window, Flow::Component *component)
                                                   { window->setCurrentPage(destination_page_id); });
}

Flow::Text *LinqComponents::createInputFrame(Flow::Window *window, Flow::Component *parent, std::string title, double row_index, int page_id)
{
    Flow::Image *input_frame = new Flow::Image(parent);
    Flow::Text *input_frame_text = new Flow::Text(input_frame);

    std::function<void(Flow::Component *)> onHoverEnter = [](Flow::Component *component)
    { if (!((Flow::Image *)component)->isFocused()) ((Flow::Image *)component)->setPath(LinqComponents::InputFrameHoverImagePath); };

    std::function<void(Flow::Component *)> onHoverExit = [](Flow::Component *component)
    { if (!((Flow::Image *)component)->isFocused()) ((Flow::Image *)component)->setPath(LinqComponents::InputFrameImagePath); };

    std::function<void(Flow::Component *)> onFocused = [](Flow::Component *component)
    { ((Flow::Image *)component)->setPath(LinqComponents::InputFrameFocusImagePath); };

    std::function<void(Flow::Component *)> onUnfocused = [](Flow::Component *component)
    { ((Flow::Image *)component)->setPath(LinqComponents::InputFrameImagePath); };

    std::function<void(Flow::Window *, Flow::Component *, std::string, Flow::Text * displayer)>
        onWrite = [](Flow::Window *window, Flow::Component *component, std::string text, Flow::Text *displayer)
    {
        if (((Flow::Image *)component)->isFocused())
        {
            std::string output = displayer->getText();
            if (text == "\b")
            {
                if (output.size() > 0)
                    output.pop_back();
            }
            else
            {
                output += text;
            }

            displayer->setText(output);
        }
    };

    // Input frame
    input_frame->setPath(LinqComponents::InputFrameImagePath);
    input_frame->setRelativePosition({0, (int)(25 * row_index)});
    input_frame->setBackground({0, 0, 255, 255});
    input_frame->setDimension({300, 50});
    input_frame->setChildReference(Flow::ReferencePoint::Center);
    input_frame->setParentReference(Flow::ReferencePoint::Center);
    input_frame->onClick([onFocused](Flow::Window *window, Flow::Component *component)
                         { ((Flow::Image *)component)->setFocused(true); onFocused(component); });
    input_frame->onClickOutside([onUnfocused](Flow::Window *window, Flow::Component *component)
                                { ((Flow::Image *)component)->setFocused(false); onUnfocused(component); });
    input_frame->onHoverEnter(onHoverEnter);
    input_frame->onHoverExit(onHoverExit);
    input_frame->onWrite([onWrite, input_frame_text](Flow::Window *window, Flow::Component *component, std::string text)
                         { onWrite(window, component, text, input_frame_text); });

    window->addComponent(page_id, input_frame);

    // Input frame text
    input_frame_text->setText("");
    input_frame_text->loadFont("res/fonts/Old_Standard_TT/OldStandardTT-Regular.ttf", 30);
    input_frame_text->setRelativePosition({0, 0});
    input_frame_text->setAutoSize(true);
    input_frame_text->setBackground({0, 0, 0, 0});
    input_frame_text->setColor({12, 12, 12, 255});
    input_frame_text->setChildReference(Flow::ReferencePoint::Center);
    input_frame_text->setParentReference(Flow::ReferencePoint::Center);
    window->addComponent(page_id, input_frame_text);

    return input_frame_text;
}

Flow::Text *LinqComponents::createTextLine(Flow::Window *window, Flow::Component *parent, std::string text, std::string font_path, int font_size, double row_index, int page_id)
{
    Flow::Text *text_section = new Flow::Text(parent);
    text_section->setText(text);
    text_section->loadFont(font_path, font_size);
    text_section->setRelativePosition({20, 50 + (int)(25 * row_index)});
    text_section->setAutoSize(true);
    text_section->setBackground({0, 0, 0, 0});
    text_section->setColor({12, 12, 12, 255});
    text_section->setChildReference(Flow::ReferencePoint::TopLeft);
    text_section->setParentReference(Flow::ReferencePoint::TopLeft);
    window->addComponent(page_id, text_section);

    return text_section;
}
