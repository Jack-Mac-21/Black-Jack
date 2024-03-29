#include "view.hxx"

using namespace ge211;

View::View(Model const& model)
        : model_(model)
{}

void View::draw(ge211::Sprite_set& set) const
{
    set.add_sprite(hit_button_, hit_pos_,0);
    set.add_sprite(hit_text_, {205,482},1);
    set.add_sprite(stand_button_, stand_pos_, 0);
    set.add_sprite(stand_text_,{493,482},1);

    ge211::Transform transform;
    transform.set_scale(.1893939394);
    ge211::Transform cat_scale;
    cat_scale.set_scale(0.3);

    if (model_.winner() != Model::Player::neither) {
        if(back_color_ == "purple")
            set.add_sprite(go_cats_, {550, 40}, 0, cat_scale);
        set.add_sprite(screen_dimmer_, {0,0}, 10);
        set.add_sprite(theme_change_, {130,350}, 11);
        if (model_.is_user_blackjack() && model_.winner() == Model::Player::user) {
            set.add_sprite(blackjack_text_,
                           {275,190},11);
        }
        if (model_.winner() == Model::Player::user) {
            set.add_sprite(user_win_text_,
                           {295,250},11);
        } else if (model_.winner() == Model::Player::dealer) {
            set.add_sprite(dealer_win_text_,
                           {267,250},11);
        } else {
            set.add_sprite(push_text_,{330,250},11);
        }
    }



    int i = 0;
    if (model_.user_score() != 0) {
        for (const Model::Card& card : model_.get_user_hand_()) {
            for (const View::View_Card& view_card : view_deck_) {
                if (view_card.first == card.first) {
                    set.add_sprite(view_card.second,
                                   {200 + 65 * i,250},i,transform);
                    i++;
                }
            }
        }
    }

    i = 0;

        if (model_.turn() == Model::Player::user) {
            if(back_color_ == "red")
                set.add_sprite(red_back_, {200, 25}, 0, transform);
            if(back_color_ == "blue")
                set.add_sprite(blue_back_, {200, 25}, 0, transform);
            if(back_color_ == "green")
                set.add_sprite(green_back_, {200, 25}, 0, transform);
            if(back_color_ == "purple"){
                set.add_sprite(purple_back_, {200, 25}, 0, transform);
                set.add_sprite(go_cats_, {550, 40}, 0, cat_scale);
            }
            for (const View::View_Card &view_card : view_deck_) {
                if (model_.dealer_score() != 0 && view_card.first == model_.get_dealer_hand_()[1].first) {
                    set.add_sprite(view_card.second,
                                   {200 + 65, 25}, 1, transform);
                    break;
                }
            }
        } else if (model_.dealer_score() != 0) {
            for (const Model::Card &card : model_.get_dealer_hand_()) {
                for (const View::View_Card &view_card : view_deck_) {
                    if (view_card.first == card.first) {
                        set.add_sprite(view_card.second,
                                       {200 + 65 * i, 25}, i, transform);
                        i++;
                    }
                }
            }
        }




    for (const View::Score_Pair& pair : scores_) {
        if (model_.user_score() == pair.first) {
            set.add_sprite(pair.second, {75,308},0);
            break;
        }
    }

    if (model_.turn() == Model::Player::user) {
        for (const View::Score_Pair& pair : scores_) {
            if (model_.dealer_score() != 0 && model_.get_dealer_hand_()[1].second == pair.first) {
                set.add_sprite(pair.second, {75,72},0);
                break;
            }
        }
    } else {
        for (const View::Score_Pair& pair : scores_) {
            if (model_.dealer_score() == pair.first) {
                set.add_sprite(pair.second, {75,72},0);
                break;
            }
        }
    }

}

void View::set_color_choice(std::string color){
    if(color == "red")
        back_color_ = "red";
    if(color == "blue")
        back_color_ = "blue";
    if(color == "purple")
        back_color_ = "purple";
    if(color == "green")
        back_color_ = "green";

}
