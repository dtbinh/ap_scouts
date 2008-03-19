/*
 * This file is part of Robotic Swarm Simulator.
 * 
 * Copyright (C) 2007, 2008 Antons Rebguns <anton at cs dot uwyo dot edu>.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <gsl/gsl_rng.h>

#include "definitions.h"
#include "swarm.h"

gsl_rng *general_rng;

gsl_rng *goal_rng;
gsl_rng *obstacle_rng;
gsl_rng *agent_rng;

/**
 * \fn int read_config_file( char *p_filename )
 * \brief parses configuration file
 * \param p_filename to configuration file name
 * \return 0 on success, -1 on failure
 */
int read_config_file( char *p_filename )
{
    FILE *p_config;
    p_config = fopen( p_filename, "r" );
    
    if ( p_config != NULL )
    {
        char parameter[100];
        char value[100];
        
        while ( fscanf( p_config, "%100s%100s%*[^\n]", parameter, value ) != EOF )
        {
            if ( strcasecmp( "world_width", parameter ) == 0 )
            {
                params.world_width = atoi( value );
            }
            else if ( strcasecmp( "world_height", parameter ) == 0 )
            {
                params.world_height = atoi( value );
            }
            else if ( strcasecmp( "timer_delay_ms", parameter ) == 0 )
            {
                params.timer_delay_ms = atoi( value );
            }
            else if ( strcasecmp( "goal_random_seed", parameter ) == 0 )
            {
                params.goal_random_seed = atoi( value );
            }
            else if ( strcasecmp( "goal_width", parameter ) == 0 )
            {
                params.goal_width = atof( value );
            }
            else if ( strcasecmp( "goal_mass", parameter ) == 0 )
            {
                params.goal_mass = atof( value );
            }
            else if ( strcasecmp( "goal_quadrant", parameter ) == 0 )
            {
                params.goal_quadrant = atoi( value );
            }
            else if ( strcasecmp( "agent_random_seed", parameter ) == 0 )
            {
                params.agent_random_seed = atoi( value );
            }
            else if ( strcasecmp( "agent_number", parameter ) == 0 )
            {
                params.agent_number = atoi( value );
            }
            else if ( strcasecmp( "agent_radius", parameter ) == 0 )
            {
                params.agent_radius = atof( value );
            }
            else if ( strcasecmp( "agent_mass", parameter ) == 0 )
            {
                params.agent_mass = atof( value );
            }
            else if ( strcasecmp( "deployment_width", parameter ) == 0 )
            {
                params.deployment_width = atoi( value );
            }
            else if ( strcasecmp( "deployment_height", parameter ) == 0 )
            {
                params.deployment_height = atoi( value );
            }
            else if ( strcasecmp( "deployment_quadrant", parameter ) == 0 )
            {
                params.deployment_quadrant = atoi( value );
            }
            else if ( strcasecmp( "obstacle_random_seed", parameter ) == 0 )
            {
                params.obstacle_random_seed = atoi( value );
            }
            else if ( strcasecmp( "obstacle_number", parameter ) == 0 )
            {
                params.obstacle_number = atoi( value );
            }
            else if ( strcasecmp( "obstacle_radius", parameter ) == 0 )
            {
                params.obstacle_radius = atof( value );
            }
            else if ( strcasecmp( "obstacle_radius_min", parameter ) == 0 )
            {
                params.obstacle_radius_min = atof( value );
            }
            else if ( strcasecmp( "obstacle_radius_max", parameter ) == 0 )
            {
                params.obstacle_radius_max = atof( value );
            }
            else if ( strcasecmp( "obstacle_mass", parameter ) == 0 )
            {
                params.obstacle_mass = atof( value );
            }
            else if ( strcasecmp( "enable_agent_goal_f", parameter ) == 0 )
            {
                params.enable_agent_goal_f = atoi( value );
            }
            else if ( strcasecmp( "enable_agent_obstacle_f", parameter ) == 0 )
            {
                params.enable_agent_obstacle_f = atoi( value );
            }
            else if ( strcasecmp( "enable_agent_agent_f", parameter ) == 0 )
            {
                params.enable_agent_agent_f = atoi( value );
            }
            else if ( strcasecmp( "R", parameter ) == 0 )
            {
                params.R = atof( value );
            }
            else if ( strcasecmp( "friction_coefficient", parameter ) == 0 )
            {
                params.friction_coefficient = atof( value );
            }
            else if ( strcasecmp( "range_coefficient", parameter ) == 0 )
            {
                params.range_coefficient = atof( value );
            }
            else if ( strcasecmp( "max_V", parameter ) == 0 )
            {
                params.max_V = atof( value );
            }
            else if ( strcasecmp( "force_law", parameter ) == 0 )
            {
                params.force_law = atoi( value );
            }
            else if ( strcasecmp( "G_agent_agent", parameter ) == 0 )
            {
                params.G_agent_agent = atof( value );
            }
            else if ( strcasecmp( "G_agent_obstacle", parameter ) == 0 )
            {
                params.G_agent_obstacle = atof( value );
            }
            else if ( strcasecmp( "G_agent_goal", parameter ) == 0 )
            {
                params.G_agent_goal = atof( value );
            }
            else if ( strcasecmp( "p_agent_agent", parameter ) == 0 )
            {
                params.p_agent_agent = atof( value );
            }
            else if ( strcasecmp( "p_agent_obstacle", parameter ) == 0 )
            {
                params.p_agent_obstacle = atof( value );
            }
            else if ( strcasecmp( "p_agent_goal", parameter ) == 0 )
            {
                params.p_agent_goal = atof( value );
            }
            else if ( strcasecmp( "max_f_agent_agent_n", parameter ) == 0 )
            {
                params.max_f_agent_agent_n = atof( value );
            }
            else if ( strcasecmp( "max_f_agent_obstacle_n", parameter ) == 0 )
            {
                params.max_f_agent_obstacle_n = atof( value );
            }
            else if ( strcasecmp( "max_f_agent_goal_n", parameter ) == 0 )
            {
                params.max_f_agent_goal_n = atof( value );
            }
            else if ( strcasecmp( "epsilon_agent_agent", parameter ) == 0 )
            {
                params.epsilon_agent_agent = atof( value );
            }
            else if ( strcasecmp( "epsilon_agent_obstacle", parameter ) == 0 )
            {
                params.epsilon_agent_obstacle = atof( value );
            }
            else if ( strcasecmp( "epsilon_agent_goal", parameter ) == 0 )
            {
                params.epsilon_agent_goal = atof( value );
            }
            else if ( strcasecmp( "c_agent_agent", parameter ) == 0 )
            {
                params.c_agent_agent = atof( value );
            }
            else if ( strcasecmp( "c_agent_obstacle", parameter ) == 0 )
            {
                params.c_agent_obstacle = atof( value );
            }
            else if ( strcasecmp( "c_agent_goal", parameter ) == 0 )
            {
                params.c_agent_goal = atof( value );
            }
            else if ( strcasecmp( "d_agent_agent", parameter ) == 0 )
            {
                params.d_agent_agent = atof( value );
            }
            else if ( strcasecmp( "d_agent_obstacle", parameter ) == 0 )
            {
                params.d_agent_obstacle = atof( value );
            }
            else if ( strcasecmp( "d_agent_goal", parameter ) == 0 )
            {
                params.d_agent_goal = atof( value );
            }
            else if ( strcasecmp( "max_f_agent_agent_lj", parameter ) == 0 )
            {
                params.max_f_agent_agent_lj = atof( value );
            }
            else if ( strcasecmp( "max_f_agent_obstacle_lj", parameter ) == 0 )
            {
                params.max_f_agent_obstacle_lj = atof( value );
            }
            else if ( strcasecmp( "max_f_agent_goal_lj", parameter ) == 0 )
            {
                params.max_f_agent_goal_lj = atof( value );
            }
            else if ( strcasecmp( "time_limit", parameter ) == 0 )
            {
                params.time_limit = atoi( value );
            }
            else if ( strcasecmp( "runs_number", parameter ) == 0 )
            {
                params.runs_number = atoi( value );
            }
            else if ( strcasecmp( "run_simulation", parameter ) == 0 )
            {
                params.run_simulation = atoi( value );
            }
            else if ( strcasecmp( "env_probability", parameter ) == 0 )
            {
                params.env_probability = atof( value );
            }
            else if ( strcasecmp( "initialize_from_file", parameter ) == 0 )
            {
                params.initialize_from_file = atoi( value );
            }
            else if ( strcasecmp( "scenario_filename", parameter ) == 0 )
            {
                params.scenario_filename = strdup( value );
            }
            else if ( strcasecmp( "results_filename", parameter ) == 0 )
            {
                params.results_filename = strdup( value );
            }
            else if ( strcasecmp( "n_number", parameter ) == 0 )
            {
                params.n_number = atoi( value );
            }
            else if ( strcasecmp( "k_number", parameter ) == 0 )
            {
                params.k_number = atoi( value );
            }
            else if ( strcasecmp( "a_b_number", parameter ) == 0 )
            {
                params.a_b_number = atoi( value );
            }
            else if ( strcasecmp( "n_array", parameter ) == 0 )
            {
                params.n_array = ( int * ) calloc( params.n_number, sizeof( int ) );
                
                if ( params.n_array == NULL )
                {
                    printf( "ERROR (%s:%d): allocating memory for n_array failed!", __FILE__, __LINE__ );
                    return -1;
                }
                
                int i;
                
                params.n_array[0] = atoi( strtok( value, "," ) );
                
                for ( i = 1; i < params.n_number; ++i )
                {
                    params.n_array[i] = atoi( strtok( NULL, "," ) );
                }
            }
            else if ( strcasecmp( "k_array", parameter ) == 0 )
            {
                params.k_array = ( int * ) calloc( params.k_number, sizeof( int ) );

                if ( params.k_array == NULL )
                {
                    printf( "ERROR (%s:%d): allocating memory for k_array failed!", __FILE__, __LINE__ );
                    return -1;
                }
                
                int i;
                
                params.k_array[0] = atoi( strtok( value, "," ) );
                
                for ( i = 1; i < params.k_number; ++i )
                {
                    params.k_array[i] = atoi( strtok( NULL, "," ) );
                }
            }
            else if ( strcasecmp( "alpha_array", parameter ) == 0 )
            {
                params.alpha_array = ( float * ) calloc( params.a_b_number, sizeof( float ) );

                if ( params.alpha_array == NULL )
                {
                    printf( "ERROR (%s:%d): allocating memory for alpha_array failed!", __FILE__, __LINE__ );
                    return -1;
                }
                
                int i;
                
                params.alpha_array[0] = atof( strtok( value, "," ) );
                
                for ( i = 1; i < params.a_b_number; ++i )
                {
                    params.alpha_array[i] = atof( strtok( NULL, "," ) );
                }
            }
            else if ( strcasecmp( "beta_array", parameter ) == 0 )
            {
                params.beta_array = ( float * ) calloc( params.a_b_number, sizeof( float ) );

                if ( params.beta_array == NULL )
                {
                    printf( "ERROR (%s:%d): allocating memory for beta_array failed!", __FILE__, __LINE__ );
                    return -1;
                }
                
                int i;
                
                params.beta_array[0] = atof( strtok( value, "," ) );
                
                for ( i = 1; i < params.a_b_number; ++i )
                {
                    params.beta_array[i] = atof( strtok( NULL, "," ) );
                }
            }
            else
            {
                printf( "WARNING (%s:%d): Unknown parameter [%s]\n", __FILE__, __LINE__, parameter );
            }
        }
    }
    else
    {
        printf( "ERROR (%s:%d): failed to open configuration file \"%s\"!\n", __FILE__, __LINE__, p_filename );
        return -1;
    }
    
    fclose( p_config );
    
    return 0;
}

