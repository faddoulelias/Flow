#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "headers/Flow.hpp"
#include "headers/FlowComponents.hpp"

using namespace std;
using namespace Flow;

Position computePosition(Dimension parent_dimension, Dimension child_dimension, Position relative_position, Position parent_position, ReferencePoint parent_reference, ReferencePoint child_reference)
{
    Position child_absolute_position = {0, 0};

    if (child_reference == ReferencePoint::Absolute)
    {
        child_absolute_position.x = relative_position.x;
        child_absolute_position.y = relative_position.y;

        return child_absolute_position;
    }

    switch (parent_reference)
    {
    case ReferencePoint::TopLeft:
        child_absolute_position.x = parent_position.x;
        child_absolute_position.y = parent_position.y;
        break;
    case ReferencePoint::TopCenter:
        child_absolute_position.x = parent_position.x + (parent_dimension.width / 2);
        child_absolute_position.y = parent_position.y;
        break;
    case ReferencePoint::TopRight:
        child_absolute_position.x = parent_position.x + parent_dimension.width;
        child_absolute_position.y = parent_position.y;
        break;
    case ReferencePoint::CenterLeft:
        child_absolute_position.x = parent_position.x;
        child_absolute_position.y = parent_position.y + (parent_dimension.height / 2);
        break;
    case ReferencePoint::Center:
        child_absolute_position.x = parent_position.x + (parent_dimension.width / 2);
        child_absolute_position.y = parent_position.y + (parent_dimension.height / 2);
        break;
    case ReferencePoint::CenterRight:
        child_absolute_position.x = parent_position.x + parent_dimension.width;
        child_absolute_position.y = parent_position.y + (parent_dimension.height / 2);
        break;
    case ReferencePoint::BottomLeft:
        child_absolute_position.x = parent_position.x;
        child_absolute_position.y = parent_position.y + parent_dimension.height;
        break;
    case ReferencePoint::BottomCenter:
        child_absolute_position.x = parent_position.x + (parent_dimension.width / 2);
        child_absolute_position.y = parent_position.y + parent_dimension.height;
        break;
    case ReferencePoint::BottomRight:
        child_absolute_position.x = parent_position.x + parent_dimension.width;
        child_absolute_position.y = parent_position.y + parent_dimension.height;
        break;
    default:
        break;
    }

    switch (child_reference)
    {
    case ReferencePoint::TopLeft:
        child_absolute_position.x += relative_position.x;
        child_absolute_position.y += relative_position.y;
        break;
    case ReferencePoint::TopCenter:
        child_absolute_position.x += relative_position.x - (child_dimension.width / 2);
        child_absolute_position.y += relative_position.y;
        break;
    case ReferencePoint::TopRight:
        child_absolute_position.x += relative_position.x - child_dimension.width;
        child_absolute_position.y += relative_position.y;
        break;
    case ReferencePoint::CenterLeft:
        child_absolute_position.x += relative_position.x;
        child_absolute_position.y += relative_position.y - (child_dimension.height / 2);
        break;
    case ReferencePoint::Center:
        child_absolute_position.x += relative_position.x - (child_dimension.width / 2);
        child_absolute_position.y += relative_position.y - (child_dimension.height / 2);
        break;
    case ReferencePoint::CenterRight:
        child_absolute_position.x += relative_position.x - child_dimension.width;
        child_absolute_position.y += relative_position.y - (child_dimension.height / 2);
        break;
    case ReferencePoint::BottomLeft:
        child_absolute_position.x += relative_position.x;
        child_absolute_position.y += relative_position.y - child_dimension.height;
        break;
    case ReferencePoint::BottomCenter:
        child_absolute_position.x += relative_position.x - (child_dimension.width / 2);
        child_absolute_position.y += relative_position.y - child_dimension.height;
        break;
    case ReferencePoint::BottomRight:
        child_absolute_position.x += relative_position.x - child_dimension.width;
        child_absolute_position.y += relative_position.y - child_dimension.height;
        break;
    default:
        break;
    }

    return child_absolute_position;
}

