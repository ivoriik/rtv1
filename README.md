# rtv1

UNIT Factory/42 School project.

## Description

RTv1 is a simple ray tracing program. The project was developed as a part of 42 school program. It parses a 3D scene from a file and applies ray tracing algorithm to render the given scene.
Project implemented in pure C with mlx library.

## Screenshots



## Features

- 4 simple geometric objects: plane, sphere, cylinder and cone
- multi light spots, color lights
- shine effect
- select objects within the scene
- translate and rotate the camera
- ranslate and rotate the selected object
- increase the radius/angle of the selected object

## Install & launch

```
Note: this project was made for MacOS.
```
```
https://github.com/vbespalk/rtv1.git ~/rtv1
cd ~/rtv1 && make
./RTv1 [filename]
```
`filename` must contain path to a valid scene.
If the scene is not valid, RTv1 will write corresponding error on standard output.
