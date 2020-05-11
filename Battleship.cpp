// enemy -'e' противник не видна
// 'i' союзник зелёная
// null 'n' пустая ячейка
// crash 'c' попадание красная
// beside 'b' промах синий 

#include <iostream>
#include <glut.h>
#include <ctime>
#include <fstream>
#include<string>

using namespace std;


const int N = 10;

double rotate_y = -10;
double rotate_x = 30;

int  speedRotate = 5;

double a = 0.5,
b = a / N;

double Kx = 0, Ky = 0, Kz = 0,
K = 2 * b;


int SelectX = N / 2;
int SelectY = N / 2;

int Free = 20;
int BestScore;
bool enemyTemp = 0;


class Cube
{
    char arena[N][N];
public:
    Cube()
    {
        for (int x = 0; x < N; x++)
            for (int y = 0; y < N; y++)
                    arena[x][y] = 'n';
    }

    void Set(int x, int y, char c)
    {
        arena[x][y] = c;
    }

    char get(int x, int y) {
        return arena[x][y];
    }

    void cubA(double x, double y, double z, double kx, double ky, double kz, char color = 'w') {

        double r, g, b;

        if (color == 'w' || color == 'e') {
            r = 1.0; g = 1.0; b = 1.0;
        }
        else if (color == 'i') {
            r = 0.0; g = 1.0; b = 0.0; //green
        }
        else if (color == 'c') {
            r = 1.0; g = 0.0; b = 0.0; //red
        }
        else if (color == 'b') {
            r = 0.0; g = 0.0; b = 1.0; //blue
        }


        // Reset transformations
        glLoadIdentity();

        // Rotate when user changes rotate_x and rotate_y
        glRotatef(rotate_x, 1.0, 0.0, 0.0);
        glRotatef(rotate_y, 0.0, 1.0, 0.0);

        // Purple side - RIGHT
        glBegin(GL_POLYGON);//(GL_POLYGON);
        //glColor3f(0.0, 1.0, 1.0);
        glColor3f(r, g, b);

        glVertex3f(x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, y + ky, -z + kz);
        glVertex3f(x + kx, y + ky, z + kz);
        glVertex3f(x + kx, -y + ky, z + kz);
        glEnd();

        // Green side - LEFT
        glBegin(GL_POLYGON);
        //glColor3f(0.0, 1.0, 1.0);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, y + ky, z + kz);
        glVertex3f(-x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, -y + ky, -z + kz);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glEnd();

        // Blue side - TOP
        glBegin(GL_POLYGON);
        //glColor3f(0.0, 0.0, 1.0);
        //glColor3f(0.0, 1.0, 1.0);
        glVertex3f(x + kx, y + ky, z + kz);
        glVertex3f(x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, y + ky, z + kz);
        glVertex3f(x + kx, y + ky, z + kz);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex3f(x + kx, -y + ky, z + kz);
        glVertex3f(x + kx, y + ky, z + kz);
        glVertex3f(-x + kx, y + ky, z + kz);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glEnd();

        // Red side - BOTTOM
        glBegin(GL_LINE_STRIP);//(GL_LINE_STRIP);
        //glColor3f(0.0, 1.0, 1.0);
        glVertex3f(x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, -y + ky, -z + kz);
        glColor3f(1.0, 1.0, 1.0);
        glEnd();
    }

    void cubSelect(double x, double y, double z, double kx, double ky, double kz) {

        // Reset transformations
        glLoadIdentity();


        // Rotate when user changes rotate_x and rotate_y
        glRotatef(rotate_x, 1.0, 0.0, 0.0);
        glRotatef(rotate_y, 0.0, 1.0, 0.0);

        // Purple side - RIGHT
        glBegin(GL_LINE_STRIP);//(GL_POLYGON);
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, y + ky, -z + kz);
        glVertex3f(x + kx, y + ky, z + kz);
        glVertex3f(x + kx, -y + ky, z + kz);
        glEnd();