bool isMouseInside(Position object_position, Dimension object_dimension)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    if (mouse_x >= object_position.x && mouse_x <= object_position.x + object_dimension.width && mouse_y >= object_position.y && mouse_y <= object_position.y + object_dimension.height)
    {
        return true;
    }

    return false;
}

/* ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------- ObjectComponent ------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------- */
ObjectComponent::ObjectComponent(Component *parent)
{
    this->parent = parent;
    this->relative_position = {0, 0};
    this->parent_reference = ReferencePoint::TopLeft;
    this->child_reference = ReferencePoint::TopLeft;
    this->ratio_dimension = {0, 0, 0};
    this->on_click = nullptr;
    this->on_hover_enter = nullptr;
    this->on_hover_exit = nullptr;
}

Component *ObjectComponent::getParent()
{
    return parent;
}

void ObjectComponent::setParent(Component *parent)
{
    this->parent = parent;
}

Position ObjectComponent::getRelativePosition()
{
    return relative_position;
}

void ObjectComponent::setRelativePosition(Position relative_position)
{
    this->relative_position = relative_position;
}

ReferencePoint ObjectComponent::getParentReference()
{
    return parent_reference;
}

void ObjectComponent::setParentReference(ReferencePoint parent_reference)
{
    this->parent_reference = parent_reference;
}

ReferencePoint ObjectComponent::getChildReference()
{
    return child_reference;
}

void ObjectComponent::setChildReference(ReferencePoint child_reference)
{
    this->child_reference = child_reference;
}

RatioDimension ObjectComponent::getRatioDimension()
{
    return ratio_dimension;
}

void ObjectComponent::setRatioDimension(RatioDimension relative_dimension)
{
    this->ratio_dimension = relative_dimension;
}

bool ObjectComponent::isHovered()
{
    return hovered;
}

bool ObjectComponent::isClickable()
{
    return (this->on_click != nullptr);
}

void ObjectComponent::onClick(ClickEventFunction on_click)
{
    this->on_click = on_click;
}

void ObjectComponent::handleOnClick(Window *window)
{
    if (on_click != nullptr)
    {
        on_click(window, this);
    }
}

void ObjectComponent::onHoverEnter(HoverFunction on_hover_enter)
{
    this->on_hover_enter = on_hover_enter;
}

void ObjectComponent::onHoverExit(HoverFunction on_hover_exit)
{
    this->on_hover_exit = on_hover_exit;
}

/* ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------ Frame ------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------- */

Frame::Frame(Component *parent) : ObjectComponent(parent)
{
}

void Frame::render(Window *window)
{
    if (this->ratio_dimension.is_ratio == 1)
    {
        Dimension parent_dimension = parent->getDimension();
        Dimension dimension = {(int)(parent_dimension.width * ratio_dimension.width), (int)(parent_dimension.height * ratio_dimension.height)};
        this->setDimension(dimension);
    }

    Position absolute_pos = computePosition(parent->getDimension(), dimension, relative_position, parent->getPosition(), parent_reference, child_reference);

    bool hovered_before = hovered;
    hovered = isMouseInside(absolute_pos, dimension);

    if (hovered && !hovered_before)
    {
        if (on_hover_enter != nullptr)
        {
            on_hover_enter(this);
        }
    }
    else if (!hovered && hovered_before)
    {
        if (on_hover_exit != nullptr)
        {
            on_hover_exit(this);
        }
    }

    SDL_Rect rect;
    rect.x = absolute_pos.x;
    rect.y = absolute_pos.y;
    rect.w = dimension.width;
    rect.h = dimension.height;

    SDL_Renderer *renderer = (SDL_Renderer *)window->getRenderer();

    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    position = absolute_pos;
}

/* ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------ Text ------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------- */

Text::Text(Component *parent) : ObjectComponent(parent)
{
    this->text = "";
    this->color = {0, 0, 0, 255};
    this->auto_size = true;
    this->path = "";
    this->font = nullptr;
    this->font_size = 25;
}

string Text::getText()
{
    return text;
}

void Text::setText(std::string text)
{
    this->text = text;
}

Color Text::getColor()
{
    return color;
}

void Text::setColor(Color color)
{
    this->color = color;
}

