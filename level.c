///////////////////////////////
#include <acknex.h>
#include <default.c>
#include <mtlFX.c>
///////////////////////////////

STRING* command_one = "Harry Up !" ;
STRING* command_two = "We Don't have time ... " ;
STRING* command_three = "Zombies are behind me , they want to kill me ..." ;
STRING* command_fore = "Press enter to Enter" ;
STRING* command_five = "Loading . . ." ;

var game_time = 45 ;
var level_number = 1 ;

SOUND* door_wav = "001.wav";
SOUND* heart_wav = "002.wav";
SOUND* blood_wav = "003.wav";
SOUND* hoo_wav = "004.wav";
SOUND* harrid_wav = "005.wav";
SOUND* crow_wav = "006.wav";
SOUND* background_wav = "Music.ogg";

ENTITY* gun ;
ENTITY* enemy ;

PANEL* CommandOne =
{
	pos_x = 350 ;
	pos_y = 100 ;
	digits(0,0,0,"Arial#25",0,command_one);
}

PANEL* Commandtwo =
{
	pos_x = 310 ;
	pos_y = 100 ;
	digits(0,0,0,"Arial#25",0,command_two);
}

PANEL* Commandthree =
{
	pos_x = 200 ;
	pos_y = 100 ;
	digits(0,0,0,"Arial#25",0,command_three);
}

PANEL* Commandfore =
{
	pos_x = 300 ;
	pos_y = 430 ;
	digits(0,0,0,"Arial#25",0,command_fore);
}

PANEL* Game_Timer =
{
	pos_x = 400 ;
	pos_y = 10 ;
	digits(0,0,"%.f","Arial#24",1,game_time);
	flags = SHOW | TRANSLUCENT ;
}

PANEL* screen_color_pan =
{
	pos_x = 0 ;
	pos_y = 0 ;
	bmap = "black.png" ;
	scale_x = 200 ;
	scale_y = 200 ;
}

PANEL* loading_pan =
{
	pos_x = 400 ;
	pos_y = 200 ;
	digits(0,0,0,"Arial#25",0,command_five);
	scale_x = 200 ;
	scale_y = 150 ;
}


function gun_function ()
{
	my.z = camera.z;
	
	my.pan = camera.pan - 75 ;
	
	var gun_roll ;
	var gun_new_roll ;
	var gun_force = 8 ;
	
	while(1)
	{
		my.roll += mouse_force.y/4 ;
		my.pan -= mouse_force.x/4 ;
		
		my.y = camera.y - 20 ;
		my.x = camera.x - 50 ;
		my.z = camera.z - 10 ;

		
		wait(1);
	}
}

function warlockfun()
{
	
}

function panel_show ()
{
	var time_to_show = 0 ;
	
	while(level_number == 1 || level_number == 2)
	{
		time_to_show ++ ;
		
		if(time_to_show == 1)
			CommandOne.flags = SHOW | TRANSLUCENT ;
		
		if(time_to_show == 3)
		{
			CommandOne.flags = 0 ;
			Commandtwo.flags = SHOW | TRANSLUCENT ;
		}
		
		if(time_to_show == 5)
		{
			CommandOne.flags = 0 ;
			Commandtwo.flags = 0 ;
			Commandthree.flags = SHOW | TRANSLUCENT ;
		}
		
		if(time_to_show == 7)
		{
			CommandOne.flags = 0 ;
			Commandtwo.flags = 0 ;
			Commandthree.flags = 0 ;
		}
			
		if(time_to_show == 12)
			time_to_show = 1 ;
		
		wait(-1) ;
	}
}

function game_timer_fun ()
{
	while(game_time >= 0 && (level_number == 1 || level_number == 2))
	{
		game_time -- ;		
		if(game_time == 0)
			break ;
			
		wait(-1);
	}
}

function sound_player()
{
	var sound_time = 0 ;
	
	snd_play(background_wav,100,0);
	
	while(level_number == 1)
	{
		sound_time ++ ;
		
		if(sound_time == 2)
			snd_play(hoo_wav,60,0);
			
		if(sound_time == 5)
		{
			snd_play(hoo_wav,60,0);
			snd_play(harrid_wav,60,0);
		}
			
		if(sound_time == 10)
			snd_play(harrid_wav,60,0);
			
		if(sound_time == 14)
			sound_time = 0 ;
			
		snd_play(heart_wav,20,50);
		
		wait(-1);
	}
}