void output_simulation_parameters( FILE *output )
{
    fprintf( output, "\n\n" );
    
    fprintf( output, "# world_width = %d\n", params.world_width );
    fprintf( output, "# world_height = %d\n", params.world_height );
    fprintf( output, "# timer_delay_ms = %d\n", params.timer_delay_ms );
    fprintf( output, "# goal_random_seed = %d\n", params.goal_random_seed );
    fprintf( output, "# goal_width = %.2f\n", params.goal_width );
    fprintf( output, "# goal_mass = %.2f\n", params.goal_mass );
    fprintf( output, "# goal_quadrant = %d\n", params.goal_quadrant );
    fprintf( output, "# agent_random_seed = %d\n", params.agent_random_seed );
    fprintf( output, "# agent_number = %d\n", params.agent_number );
    fprintf( output, "# agent_radius = %.2f\n", params.agent_radius );
    fprintf( output, "# agent_mass = %.2f\n", params.agent_mass );
    fprintf( output, "# deployment_width = %d\n", params.deployment_width );
    fprintf( output, "# deployment_height = %d\n", params.deployment_height );
    fprintf( output, "# deployment_quadrant = %d\n", params.deployment_quadrant );
    fprintf( output, "# obstacle_random_seed = %d\n", params.obstacle_random_seed );
    fprintf( output, "# obstacle_number = %d\n", params.obstacle_number );
    fprintf( output, "# obstacle_radius = %.2f\n", params.obstacle_radius );
    fprintf( output, "# obstacle_radius_min = %.2f\n", params.obstacle_radius_min );
    fprintf( output, "# obstacle_radius_max = %.2f\n", params.obstacle_radius_max );
    fprintf( output, "# obstacle_mass = %.2f\n", params.obstacle_mass );
    fprintf( output, "# enable_agent_goal_f = %d\n", params.enable_agent_goal_f );
    fprintf( output, "# enable_agent_obstacle_f = %d\n", params.enable_agent_obstacle_f );
    fprintf( output, "# enable_agent_agent_f = %d\n", params.enable_agent_agent_f );
    fprintf( output, "# R = %.2f\n", params.R );
    fprintf( output, "# friction_coefficient = %.2f\n", params.friction_coefficient );
    fprintf( output, "# range_coefficient = %.2f\n", params.range_coefficient );
    fprintf( output, "# max_V = %.2f\n", params.max_V );
    fprintf( output, "# force_law = %d\n", params.force_law );
    fprintf( output, "# G_agent_agent = %.2f\n", params.G_agent_agent );
    fprintf( output, "# G_agent_obstacle = %.2f\n", params.G_agent_obstacle );
    fprintf( output, "# G_agent_goal = %.2f\n", params.G_agent_goal );
    fprintf( output, "# p_agent_agent = %.2f\n", params.p_agent_agent );
    fprintf( output, "# p_agent_obstacle = %.2f\n", params.p_agent_obstacle );
    fprintf( output, "# p_agent_goal = %.2f\n", params.p_agent_goal );
    fprintf( output, "# max_f_agent_agent_n = %.2f\n", params.max_f_agent_agent_n );
    fprintf( output, "# max_f_agent_obstacle_n = %.2f\n", params.max_f_agent_obstacle_n );
    fprintf( output, "# max_f_agent_goal_n = %.2f\n", params.max_f_agent_goal_n );
    fprintf( output, "# epsilon_agent_agent = %.2f\n", params.epsilon_agent_agent );
    fprintf( output, "# epsilon_agent_obstacle = %.2f\n", params.epsilon_agent_obstacle );
    fprintf( output, "# epsilon_agent_goal = %.2f\n", params.epsilon_agent_goal );
    fprintf( output, "# c_agent_agent = %.2f\n", params.c_agent_agent );
    fprintf( output, "# c_agent_obstacle = %.2f\n", params.c_agent_obstacle );
    fprintf( output, "# c_agent_goal = %.2f\n", params.c_agent_goal );
    fprintf( output, "# d_agent_agent = %.2f\n", params.d_agent_agent );
    fprintf( output, "# d_agent_obstacle = %.2f\n", params.d_agent_obstacle );
    fprintf( output, "# d_agent_goal = %.2f\n", params.d_agent_goal );
    fprintf( output, "# max_f_agent_agent_lj = %.2f\n", params.max_f_agent_agent_lj );
    fprintf( output, "# max_f_agent_obstacle_lj = %.2f\n", params.max_f_agent_obstacle_lj );
    fprintf( output, "# max_f_agent_goal_lj = %.2f\n", params.max_f_agent_goal_lj );
    fprintf( output, "# time_limit = %d\n", params.time_limit );
    fprintf( output, "# runs_number = %d\n", params.runs_number );
    fprintf( output, "# run_simulation = %d\n", params.run_simulation );
    fprintf( output, "# env_probability = %.2f\n", params.env_probability );
    fprintf( output, "# initialize_from_file = %d\n", params.initialize_from_file );
    fprintf( output, "# scenario_filename = %s\n", params.scenario_filename );
    fprintf( output, "# results_filename = %s\n", params.results_filename );
    fprintf( output, "# n_number = %d\n", params.n_number );
    fprintf( output, "# k_number = %d\n", params.k_number );
    fprintf( output, "# a_b_number = %d\n", params.a_b_number );
    fprintf( output, "# n_array = ");
    
    int i;
    
    for ( i = 0; i < params.n_number; ++i )
    {
        fprintf( output, "%d,", params.n_array[i] );
    }
    
    fprintf( output, "\n# k_array = " );
    
    for ( i = 0; i < params.k_number; ++i )
    {
        fprintf( output, "%d,", params.k_array[i] );
    }
    
    fprintf( output, "\n# alpha_array = " );
    
    for ( i = 0; i < params.a_b_number; ++i )
    {
        fprintf( output, "%.2f,", params.alpha_array[i] );
    }

    fprintf( output, "\n# beta_array = " );
    
    for ( i = 0; i < params.a_b_number; ++i )
    {
        fprintf( output, "%.2f,", params.beta_array[i] );
    }

    fprintf( output, "\n\n" );
}