        // Green side - LEFT
        glBegin(GL_LINE_STRIP);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, y + ky, z + kz);
        glVertex3f(-x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, -y + ky, -z + kz);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glEnd();

        // Blue side - TOP
        glBegin(GL_POLYGON);
        glVertex3f(x + kx, y + ky, z + kz);
        glVertex3f(x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, y + ky, z + kz);
        glVertex3f(x + kx, y + ky, z + kz);
        glColor3f(1.0, 1.0, 1.0);
        glEnd();

        // Red side - BOTTOM
        glBegin(GL_LINE_STRIP);
        glVertex3f(x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, -y + ky, -z + kz);
        glEnd();
    }

    void cubNull(double x, double y, double z, double kx, double ky, double kz) {
        // Reset transformations
        glLoadIdentity();

        // Rotate when user changes rotate_x and rotate_y
        glRotatef(rotate_x, 1.0, 0.0, 0.0);
        glRotatef(rotate_y, 0.0, 20.0, 0.0);

        // Purple side - RIGHT
        glBegin(GL_LINE_STRIP);//(GL_POLYGON);
        //glColor3f(0.0, 1.0, 1.0);
        glColor3f(0.0, 0.0, 1.0);

        glVertex3f(x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, y + ky, -z + kz);
        glVertex3f(x + kx, y + ky, z + kz);
        glVertex3f(x + kx, -y + ky, z + kz);
        glEnd();

        // Green side - LEFT
        glBegin(GL_LINE_STRIP);
        //glColor3f(0.0, 1.0, 1.0);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, y + ky, z + kz);
        glVertex3f(-x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, -y + ky, -z + kz);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glEnd();

        // Blue side - TOP
        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 1.0);
        //glColor3f(0.0, 1.0, 1.0);
        glVertex3f(x + kx, y + ky, z + kz);
        glVertex3f(x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, y + ky, z + kz);
        glVertex3f(x + kx, y + ky, z + kz);
        // glColor3f(1.0, 1.0, 1.0);

        glEnd();

        // Red side - BOTTOM
        glBegin(GL_LINE_STRIP);//(GL_LINE_STRIP);
        //glColor3f(0.0, 1.0, 1.0);
        glVertex3f(x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, -y + ky, -z + kz);
        glEnd();
    }
};
Cube Arena;


void drawString(void* font, const char* text, float x, float y)
{
    if (!text) // нульовий указівник
    {
        return;
    }
    // Встановлення позиції тексту:
    glRasterPos2f(x, y);
    while (*text)
    {
        // Рядок виводиться посимвольно:
        glutBitmapCharacter(font, *text);
        text++;
    }
}

void text(bool f,  double x, double y, string line, int num = -1) {
    if (f)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();
    if (num != -1) {
        string line1 = to_string(num);
        line += line1;
    }
    char* c = &*line.begin();
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, c, x, y);
}

int Sn, Se, Sc, Sb, Si,uShot, hit;
void statistics(){
    Sn = 0, Se = 0, Sc = 0, Sb = 0, Si = 0;;
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            if (Arena.get(x,y) == 'n') Sn++;
            else if (Arena.get(x, y) == 'e') Se++;
            else if (Arena.get(x, y) == 'c') Sc++;
            else if (Arena.get(x, y) == 'b') Sb++;
            else if (Arena.get(x, y) == 'i') Si++;

}

void enemy() {
    srand(time(0));
    int randomX = rand() % 10, randomY = rand() % 10;
    for (int i = 0; i <= 22; i++) {
        randomX = rand() % 10, randomY = rand() % 10;
        if (Arena.get(randomX, randomY) != 'i')
            Arena.Set(randomX, randomY, 'e');
        else i--;
    }
    cout << randomX << ' ' << randomY;
}

void enemyShot() {
    int randomX, randomY;
    m:randomX = rand() % 10, randomY = rand() % 10;
    if (Arena.get(randomX, randomY) == 'i') {
        Arena.Set(randomX, randomY, 'c');
        enemyShot();
    }
    else if (Arena.get(randomX, randomY) == 'n')
        Arena.Set(randomX, randomY, 'b');
    else goto m;
}

void setup() {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            Arena.Set(x, y, 'n');
        }
    }
    ifstream outf("BestScore.txt");

    if (!outf)
    {
        BestScore = 0;
    }
    else {
        outf >> BestScore;
    }
}