function main()
{
	level_load("Level.WMB");
	
	video_window(NULL,NULL,1,"Evil - LH");
	video_depth = 32 ;
	video_screen = 1 ;
	
	video_gamma = 50 ;
	sun_light = 0;
	
	d3d_fogcolor1.blue = 50;
	d3d_fogcolor1.red = 255 ;
	d3d_fogcolor1.green = 10 ;
	
	camera.fog_start = 10;
	camera.fog_end = 800;
	
	vec_set(screen_color,vector(0,0,128));
	
	fog_color = 3 ;
	
	var movement_case = 1 ;
	var camera_case = 0 ;
	var sinx = 5 ;
	
	panel_show () ;
	game_timer_fun () ;
	sound_player() ;
	
	while(game_time >= 0)
	{
		if(key_w == 0 && camera_case == 1)
		{
			camera.z += time_step/3 ;
			if(camera.z >= 51)
				camera_case ++ ;
		}
		
		if(key_w == 0 && camera_case == 2)
		{
			camera.z -= time_step/3;
			if(camera.z <= 46)
				camera_case -- ;
		}
		
		if(movement_case == 1 && key_w == 1)
		{
			camera_case = 0 ;
			camera.z += sin(90-sinx)*time_step;
			if(camera.z >=54)
				movement_case ++ ;
				
			if(camera.y >= -68)
				camera.x -= 0.1*time_step ;
				
			if(camera.y < -68)
				camera.x += 0.2*time_step ;
				
			camera.y -= sin(90-sinx)*time_step ;
				
		}
		
		if(movement_case == 2 && key_w == 1)
		{
			camera_case = 0 ;
			camera.z -= 3*time_step;
			if(camera.z <=40)
				movement_case -- ;
				
			if(camera.y >= -68)
				camera.x -= 0.1*time_step ;
			
			if(camera.y < -68)
				camera.x += 0.2*time_step ;
				
			camera.y -= sin(5)*time_step ;
		}
		
		if(key_w == 0 && camera_case == 0)
		{
			camera.z -= (camera.z - 48)*time_step;
			if(camera.z >= 47 && camera.z <= 49)
				camera_case = 1 ;
		}
		
		if(camera.pan >= 220 && camera.pan <= 320)
			camera.pan -= mouse_force.x/4 ;
		
		if(camera.pan >= 320)
			camera.pan = 319 ;
			
		if(camera.pan <= 220)
			camera.pan = 221 ;
			
		if(camera.tilt <= 1 && camera.tilt >= -20)
			camera.tilt += mouse_force.y/4 ;
			
		if(camera.tilt <= -20)
			camera.tilt = -19.9 ;
			
		if(camera.tilt > 1)
			camera.tilt = 1 ;
		
		if(camera.y <= -210)
		{
			movement_case = 0 ;
			break;
		}
			
		wait(1);
	}
	
	Commandfore.flags = SHOW | TRANSLUCENT ;
	camera.tilt = 0 ;
	camera.pan = 270 ;
	
	
	while(game_time > 0 )
	{
		if(key_enter == 1)
		{
			screen_color_pan.flags = SHOW | TRANSLUCENT ;
			level_number += 0.5 ;
			screen_color_pan.alpha = 0 ;
			
			while(1)
			{
				screen_color_pan.alpha += 5*time_step ;
				if(screen_color_pan.alpha >= 100)
				{
					level_load(NULL);
					loading_pan.flags = SHOW ;
					Commandfore.flags = 0 ;
					Game_Timer.flags = 0 ;
					CommandOne.flags = 0 ;
					Commandtwo.flags = 0 ;
					Commandthree.flags = 0 ;
					break ;
				}
				wait(1);
			}
			break ;
		}
		wait(1);
	}
	
	while(game_time == 0 && (level_number == 1 || level_number == 2))
	{
		if(movement_case == 0)
		{
			camera.z -= 2*time_step ;
			if(camera.z <= 20)
				movement_case ++ ;
		}
		
		if(movement_case == 1)
		{
			camera.z -= 0.2*time_step ;
			camera.x += 0.5*time_step ;
			camera.roll -= 2*time_step ;
			if(camera.roll <= -90)
				break ;
		}
		
		wait(1);
	}
	
}