int create_goal( void )
{
    /******************** Initialize goal ********************************/
    goal = ( Goal * ) malloc( sizeof( Goal ) );
    
    if ( goal == NULL )
    {
        printf( "ERROR (%s:%d): allocating memory for a goal failed!", __FILE__, __LINE__ );
        return -1;
    }
    
    goal->id = 0;
    goal->mass = params.goal_mass;
    goal->width = params.goal_width;
    
    float quadrant_width = params.world_width / 3.0f;
    float quadrant_height = params.world_height / 3.0f;

    float offset_x;
    float offset_y;
    
    /*
     *         ------------- 
     *         | NW | N | NE |
     *         |-------------
     *         | N  | C | E  |
     *         |-------------
     *         | SW | S | SE |
     *          -------------
     */
    switch ( params.goal_quadrant )
    {
        case NW:
            offset_x = 0.0f;
            offset_y = quadrant_height * 2.0f;
            break;
            
        case N:
            offset_x = quadrant_width;
            offset_y = quadrant_height * 2.0f;
            break;
            
        case NE:
            offset_x = quadrant_width * 2.0f;
            offset_y = quadrant_height * 2.0f;
            break;
            
        case W:
            offset_x = 0.0f;
            offset_y = quadrant_height;
            break;
            
        case C:
            offset_x = quadrant_width;
            offset_y = quadrant_height;
            break;
            
        case E:
            offset_x = quadrant_width * 2.0f;;
            offset_y = quadrant_height * 2.0f;
            break;
            
        case SW:
            offset_x = 0.0f;
            offset_y = 0.0f;
            break;
            
        case S:
            offset_x = quadrant_width;
            offset_y = 0.0f;
            break;
            
        case SE:
            offset_x = quadrant_width * 2.0f;
            offset_y = 0.0f;
            break;
            
        default:
            offset_x = 0.0f;
            offset_y = 0.0f;
    }
    
    goal->position.x = gsl_rng_get( goal_rng ) % ( int ) quadrant_width + offset_x;
    goal->position.y = gsl_rng_get( goal_rng ) % ( int ) quadrant_height + offset_y;
    
    memcpy( goal->color, goal_color, 3 * sizeof( float ) );
    
    return 0;
}

void deploy_agent( Agent *agent )
{
    float quadrant_width = params.world_width / 3.0f;
    float quadrant_height = params.world_height / 3.0f;

    float offset_x;
    float offset_y;
    
    /*
     *         ------------- 
     *         | NW | N | NE |
     *         |-------------
     *         | N  | C | E  |
     *         |-------------
     *         | SW | S | SE |
     *          -------------
     */
    switch ( params.deployment_quadrant )
    {
        case NW:
            offset_x = 10.0f;
            offset_y = params.world_height - params.deployment_height - 10.0f;
            break;
            
        case N:
            offset_x = quadrant_width + ( quadrant_width - params.deployment_height ) / 2.0f;
            offset_y = params.world_height - params.deployment_height - 10.0f;
            break;
            
        case NE:
            offset_x = params.world_width - params.deployment_width - 10.0f;
            offset_y = params.world_height - params.deployment_height - 10.0f;
            break;
            
        case W:
            offset_x = 10.0f;
            offset_y = quadrant_height + ( quadrant_height - params.deployment_height ) / 2.0f;
            break;
            
        case C:
            offset_x = quadrant_width + ( quadrant_width - params.deployment_height ) / 2.0f;
            offset_y = quadrant_height + ( quadrant_height - params.deployment_height ) / 2.0f;
            break;
            
        case E:
            offset_x = params.world_width - params.deployment_width - 10.0f;
            offset_y = quadrant_height + ( quadrant_height - params.deployment_height ) / 2.0f;
            break;
            
        case SW:
            offset_x = 10.0f;
            offset_y = 10.0f;
            break;
            
        case S:
            offset_x = quadrant_width + ( quadrant_width - params.deployment_height ) / 2.0f;
            offset_y = 10.0f;
            break;
            
        case SE:
            offset_x = params.world_width - params.deployment_width - 10.0f;
            offset_y = 10.0f;
            break;
            
        default:
            offset_x = 10.0f;
            offset_y = 10.0f;
    }
    
    agent->i_position.x = gsl_rng_get( agent_rng ) % params.deployment_width + offset_x;
    agent->i_position.y = gsl_rng_get( agent_rng ) % params.deployment_height + offset_y;
    
    agent->position.x = agent->i_position.x;
    agent->position.y = agent->i_position.y;
}

Agent * create_agent( int id )
{
    Agent *agent = ( Agent * ) malloc( sizeof( Agent ) );
    
    if ( agent == NULL )
    {
        printf( "ERROR (%s:%d): allocating memory for an agent failed!", __FILE__, __LINE__ );
        return NULL;
    }
    
    agent->id = id;
    agent->mass = params.agent_mass;
    agent->collided = false;
    agent->goal_reached = false;
    agent->radius = params.agent_radius;
    agent->velocity.x = 0.0f;
    agent->velocity.y = 0.0f;
    
    deploy_agent( agent );
    
    memcpy( agent->color, agent_color, 3 * sizeof( float ) );
    
    return agent;
}

