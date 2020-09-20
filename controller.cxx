#include "controller.hxx"
#include "view.hxx"

using namespace ge211;

Controller::Controller()
        : view_(model_)
{
    model_.deal_cards();
}

void Controller::on_mouse_up(ge211::Mouse_button, ge211::Position pos) {
    if (model_.winner() == Model::Player::neither) {
        if (pos.x >= view_.get_hit_pos().x && pos.y >= view_.get_hit_pos().y
            && pos.x <= view_.get_hit_pos().x + view_.get_hit_dims().width
            && pos.y <= view_.get_hit_pos().y + view_.get_stand_dims().height) {
            model_.user_draw_card();
        }

        if (pos.x >= view_.get_stand_pos().x && pos.y >= view_.get_stand_pos().y
            && pos.x <= view_.get_stand_pos().x + view_.get_stand_dims().width
            && pos.y <= view_.get_stand_pos().y + view_.get_stand_dims().height) {
            model_.dealer_turn();
        }
    }
}

void Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q'))
        quit();
    if (key == ge211::Key::code(' '))
        if (model_.winner() != Model::Player::neither) {
            model_.reset_game();
        }
    if (model_.winner() != Model::Player::neither){
        if (key == ge211::Key::code('b')){
            view_.set_color_choice("blue");
            model_.reset_game();
        }
        if (key == ge211::Key::code('r')){
            view_.set_color_choice("red");
            model_.reset_game();
        }
        if (key == ge211::Key::code('g')){
            view_.set_color_choice("green");
            model_.reset_game();
        }
        if (key == ge211::Key::code('p')){
            view_.set_color_choice("purple");
            model_.reset_game();
        }
    }

}

void Controller::draw(Sprite_set& sprites)
{
    view_.draw(sprites);
    background_color = ge211::Color {0,55,0};
}

Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}