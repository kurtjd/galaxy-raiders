#include <sstream>
#include "../inc/ScoreDisplay.hpp"
#include "../inc/game.hpp"

ScoreDisplay::ScoreDisplay(const unsigned &score): game_score(score)
{

}

void ScoreDisplay::draw(sf::RenderWindow &window)
{
    std::ostringstream scoreboard;
    scoreboard << "S C O R E <  1  >      H I - S C O R E      SCORE <  2  > ";
    Game::draw_text(window, scoreboard.str(), this->X + 90, this->Y + 20);

    // Draw each digit of the score, with a leading 0 if necessary.
    std::ostringstream score;
    score << (this->game_score / 1000) % 10 << " " << (this->game_score / 100) % 10 << " " << (this->game_score / 10) % 10 << " " << (this->game_score / 1) % 10;
    Game::draw_text(window, score.str(), this->X + 140, this->Y + 60);

    // Draw the hi-score.
    Game::draw_text(window, "0 0 0 0", this->X + 330, this->Y + 60);
}
