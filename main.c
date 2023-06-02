#include <stdio.h>
#include <stdlib.h>

#define TOP_LINE_TO_RIGHT 0
#define TOP_LINE_TO_LEFT 1
#define MIDDLE_LINE_TO_RIGHT 2
#define MIDDLE_LINE_TO_LEFT 3
#define BOTTOM_LINE_TO_RIGHT 4
#define BOTTOM_LINE_TO_LEFT 5
#define LEFT_COLUMN_TO_ABOVE 6
#define LEFT_COLUMN_TO_BELOW 7
#define CENTER_COLUMN_TO_ABOVE 8
#define CENTER_COLUMN_TO_BELOW 9
#define RIGHT_COLUMN_TO_ABOVE 10
#define RIGHT_COLUMN_TO_BELOW 11
#define CLOCKWISE_FACE_ROTATE 12
#define COUNTERCLOCKWISE_FACE_ROTATE 13

typedef int*** rubiks_cube;
typedef int** rubiks_face;
typedef int* rubiks_line;


rubiks_cube generateCube() {
    rubiks_cube cube = (rubiks_cube) malloc(sizeof(rubiks_face) * 6);

    for(int i = 0; i < 6; i++) {
        cube[i] = (rubiks_face) malloc(sizeof(rubiks_line) * 3);
        
        for(int j = 0; j < 3; j++) {
            cube[i][j] = (rubiks_line) (malloc(sizeof(int) * 3));
            
            for(int k = 0; k < 3; k++) cube[i][j][k] = 'a' + i;
        }
    }

    return cube;
}

void printCube(rubiks_cube cube) {
    for(int i = 0; i < 6; i++) {
        printf("Face %d:\n", i + 1);

        for(int j = 0; j < 3; j++) {
            printf("%c %c %c\n", cube[i][j][0], cube[i][j][1], cube[i][j][2]);
        }

        putchar('\n');
    }
}

void freeCube(rubiks_cube cube) {
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 3; j++) {
            free(cube[i][j]);
        }

        free(cube[i]);
    }

    free(cube);
}

