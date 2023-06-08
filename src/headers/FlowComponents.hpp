#pragma once
#include <functional>
#include "Flow.hpp"

namespace Flow
{
    typedef std::function<void(Window *)> RenderFunction;
    typedef std::function<void(Window *, Component *)> ClickEventFunction;

    class ObjectComponent : public Component
    {
    protected:
        Component *parent;
        Position relative_position;
        ReferencePoint parent_reference;
        ReferencePoint child_reference;
        ClickEventFunction on_click;
        bool hovered;

    public:
        virtual void
        render(Window *window) = 0;

        Component *getParent();
        void setParent(Component *parent);

        Position getRelativePosition();
        void setRelativePosition(Position relative_position);

        ReferencePoint getParentReference();
        void setParentReference(ReferencePoint parent_reference);

        ReferencePoint getChildReference();
        void setChildReference(ReferencePoint child_reference);

        bool isHovered();
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
        Color color;

    public:
        Text(Component *parent);
        ~Text() = default;

        std::string getText();
        void setText(std::string text);

        Color getColor();
        void setColor(Color color);

        void render(Window *window) override;
    };

    class Image : public ObjectComponent
    {
    private:
        std::string path;

    public:
        Image(Component *parent);
        ~Image() = default;

        std::string getPath();
        void setPath(std::string path);

        void render(Window *window) override;
    };

    // void renderFrame(Window *window, Component *parent, Position position, Dimension dimension, ReferencePoint parent_reference, ReferencePoint child_reference, Color background);
    // void renderText(Window *window, Component *parent, Position position, Dimension dimension, ReferencePoint parent_reference, ReferencePoint child_reference, Color color, std::string text);
    // void renderImage(Window *window, Component *parent, Position position, Dimension dimension, ReferencePoint parent_reference, ReferencePoint child_reference, std::string path);
    // Position computePosition(Dimension parent_dimension, Dimension child_dimension, Position relative_position, Position parent_position, ReferencePoint parent_reference, ReferencePoint child_reference);
};