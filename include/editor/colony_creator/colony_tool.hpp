#pragma once
#include "GUI/container.hpp"
#include "GUI/button.hpp"
#include "GUI/rounded_rectangle.hpp"
#include "editor/color_picker/color_picker.hpp"


struct ColonyTool : GUI::Container
{
    SPtr<GUI::Container> top_zone;
    SPtr<edtr::ColorPicker> color_picker;

    ColonyTool()
        : GUI::Container(Container::Orientation::Vertical)
    {
        padding = 5.0f;
        size_type.y = GUI::Size::FitContent;

        top_zone = create<GUI::Container>(GUI::Container::Orientation::Horizontal);
        top_zone->size_type.y = GUI::Size::FitContent;
        top_zone->padding = 0.0f;
        this->addItem(top_zone);

        auto color_button = create<GUI::Button>("", [this](){
            this->createColorPicker();
        });
        color_button->setHeight(30.0f);
        color_button->setWidth(30.0f);
        top_zone->addItem(color_button, "colony_color_button");

        auto to_focus_button = create<GUI::Button>("Focus", [](){});
        to_focus_button->setHeight(20.0f);
        to_focus_button->setWidth(40.0f);
        top_zone->addItem(to_focus_button);

        auto remove_button = create<GUI::Button>("Remove", [](){});
        remove_button->setHeight(20.0f);
        remove_button->setWidth(60.0f);
        top_zone->addItem(remove_button, "remove");

        // Create color picker
        color_picker = create<edtr::ColorPicker>();
        color_picker->setHeight(100.0f);
        watch(color_picker, [this](){
            setColor(color_picker->getColor());
        });

        setColor(ColorUtils::getRandomColor());
    }

    void setColor(sf::Color color) const
    {
        top_zone->getByName<GUI::Button>("colony_color_button")->background_color = color;
    }

    void createColorPicker()
    {
        if (getByName<edtr::ColorPicker>("color_picker")) {
            return;
        }

        this->addItem(color_picker, "color_picker");
    }

    void onMouseOut() override
    {
        GUI::Container::removeItem(color_picker);
    }

    void render(sf::RenderTarget& target) override
    {
        auto background = GUI::RoundedRectangle(size, position, 5.0f);
        background.setFillColor(sf::Color(200, 200, 200));
        GUI::Item::draw(target, background);
    }
};