void flip(int movement, rubiks_cube cube) {
    rubiks_line tmpLine = (rubiks_line) malloc(sizeof(int) * 3);

    switch (movement) {
        case TOP_LINE_TO_RIGHT:
            tmpLine[0] = cube[0][0][0];
            tmpLine[1] = cube[0][0][1];
            tmpLine[2] = cube[0][0][2];

            for(int i = 0; i < 3; i++) {
                cube[i][0][0] = cube[i + 1][0][0];
                cube[i][0][1] = cube[i + 1][0][1];
                cube[i][0][2] = cube[i + 1][0][2];
            }

            cube[3][0][0] = tmpLine[0];
            cube[3][0][1] = tmpLine[1];
            cube[3][0][2] = tmpLine[2];

            break;
        case TOP_LINE_TO_LEFT:
            tmpLine[0] = cube[3][0][0];
            tmpLine[1] = cube[3][0][1];
            tmpLine[2] = cube[3][0][2];

            for(int i = 3; i > 0; i--) {
                cube[i][0][0] = cube[i - 1][0][0];
                cube[i][0][1] = cube[i - 1][0][1];
                cube[i][0][2] = cube[i - 1][0][2];
            }

            cube[0][0][0] = tmpLine[0];
            cube[0][0][1] = tmpLine[1];
            cube[0][0][2] = tmpLine[2];
            break;
        case MIDDLE_LINE_TO_RIGHT:
            tmpLine[0] = cube[0][1][0];
            tmpLine[1] = cube[0][1][1];
            tmpLine[2] = cube[0][1][2];

            for(int i = 0; i < 3; i++) {
                cube[i][1][0] = cube[i + 1][1][0];
                cube[i][1][1] = cube[i + 1][1][1];
                cube[i][1][2] = cube[i + 1][1][2];
            }

            cube[3][1][0] = tmpLine[0];
            cube[3][1][1] = tmpLine[1];
            cube[3][1][2] = tmpLine[2];

            break;
        case MIDDLE_LINE_TO_LEFT:
            tmpLine[0] = cube[3][1][0];
            tmpLine[1] = cube[3][1][1];
            tmpLine[2] = cube[3][1][2];

            for(int i = 3; i > 0; i--) {
                cube[i][1][0] = cube[i - 1][1][0];
                cube[i][1][1] = cube[i - 1][1][1];
                cube[i][1][2] = cube[i - 1][1][2];
            }

            cube[0][1][0] = tmpLine[0];
            cube[0][1][1] = tmpLine[1];
            cube[0][1][2] = tmpLine[2];
            break;
        case BOTTOM_LINE_TO_RIGHT:
            tmpLine[0] = cube[0][2][0];
            tmpLine[1] = cube[0][2][1];
            tmpLine[2] = cube[0][2][2];

            for(int i = 0; i < 3; i++) {
                cube[i][2][0] = cube[i + 1][2][0];
                cube[i][2][1] = cube[i + 1][2][1];
                cube[i][2][2] = cube[i + 1][2][2];
            }

            cube[3][2][0] = tmpLine[0];
            cube[3][2][1] = tmpLine[1];
            cube[3][2][2] = tmpLine[2];
            break;
        case BOTTOM_LINE_TO_LEFT:
            tmpLine[0] = cube[3][2][0];
            tmpLine[1] = cube[3][2][1];
            tmpLine[2] = cube[3][2][2];

            for(int i = 3; i > 0; i--) {
                cube[i][2][0] = cube[i - 1][2][0];
                cube[i][2][1] = cube[i - 1][2][1];
                cube[i][2][2] = cube[i - 1][2][2];
            }

            cube[0][2][0] = tmpLine[0];
            cube[0][2][1] = tmpLine[1];
            cube[0][2][2] = tmpLine[2];
            break;
        case LEFT_COLUMN_TO_ABOVE:
            for (int i = 0; i < 3; i++)
                tmpLine[i] = cube[1][i][0];

            const int faces0[4] = {5, 3, 4, 1};

            for (int i = 0; i < 3; i++) {
                int idx = i == 0 ? 3 : i - 1;

                for (int j = 0; j < 3; j++)
                    cube[faces0[idx]][j][0] = cube[faces0[i]][j][0];
            }

            for (int i = 0; i < 3; i++)
                cube[4][i][0] = tmpLine[i];

            break;
        case LEFT_COLUMN_TO_BELOW:
            for (int i = 0; i < 3; i++)
                tmpLine[i] = cube[4][i][0];

            const int faces1[4] = {3, 5, 1, 4};

            for (int i = 0; i < 3; i++) {
                int idx = i == 0 ? 3 : i - 1;

                for (int j = 0; j < 3; j++)
                    cube[faces1[idx]][j][0] = cube[faces1[i]][j][0];
            }

            for (int i = 0; i < 3; i++)
                cube[1][i][0] = tmpLine[i];

            break;
        case CENTER_COLUMN_TO_ABOVE:
            for (int i = 0; i < 3; i++)
                tmpLine[i] = cube[1][i][1];

            const int faces2[4] = {5, 3, 4, 1};

            for (int i = 0; i < 3; i++) {
                int idx = i == 0 ? 3 : i - 1;

                for (int j = 0; j < 3; j++)
                    cube[faces2[idx]][j][1] = cube[faces2[i]][j][1];
            }

            for (int i = 0; i < 3; i++)
                cube[4][i][1] = tmpLine[i];

            break;
        case CENTER_COLUMN_TO_BELOW:
            for (int i = 0; i < 3; i++)
                tmpLine[i] = cube[4][i][1];

            const int faces3[4] = {3, 5, 1, 4};

            for (int i = 0; i < 3; i++) {
                int idx = i == 0 ? 3 : i - 1;

                for (int j = 0; j < 3; j++)
                    cube[faces3[idx]][j][1] = cube[faces3[i]][j][1];
            }

            for (int i = 0; i < 3; i++)
                cube[1][i][1] = tmpLine[i];

            break;
        case RIGHT_COLUMN_TO_ABOVE:
            for (int i = 0; i < 3; i++)
                tmpLine[i] = cube[1][i][2];

            const int faces4[4] = {5, 3, 4, 1};

            for (int i = 0; i < 3; i++) {
                int idx = i == 0 ? 3 : i - 1;

                for (int j = 0; j < 3; j++)
                    cube[faces4[idx]][j][2] = cube[faces4[i]][j][2];
            }

            for (int i = 0; i < 3; i++)
                cube[4][i][2] = tmpLine[i];

            break;
        case RIGHT_COLUMN_TO_BELOW:
            for (int i = 0; i < 3; i++)
                tmpLine[i] = cube[4][i][2];

            const int faces5[4] = {3, 5, 1, 4};

            for (int i = 0; i < 3; i++) {
                int idx = i == 0 ? 3 : i - 1;

                for (int j = 0; j < 3; j++)
                    cube[faces5[idx]][j][2] = cube[faces5[i]][j][2];
            }

            for (int i = 0; i < 3; i++)
                cube[1][i][2] = tmpLine[i];

            break;
        case CLOCKWISE_FACE_ROTATE:
            break;
        case COUNTERCLOCKWISE_FACE_ROTATE:
            break;
        default:
            printf("Invalid move!");
    }

    free(tmpLine);
}

int main() {
    rubiks_cube cube = generateCube();

    printCube(cube);

    flip(CENTER_COLUMN_TO_ABOVE, cube);
    flip(RIGHT_COLUMN_TO_BELOW, cube);
    printCube(cube);

    freeCube(cube);

    return 0;
}