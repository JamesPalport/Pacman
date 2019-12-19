#ifndef CONSTANTS_H
#define CONSTANTS_H

#define	TILE_SIZE	32
#define	FPS			60
#define	TIME		1000 / FPS
#define	SPEED		(TIME / 3  - 0.5)//500 / (FPS + FPS / 2)
#define GSPEED      ((SPEED > 1)? SPEED - 0.5: SPEED)
#define DTHETA		360 / FPS

#endif // CONSTANTS_H
