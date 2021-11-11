#include "stdio.h"
#include "stdlib.h"
#include "SDL.h"


/*Changed as clock() gives poor results on mac
#include "time.h"
*/
#include <sys/time.h>
#include "math.h" 
#include "formulas.h"
#include "wall.h"
#include "robot.h"

int done = 0;

//将表面应用到渲染器
void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
     SDL_RenderCopy(rend, tex, NULL, &pos);
}
int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);//SDL初始化
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *loadedImage;
    SDL_Texture *texture;
    SDL_Texture *background;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);
    loadedImage = SDL_LoadBMP("background.bmp");
    background = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);

    struct Robot robot;
    struct Wall_collection *head = NULL;
    int front_sensor, right_sensor, left_sensor=0;

    /*Changed as clock() gives poor results on mac
    clock_t start_time,end_time;
    int msec;
    */
    struct timeval start_time, end_time;
    gettimeofday(&start_time, 0);
    unsigned long msec;

    // SETUP MAZE
    // You can create your own maze here. line of code is adding a wall.
    // You describe position of top left corner of wall (x, y), then width and height going down/to right
    // Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
    // But you can use absolute positions. 10 is used as the width, but you can change this.
    insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
    insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
    insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
    insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 150, 10);
    insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 10, 100);
    insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 450, 10);
    insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 250, 10);
    insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-100, 10, 300);
    insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
    insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2-100, 10);

    /*insertAndSetFirstWall(&head, 2,  220, 400, 10, 80);
    insertAndSetFirstWall(&head, 2,  20, 400, 200, 10);
    insertAndSetFirstWall(&head, 2,  20, 50, 10, 350);
    insertAndSetFirstWall(&head, 2,  20, 50, 280, 10);
    insertAndSetFirstWall(&head, 2,  300, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  300, 150, 110, 10);
    insertAndSetFirstWall(&head, 2,  400, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  400, 50, 220, 10);
    insertAndSetFirstWall(&head, 2,  620, 50, 10, 290);
    insertAndSetFirstWall(&head, 2,  620, 340, 20, 10);

    insertAndSetFirstWall(&head, 1,  320, 300, 10, 180);
    insertAndSetFirstWall(&head, 2,  120, 300, 200, 10);
    insertAndSetFirstWall(&head, 2,  120, 150, 10, 150);
    insertAndSetFirstWall(&head, 2,  120, 150, 80, 10);
    insertAndSetFirstWall(&head, 2,  200, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  200, 250, 310, 10);
    insertAndSetFirstWall(&head, 2,  500, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  500, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  500, 150, 20, 10);
    insertAndSetFirstWall(&head, 2,  520, 150, 10, 290);
    insertAndSetFirstWall(&head, 2,  520, 440, 120, 10);*/

    // US
    /*insertAndSetFirstWall(&head, 1, 30, 50, 10, 420);
    
    insertAndSetFirstWall(&head, 2, 110, 50, 500, 10);
    
    insertAndSetFirstWall(&head, 3, 400, 50, 10, 60);

    insertAndSetFirstWall(&head, 3, 400, 200, 10, 105);
    insertAndSetFirstWall(&head, 3, 535, 110, 10, 200);
    insertAndSetFirstWall(&head, 1, 465, 110, 80, 10);
    insertAndSetFirstWall(&head, 1, 465, 110, 10, 100);
    insertAndSetFirstWall(&head, 1, 30, 300, 205, 10);
    insertAndSetFirstWall(&head, 1, 420, 380, 100, 10);
    insertAndSetFirstWall(&head, 1, 320, 300, 10, 200);
    insertAndSetFirstWall(&head, 1, 320, 300, 220, 10);
    insertAndSetFirstWall(&head, 1, 110, 300, 10, 130);
    insertAndSetFirstWall(&head, 1, 230, 370, 10, 100);
    insertAndSetFirstWall(&head, 5, 110, 50, 10, 180);
   insertAndSetFirstWall(&head, 1, 460, 380, 10, 100);
    insertAndSetFirstWall(&head, 6, 110, 220, 210, 10);
    insertAndSetFirstWall(&head, 7, 200, 110, 210, 10);
    insertAndSetFirstWall(&head, 8, 310, 180, 10, 50);

    
    insertAndSetFirstWall(&head, 3, 610, 50, 10, 420);

    insertAndSetFirstWall(&head, 3, 30, 470, 500, 10);*/

    setup_robot(&robot);
    updateAllWalls(head, renderer);

    SDL_Event event;
    while(!done){
        SDL_SetRenderDrawColor(renderer, 255, 245, 238, 255);
        SDL_RenderClear(renderer);
        ApplySurface(300, 300, background, renderer);


        //Move robot based on user input commands/auto commands
        if (robot.auto_mode == 1)
            robotAutoMotorMove(&robot, left_sensor, front_sensor, right_sensor);
        robotMotorMove(&robot);

        //Check if robot reaches endpoint. and check sensor values
        if (checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT/2+100, 10, 100)){
        // US
        //if (checkRobotReachedEnd(&robot, 530, 470, 100, 10)){ //Maze 6
           /* Changed as clock() gives poor results on mac
            end_time = clock();
            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
            */
            gettimeofday(&end_time, 0);
            msec = ((end_time.tv_sec - start_time.tv_sec)*1000)+(end_time.tv_usec - start_time.tv_usec)/1000;
            robotSuccess(&robot, msec);
        }
        else if(checkRobotHitWalls(&robot, head))
            robotCrash(&robot);
        //Otherwise compute sensor information
        else {
            left_sensor = checkRobotSensorLeftAllWalls(&robot, head);
            if (left_sensor!=0)
                printf("Getting close on the left. Score = %d\n", left_sensor);

            front_sensor = checkRobotSensorFrontAllWalls(&robot, head);
            if (front_sensor!=0)
                printf("Getting close on the front. Score = %d\n", front_sensor);
            right_sensor = checkRobotSensorRightAllWalls(&robot, head);
            if (right_sensor!=0)
                printf("Getting close on the right. Score = %d\n", right_sensor);
        }
        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer);

        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != DOWN){
                robot.direction = UP;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != UP){
                robot.direction = DOWN;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                setup_robot(&robot);
            }
            if(state[SDL_SCANCODE_RETURN]){
                robot.auto_mode = 1;
                /* Changed as clock() gives poor results on mac
                start_time = clock();
                */
                gettimeofday(&start_time, 0);


            }
        }

        SDL_Delay(120);
    }
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
}
