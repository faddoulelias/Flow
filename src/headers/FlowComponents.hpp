#pragma once
#include <functional>
#include "Flow.hpp"

namespace Flow
{
    typedef std::function<void(Window *)> RenderFunction;
    typedef std::function<void(Window *, Component *)> ClickEventFunction;
    typedef std::function<void(Component *)> HoverFunction;

    struct RatioDimension
    {
        bool is_ratio;
        float width;
        float height;
    };

    class ObjectComponent : public Component
    {
    protected:
        Component *parent;
        Position relative_position;
        RatioDimension ratio_dimension;
        ReferencePoint parent_reference;
        ReferencePoint child_reference;
        ClickEventFunction on_click;
        HoverFunction on_hover_enter;
        HoverFunction on_hover_exit;
        bool hovered;

    public:
        ObjectComponent(Component *parent);
        ~ObjectComponent() = default;

        virtual void render(Window *window) = 0;

        Component *getParent();
        void setParent(Component *parent);

        Position getRelativePosition();
        void setRelativePosition(Position relative_position);

        ReferencePoint getParentReference();
        void setParentReference(ReferencePoint parent_reference);

        ReferencePoint getChildReference();
        void setChildReference(ReferencePoint child_reference);

        RatioDimension getRatioDimension();
        void setRatioDimension(RatioDimension relative_dimension);

        bool isHovered();
        void onHoverEnter(HoverFunction on_hover_enter);
        void onHoverExit(HoverFunction on_hover_exit);

        bool isClickable();

        void onClick(ClickEventFunction on_click);
        void handleOnClick(Window *window);
    };

    class Frame : public ObjectComponent
    {
    public:
        Frame(Component *parent);
        ~Frame() = default;
        void render(Window *window) override;
    };

    class Text : public ObjectComponent
    {
    private:
        std::string text;
        int font_size;
        bool auto_size;
        Color color;
        std::string path;
        void *font;

    public:
        Text(Component *parent);
        ~Text() = default;

        std::string getText();
        void setText(std::string text);

        Color getColor();
        void setColor(Color color);

        bool isAutoSize();
        void setAutoSize(bool auto_size);

        void loadFont(std::string path, int font_size);

        void render(Window *window) override;
    };

    class Image : public ObjectComponent
    {
    private:
        std::string path;
        void *image;

    public:
        Image(Component *parent);
        ~Image() = default;

        std::string getPath();
        void setPath(std::string path);

        void render(Window *window) override;
    };
};