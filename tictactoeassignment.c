#include <stdio.h>

int main()
{
    char again;

    do
    {
        char p1 = '1', p2 = '2', p3 = '3';
        char p4 = '4', p5 = '5', p6 = '6';
        char p7 = '7', p8 = '8', p9 = '9';

        int move;
        int turn = 0;
        int gameOver = 0;

      
        printf("     TIC TAC TOE\n");
        printf("====================\n");
        printf("You = X\n");
        printf("Computer = O\n");

        while (turn < 9 && gameOver == 0)
        {
            printf("\n");
            printf(" %c | %c | %c\n", p1, p2, p3);
            printf("---+---+---\n");
            printf(" %c | %c | %c\n", p4, p5, p6);
            printf("---+---+---\n");
            printf(" %c | %c | %c\n", p7, p8, p9);

            printf("\nEnter your move (1-9): ");

            if (scanf("%d", &move) != 1)
            {
                printf("Invalid input! Enter a number from 1 to 9.\n");

                while (getchar() != '\n');

                continue;
            }

            if (move == 1 && p1 == '1')
                p1 = 'X';
            else if (move == 2 && p2 == '2')
                p2 = 'X';
            else if (move == 3 && p3 == '3')
                p3 = 'X';
            else if (move == 4 && p4 == '4')
                p4 = 'X';
            else if (move == 5 && p5 == '5')
                p5 = 'X';
            else if (move == 6 && p6 == '6')
                p6 = 'X';
            else if (move == 7 && p7 == '7')
                p7 = 'X';
            else if (move == 8 && p8 == '8')
                p8 = 'X';
            else if (move == 9 && p9 == '9')
                p9 = 'X';
            else
            {
                printf("Invalid move! Try again.\n");
                continue;
            }

            turn++;

            if ((p1 == 'X' && p2 == 'X' && p3 == 'X') ||
                (p4 == 'X' && p5 == 'X' && p6 == 'X') ||
                (p7 == 'X' && p8 == 'X' && p9 == 'X') ||
                (p1 == 'X' && p4 == 'X' && p7 == 'X') ||
                (p2 == 'X' && p5 == 'X' && p8 == 'X') ||
                (p3 == 'X' && p6 == 'X' && p9 == 'X') ||
                (p1 == 'X' && p5 == 'X' && p9 == 'X') ||
                (p3 == 'X' && p5 == 'X' && p7 == 'X'))
            {
                printf("\n");
                printf(" %c | %c | %c\n", p1, p2, p3);
                printf("---+---+---\n");
                printf(" %c | %c | %c\n", p4, p5, p6);
                printf("---+---+---\n");
                printf(" %c | %c | %c\n", p7, p8, p9);

                printf("\nPLAYER WINS!\n");

                gameOver = 1;
                continue;
            }

            if (turn == 9)
            {
                printf("\nDRAW!\n");
                gameOver = 1;
                continue;
            }

            if (p1 == '1')
                p1 = 'O';
            else if (p2 == '2')
                p2 = 'O';
            else if (p3 == '3')
                p3 = 'O';
            else if (p4 == '4')
                p4 = 'O';
            else if (p5 == '5')
                p5 = 'O';
            else if (p6 == '6')
                p6 = 'O';
            else if (p7 == '7')
                p7 = 'O';
            else if (p8 == '8')
                p8 = 'O';
            else if (p9 == '9')
                p9 = 'O';

            turn++;

            if ((p1 == 'O' && p2 == 'O' && p3 == 'O') ||
                (p4 == 'O' && p5 == 'O' && p6 == 'O') ||
                (p7 == 'O' && p8 == 'O' && p9 == 'O') ||
                (p1 == 'O' && p4 == 'O' && p7 == 'O') ||
                (p2 == 'O' && p5 == 'O' && p8 == 'O') ||
                (p3 == 'O' && p6 == 'O' && p9 == 'O') ||
                (p1 == 'O' && p5 == 'O' && p9 == 'O') ||
                (p3 == 'O' && p5 == 'O' && p7 == 'O'))
            {
                printf("\n");
                printf(" %c | %c | %c\n", p1, p2, p3);
                printf("---+---+---\n");
                printf(" %c | %c | %c\n", p4, p5, p6);
                printf("---+---+---\n");
                printf(" %c | %c | %c\n", p7, p8, p9);

                printf("\nCOMPUTER WINS!\n");

                gameOver = 1;
            }
        }

        printf("\nPlay again? (y/n): ");
        scanf(" %c", &again);

    } while (again == 'y' || again == 'Y');

    printf("\nThanks for playing!\n");

    return 0;
}