int create_swarm( void )
{
    /******************** Initialize agents ******************************/
    agents = ( Agent ** ) calloc( params.agent_number, sizeof( Agent * ) );
    
    if ( agents == NULL )
    {
        printf( "ERROR (%s:%d): allocating memory for agents array failed!", __FILE__, __LINE__ );
        return -1;
    }
    
    int i;
    
    for ( i = 0; i < params.agent_number; ++i )
    {
        agents[i] = create_agent( i );
        
        if ( agents[i] == NULL )
        {
            printf( "ERROR (%s:%d): allocating memory for agent %d failed!", __FILE__, __LINE__, i );
            return -1;
        }
    }

    return 0;
}

Obstacle * create_obstacle( int id, bool random_radius, float radius_range )
{
    Obstacle *obstacle = ( Obstacle * ) malloc( sizeof( Obstacle ) );
    
    if ( obstacle == NULL )
    {
        printf( "ERROR (%s:%d): allocating memory for an obstacle failed!", __FILE__, __LINE__ );
        return NULL;
    }
    
    obstacle->id = id;
    obstacle->mass = params.obstacle_mass;
            
    if ( random_radius )
    {
        double random = ( double ) gsl_rng_get( general_rng ) / ( double ) gsl_rng_max( general_rng );
        obstacle->radius = random * radius_range + params.obstacle_radius_min;
    } 
    else { obstacle->radius = params.obstacle_radius; }
    
    obstacle->position.x = gsl_rng_get( obstacle_rng ) % ( params.world_width - 20 ) + 10;
    obstacle->position.y = gsl_rng_get( obstacle_rng ) % ( params.world_height - 20 ) + 10;
    
    memcpy( obstacle->color, obstacle_color, 3 * sizeof( float ) );
    
    return obstacle;
}

int create_obstacle_course( void )
{
    /******************** Initialize obstacles ***************************/
    obstacles = ( Obstacle ** ) calloc( params.obstacle_number, sizeof( Obstacle * ) );
    
    if ( obstacles == NULL )
    {
        printf( "ERROR (%s:%d): allocating memory for an obstacles array failed!", __FILE__, __LINE__ );
        return -1;
    }
    
    bool random_radius = ( params.obstacle_radius == 0 ) ? true : false;
    float radius_range = params.obstacle_radius_max - params.obstacle_radius_min;

    int i;
    
    for ( i = 0; i < params.obstacle_number; ++i )
    {
        obstacles[i] = create_obstacle( i, random_radius, radius_range );
        
        if ( obstacles[i] == NULL )
        {
            printf( "ERROR (%s:%d): allocating memory for obstacle %d failed!", __FILE__, __LINE__, i );
            return -1;
        }
    }

    return 0;
}

void free_memory( void )
{
    int i;
    
    if ( goal != NULL ) { free( goal ); }
    
    for ( i = 0; i < params.agent_number; ++i )
    {
        if ( agents[i] != NULL ) { free( agents[i] ); }
    }
    
    if ( agents != NULL ) { free( agents ); }
    
    for ( i = 0; i < params.obstacle_number; ++i )
    {
        if ( obstacles[i] != NULL ) { free( obstacles[i] ); }
    }
    
    if ( obstacles != NULL ) { free( obstacles ); }
    if ( params.n_array != NULL ) { free( params.n_array ); }
    if ( params.k_array != NULL ) { free( params.k_array ); }
    
    if ( general_rng != NULL ) { gsl_rng_free( goal_rng ); }
    if ( goal_rng != NULL ) { gsl_rng_free( goal_rng ); }
    if ( obstacle_rng != NULL ) { gsl_rng_free( obstacle_rng ); }
    if ( agent_rng != NULL ) { gsl_rng_free( agent_rng ); }
}

void reset_statistics( void )
{
    stats.time_step = 0;
    stats.reach_ratio = 0.0f;
    stats.reached_goal = 0;
    stats.collisions = 0;
    stats.collision_ratio = 0.0f;
}

/**
 * \fn bool agent_reached_goal_actual( Agent *agent )
 * \brief decide if agent reached the goal (agent should actually "touch" the goal)
 * \param agent pointer to an agent
 * \return true if agent reached the goal, false otherwise
 */
