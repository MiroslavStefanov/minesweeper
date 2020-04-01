#include <windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include"glut.h"
#include<iostream>
#include<string>
#include<math.h>
#include<time.h>
#include<stdlib.h>
using namespace std;

void draw_cell_with_flag(double x, double y)
{
    glPushMatrix();
    glTranslated(x, y, 0);
    glColor3f(0.3, 0.3, 0.3);
    glRectd(-10, -10, 10, 10);
    glEnable(GL_POLYGON_MODE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0, 0, 0);
    glEnable(GL_LINE_WIDTH);
    glLineWidth(1.5);
    glRectf(-10, -10, 10, 10);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_LINES);
    glVertex2d(1.5, -10);
    glVertex2d(1.5, 0);
    glEnd();
    glColor3f(1, 1, 0);
    glBegin(GL_POLYGON);
    glVertex2d(1.5, 0);
    glVertex2d(-5, 3);
    glVertex2d(1.5, 6);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_MODE);
    glLineWidth(1);
    glDisable(GL_LINE_WIDTH);
    glPopMatrix();
    //glFlush();
}

void draw_cell_with_mine(double x, double y)
{
    glPushMatrix();
    glLoadIdentity();
    glEnable(GL_POLYGON_MODE);
    glEnable(GL_LINE_WIDTH);
    glLineWidth(1.5);
    glTranslated(x, y, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3d(1, 0, 0);
    glRectd(-10, -10, 10, 10);
    glColor3d(0, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectd(-10, -10, 10, 10);
    float x1, y1, x2, y2;
    float angle;
    double radius = 4;
    x1 = 0, y1 = 0;
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);
    for (angle = 1.0f; angle < 361.0f; angle += 0.2)
    {
        x2 = x1 + sin(angle) * radius;
        y2 = y1 + cos(angle) * radius;
        glVertex2f(x2, y2);
    }
    glEnd();
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glRotated(i * 45, 0, 0, 1);
        glBegin(GL_LINES);
        glVertex2d(0, 8);
        glVertex2d(0, -8);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_MODE);
    glLineWidth(1);
    glDisable(GL_LINE_WIDTH);
    glPopMatrix();
    //glFlush();
}

void draw_cell_with_number(double x, double y, string text)
{
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    glTranslated(x, y, 0);
    glRectd(-10, -10, 10, 10);
    glEnable(GL_POLYGON_MODE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_LINE_WIDTH);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    glRectd(-10, -10, 10, 10);
    glColor3f(0, 0, 1);
    glRasterPos2d(-4, -4);
    for (int i = 0; i < text.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text.data()[i]);
    }
    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_MODE);
    glLineWidth(1);
    glDisable(GL_LINE_WIDTH);
    glPopMatrix();
    //glFlush();
}

void draw_closed_cell(double x, double y)
{
    glColor3f(0.3, 0.3, 0.3);
    glPushMatrix();
    glTranslated(x, y, 0);
    glRectd(-10, -10, 10, 10);
    glEnable(GL_POLYGON_MODE | GL_LINE_WIDTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    glRectd(-10, -10, 10, 10);
    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_MODE);
    glLineWidth(1);
    glDisable(GL_LINE_WIDTH);
    //glFlush();
}

void draw_cell_with_zero(double x, double y)
{
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    glTranslated(x, y, 0);
    glRectd(-10, -10, 10, 10);
    glEnable(GL_POLYGON_MODE | GL_LINE_WIDTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    glRectd(-10, -10, 10, 10);
    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_MODE);
    glLineWidth(1);
    glDisable(GL_LINE_WIDTH);
    //glFlush();
}

int table[10][10], tableFake[10][10], tableWidth, tableHeight, numberOfMines, numberOfFlags;

bool is_in_table(int a, int b)
{
    return a >= 0 && a < tableWidth && b >= 0 && b <= tableHeight;
}