void display() {

    text(1,-0.94, 0.9, "S H O T  ", uShot);
    text(0,-0.94, 0.8, "H I T  ", hit);
    text(0, 0.6, 0.9, "your ships  ", Si);
    text(0, 0.55, 0.8, "enemy ships  ", Se);

    text(0, -0.1, 0.9, "best score  ", BestScore);


    Arena.cubSelect(b, b, b, Kx, Ky, Kz);
   
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++) {
            if (Arena.get(x,y) == 'n' || Arena.get(x, y) == 'e')
                Arena.cubNull(b, b, b, (-x + N / 2) * K, 0, (-y + N / 2) * K);
            else if (Arena.get(x, y) == 'i')
                Arena.cubA(b, b, b, (-x + N / 2) * K, 0, (-y + N / 2) * K, 'i');
            else if (Arena.get(x, y) == 'c')
                Arena.cubA(b, b, b, (-x + N / 2) * K, 0, (-y + N / 2) * K, 'c');
            else if (Arena.get(x, y) == 'b')
                Arena.cubA(b, b, b, (-x + N / 2) * K, 0, (-y + N / 2) * K, 'b');
        }


    system("cls");
    for (int x = 0; x < N; x++) {
        cout << endl;
        for (int y = 0; y < N; y++) {
            cout << Arena.get(x,y);
        }
    }

    cout << endl << "Free " << Free << endl << "Sn " << Sn << endl << "Se " << Se << endl;
    cout << BestScore;


    if (Si == 0 && enemyTemp ==1) {
        cout << "game over";
        text(1, 0, -0.1, "G A M E  O V E R");
    }
    else if (Se == 0 && enemyTemp == 1) {
        cout << "WIN";
        text(1, 0, -0.1, "Y O U  W I N");
        if (uShot < BestScore || BestScore == 0) {
            text(0, -0.1, -0.2, "N E W  S C O C E");

            ofstream outf("BestScore.txt");

            if (!outf)
            {
                cerr << "Uh oh, SomeText.txt could not be opened for writing!" << endl;
            }
            outf << uShot;
        }
    }


    glFlush();
    glutSwapBuffers();

}

void specialKeys(int key, int x, int y) {

    if (key == GLUT_KEY_HOME) {
        rotate_x += speedRotate;
    }


    if (key == GLUT_KEY_RIGHT) {
        rotate_y += speedRotate;
    }

    //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT) {
        rotate_y -= speedRotate;
    }

    else if (key == GLUT_KEY_UP) {
       // 
        if (a < 0.61) {
            a = a + 0.01;
            b = b + 0.01 / N;
            K = 2 * b;
        }
    }

    else if (key == GLUT_KEY_DOWN) {
        //
        if (a > 0.05) {
            a = a - 0.01;
            b = b - 0.01 / N;
            K = 2 * b;
        }
    }

    //  Request display update
    glutPostRedisplay();
}
void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) // кнопка віджата
        {
            rotate_x = 90;
            rotate_y = 0;
            display();
        }
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_UP) // кнопка віджата
        {
            rotate_x = 30;;
            rotate_y = -10;
            display();
        }
    }
    }

int limX = 5, limY = 5;
void NormalKeyHandler(unsigned char key, int x, int y)
{
    cout << x << ' ' << y << endl;
    if (key == 'u')
        rotate_x += 5;
    else if (key == 'j')
        rotate_x -= 5;
    else if (key == 'd' && limX<10) {
        Kx += 2 * b;
        SelectX--;
        limX++;
    }
    else if (key == 'a' && limX>1) {
        Kx -= K;
        SelectX++;
        limX--;
    }
    else if (key == 's' && limY>0) {
        Kz += K;
        SelectY--;
        limY--;
    }
    else if (key == 'w' && limY<9) {
        Kz -= K;
        SelectY++;
        limY++;
    }
    else if (key == 27)
        exit(0);


    else if (key == 32) {
        if (Free > 0 && Arena.get(SelectX,SelectY) != 'i') {
            Arena.Set(SelectX, SelectY, 'i');
            Free--;
        }
        else if (Free == 0 && enemyTemp == 0) { enemy(); enemyTemp = 1;}
    }
    else if (key == 'f' && Arena.get(SelectX, SelectY) != 'b' && Arena.get(SelectX, SelectY) != 'c' && Arena.get(SelectX, SelectY) != 'i' && Free == 0) {
        uShot++;
        if (Arena.get(SelectX, SelectY) == 'e' && Free == 0) {
            Arena.Set(SelectX, SelectY, 'c');
            hit++;
        }
        else if (Arena.get(SelectX, SelectY) == 'n') {
            Arena.Set(SelectX, SelectY, 'b');
            enemyShot();

        }
    }


    statistics();
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    setup();
    //  Initialize GLUT and process user parameters
    glutInit(&argc, argv);

    //  Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create window
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("---");

    //  Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);

    // Callback functions
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(NormalKeyHandler);
    glutMouseFunc(mouseButton);

    glutDisplayFunc(display);


    //  Pass control to GLUT for events
    glutMainLoop();

    return 0;

}