bool agent_reached_goal_actual( Agent *agent )
{
    Vector2f g_pos = goal->position;
    Vector2f a_pos = agent->position;
    
    float g_x1 = g_pos.x - goal->width / 2.0f;
    float g_y1 = g_pos.y - goal->width / 2.0f;
    
    float g_x2 = g_pos.x + goal->width / 2.0f;
    float g_y2 = g_pos.y + goal->width / 2.0f;
    
    if ( a_pos.x >= g_x1 && a_pos.y >= g_y1 &&
         a_pos.x <= g_x2 && a_pos.y <= g_y2 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * \fn bool agent_reached_goal_radius( Agent *agent )
 * \brief decide if agent reached the goal (agent is within some predefined distance to the center of the goal)
 * \param agent pointer to an agent
 * \return true if agent reached the goal, false otherwise
 */
bool agent_reached_goal_radius( Agent *agent )
{
    float distance_to_obj = hypotf( agent->position.x - goal->position.x, agent->position.y - goal->position.y );

    if ( distance_to_obj < params.range_coefficient * params.R ) { return true; }
    else { return false; }
}

bool agent_reached_goal_chain( Agent *agent )
{
    if ( agent_reached_goal_radius( agent ) )
    {
        return true;
    }
    else
    {
        Vector2f agent1_pos = agent->position;
        
        int i;

        for ( i = 0; i < params.agent_number; ++i )
        {
            Agent *agent2 = agents[i];
            Vector2f agent2_pos = agent2->position;

            if ( agent2->goal_reached )
            {
                float distance = hypotf( agent1_pos.x - agent2_pos.x, agent1_pos.y - agent2_pos.y );
                if ( distance <= params.range_coefficient * params.R ) { return true; }
            }
        }
    }

    return false;
}

void initialize_simulation( void )
{
    running = false;
    
    // Initialize simulation parameters to sane defaults,
    // in case some information is missing from config file
    params.world_width = 800;
    params.world_height = 600;
    params.timer_delay_ms = 8;
    params.goal_random_seed = 0;
    params.goal_width = 15.0f;
    params.goal_mass = 10.0f;
    params.goal_quadrant = 2;
    params.agent_random_seed = 0;
    params.agent_number = 100;
    params.deployment_width = 100;
    params.deployment_height = 100;
    params.deployment_quadrant = 4;
    params.obstacle_random_seed = 0;
    params.obstacle_number = 20;
    params.obstacle_radius = 3.0f;
    params.obstacle_mass = 1.0f;
    params.enable_agent_goal_f = 1;
    params.enable_agent_obstacle_f = 1;
    params.enable_agent_agent_f = 0;
    params.R = 50.0f;
    params.friction_coefficient = 0.5f;
    params.range_coefficient = 1.5f;
    params.force_law = 0;
    params.max_V = 0.5f;
    params.G_agent_agent = 1000.0f;
    params.G_agent_obstacle = 1000.0f;
    params.G_agent_goal = 1000.0f;
    params.p_agent_agent = 2.0f;
    params.p_agent_obstacle = 2.0f;
    params.p_agent_goal = 2.0f;
    params.max_f_agent_agent_n = 4.0f;
    params.max_f_agent_obstacle_n = 14.0f;
    params.max_f_agent_goal_n = 4.0f;
    params.epsilon_agent_agent = 16.5f;
    params.epsilon_agent_obstacle = 16.5f;
    params.epsilon_agent_goal = 16.5f;
    params.c_agent_agent = 0.1f;
    params.c_agent_obstacle = 0.1f;
    params.c_agent_goal = 0.1f;
    params.d_agent_agent = 0.1f;
    params.d_agent_obstacle = 0.1f;
    params.d_agent_goal = 0.1f;
    params.max_f_agent_agent_lj = 4.0f;
    params.max_f_agent_obstacle_lj = 14.0f;
    params.max_f_agent_goal_lj = 4.0f;
    params.time_limit = 1000;
    params.runs_number = 10;
    params.run_simulation = false;
    params.env_probability = 0.9f;
    params.initialize_from_file = false;
    
    // set function to use when deciding wheter agent reached a goal
    agent_reached_goal = agent_reached_goal_chain;
    
    // initialize random number generators for all objects
    gsl_rng_set( general_rng, 0 );
    gsl_rng_set( goal_rng, 0 );
    gsl_rng_set( obstacle_rng, 0 );
    gsl_rng_set( agent_rng, 0 );
    
    // Reset statistics
    reset_statistics();    
}

int save_scenario( char *filename )
{
    FILE *config;
    config = fopen( filename, "w" );
    
    if ( config != NULL )
    {
        int i;

        // World parameters
        fprintf( config, "world_width              %d    # Simulation area width\n",  params.world_width );
        fprintf( config, "world_height             %d    # Simulation area height\n", params.world_height );
        fprintf( config, "\n" );
        
        fprintf( config, "timer_delay_ms           %d    # Controls simulation speed\n", params.timer_delay_ms );
        fprintf( config, "\n" );
        
        // Goal parameters
        fprintf( config, "goal_random_seed         %d    # Random number seed for goal; 0 for random seed initialized with current time\n", params.goal_random_seed );
        fprintf( config, "goal_width               %f    # Size of the goal\n",                                                             params.goal_width );
        fprintf( config, "goal_mass                %f    # Goal mass (for calculating forces)\n",                                           params.goal_mass );
        fprintf( config, "goal_quadrant            %d    # Goal position\n",                                                                params.goal_quadrant );
        fprintf( config, "\n" );
        
        // Agent parameters
        fprintf( config, "agent_random_seed        %d    # Random number seed for agents; 0 for random seed initialized with current time\n", params.agent_random_seed );
        fprintf( config, "agent_number             %d    # Number of agents in the swarm\n",                                                  params.agent_number );
        fprintf( config, "agent_radius             %f    # Size of the agent\n",                                                              params.agent_radius );
        fprintf( config, "agent_mass               %f    # Mass of the agent\n",                                                              params.agent_mass );
        fprintf( config, "deployment_width         %d    # Initial deployment area width\n",                                                  params.deployment_width );
        fprintf( config, "deployment_height        %d    # Initial deployment area width\n",                                                  params.deployment_height );
        fprintf( config, "deployment_quadrant      %d    # Initial deployment area position\n",                                               params.deployment_quadrant );
        fprintf( config, "\n" );

        // Obstacle parameters
        fprintf( config, "obstacle_random_seed     %d    # Random number seed for obstacles; 0 for random seed initialized with current time\n", params.obstacle_random_seed );
        fprintf( config, "obstacle_number          %d    # Number of obstacles\n",                                                               params.obstacle_number );
        fprintf( config, "obstacle_radius          %f    # Size of the obstacle; 0.0 for random, specify min and max below\n",                   params.obstacle_radius );
        fprintf( config, "obstacle_radius_min      %f    # Minimum obstacle radius\n",                                                           params.obstacle_radius_min );
        fprintf( config, "obstacle_radius_max      %f    # Maximum obstacle radius\n",                                                           params.obstacle_radius_max );
        fprintf( config, "obstacle_mass            %f    # Obstacle mass (for calculating forces)\n",                                            params.obstacle_mass );
        fprintf( config, "\n" );

        // Enable/Disable forces
        fprintf( config, "enable_agent_goal_f      %d    # enable/disable agent-goal interactions, 0 - disable, 1 - enable\n",     params.enable_agent_goal_f );
        fprintf( config, "enable_agent_obstacle_f  %d    # enable/disable agent-obstacle interactions, 0 - disable, 1 - enable\n", params.enable_agent_obstacle_f );
        fprintf( config, "enable_agent_agent_f     %d    # enable/disable agent-agent interactions, 0 - disable, 1 - enable\n",    params.enable_agent_agent_f );
        fprintf( config, "\n" );

        // General physics parameters
        fprintf( config, "R                        %f    # Desired distance R\n",                       params.R );
        fprintf( config, "friction_coefficient     %f    # Friction coefficient (for stabilization)\n", params.friction_coefficient );
        fprintf( config, "range_coefficient        %f    # Agent visual range coefficient\n",           params.range_coefficient );
        fprintf( config, "max_V                    %f    # Maximum agent velocity\n",                   params.max_V );
        fprintf( config, "force_law                %d    # 0 - Newtonian, 1 - Lennard-Jones\n",         params.force_law );
        fprintf( config, "\n" );

         // Newtonian force law parameters
        fprintf( config, "G_agent_agent            %f    # Newtonian - Gravitational constant of agent-agent interactions\n",    params.G_agent_agent );
        fprintf( config, "G_agent_obstacle         %f    # Newtonian - Gravitational constant of agent-obstacle interactions\n", params.G_agent_obstacle );
        fprintf( config, "G_agent_goal             %f    # Newtonian - Gravitational constant of agent-goal interactions\n",     params.G_agent_goal );
        fprintf( config, "\n" );

        fprintf( config, "p_agent_agent            %f    # Newtonian - (distance_between_objects) ^ p of agent-agent interactions\n",    params.p_agent_agent );
        fprintf( config, "p_agent_obstacle         %f    # Newtonian - (distance_between_objects) ^ p of agent-obstacle interactions\n", params.p_agent_obstacle );
        fprintf( config, "p_agent_goal             %f    # Newtonian - (distance_between_objects) ^ p of agent-goal interactions\n",     params.p_agent_goal );
        fprintf( config, "\n" );

        fprintf( config, "max_f_agent_agent_n      %f    # Newtonian - Force cutoff agent-agent\n",    params.max_f_agent_agent_n );
        fprintf( config, "max_f_agent_obstacle_n   %f    # Newtonian - Force cutoff agent-obstacle\n", params.max_f_agent_obstacle_n );
        fprintf( config, "max_f_agent_goal_n       %f    # Newtonian - Force cutoff agent-goal\n",     params.max_f_agent_goal_n );
        fprintf( config, "\n" );

        // Lennard-Jones force law parameters
        fprintf( config, "epsilon_agent_agent      %f    # LJ - Strength of agent-agent interactions (acceptable values 1.0 - 20.0)\n",    params.epsilon_agent_agent );
        fprintf( config, "epsilon_agent_obstacle   %f    # LJ - Strength of agent-obstacle interactions (acceptable values 1.0 - 20.0)\n", params.epsilon_agent_obstacle );
        fprintf( config, "epsilon_agent_goal       %f    # LJ - Strength of agent-goal interactions (acceptable values 1.0 - 20.0)\n",     params.epsilon_agent_goal );
        fprintf( config, "\n" );

        fprintf( config, "c_agent_agent            %f    # LJ - Attractive agent-agent parameter (acceptable values 1.0 - 10.0)\n",    params.c_agent_agent );
        fprintf( config, "c_agent_obstacle         %f    # LJ - Attractive agent-obstacle parameter (acceptable values 1.0 - 10.0)\n", params.c_agent_obstacle );
        fprintf( config, "c_agent_goal             %f    # LJ - Attractive agent-goal parameter (acceptable values 1.0 - 10.0)\n",     params.c_agent_goal );
        fprintf( config, "\n" );

        fprintf( config, "d_agent_agent            %f    # LJ - Repulsive agent-agent parameter (acceptable values 1.0 - 10.0)\n",    params.d_agent_agent );
        fprintf( config, "d_agent_obstacle         %f    # LJ - Repulsive agent-obstacle parameter (acceptable values 1.0 - 10.0)\n", params.d_agent_obstacle );
        fprintf( config, "d_agent_goal             %f    # LJ - Repulsive agent-goal parameter (acceptable values 1.0 - 10.0)\n",     params.d_agent_goal );
        fprintf( config, "\n" );

        fprintf( config, "max_f_agent_agent_lj     %f    # LJ - Force cutoff agent-agent\n",    params.max_f_agent_agent_lj );
        fprintf( config, "max_f_agent_obstacle_lj  %f    # LJ - Force cutoff agent-obstacle\n", params.max_f_agent_obstacle_lj );
        fprintf( config, "max_f_agent_goal_lj      %f    # LJ - Force cutoff agent-goal\n",     params.max_f_agent_goal_lj );
        fprintf( config, "\n" );

        // Batch parameters
        fprintf( config, "time_limit               %d    # CLI only - time limit per run\n", params.time_limit );
        fprintf( config, "runs_number              %d    # CLI only - number of runs\n",     params.runs_number );
        fprintf( config, "run_simulation           %d    # CLI only - run simulator to get probabilities or use random number generator, 0 - RNG, 1 - simulation\n", params.run_simulation );
        fprintf( config, "env_probability           %f     # CLI only - used when run_simulation = 0\n", params.env_probability );
        fprintf( config, "\n" );

        fprintf( config, "initialize_from_file     %d    # Initialize all objects state from scenario file, 0 - disable, 1 - enable\n", params.initialize_from_file );
        fprintf( config, "scenario_filename        %s    # Scenario filename\n",                                                        params.scenario_filename );
        fprintf( config, "results_filename         %s    # CLI only - File name for writing results\n",                                 params.results_filename );
        fprintf( config, "\n" );

        fprintf( config, "n_number                 %d    # CLI only - Number of different n values\n",                                    params.n_number );
        fprintf( config, "k_number                 %d    # CLI only - Number of different k values, k = n will be added automatically\n", params.k_number );
        fprintf( config, "a_b_number               %d    # CLI only - Number of prior distributions (alpha-beta pairs)\n",                params.a_b_number );
        fprintf( config, "\n" );

        fprintf( config, "n_array                  " );

        for ( i = 0; i < params.n_number; ++i )
        {
            fprintf( config, "%d,", params.n_array[i] );
        }

        fprintf( config, "   # CLI only - Actual n values\n" );

        fprintf( config, "k_array                  " );

        for ( i = 0; i < params.k_number; ++i )
        {
            fprintf( config, "%d,", params.k_array[i] );
        }

        fprintf( config, "   # CLI only - Actual k values\n" );

        fprintf( config, "alpha_array              " );

        for ( i = 0; i < params.a_b_number; ++i )
        {
            fprintf( config, "%f,", params.alpha_array[i] );
        }

        fprintf( config, "   # CLI only - Actual alpha values\n" );
        
        fprintf( config, "beta_array               " );

        for ( i = 0; i < params.a_b_number; ++i )
        {
            fprintf( config, "%f,", params.beta_array[i] );
        }

        fprintf( config, "   # CLI only - Actual beta values\n" );        
    }
    else
    {
        printf( "Configuration file [%s] could not be created!", filename );
        return -1;
    }
    
    fclose( config );

    if ( params.initialize_from_file )
    {
        FILE *scenario;
        scenario = fopen( params.scenario_filename, "w" );

        if ( scenario != NULL )
        {
            int i;
            
            // Statistics
            fprintf( scenario, "%d %d %f %d %f\n", stats.time_step, stats.reached_goal, stats.reach_ratio, stats.collisions, stats.collision_ratio );

            // Current values for goal
            fprintf( scenario, "%d %f %f %f %f\n", goal->id, goal->mass, goal->width, goal->position.x, goal->position.y );

            // Current values for all agents
            for ( i = 0; i < params.agent_number; ++i )
            {
                Agent *a = agents[i];

                fprintf( scenario, "%d %f %f %d ", a->id, a->mass, a->radius, a->goal_reached );
                fprintf( scenario, "%f %f ", a->i_position.x, a->i_position.y );
                fprintf( scenario, "%f %f ", a->position.x, a->position.y );
                fprintf( scenario, "%f %f\n", a->velocity.x, a->velocity.y );
            }

            // Current values for all obstacles
            for ( i = 0; i < params.obstacle_number; ++i )
            {
                Obstacle *o = obstacles[i];

                fprintf( scenario, "%d %f %f ", o->id, o->mass, o->radius );
                fprintf( scenario, "%f %f\n", o->position.x, o->position.y );
            }
        }
        else
        {
            printf( "Scenario file [%s] could not be created!", filename );
            return -1;
        }
        
        fclose( scenario );
    }

    return 0;
}

int load_scenario( char *filename )
{
    free_memory();
    
    // create random number generators for all objetcts
    general_rng = gsl_rng_alloc( gsl_rng_ranlxs2 );
    goal_rng = gsl_rng_alloc( gsl_rng_ranlxs2 );
    obstacle_rng = gsl_rng_alloc( gsl_rng_ranlxs2 );
    agent_rng = gsl_rng_alloc( gsl_rng_ranlxs2 );

    // Load defaults in case config file is broken
    initialize_simulation();
    
    // Read configuration
    if ( read_config_file( filename ) == -1 ) { return -1; }
    output_simulation_parameters( stdout );

    // Initialize goal random number seed
    if ( params.goal_random_seed == -1 ) { gsl_rng_set( goal_rng, ( unsigned int ) time( NULL ) ); }
    else { gsl_rng_set( goal_rng, params.goal_random_seed ); }
    
    // Initialize agents random number seed
    if ( params.agent_random_seed == -1 ) { gsl_rng_set( agent_rng, ( unsigned int ) time( NULL ) ); }
    else { gsl_rng_set( agent_rng, ( unsigned int ) params.agent_random_seed ); }
    
    // Initialize obstacles random number seed
    if ( params.obstacle_random_seed == -1 ) { gsl_rng_set( obstacle_rng, ( unsigned int ) time( NULL ) ); }
    else { gsl_rng_set( obstacle_rng, params.obstacle_random_seed ); }
    
    // Load scenario if necessary
    if ( params.initialize_from_file )
    {
        FILE *scenario;
        scenario = fopen( params.scenario_filename, "r" );
    
        if ( scenario != NULL )
        {
            int i;
        
            // Statistics
            fscanf( scenario, "%d %d %f %d %f", &stats.time_step, &stats.reached_goal, &stats.reach_ratio, &stats.collisions, &stats.collision_ratio );

            /******************************* Current values for all objects **********************************************/
            // Create simulation objects
            if ( create_goal() != 0 ) { return -1; }
            if ( create_swarm() != 0 ) { return -1; }
            if ( create_obstacle_course() != 0 ) { return -1; }

            fscanf( scenario, "%d %f %f %f %f", &(goal->id), &(goal->mass), &(goal->width), &(goal->position.x), &(goal->position.y) );

            for ( i = 0; i < params.agent_number; ++i )
            {
                Agent *a = agents[i];

                fscanf( scenario, "%d %f %f %d", &(a->id), &(a->mass), &(a->radius), ( int * ) &(a->goal_reached) );
                fscanf( scenario, "%f %f", &(a->i_position.x), &(a->i_position.y) );
                fscanf( scenario, "%f %f", &(a->position.x), &(a->position.y) );
                fscanf( scenario, "%f %f", &(a->velocity.x), &(a->velocity.y) );
            }

            for ( i = 0; i < params.obstacle_number; ++i )
            {
                Obstacle *o = obstacles[i];

                fscanf( scenario, "%d %f %f", &(o->id), &(o->mass), &(o->radius) );
                fscanf( scenario, "%f %f", &(o->position.x), &(o->position.y) );
            }
            /************************************************************************************************************/
        }
        else
        {
            printf( "Scenario file [%s] not found!\n", params.scenario_filename );
            return -1;
        }
    
        fclose( scenario );
    }
    else
    {
        running = false;

        // Reset statistics
        reset_statistics();

        // Create simulation objects
        if ( create_goal() != 0 ) { return -1; }
        if ( create_swarm() != 0 ) { return -1; }
        if ( create_obstacle_course() != 0 ) { return -1; }
    }
    
    return 0;
}

void restart_simulation( void )
{
    int i;
    
    running = false;
    
    // Reset statistics
    reset_statistics();
    
    // initialize random number generators for all objects
    gsl_rng_set( goal_rng, 0 );
    gsl_rng_set( obstacle_rng, 0 );
    gsl_rng_set( agent_rng, 0 );
    
    for ( i = 0; i < params.agent_number; ++i )
    {
        agents[i]->position.x = agents[i]->i_position.x;
        agents[i]->position.y = agents[i]->i_position.y;
        agents[i]->velocity.x = 0.0f;
        agents[i]->velocity.y = 0.0f;
        agents[i]->collided = false;
        agents[i]->goal_reached = false;
        
        memcpy( agents[i]->color, agent_color, 3 * sizeof( float ) );
    }
}

int change_agent_number( int agent_number )
{
    int i;    
    int delta = agent_number - params.agent_number;
    
    if ( delta > 0 )
    {
        agents = ( Agent ** ) realloc( agents, agent_number * sizeof( Agent * ) );
        
        if ( agents == NULL )
        {
            printf( "ERROR (%s:%d): expanding memory for agents array failed!", __FILE__, __LINE__ );
            return -1;
        }
        
        for ( i = params.agent_number; i < agent_number; ++i )
        {
            agents[i] = create_agent( i );
        }
        
        params.agent_number = agent_number;
    }
    else if ( delta < 0 && abs( delta ) < params.agent_number )
    {
        agents = ( Agent ** ) realloc( agents, agent_number * sizeof( Agent * ) );
        
        if ( agents == NULL )
        {
            printf( "ERROR (%s:%d): shrinking memory for agents array failed!", __FILE__, __LINE__ );
            return -1;
        }
        
        params.agent_number = agent_number;
    }
    else if ( delta < 0 && abs( delta ) >= params.agent_number )
    {
        agents = ( Agent ** ) realloc( agents, sizeof( Agent * ) );
        
        if ( agents == NULL )
        {
            printf( "ERROR (%s:%d): shrinking memory for agents array failed!", __FILE__, __LINE__ );
            return -1;
        }
        
        params.agent_number = 1;
    }
    
    return 0;
}

int change_obstacle_number( int obstacle_number )
{
    int i;    
    int delta = obstacle_number - params.obstacle_number;
    
    if ( delta > 0 )
    {
        obstacles = ( Obstacle ** ) realloc( obstacles, obstacle_number * sizeof( Obstacle * ) );
        
        if ( obstacles == NULL )
        {
            printf( "ERROR (%s:%d): expanding memory for obstacles array failed!", __FILE__, __LINE__ );
            return -1;
        }
        
        bool random_radius = ( params.obstacle_radius == 0 ) ? true : false;
        float radius_range = params.obstacle_radius_max - params.obstacle_radius_min;
        
        for ( i = params.obstacle_number; i < obstacle_number; ++i )
        {
            obstacles[i] = create_obstacle( i, random_radius, radius_range );
        }
        
        params.obstacle_number = obstacle_number;
    }
    else if ( delta < 0 && abs( delta ) < params.obstacle_number )
    {
        obstacles = ( Obstacle ** ) realloc( obstacles, obstacle_number * sizeof( Obstacle * ) );
        
        if ( agents == NULL )
        {
            printf( "ERROR (%s:%d): shrinking memory for obstacles array failed!", __FILE__, __LINE__ );
            return -1;
        }
        
        params.obstacle_number = obstacle_number;
    }
    else if ( delta < 0 && abs( delta ) >= params.obstacle_number )
    {
        obstacles = ( Obstacle ** ) realloc( obstacles, sizeof( Obstacle * ) );
        
        if ( agents == NULL )
        {
            printf( "ERROR (%s:%d): shrinking memory for obstacles array failed!", __FILE__, __LINE__ );
            return -1;
        }
        
        params.obstacle_number = 1;
    }
    
    return 0;
}

float calculate_force( Agent *agent, void *object, ObjectType obj_type )
{
    Vector2f agent_pos = agent->position;
    Vector2f obj_pos;
    float obj_mass = 0.0f;
    float distance_to_obj = 0.0f;
    
    switch( obj_type )
    {
        case AGENT:
            obj_pos = ( ( Agent * ) object )->position;
            obj_mass = ( ( Agent * ) object )->mass;
            distance_to_obj = hypotf( agent_pos.x - obj_pos.x, agent_pos.y - obj_pos.y );
            break;
            
        case OBSTACLE:
            obj_pos = ( ( Obstacle * ) object )->position;
            obj_mass = ( ( Obstacle * ) object )->mass;
            distance_to_obj = hypotf( agent_pos.x - obj_pos.x, agent_pos.y - obj_pos.y );
            distance_to_obj -= ( ( Obstacle * ) object )->radius;
            break;
            
        case GOAL:
            obj_pos = ( ( Goal * ) object )->position;
            obj_mass = ( ( Goal * ) object )->mass;
            distance_to_obj = hypotf( agent_pos.x - obj_pos.x, agent_pos.y - obj_pos.y );
            break;
    }

    // prevent division by 0 later
    distance_to_obj = distance_to_obj != 0 ? distance_to_obj : distance_to_obj + 0.1;
    
    double f = 0.0;
    
    switch( params.force_law )
    {
        case NEWTONIAN:
            switch( obj_type )
            {
                case AGENT:
                    if ( distance_to_obj <= params.range_coefficient * params.R )
                    {
                        f = params.G_agent_agent * agent->mass * obj_mass / pow( distance_to_obj, params.p_agent_agent );

                        if ( distance_to_obj < params.R ) { f = -f; }
                        if ( f > params.max_f_agent_agent_n ) { f = params.max_f_agent_agent_n; }
                        if ( f < -params.max_f_agent_agent_n ) { f = -params.max_f_agent_agent_n; }
                    }
                    break;

                case GOAL:
                    f = params.G_agent_goal * agent->mass * obj_mass / pow( distance_to_obj, params.p_agent_goal );

                    if ( f > params.max_f_agent_goal_n ) { f = params.max_f_agent_goal_n; }
                    break;

                case OBSTACLE:
                    if ( distance_to_obj <= params.range_coefficient * params.R )
                    {
                        f = -( params.G_agent_obstacle * agent->mass * obj_mass / pow( distance_to_obj, params.p_agent_obstacle ) );

                        if ( f < -params.max_f_agent_obstacle_n ) { f = -params.max_f_agent_obstacle_n; }
                    }
                    break;
            }
            break;

        case LENNARD_JONES:
            switch( obj_type )
            {
                float epsilon, sigma;
                float c, d;
                double lhs, rhs;

                // agent-agent interactions, repulsive and attractive components
                case AGENT:
                    if ( distance_to_obj <= params.range_coefficient * params.R )
                    {
                        epsilon = params.epsilon_agent_agent;
                        c = params.c_agent_agent;
                        d = params.d_agent_agent;
                        sigma = params.R;

                        lhs = c * pow( sigma, 6.0 ) / pow( distance_to_obj, 7.0 );
                        rhs = 2.0 * d * pow( sigma, 12.0 ) / pow( distance_to_obj, 13.0 );

                        f = 24.0 * epsilon * ( lhs - rhs );

                        if ( isinf( f ) == 1 ) { f = DBL_MAX; }
                        else if ( isinf( f ) == -1 ) { f = DBL_MIN; }

                        if ( f > params.max_f_agent_agent_lj ) { f = params.max_f_agent_agent_lj; }
                        if ( f < -params.max_f_agent_agent_lj ) { f = -params.max_f_agent_agent_lj; }
                    }
                    break;

                // agent-obstacle interactions, repulsive component only
                case OBSTACLE:
                    if ( distance_to_obj <= params.range_coefficient * params.R )
                    {
                        epsilon = params.epsilon_agent_obstacle;
                        d = params.d_agent_obstacle;
                        sigma = ( ( Obstacle * ) object )->radius + 1.0f;

                        rhs = 2.0 * d * pow( sigma, 12.0 ) / pow( distance_to_obj, 13.0 );

                        f = -24.0 * epsilon * rhs;

                        if ( isinf( f ) == 1 ) { f = DBL_MAX; }
                        else if ( isinf( f ) == -1 ) { f = DBL_MIN; }

                        if ( f < -params.max_f_agent_obstacle_lj ) { f = -params.max_f_agent_obstacle_lj; }
                        if ( f > params.max_f_agent_obstacle_lj ) { f = params.max_f_agent_obstacle_lj; }
                    }
                    break;

                // agent-goal interactions, attractive component only
                case GOAL:
                    epsilon = params.epsilon_agent_goal;
                    c = params.c_agent_goal;
                    sigma = pow( params.R, 2.0f ) * 5.0f;

                    lhs = c * pow( sigma, 6.0 ) / pow( distance_to_obj, 7.0 );

                    f = 24.0 * epsilon * lhs;

                    if ( isinf( f ) == 1 ) { f = DBL_MAX; }
                    else if ( isinf( f ) == -1 ) { f = DBL_MIN; }

                    if ( f > params.max_f_agent_goal_lj ) { f = params.max_f_agent_goal_lj; }
                    break;
            }
            break;
    }
    
    return f;
}

void move_agents( void )
{
    int i, j;

    for ( i = 0; i < params.agent_number; ++i )
    {
        Agent *agent = agents[i];
        
        Vector2f agent_pos = agent->position;
        Vector2f goal_pos = goal->position;
        
        double force_x = 0.0f;
        double force_y = 0.0f;
        
        agent->velocity.x *= params.friction_coefficient;
        agent->velocity.y *= params.friction_coefficient;
        
        /************************** Calculate force between an obstacle and an agent ***********************/
        if ( params.enable_agent_obstacle_f )
        {
            for ( j = 0; j < params.obstacle_number; ++j )
            {
                Obstacle *obs = obstacles[j];
                Vector2f obs_pos = obs->position;
                
                float angle_to_obstacle = atan2( obs_pos.y - agent_pos.y, obs_pos.x - agent_pos.x );
                double net_force = calculate_force( agent, obs, OBSTACLE );
                
                force_x += net_force * cos( angle_to_obstacle );
                force_y += net_force * sin( angle_to_obstacle );
            }
        }
        /****************************************************************************************************/
        
        /************************** Calculate force between agents *************************************************/
        if ( params.enable_agent_agent_f )
        {
            for ( j = 0; j < params.agent_number; ++j )
            {
                Agent *agent2 = agents[j];
                Vector2f agent2_pos = agent2->position;
                
                float angle_to_agent2 = atan2( agent2_pos.y - agent_pos.y, agent2_pos.x - agent_pos.x );
                double net_force = calculate_force( agent, agent2, AGENT );
                
                force_x += net_force * cos( angle_to_agent2 );
                force_y += net_force * sin( angle_to_agent2 );
            }
        }
        /***********************************************************************************************************/
        
        /********************** Calculate force between the goal and an agent *************************/
        if ( params.enable_agent_goal_f )
        {
            float angle_to_goal = atan2( goal_pos.y - agent_pos.y, goal_pos.x - agent_pos.x );
            double net_force = calculate_force( agent, goal, GOAL );

            force_x += net_force * cos( angle_to_goal );
            force_y += net_force * sin( angle_to_goal );
        }
        /**********************************************************************************************/
        
        agent->n_velocity = agent->velocity;
        
        // update agent velocity vector
        agent->n_velocity.x += force_x / agent->mass;
        agent->n_velocity.y += force_y / agent->mass;
        
        float velocity_magnitude = hypotf( agent->n_velocity.x, agent->n_velocity.y );
        
        // check if new velocity exceeds the maximum
        if ( velocity_magnitude > params.max_V )
        {
            agent->n_velocity.x = ( agent->n_velocity.x * params.max_V ) / velocity_magnitude;
            agent->n_velocity.y = ( agent->n_velocity.y * params.max_V ) / velocity_magnitude;
        }
        
        agent->n_position = agent->position;
        
        // update agent position
        agent->n_position.x += agent->n_velocity.x;
        agent->n_position.y += agent->n_velocity.y;
        
        // calculate number of agent-obstacle collisions
        for ( j = 0; j < params.obstacle_number; ++j )
        {
            Obstacle *obs = obstacles[j];
            Vector2f obs_pos = obs->position;
            
            float distance_to_obs = hypotf( agent_pos.x - obs_pos.x, agent_pos.y - obs_pos.y );
            distance_to_obs -= obs->radius;
            
            if ( !agent->collided &&
                 distance_to_obs <= obs->radius &&
                 fabs( agent_pos.x - obs_pos.x ) <= obs->radius &&
                 fabs( agent_pos.y - obs_pos.y ) <= obs->radius )
            {
                agent->collided = true;
                memcpy( agent->color, agent_color_coll, 3 * sizeof( float ) );
                
                ++stats.collisions;
                stats.collision_ratio = ( float ) stats.collisions / ( float ) params.agent_number;
            }
        }
    }
    
    // move all agents in lock step
    for ( i = 0; i < params.agent_number; ++i )
    {
        agents[i]->velocity.x = agents[i]->n_velocity.x;
        agents[i]->velocity.y = agents[i]->n_velocity.y;
        
        agents[i]->position.x = agents[i]->n_position.x;
        agents[i]->position.y = agents[i]->n_position.y;
    }
    
    ++stats.time_step;
}

void update_reach( void )
{
    bool changed;
    int i;
    
    do
    {
        changed = false;
        
        for ( i = 0; i < params.agent_number; ++i )
        {
            Agent *agent1 = agents[i];
            
            if ( !agent1->goal_reached )
            {
                if ( agent_reached_goal( agent1 ) )
                {
                    agent1->goal_reached = true;
                    ++stats.reached_goal;
                    changed = true;
                }
            }
        }
    }
    while ( changed );

    stats.reach_ratio = ( float ) stats.reached_goal / ( float ) params.agent_number;
}