void initialize_table()
{
    srand(time(0));
    for (int i = 0; i < numberOfMines; i++)
    {
        int x = rand() % tableWidth, y = rand() % tableHeight;
        if (table[x][y] == 0)
        {
            table[x][y] = -1;
        }
        else
        {
            i--;
        }
    }
    for (int i = 0; i < tableWidth; i++)
    {
        for (int j = 0; j < tableHeight; j++)
        {
            if (table[i][j] == -1)
            {
                if (table[i - 1][j] > -1 && is_in_table(i - 1, j) == true)
                {
                    table[i - 1][j] ++;
                }
                if (table[i - 1][j - 1] > -1 && is_in_table(i - 1, j - 1) == true)
                {
                    table[i - 1][j - 1] ++;
                }
                if (table[i][j - 1] > -1 && is_in_table(i, j - 1) == true)
                {
                    table[i][j - 1] ++;
                }
                if (table[i + 1][j - 1] > -1 && is_in_table(i + 1, j - 1) == true)
                {
                    table[i + 1][j - 1] ++;
                }
                if (table[i + 1][j] > -1 && is_in_table(i + 1, j) == true)
                {
                    table[i + 1][j] ++;
                }
                if (table[i + 1][j + 1] > -1 && is_in_table(i + 1, j + 1) == true)
                {
                    table[i + 1][j + 1] ++;
                }
                if (table[i][j + 1] > -1 && is_in_table(i, j + 1) == true)
                {
                    table[i][j + 1] ++;
                }
                if (table[i - 1][j + 1] > -1 && is_in_table(i - 1, j + 1) == true)
                {
                    table[i - 1][j + 1] ++;
                }
            }
        }
    }
    for (int i = 0; i < tableWidth; i++)
    {
        for (int j = 0; j < tableHeight; j++)
        {
            tableFake[i][j] = 9;
        }
    }
}

void set_flag(int x, int y)
{
    tableFake[x][y] = -2;
    numberOfFlags--;
}

void remove_flag(int x, int y)
{
    tableFake[x][y] = 9;
    numberOfFlags++;
}

void open(int i, int j)
{
    if (table[i][j] > 0 && tableFake[i][j] == 9)
    {
        tableFake[i][j] = table[i][j];
    }
    if (table[i][j] == -1 && tableFake[i][j] == 9)
    {
        for (int x = 0; x < tableWidth; x++)
        {
            for (int y = 0; y < tableHeight; y++)
            {
                if (table[x][y] == -1)
                {
                    tableFake[x][y] = -1;
                }
            }
        }
    }
    if (table[i][j] == 0 && tableFake[i][j] == 9)
    {
        tableFake[i][j] = 0;
        if (is_in_table(i - 1, j) == true)
        {
            open(i - 1, j);
        }
        if (is_in_table(i - 1, j - 1) == true)
        {
            open(i - 1, j - 1);
        }
        if (is_in_table(i, j - 1) == true)
        {
            open(i, j - 1);
        }
        if (is_in_table(i + 1, j - 1) == true)
        {
            open(i + 1, j - 1);
        }
        if (is_in_table(i + 1, j) == true)
        {
            open(i + 1, j);
        }
        if (is_in_table(i + 1, j + 1) == true)
        {
            open(i + 1, j + 1);
        }
        if (is_in_table(i, j + 1) == true)
        {
            open(i, j + 1);
        }
        if (is_in_table(i - 1, j + 1) == true)
        {
            open(i - 1, j + 1);
        }
    }
}

bool is_game_over()
{
    for (int i = 0; i < tableWidth; i++)
    {
        for (int j = 0; j < tableHeight; j++)
        {
            if (tableFake[i][j] == -1)
                return true;
        }
    }
    return false;
}

bool winner()
{
    int s = 0;
    for (int i = 0; i < tableWidth; i++)
    {
        for (int j = 0; j < tableHeight; j++)
        {
            if (tableFake[i][j] == -2 && table[i][j] == -1)
                s++;
        }
    }
    return s == numberOfMines;
}

