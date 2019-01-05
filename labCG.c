#include <GL/glut.h>
#include<math.h>
#include<stdlib.h>

#define XMIN 0
#define YMIN 0
#define XMAX 500
#define YMAX 500

#define FIRST_X 100
#define FIRST_Y 400

#define DIFF_COOR 100

#define NUM 4

double vertex[][3] = {   /* 頂点を配列で宣言する方法 */
  {-50.,-50., 0.0},
  { 50.,-50., 0.0},
  { 50., 50., 0.0},
  {-50., 50., 0.0},
};

float color_r[5] = {1.0, 0.0, 0.0, 0.0, 1.0};
float color_g[5] = {0.0, 1.0, 0.0, 0.0, 1.0};
float color_b[5] = {0.0, 0.0, 1.0, 0.0, 1.0};

float xx = 0.0, yy =0.0;
int c_num;

float each_color_r[NUM][5];
float each_color_g[NUM][5];
float each_color_b[NUM][5];

int each_i[NUM];

int place_num;
int count = 0;

int judge_tile(int pos_x, int pos_y){
  int i;
  int base_x, base_y;
  int half_diff = DIFF_COOR / 2;
  base_x = FIRST_X;
  base_y = FIRST_Y;
  for(i = 0; i < NUM; i++){
    if((base_x - half_diff) <= pos_x && pos_x <= (base_x + half_diff)){
      if((base_y - half_diff) <= pos_y && pos_y <= (base_y + half_diff)){
        return i + 1;
      }
    }
    base_x += DIFF_COOR;
    //base_y += DIFF_COOR;
  }
  return 0;
}

void initial_array_setting(void){
  int i,j;
  for(i = 0; i < NUM; i++){
    each_i[i] = 0;
    for(j = 0; j < 5; j++){
      each_color_r[i][j] = color_r[j];
      each_color_g[i][j] = color_g[j];
      each_color_b[i][j] = color_b[j];
    }
  }
}

void display(void)
{
  int i, j;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();   /* 物体をx方向に-1.0平行移動する */
  glTranslatef(FIRST_X, FIRST_Y, 0.0);
  if(place_num == 1){
    each_i[0]++;
    place_num = 0;
  }
  glColor3f(each_color_r[0][each_i[0]], each_color_g[0][each_i[0]], each_color_b[0][each_i[0]]);
  glBegin(GL_QUADS);
  for(i=0; i<4; i++){
    glVertex3f(vertex[i][0],vertex[i][1],vertex[i][2]);
  }
  glEnd();
  // glPopMatrix();
  for(j = 1; j < NUM; j++){
    c_num = j % NUM;
    glPushMatrix();
    glTranslatef(DIFF_COOR, 0.0, 0.0);
    if(place_num == j + 1){
      each_i[j]++;
      place_num = 0;
    }
    glColor3f(each_color_r[j][each_i[j]], each_color_g[j][each_i[j]], each_color_b[j][each_i[j]]);
    glBegin(GL_QUADS);
    for(i=0; i<4; i++){
      glVertex3f(vertex[i][0], vertex[i][1], vertex[i][2]);
    }
    glEnd();
  }

  for(j = 0; j < NUM; j++){
      glPopMatrix();
  }

  glPushMatrix();
  glPopMatrix();
  glPointSize(10.0);
  glBegin(GL_POINTS);
  glColor3f(1.0, 1.0, 0.0);
  glVertex2f(xx, yy);
  glEnd();

  glutSwapBuffers();
  //glFlush();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 'q':
      exit(0);
    default:
      break;
  }
}

void idle(void)
{
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
  if(state == GLUT_DOWN){
    switch (button) {
      case GLUT_LEFT_BUTTON:
        place_num = judge_tile(x + XMIN, YMAX - y);
        break;
      case GLUT_RIGHT_BUTTON:
        break;
    }
  }
}

void mousemotion(int x, int y){
  xx = x + XMIN;
  yy = YMAX - y;
}

void init(char *winname)
{
  glutInitWindowPosition( XMIN, YMIN);
  glutInitWindowSize( XMAX-XMIN, YMAX-YMIN);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow(winname);
  glClearColor(0.2, 0.4, 0.4, 1.0);
  glLoadIdentity();
  glOrtho( (float)XMIN, (float)XMAX, (float)YMIN, (float)YMAX, -1.0, 1.0 );
}

int main(int argc, char *argv[])
{
  if(count == 0){
    initial_array_setting();
    count++;
  }
  glutInit(&argc, argv);           /* glutの初期化 */
  init(argv[0]);
  glutDisplayFunc(display);        /* ディスプレイコールバック関数の指定 */
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutPassiveMotionFunc(mousemotion); //glutMouseFunc(mouse);
  glutIdleFunc(idle);
  glutMainLoop();                  /* イベント待ちの無限ループへ入る */
  return 0;                   /* ループが終わったら0を返して終了 */
}
