#include <ncurses.h>
#include <stdio.h>

int input_loop();
int ball_change(int i, int d);
void ball_rocket(int i_ball, int j_ball, int rocket_left, int rocket_right, int score1, int score2);

int main(void) {
    int result;

    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    result = input_loop();
    refresh();
    endwin();
    if (result == 0) return 0;
    printf("Player %d WIN. Congratulation!", result);
    return 0;
}

int input_loop() {
    int rocket_left_i = 11;
    int rocket_right_i = 11;

    int ball_i = 12;
    int ball_j = 41;

    int direction_i = -1;
    int direction_j = 1;

    int score_left = 0;
    int score_right = 0;

    char c = '0';
    double t = 0;

    ball_rocket(ball_i, ball_j, rocket_left_i, rocket_right_i, score_left, score_right);
    while (c != 'Q' && c != 'q') {
        t += 5e-3;
        c = getch();
        if (c == 'a' || c == 'A') {
            if (rocket_left_i > 1) {
                rocket_left_i -= 1;
            }
        } else if (c == 'z' || c == 'Z') {
            if (rocket_left_i < 23) {
                rocket_left_i += 1;
            }
        } else if (c == 'k' || c == 'K') {
            if (rocket_right_i > 1) {
                rocket_right_i -= 1;
            }
        } else if (c == 'm' || c == 'M') {
            if (rocket_right_i < 23) {
                rocket_right_i += 1;
            }
        }

        if (t > 1) {
            t = 0;
            ball_i = ball_change(ball_i, direction_i);
            ball_j = ball_change(ball_j, direction_j);
            if (ball_i == 1 || ball_i == 25) {
                direction_i *= -1;
            }
            if (ball_j == 1) {
                score_right += 1;
                ball_i = rocket_left_i + 1;
                ball_j = 4;
            }
            if (ball_j == 80) {
                score_left += 1;
                ball_i = rocket_right_i + 1;
                ball_j = 77;
            }
            if (ball_j == 77) {
                if (rocket_right_i == ball_i || (rocket_right_i + 1) == ball_i ||
                    (rocket_right_i + 2) == ball_i) {
                    direction_j *= -1;
                } else if (rocket_right_i - 1 == ball_i && direction_i == 1 && direction_j == 1) {
                    direction_i *= -1;
                    direction_j *= -1;
                } else if (rocket_right_i + 3 == ball_i && direction_i == -1 && direction_j == 1) {
                    direction_i *= -1;
                    direction_j *= -1;
                }
            }
            if (ball_j == 4) {
                if (rocket_left_i == ball_i || (rocket_left_i + 1) == ball_i ||
                    (rocket_left_i + 2) == ball_i) {
                    direction_j *= -1;
                } else if (rocket_left_i - 1 == ball_i && direction_i == 1 && direction_j == -1) {
                    direction_i *= -1;
                    direction_j *= -1;
                } else if (rocket_left_i + 3 == ball_i && direction_i == -1 && direction_j == -1) {
                    direction_i *= -1;
                    direction_j *= -1;
                }
            }
        }
        ball_rocket(ball_i, ball_j, rocket_left_i, rocket_right_i, score_left, score_right);
        if (score_left == 21) {
            refresh();
            return 1;
        } else if (score_right == 21) {
            refresh();
            return 2;
        }
    }
    return 0;
}

int ball_change(int i, int d) {
    if (d == -1) {
        i -= 1;
    } else {
        i += 1;
    }
    return i;
}

void ball_rocket(int i_ball, int j_ball, int rocket_left, int rocket_right, int score1, int score2) {
    int a;

    a = 0;
    while (a < 27) {
        int b;

        b = 0;
        while (b < 82) {
            if (a == i_ball && b == j_ball) {
                mvprintw(a, b, "@");
            } else if (a == 0 || a == 26) {
                mvprintw(a, b, "-");

            } else if (b == 0 || b == 81 || b == 40 || b == 41) {
                mvprintw(a, b, "|");
            } else if ((b == 3) && (a == rocket_left || a == rocket_left + 1 || a == rocket_left + 2)) {
                mvprintw(a, b, "|");
            } else if ((b == 78) && (a == rocket_right || a == rocket_right + 1 || a == rocket_right + 2)) {
                mvprintw(a, b, "|");
            } else if (b == 36 && a == 2 && score1 > 9) {
                mvprintw(a, b, "%d", score1);
                b += 1;
            } else if (b == 37 && a == 2 && score1 <= 9) {
                mvprintw(a, b, "%d", score1);
            } else if (b == 44 && a == 2 && score2 > 9) {
                mvprintw(a, b, "%d", score2);
                b += 1;
            } else if (b == 44 && a == 2 && score2 <= 9) {
                mvprintw(a, b, "%d", score2);
            } else if (b == 25 && a == 2) {
                mvprintw(a, b, "Player 1");
                b += 7;
            } else if (b == 50 && a == 2) {
                mvprintw(a, b, "Player 2");
                b += 7;
            } else {
                mvprintw(a, b, " ");
            }
            b += 1;
        }
        refresh();
        a += 1;
    }
    refresh();
    return;
}
