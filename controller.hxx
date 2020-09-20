#pragma once
#include "model.hxx"
#include "view.hxx"

class Controller : public ge211::Abstract_game
{
public:

    explicit Controller();

protected:

    void on_mouse_up(ge211::Mouse_button, ge211::Position) override;

    void on_key(ge211::Key) override;

    void draw(ge211::Sprite_set&) override;

    ge211::Dimensions initial_window_dimensions() const override;


private:

    Model                model_;
    View                 view_;

};