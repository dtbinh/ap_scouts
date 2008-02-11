/*
 ============================================================================
 Name        : graphics.c
 Author      : Antons Rebguns
 Version     : 0.4.0
 Copyright   : Copyright(c) 2007, 2008
 Description : Robotic swarm simulator (OpenGL)
 ============================================================================
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "GL/gl.h"
#include "GL/glut.h"

#include "graphics.h"
#include "defs.h"

int help_area_height = 100;
int stats_area_width = 150;

GLfloat agent_color[3] = { 0.0f, 0.2f, 1.0f };
GLfloat agent_color_coll[3] = { 1.0f, 0.0f, 0.0f };
GLfloat agent_color_conn[3] = { 0.8f, 0.8f, 0.8f };
GLfloat goal_color[3] = { 1.0f, 0.0f, 0.2f };
GLfloat obstacle_color[3] = { 0.0f, 0.4f, 0.0f };

bool inside_window = false;
bool selection_active = false;
int selected_obstacle_id = -1;

int increments[6] = { 1, 5, 10, 20, 50, 100 };
int cur_inc_index = 0;

char *selections[3] = { "AGENT", "OBSTACLE", "GOAL" };
int cur_sel_index = 0;

bool show_connectivity = false;

void draw_all( void )
{
    int i;
    
    glClear( GL_COLOR_BUFFER_BIT );
    
    draw_goal( goal );
    
    for ( i = 0; i < params.obstacle_number; i++ )
    {
        draw_obstacle( obstacles[i] );
    }
    
    if ( show_connectivity ) { draw_agent_connectivity(); }

    for( i = 0; i < params.agent_number; i++ )
    {
        draw_agent( agents[i] );
    }
    
    draw_params_stats();
    draw_instructions();

    glutSwapBuffers();
}

inline void draw_string( char *s )
{
    int i;
    
    for ( i = 0; i < strlen( s ); i++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, s[i] );
    }
}

inline void draw_goal( Goal *goal )
{
    float x1 = goal->position.x - goal->width / 2;
    float y1 = goal->position.y + goal->width / 2;
    float x2 = goal->position.x + goal->width / 2;
    float y2 = goal->position.y - goal->width / 2;

    glColor3fv( goal->color );
    glRectf( x1, y1, x2, y2 );
}

inline void draw_agent( Agent *agent )
{
    if ( agent->position.x >= 0.0f && agent->position.y >= 0.0f )
    {
        glPointSize( agent->radius );
        glColor3fv( agent->color );
    
        glBegin( GL_POINTS );
            glVertex2f( agent->position.x, agent->position.y );
        glEnd();
    }
}

inline void draw_agent_connectivity( void )
{
    int i, j;
    
    glColor3fv( agent_color_conn );

    for ( i = 0; i < params.agent_number; i++ )
    {
        Agent *a1 = agents[i];
        Vector2f a1_pos = a1->position;
        
        for ( j = i; j < params.agent_number; j++ )
        {
            Agent *a2 = agents[j];
            Vector2f a2_pos = a2->position;

            float distance = sqrt( pow( a1_pos.x - a2_pos.x, 2 ) + pow( a1_pos.y - a2_pos.y, 2 ) );

            if ( distance <= params.range_coefficient * params.R )
            {
                glBegin( GL_LINES );
                    if ( a1_pos.x < 0.0f ) { glVertex2f( 0.0f, a1_pos.y ); }
                    else if ( a1_pos.y < 0.0f ) { glVertex2f( a1_pos.x, 0.0f ); }
                    else if ( a1_pos.x < 0.0f && a1_pos.y < 0.0f ) { glVertex2f( 0.0f, 0.0f ); }
                    else { glVertex2f( a1_pos.x, a1_pos.y ); }

                    if ( a2_pos.x < 0.0f ) { glVertex2f( 0.0f, a2_pos.y ); }
                    else if ( a2_pos.y < 0.0f ) { glVertex2f( a2_pos.x, 0.0f ); }
                    else if ( a2_pos.x < 0.0f && a2_pos.y < 0.0f ) { glVertex2f( 0.0f, 0.0f ); }
                    else { glVertex2f( a2_pos.x, a2_pos.y ); }
                glEnd();
            }
        }
    }
}

inline void draw_obstacle( Obstacle *obstacle )
{
    glColor3fv( obstacle->color );

    glPushMatrix();
        glTranslatef( obstacle->position.x, obstacle->position.y, 0.0f );
        glutSolidSphere( obstacle->radius, 20, 20 );
    glPopMatrix();
}

inline void draw_params_stats( void )
{
    // Draw simulation parameters on screen
    
    char label[100];
    int line = 1;
    int line_offset = 13;
    int screen_offset_x = 10 - stats_area_width;
    int screen_offset_y = 10;
    
    glColor3f( 0.7f, 0.0f, 0.6f );
    
    glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - line * line_offset );
    sprintf( label, "Agent #: %d", params.agent_number );
    draw_string( label );
    
    glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
    sprintf( label, "Obstacle #: %d", params.obstacle_number );
    draw_string( label );

    glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
    sprintf( label, "Timer Delay: %d", params.timer_delay_ms );
    draw_string( label );
    
    glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
    sprintf( label, "Max Velocity: %.2f", params.max_V );
    draw_string( label );
    
    ++line;
    
    switch ( params.force_law )    
    {
        case NEWTONIAN:
            glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
            sprintf( label, "G Force A-A: %.2f", params.G_agent_agent );
            draw_string( label );
            
            glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
            sprintf( label, "G Force A-O: %.2f", params.G_agent_obstacle );
            draw_string( label );
            
            glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
            sprintf( label, "G Force A-G: %.2f", params.G_agent_goal );
            draw_string( label );
            
            glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
            sprintf( label, "p Power A-A: %.2f", params.p_agent_agent );
            draw_string( label );
            
            glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
            sprintf( label, "p Power A-O: %.2f", params.p_agent_obstacle );
            draw_string( label );
            
            glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
            sprintf( label, "p Power A-G: %.2f", params.p_agent_goal );
            draw_string( label );
            break;
            
        case LENNARD_JONES:
            break;
    }
    
    ++line;
    
    glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
    sprintf( label, "Reached Goal #: %d", stats.reached_goal );
    draw_string( label );
    
    glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
    sprintf( label, "Reach Ratio: %.2f%%", stats.reach_ratio * 100.0f );
    draw_string( label );
    
    glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
    sprintf( label, "Collisions: %d", stats.collisions );
    draw_string( label );
    
    glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
    sprintf( label, "Collision Ratio: %.2f%%", stats.collision_ratio * 100.0f );
    draw_string( label );

    glRasterPos2i( screen_offset_x, params.world_height - screen_offset_y - ( ++line * line_offset ) );
    sprintf( label, "Time Step: %d", stats.time_step );
    draw_string( label );
    
    glColor3f( 0.0f, 0.0f, 0.0f );
    
    glBegin( GL_LINES );
        glVertex2f( 0.0f, 0.0f );
        glVertex2f( 0.0f, params.world_height );
    glEnd();
}

inline void draw_instructions( void )
{
    // Draw simulation instructions (help)
    
    char label[100];
    int line = 1;
    int line_offset = 13;
    int screen_offset = 10;
    
    glColor3f( 0.0f, 0.0f, 0.0f );
    
    glRasterPos2i( screen_offset, -3 * screen_offset - line * line_offset );
    sprintf( label, "'S' -- Start/Stop the simualtion" );
    draw_string( label );
    
    glRasterPos2i( screen_offset, -3 * screen_offset - ( ++line * line_offset ) );
    sprintf( label, "'R' -- Restart the simulation" );
    draw_string( label );

    glRasterPos2i( screen_offset, -3 * screen_offset - ( ++line * line_offset ) );
    sprintf( label, "'PageUp' -- Increase timer delay (slower)" );
    draw_string( label );

    glRasterPos2i( screen_offset, -3 * screen_offset - ( ++line * line_offset ) );
    sprintf( label, "'PageDown' -- Decrease timer delay (faster)" );
    draw_string( label );
    
    line = 1;
    
    glRasterPos2i( screen_offset + 300, -3 * screen_offset - line * line_offset );
    sprintf( label, "'I' -- Change object increment/decrement" );
    draw_string( label );
    
    glRasterPos2i( screen_offset + 300, -3 * screen_offset - ( ++line * line_offset ) );
    sprintf( label, "'A' -- Selects agent # to be incremented/decremented" );
    draw_string( label );
    
    glRasterPos2i( screen_offset + 300, -3 * screen_offset - ( ++line * line_offset ) );
    sprintf( label, "'UP' -- Increments # of objects" );
    draw_string( label );
    
    glRasterPos2i( screen_offset + 300, -3 * screen_offset - ( ++line * line_offset ) );
    sprintf( label, "'DOWN' -- Decrements # of objects" );
    draw_string( label );
    
    if ( running )
    {
        glColor3f( 0.0f, 0.5f, 0.0f );
        glRasterPos2i( params.world_width - 70, -help_area_height + line_offset );
        sprintf( label, "RUNNING" );
        draw_string( label );
    }
    else
    {
        glColor3f( 0.5f, 0.0f, 0.0f );
        glRasterPos2i( params.world_width - 70, -help_area_height + line_offset );
        sprintf( label, "STOPPED" );
        draw_string( label );
    }
    
    glColor3f( 0.0f, 0.0f, 0.0f );
    glRasterPos2i( params.world_width - 170, -help_area_height + line_offset );
    sprintf( label, "%s [%3d]", selections[cur_sel_index], increments[cur_inc_index] );
    draw_string( label );
    
    glBegin( GL_LINES );
        glVertex2f( 0.0f, 0.0f );
        glVertex2f( params.world_width, 0.0f );
    glEnd();
}