void display()
{
    for (int i = tableWidth - 1; i >= 0; i--)
    {
        for (int j = 0; j < tableHeight; j++)
        {
            if (tableFake[i][j] == 9)
            {
                double x = 10 + j * 20, y = 10 + (tableWidth - 1 - i) * 20;
                draw_closed_cell(x, y);
            }
            if (tableFake[i][j] == -2)
            {
                double x = 10 + j * 20, y = 10 + (tableWidth - 1 - i) * 20;
                draw_cell_with_flag(x, y);
            }
            if (tableFake[i][j] == -1)
            {
                double x = 10 + j * 20, y = 10 + (tableWidth - 1 - i) * 20;
                draw_cell_with_mine(x, y);
            }
            if (tableFake[i][j] == 0)
            {
                double x = 10 + j * 20, y = 10 + (tableWidth - 1 - i) * 20;
                draw_cell_with_zero(x, y);
            }
            if (tableFake[i][j] == 1)
            {
                double x = 10 + j * 20, y = 10 + (tableWidth - 1 - i) * 20;
                string number = "1";
                draw_cell_with_number(x, y, number);
            }
            if (tableFake[i][j] == 2)
            {
                double x = 10 + j * 20, y = 10 + (tableWidth - 1 - i) * 20;
                string number = "2";
                draw_cell_with_number(x, y, number);
            }
            if (tableFake[i][j] == 3)
            {
                double x = 10 + j * 20, y = 10 + (tableWidth - 1 - i) * 20;
                string number = "3";
                draw_cell_with_number(x, y, number);
            }
            if (tableFake[i][j] == 4)
            {
                double x = 10 + j * 20, y = 10 + (tableWidth - 1 - i) * 20;
                string number = "4";
                draw_cell_with_number(x, y, number);
            }
            if (tableFake[i][j] == 5)
            {
                double x = 10 + j * 20, y = 10 + (tableWidth - 1 - i) * 20;
                string number = "5";
                draw_cell_with_number(x, y, number);
            }
            if (tableFake[i][j] == 6)
            {
                double x = 10 + j * 20, y = 10 + (tableWidth - 1 - i) * 20;
                string number = "6";
                draw_cell_with_number(x, y, number);
            }
            if (tableFake[i][j] == 7)
            {
                double x = 10 + j * 20, y = 10 + (tableWidth - 1 - i) * 20;
                string number = "7";
                draw_cell_with_number(x, y, number);
            }
            if (tableFake[i][j] == 8)
            {
                double x = 10 + j * 20, y = 10 + (tableWidth - 1 - i) * 20;
                string number = "8";
                draw_cell_with_number(x, y, number);
            }
        }
    }
    if (winner() == true)
    {
        string v = "YOU WON !!!";
        glColor3f(1, 1, 1);
        glRasterPos2d(0, 10 * tableWidth);
        for (int i = 0; i < v.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, v.data()[i]);
        }
    }
    if (is_game_over() == true)
    {
        string l = "GAME OVER !";
        glColor3f(1, 1, 1);
        glRasterPos2d(0, 10 * tableWidth);
        for (int i = 0; i < l.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, l.data()[i]);
        }
    }
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, (double)w, 0, (double)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
    glClearColor(1, 1, 1, 0);
    glShadeModel(GL_FLAT);
}

void keyboard(int key, int x, int y)
{
    switch (key)
    {
    default:
        exit(0);
    }
}



void idle()
{
    if (is_game_over() == true)
    {
        glutSpecialFunc(keyboard);
    }
    if (winner() == true)
    {
        glutSpecialFunc(keyboard);
    }
}

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
            int i, j;
            i = y / 20;
            j = x / 20;
            if (tableFake[i][j] == 9)
            {
                open(i, j);
            }
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
            int i, j;
            i = y / 20;
            j = x / 20;
            if (tableFake[i][j] == 9 && numberOfFlags > 0)
            {
                set_flag(i, j);
                break;
            }
            if (tableFake[i][j] == -2)
            {
                remove_flag(i, j);
                break;
            }
        }
        break;
    }
    glutPostRedisplay();

}

int main(int argc, char** argv)
{
    cout << "Enter table`s sizes and the number of mines" << endl;
    cin >> tableWidth >> tableHeight >> numberOfMines;
    numberOfFlags = numberOfMines;
    initialize_table();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(500, 200);
    glutInitWindowSize(20 * tableHeight, 20 * tableWidth);
    glutCreateWindow("Minesweeper");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