bool Text::isAutoSize()
{
    return auto_size;
}

void Text::setAutoSize(bool auto_size)
{
    this->auto_size = auto_size;
}

void Text::loadFont(std::string path, int font_size)
{
    this->path = path;
    this->font_size = font_size;
    this->font = TTF_OpenFont(path.c_str(), font_size);
    if (this->font == nullptr)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
}

void Text::render(Window *window)
{
    if (this->ratio_dimension.is_ratio == 1)
    {
        Dimension parent_dimension = parent->getDimension();
        Dimension dimension = {(int)(parent_dimension.width * ratio_dimension.width), (int)(parent_dimension.height * ratio_dimension.height)};
        this->setDimension(dimension);
    }

    Position absolute_pos = computePosition(parent->getDimension(), dimension, relative_position, parent->getPosition(), parent_reference, child_reference);

    bool hovered_before = hovered;
    hovered = isMouseInside(absolute_pos, dimension);

    if (hovered && !hovered_before)
    {
        if (on_hover_enter != nullptr)
        {
            on_hover_enter(this);
        }
    }
    else if (!hovered && hovered_before)
    {
        if (on_hover_exit != nullptr)
        {
            on_hover_exit(this);
        }
    }

    SDL_Renderer *renderer = (SDL_Renderer *)window->getRenderer();
    SDL_Color sdl_color = {(Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.a};

    unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface(TTF_RenderText_Blended((TTF_Font *)this->font, text.c_str(), sdl_color), SDL_FreeSurface);
    unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture(SDL_CreateTextureFromSurface(renderer, surface.get()), SDL_DestroyTexture);

    if (auto_size)
    {
        dimension.width = surface->w;
        dimension.height = surface->h;
    }

    SDL_Rect text_rect;
    text_rect.x = absolute_pos.x;
    text_rect.y = absolute_pos.y;
    text_rect.w = dimension.width;
    text_rect.h = dimension.height;

    position = absolute_pos;

    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
    SDL_RenderFillRect(renderer, &text_rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderCopy(renderer, texture.get(), NULL, &text_rect);
}

/* ------------------------------------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------- Image ------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------- */

Image::Image(Component *parent) : ObjectComponent(parent)
{
    this->path = "";
}

string Image::getPath()
{
    return path;
}

void Image::setPath(std::string path)
{
    this->path = path;
    SDL_Surface *image = IMG_Load(path.c_str());
    this->image = image;
}

void Image::render(Window *window)
{
    if (this->ratio_dimension.is_ratio == 1)
    {
        Dimension parent_dimension = parent->getDimension();
        Dimension dimension = {(int)(parent_dimension.width * ratio_dimension.width), (int)(parent_dimension.height * ratio_dimension.height)};
        this->setDimension(dimension);
    }

    Position absolute_pos = computePosition(parent->getDimension(), dimension, relative_position, parent->getPosition(), parent_reference, child_reference);

    bool hovered_before = hovered;
    hovered = isMouseInside(absolute_pos, dimension);

    if (hovered && !hovered_before)
    {
        if (on_hover_enter != nullptr)
        {
            on_hover_enter(this);
        }
    }
    else if (!hovered && hovered_before)
    {
        if (on_hover_exit != nullptr)
        {
            on_hover_exit(this);
        }
    }

    if (image == nullptr)
    {
        cout << "Error loading image : " << IMG_GetError() << endl;
        return;
    }

    unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> image_texture(SDL_CreateTextureFromSurface((SDL_Renderer *)window->getRenderer(), (SDL_Surface *)this->image),
                                                                         SDL_DestroyTexture);
    if (image_texture == nullptr)
    {
        cout << "Error creating texture : " << SDL_GetError() << endl;
        return;
    }

    SDL_Rect image_rect;
    image_rect.x = absolute_pos.x;
    image_rect.y = absolute_pos.y;
    image_rect.w = dimension.width;
    image_rect.h = dimension.height;

    position = absolute_pos;

    SDL_RenderCopy((SDL_Renderer *)window->getRenderer(), image_texture.get(), NULL, &image_rect);
}